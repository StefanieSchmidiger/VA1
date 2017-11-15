#include "SpiHandler.h" // pushToQueue and popFromQueue
#include "PackageHandler.h"
#include "NetworkHandler.h"
#include "Config.h"
#include "CRC1.h" // crc_8, crc_16
#include <stdio.h> // sprintf

#define TASKDELAY_QUEUE_FULL_MS 1


// global variables, only used in this file
static xQueueHandle ReceivedPackages[NUMBER_OF_UARTS]; /* Outgoing data to wireless side stored here */
static tWirelessPackage nextDataPacketToSend[NUMBER_OF_UARTS]; /* data buffer of outgoing wireless packages, stored in here once pulled from queue */
static LDD_TDeviceData* crcPH;

// prototypes
void initPackageHandlerQueues(void);
void packageHandler_TaskInit(void);
static void sendPackageToWirelessQueue(tUartNr uartNr, tWirelessPackage* pWirelessPackage);
static void sendNonPackStartCharacter(tUartNr uartNr, uint8_t* pCharToSend);
static void readAndExtractWirelessData(uint8_t wirelessConnNr);
static bool checkForPackStartReplacement(uint8_t* ptrToData, uint16_t* dataCntr, uint16_t* patternReplaced);
uint16_t numberOfPacksInReceivedPacksQueue(tUartNr uartNr);


/*! \struct sWiReceiveHandlerStates
*  \brief Possible states of the wireless receive handler.
*/
typedef enum eWiReceiveHandlerStates
{
	STATE_START,
	STATE_READ_HEADER,
	STATE_READ_PAYLOAD
} tWiReceiveHandlerStates;



void packageHandler_TaskEntry(void* p)
{
	static tWirelessPackage package;
	const TickType_t taskInterval = pdMS_TO_TICKS(config.PackageHandlerTaskInterval);
	TickType_t xLastWakeTime;

	packageHandler_TaskInit();

	for(;;)
	{
		xLastWakeTime = xTaskGetTickCount(); /* Initialize the lastWakeTime variable with the current time. */
		for(int uartNr = 0; uartNr < NUMBER_OF_UARTS; uartNr++)
		{
			/* send generated data packages out on wireless side */
			if(numberOfBytesInTxByteQueue(MAX_14830_WIRELESS_SIDE, uartNr) < QUEUE_NUM_OF_CHARS_WL_TX_QUEUE) /* there is space available in Queue */
			{
				if(popReadyToSendPackFromQueue(uartNr, &package) == pdTRUE) /* there is a package ready for sending */
				{
					sendPackageToWirelessQueue(uartNr, &package);
					FRTOS_vPortFree(package.payload);
				}
			}

			/* assemble received bytes to form a full data package */
			if(numberOfPacksInReceivedPacksQueue(uartNr) < QUEUE_NUM_OF_WL_PACK) /* there is space available in Queue */
			{
				if(numberOfBytesInRxByteQueue(MAX_14830_WIRELESS_SIDE, uartNr) > 0) /* there are characters waiting */
				{
					readAndExtractWirelessData(uartNr);
				}
			}
		}
		vTaskDelayUntil( &xLastWakeTime, taskInterval ); /* Wait for the next cycle */
	}
}

void packageHandler_TaskInit(void)
{
	initPackageHandlerQueues();
	crcPH = CRC1_Init(NULL);
}

/*!
* \fn void initPackageHandlerQueues(void)
* \brief This function initializes the array of queues
*/
void initPackageHandlerQueues(void)
{
	for(int uartNr = 0; uartNr<NUMBER_OF_UARTS; uartNr++)
	{
		ReceivedPackages[uartNr] = xQueueCreate( QUEUE_NUM_OF_WL_PACK, sizeof(tWirelessPackage));
	}
}



/*!
* \fn static void sendPackageToWirelessQueue(Queue* pToWirelessQueue, tWirelessPackage* pToWirelessPackage)
* \brief Function to send the desired package to the desired queue character for character.
* \param pToWirelessQueue: Queue that should be used to send the characters.
* \param tWirelessPackage: Pointer to wireless package that needs to be sent.
*/
static void sendPackageToWirelessQueue(tUartNr uartNr, tWirelessPackage* pWirelessPackage)
{
	if ((uartNr > NUMBER_OF_UARTS) || (pWirelessPackage == NULL) || (pWirelessPackage->payloadSize > PACKAGE_MAX_PAYLOAD_SIZE))
	{
		//showError(__FUNCTION__, "package won't be sent, error occurred");
		return;
	}
	static uint8_t startChar = PACK_START;
	while(pushToByteQueue(MAX_14830_WIRELESS_SIDE, uartNr, &startChar) == errQUEUE_FULL)
		FRTOS_vTaskDelay(pdMS_TO_TICKS(TASKDELAY_QUEUE_FULL_MS));
	sendNonPackStartCharacter(uartNr, &pWirelessPackage->packType);
	sendNonPackStartCharacter(uartNr, &pWirelessPackage->devNum);
	sendNonPackStartCharacter(uartNr, &pWirelessPackage->sessionNr);
	sendNonPackStartCharacter(uartNr, (uint8_t*)(&pWirelessPackage->sysTime) + 3);
	sendNonPackStartCharacter(uartNr, (uint8_t*)(&pWirelessPackage->sysTime) + 2);
	sendNonPackStartCharacter(uartNr, (uint8_t*)(&pWirelessPackage->sysTime) + 1);
	sendNonPackStartCharacter(uartNr, (uint8_t*)(&pWirelessPackage->sysTime) + 0);
	sendNonPackStartCharacter(uartNr, (uint8_t*)(&pWirelessPackage->payloadSize) + 1);
	sendNonPackStartCharacter(uartNr, (uint8_t*)(&pWirelessPackage->payloadSize) + 0);
	sendNonPackStartCharacter(uartNr, &pWirelessPackage->crc8Header);
	for (uint16_t cnt = 0; cnt < pWirelessPackage->payloadSize; cnt++)
	{
		sendNonPackStartCharacter(uartNr, &pWirelessPackage->payload[cnt]);
	}
	sendNonPackStartCharacter(uartNr, (uint8_t*)(&pWirelessPackage->crc16payload) + 1);
	sendNonPackStartCharacter(uartNr, (uint8_t*)(&pWirelessPackage->crc16payload) + 0);
	/* also send two fill bytes at the end - just that we're able to make sure on the receive side that we got all replacements */
	/* TODO this is "dirty" workaround that leads to more traffic, to be replaced with better solution (but in this case also the wireless package extractor needs to be adjusted) */
	static uint8_t repChar = PACK_FILL;
	sendNonPackStartCharacter(uartNr, &repChar);
	sendNonPackStartCharacter(uartNr, &repChar);
}



/*!
* \fn static inline void sendNonPackStartCharacter(tUartNr uartNr, uint8_t charToSend)
* \brief Replaces all outgoing PACK_START characters in the stream by "PACK_START" to be able to distinguish them at the receive side.
* \param uartNr: Wireless connection number, where package/char should be sent out.
* \param pCharToSend: Pointer to the char that needs to be sent.
*/
static void sendNonPackStartCharacter(tUartNr uartNr, uint8_t* pCharToSend)
{
	if ((*pCharToSend) == PACK_START)
	{
		static uint8_t repChar = PACK_REP;
		while(pushToByteQueue(MAX_14830_WIRELESS_SIDE, uartNr, &repChar) == errQUEUE_FULL)
			FRTOS_vTaskDelay(pdMS_TO_TICKS(TASKDELAY_QUEUE_FULL_MS));
		while(pushToByteQueue(MAX_14830_WIRELESS_SIDE, uartNr, pCharToSend) == errQUEUE_FULL)
			FRTOS_vTaskDelay(pdMS_TO_TICKS(TASKDELAY_QUEUE_FULL_MS));
		while(pushToByteQueue(MAX_14830_WIRELESS_SIDE, uartNr, &repChar) == errQUEUE_FULL)
			FRTOS_vTaskDelay(pdMS_TO_TICKS(TASKDELAY_QUEUE_FULL_MS));
	}
	else
	{
		while(pushToByteQueue(MAX_14830_WIRELESS_SIDE, uartNr, pCharToSend) == errQUEUE_FULL)
			FRTOS_vTaskDelay(pdMS_TO_TICKS(TASKDELAY_QUEUE_FULL_MS));
	}
}



/*!
* \fn static void readAndExtractWirelessData(uint8_t wirelessConnNr)
* \brief Function that reads the incoming data from the queue and generates receive acknowledges from it plus sends the valid data to the corresponding devices.
* \param wirelessConnNr: Serial connection of wireless interface. Needs to be between 0 and NUMBER_OF_UARTS.
*/
static void readAndExtractWirelessData(uint8_t wirelessConnNr)
{
	/* Some static variables in order to save status and data for every wireless connection */
	static uint8_t data[NUMBER_OF_UARTS][PACKAGE_MAX_PAYLOAD_SIZE + sizeof(uint16_t)]; /* space for payload plus crc16 */
	static uint16_t dataCntr[NUMBER_OF_UARTS];
	static tWirelessPackage currentWirelessPackage[NUMBER_OF_UARTS];
	static tWiReceiveHandlerStates currentRecHandlerState[NUMBER_OF_UARTS];
	static uint32_t timestampLastValidPackage[NUMBER_OF_UARTS];
	static uint8_t sessionNumberLastValidPackage[NUMBER_OF_UARTS];
	static uint16_t patternReplaced[NUMBER_OF_UARTS];
	static uint16_t dataCntToAddAfterReadPayload[NUMBER_OF_UARTS];
	uint8_t chr;

	/* check if parameters are valid */
	if (wirelessConnNr >= NUMBER_OF_UARTS)
	{
		//showError(__FUNCTION__, "invalid parameter");
	}
	/* read incoming character and react based on the state of the state machine */
	while (popFromByteQueue(MAX_14830_WIRELESS_SIDE, wirelessConnNr, &chr))
	{
		switch (currentRecHandlerState[wirelessConnNr])
		{
		case STATE_START:
			/* when the state before was the one to read a payload, there is still something in the buffer that needs to be checked */
			while (dataCntr[wirelessConnNr] > 0)
			{
				dataCntr[wirelessConnNr]--;
				if (data[wirelessConnNr][dataCntr[wirelessConnNr]] == PACK_START)
				{
					currentRecHandlerState[wirelessConnNr] = STATE_READ_HEADER;
					patternReplaced[wirelessConnNr] = 0;
					/* check if there is still something left in the buffer to use */
					if ((dataCntToAddAfterReadPayload[wirelessConnNr] >= 2) && (dataCntr[wirelessConnNr] == 0))
					{
						/* in this case, the first char is already in the buffer => put it to the first place */
						data[wirelessConnNr][0] = data[wirelessConnNr][1];
						dataCntr[wirelessConnNr] = 1;
						if (checkForPackStartReplacement(&data[wirelessConnNr][0], &dataCntr[wirelessConnNr], &patternReplaced[wirelessConnNr]))
						{
							dataCntr[wirelessConnNr] = 0;
#if GENERATE_DEBUG_OUTPUT > 0
							showInfo(__FUNCTION__, "restart state machine, start of package detected");
#endif /* GENERATE_DEBUG_OUTPUT */
						}
					}
					else
					{
						dataCntr[wirelessConnNr] = 0;
					}
					data[wirelessConnNr][dataCntr[wirelessConnNr]++] = chr;
					if (checkForPackStartReplacement(&data[wirelessConnNr][0], &dataCntr[wirelessConnNr], &patternReplaced[wirelessConnNr]))
					{
						dataCntr[wirelessConnNr] = 0;
#if GENERATE_DEBUG_OUTPUT > 0
						showInfo(__FUNCTION__, "restart state machine, start of package detected");
#endif /* GENERATE_DEBUG_OUTPUT */
					}
					break;
				}
			}
			if (chr == PACK_START)
			{
				currentRecHandlerState[wirelessConnNr] = STATE_READ_HEADER;
				dataCntr[wirelessConnNr] = 0;
				patternReplaced[wirelessConnNr] = 0;
				break;
			}
			break;
		case STATE_READ_HEADER:
			data[wirelessConnNr][dataCntr[wirelessConnNr]++] = chr;
			if (checkForPackStartReplacement(&data[wirelessConnNr][0], &dataCntr[wirelessConnNr], &patternReplaced[wirelessConnNr]))
			{
				/* found start of package, restart reading header */
				dataCntr[wirelessConnNr] = 0;
#if GENERATE_DEBUG_OUTPUT > 0
				showInfo(__FUNCTION__, "restart state machine, start of package detected");
#endif /* GENERATE_DEBUG_OUTPUT */
			}
			if (dataCntr[wirelessConnNr] >= (PACKAGE_HEADER_SIZE - 1 + 2)) /* -1: without PACK_START; +2 to read the first 2 bytes from the payload to check if the replacement pattern is there */
			{
				/* assign header structure. Due to alignement, it's hard to do this directly */
				currentWirelessPackage[wirelessConnNr].packType = data[wirelessConnNr][0];
				currentWirelessPackage[wirelessConnNr].devNum = data[wirelessConnNr][1];
				currentWirelessPackage[wirelessConnNr].sessionNr = data[wirelessConnNr][2];
				currentWirelessPackage[wirelessConnNr].sysTime = data[wirelessConnNr][6];
				currentWirelessPackage[wirelessConnNr].sysTime |= (data[wirelessConnNr][5] << 8);
				currentWirelessPackage[wirelessConnNr].sysTime |= (data[wirelessConnNr][4] << 16);
				currentWirelessPackage[wirelessConnNr].sysTime |= (data[wirelessConnNr][3] << 24);
				currentWirelessPackage[wirelessConnNr].payloadSize = data[wirelessConnNr][8];
				currentWirelessPackage[wirelessConnNr].payloadSize |= (data[wirelessConnNr][7] << 8);
				currentWirelessPackage[wirelessConnNr].crc8Header = data[wirelessConnNr][9];
				/* the first two bytes from the payload were already read, copy them to the beginning of the buffer */
				dataCntr[wirelessConnNr] = 2;
				data[wirelessConnNr][0] = data[wirelessConnNr][10];
				data[wirelessConnNr][1] = data[wirelessConnNr][11];
				patternReplaced[wirelessConnNr] = 0;
				if (checkForPackStartReplacement(&data[wirelessConnNr][0], &dataCntr[wirelessConnNr], &patternReplaced[wirelessConnNr]) == true)
				{
					/* start of package detected, restart reading header */
					dataCntr[wirelessConnNr] = 0;
					currentRecHandlerState[wirelessConnNr] = STATE_READ_HEADER;
#if GENERATE_DEBUG_OUTPUT > 0
					showInfo(__FUNCTION__, "restart state machine, start of package detected");
#endif /* GENERATE_DEBUG_OUTPUT */
					break;
				}
				/* finish reading header. Check if header is valid */
				CRC1_ResetCRC(crcPH);
				CRC1_GetCRC8(crcPH, PACK_START);
				CRC1_GetCRC8(crcPH, currentWirelessPackage[wirelessConnNr].packType);
				CRC1_GetCRC8(crcPH, currentWirelessPackage[wirelessConnNr].devNum);
				CRC1_GetCRC8(crcPH, currentWirelessPackage[wirelessConnNr].sessionNr);
				CRC1_GetCRC8(crcPH, *((uint8_t*)(&currentWirelessPackage[wirelessConnNr].sysTime) + 3));
				CRC1_GetCRC8(crcPH, *((uint8_t*)(&currentWirelessPackage[wirelessConnNr].sysTime) + 2));
				CRC1_GetCRC8(crcPH, *((uint8_t*)(&currentWirelessPackage[wirelessConnNr].sysTime) + 1));
				CRC1_GetCRC8(crcPH, *((uint8_t*)(&currentWirelessPackage[wirelessConnNr].sysTime) + 0));
				CRC1_GetCRC8(crcPH, *((uint8_t*)(&currentWirelessPackage[wirelessConnNr].payloadSize) + 1));
				uint8_t crc8 = CRC1_GetCRC8(crcPH, *((uint8_t*)(&currentWirelessPackage[wirelessConnNr].payloadSize) + 0));

				if (1)//ToDo: (currentWirelessPackage[wirelessConnNr].crc8Header == crc8)
				{
					/* CRC is valid - also check if the header parameters are within the valid range */
					if ((currentWirelessPackage[wirelessConnNr].packType > PACK_TYPE_REC_ACKNOWLEDGE) ||
						(currentWirelessPackage[wirelessConnNr].packType == 0) ||
						(currentWirelessPackage[wirelessConnNr].devNum >= NUMBER_OF_UARTS) ||
						(currentWirelessPackage[wirelessConnNr].payloadSize > PACKAGE_MAX_PAYLOAD_SIZE))
					{
						/* at least one of the parameters is out of range..reset state machine */
						//showWarning(__FUNCTION__, "invalid header, but CRC8 was right - implementation error?");
						currentRecHandlerState[wirelessConnNr] = STATE_START;
						dataCntr[wirelessConnNr] = 0;
					}
					else
					{
						/* valid header. Start reading payload */
						currentRecHandlerState[wirelessConnNr] = STATE_READ_PAYLOAD;
					}
				}
				else
				{
					/* invalid header, reset state machine */
					currentRecHandlerState[wirelessConnNr] = STATE_START;
					//numOfInvalidRecWirelessPack[wirelessConnNr]++;
					patternReplaced[wirelessConnNr] = 0;
					dataCntr[wirelessConnNr] = 0;
#if GENERATE_DEBUG_OUTPUT > 0
					showInfo(__FUNCTION__, "invalid header received, reset state machine");
#endif /* GENERATE_DEBUG_OUTPUT */
				}
			}
			break;
		case STATE_READ_PAYLOAD:
			data[wirelessConnNr][dataCntr[wirelessConnNr]++] = chr;
			if (checkForPackStartReplacement(&data[wirelessConnNr][0], &dataCntr[wirelessConnNr], &patternReplaced[wirelessConnNr]) == true)
			{
				/* start of package detected, restart reading header */
				dataCntr[wirelessConnNr] = 0;
				currentRecHandlerState[wirelessConnNr] = STATE_READ_HEADER;
#if GENERATE_DEBUG_OUTPUT > 0
				showInfo(__FUNCTION__, "restart state machine, start of package detected");
#endif /* GENERATE_DEBUG_OUTPUT */
				break;
			}
			/* read payload plus crc */
			if (dataCntr[wirelessConnNr] >= (currentWirelessPackage[wirelessConnNr].payloadSize + sizeof(currentWirelessPackage[wirelessConnNr].crc16payload + 2))) /* +2 because we don't want to miss a replacement pattern at the end */
			{
				/* to read the two additional chars after reading the payload */
				dataCntToAddAfterReadPayload[wirelessConnNr] = 2;
				dataCntr[wirelessConnNr] -= dataCntToAddAfterReadPayload[wirelessConnNr];
				/* finish reading payload, check CRC */
				currentWirelessPackage[wirelessConnNr].crc16payload = data[wirelessConnNr][dataCntr[wirelessConnNr] - 1];
				currentWirelessPackage[wirelessConnNr].crc16payload |= (data[wirelessConnNr][dataCntr[wirelessConnNr] - 2] << 8);
				CRC1_ResetCRC(crcPH);
				CRC1_SetCRCStandard(crcPH, LDD_CRC_MODBUS_16); // ToDo: use LDD_CRC_CCITT, MODBUS only for backwards compatibility to old SW
				uint32_t crc16;
				CRC1_GetBlockCRC(crcPH, data[wirelessConnNr], currentWirelessPackage[wirelessConnNr].payloadSize, &crc16);
				if (1)//ToDo: (currentWirelessPackage[wirelessConnNr].crc16payload == (uint16_t) crc16)
				{
					/* valid data - check packet type */
					if (currentWirelessPackage[wirelessConnNr].packType == PACK_TYPE_REC_ACKNOWLEDGE)
					{
						/* received acknowledge - send message to queueRecAck */
#if GENERATE_DEBUG_OUTPUT > 0
						char infoBuf[128];
						sprintf(infoBuf, "received ACK package, device %u; systemtime: %lu", currentWirelessPackage[wirelessConnNr].devNum, millis());
						showInfo(__FUNCTION__, infoBuf);
#endif /* GENERATE_DEBUG_OUTPUT */
						currentWirelessPackage[wirelessConnNr].sysTime = *((uint32_t*)&data[wirelessConnNr][dataCntr[wirelessConnNr] - 6]);
						while(xQueueSendToBack(ReceivedPackages[wirelessConnNr], &currentWirelessPackage[wirelessConnNr], ( TickType_t ) 0) != pdTRUE)
						{
							vTaskDelay(pdMS_TO_TICKS(10)); /* queue full */
							/* queue is full */
							//showWarning(__FUNCTION__, "received acknowledge but unable to push this messaege to the send handler");
						}
					}
					else if (currentWirelessPackage[wirelessConnNr].packType == PACK_TYPE_DATA_PACKAGE)
					{
						currentWirelessPackage[wirelessConnNr].payload = (uint8_t*) FRTOS_pvPortMalloc(currentWirelessPackage[wirelessConnNr].payloadSize*sizeof(int8_t));
						for(int cnt=0; cnt < currentWirelessPackage[wirelessConnNr].payloadSize; cnt++)
						{
							currentWirelessPackage[wirelessConnNr].payload[cnt] = data[wirelessConnNr][cnt];
						}
						/* received data package - send data to corresponding devices plus inform package generator to prepare a receive acknowledge */
						while(xQueueSendToBack(ReceivedPackages[wirelessConnNr], &currentWirelessPackage[wirelessConnNr], ( TickType_t ) 0) != pdTRUE)
						{
							vTaskDelay(pdMS_TO_TICKS(10)); /* queue full */
							/* queue is full */
							//showWarning(__FUNCTION__, "received acknowledge but unable to push this messaege to the send handler");
						}
#if GENERATE_DEBUG_OUTPUT > 0
						char infoBuf[128];
						sprintf(infoBuf, "received data package, device %u; timestamp package: %lu; systemtime: %lu",
							currentWirelessPackage[wirelessConnNr].devNum, currentWirelessPackage[wirelessConnNr].sysTime, millis());
						showInfo(__FUNCTION__, infoBuf);
#endif /* GENERATE_DEBUG_OUTPUT */
						/* update average size of received payload packages */
						//updateAvPayloadSizeRecDataPack(wirelessConnNr, currentWirelessPackage[wirelessConnNr].payloadSize);
						/* check if it's the same session number as before */
						if (sessionNumberLastValidPackage[currentWirelessPackage[wirelessConnNr].devNum] != currentWirelessPackage[wirelessConnNr].sessionNr)
						{
							/* session number changed. Reset timestamp and assign new session number. */
							sessionNumberLastValidPackage[currentWirelessPackage[wirelessConnNr].devNum] = currentWirelessPackage[wirelessConnNr].sessionNr;
							timestampLastValidPackage[currentWirelessPackage[wirelessConnNr].devNum] = 0;
						}
					}
					else
					{
						/* something went wrong - invalid package type. Reset state machine and send out error. */
						//showWarning(__FUNCTION__, "invalid package type. Mustn't happen at this stage, there is probably an error in the implementation");
					}
				}
				else
				{
					/* received invalid payload */
					//numOfInvalidRecWirelessPack[wirelessConnNr]++;
#if GENERATE_DEBUG_OUTPUT > 0
					showInfo(__FUNCTION__, "received invalid payload, reset state machine");
#endif /* GENERATE_DEBUG_OUTPUT */
				}
				/* reset state machine */
				currentRecHandlerState[wirelessConnNr] = STATE_START;
				/* copy the two already replaced bytes to the beginning if there was read more data due to check for replacement pattern */
				if (dataCntToAddAfterReadPayload[wirelessConnNr] >= 2)
				{
					data[wirelessConnNr][0] = data[wirelessConnNr][dataCntr[wirelessConnNr] - 2 + dataCntToAddAfterReadPayload[wirelessConnNr]];
					data[wirelessConnNr][1] = data[wirelessConnNr][dataCntr[wirelessConnNr] - 1 + dataCntToAddAfterReadPayload[wirelessConnNr]];
				}
				else if (dataCntToAddAfterReadPayload[wirelessConnNr] >= 1)
				{
					data[wirelessConnNr][0] = data[wirelessConnNr][dataCntr[wirelessConnNr] - 1 + dataCntToAddAfterReadPayload[wirelessConnNr]];
				}
				dataCntr[wirelessConnNr] = dataCntToAddAfterReadPayload[wirelessConnNr];
				patternReplaced[wirelessConnNr] = 0;
			}
			break;
		default:
			//showError(__FUNCTION__, "invalid state in state machine");
			break;
		}
	}
}


/*!
* \fn static bool checkForPackStartReplacement(uint8_t* ptrToData, uint16_t* dataCntr, uint16_t* patternReplaced)
* \brief Checks for the PACK_START replacement in the data stream plus the start of a package itself.
*		(PACK_START is replaced by PACK_REP PACK_START PACK_REP in the header plus the data in order to be able to distinguish between the data and the start of a package.)
* \param[in,out] ptrToData: Pointer to the data buffer.
* \param[in,out] dataCntr: Pointer to the data counter.
* \param[in,out] patternReplaced: Pointer to number where the pattern was already replaced - to make sure we don't do it more than once at the same position.
* \return If true is returned, a start of a package has been detected and the state machine should restart to read the header.
*/
static bool checkForPackStartReplacement(uint8_t* ptrToData, uint16_t* dataCntr, uint16_t* patternReplaced)
{
	if ((*dataCntr) >= 3)
	{
		if ((ptrToData[(*dataCntr) - 3] == PACK_REP) && (ptrToData[(*dataCntr) - 2] == PACK_START) && (ptrToData[(*dataCntr) - 1] == PACK_REP))
		{
			/* found pattern, replace it if it wasn't already replaced */
			if (((*dataCntr) - 2) != *patternReplaced)
			{
				ptrToData[(*dataCntr) - 3] = PACK_START;
				*patternReplaced = (*dataCntr) - 3;
				(*dataCntr) -= 2;
			}
		}
		else if((ptrToData[(*dataCntr) - 2] != PACK_REP) && (ptrToData[(*dataCntr) - 1] == PACK_START))
		{
			/* found start of package */
			return true;
		}
	}
	else if ((*dataCntr) >= 2)
	{
		if ((ptrToData[(*dataCntr) - 2] != PACK_REP) && (ptrToData[(*dataCntr) - 1] == PACK_START))
		{
			/* found start of package */
			return true;
		}
	}
	else if ((*dataCntr) >= 1)
	{
		/* only one character in the buffer - if it's already the PACK_START symbol, start again */
		if (ptrToData[(*dataCntr) - 1] == PACK_START)
		{
			/* found start of package */
			return true;
		}
	}
	return false;
}


/*!
* \fn ByseType_t popReadyToSendPackFromQueue(tUartNr uartNr, tWirelessPackage *pPackage)
* \brief Stores a single byte from the selected queue in pData.
* \param uartNr: UART number the package should be transmitted to.
* \param pPackage: The location where the package should be stored
* \return Status if xQueueReceive has been successful, pdFAIL if uartNr was invalid or pop unsuccessful
*/
BaseType_t popReceivedPackFromQueue(tUartNr uartNr, tWirelessPackage *pPackage)
{
	if(uartNr < NUMBER_OF_UARTS)
	{
		return xQueueReceive(ReceivedPackages[uartNr], pPackage, ( TickType_t ) 0 );
	}
	return pdFAIL; /* if uartNr was not in range */
}


/*!
* \fn uint16_t numberOfPacksInReceivedPacksQueue(tUartNr uartNr)
* \brief Returns the number of packages stored in the queue that are ready to be received/processed by this program
* \param uartNr: UART number the packages should be read from.
* \return Number of packages waiting to be processed/received
*/
uint16_t numberOfPacksInReceivedPacksQueue(tUartNr uartNr)
{
	if(uartNr < NUMBER_OF_UARTS)
		return  (uint16_t) uxQueueMessagesWaiting(ReceivedPackages[uartNr]);
	return 0; /* if uartNr was not in range */
}


