// 
// 
// 

#include "wirelessPackageExtractor.h"
#include "errorAndWarningOutput.h"
#include "serialSwitch_General.h"
#include "serialSwitch_Config.h"
#include "hwBufferInterface.h"
#include "wirelessSendHandler.h"
#include "packageGenerator.h"
#include "throughputPrintout.h"
#include <Queue.h>
#include "FastCRC.h"	/* examples: https://github.com/FrankBoesing/FastCRC */




/*! \struct sWiReceiveHandlerStates
*  \brief Possible states of the wireless receive handler.
*/
typedef enum eWiReceiveHandlerStates
{
	STATE_START,
	STATE_READ_HEADER,
	STATE_READ_PAYLOAD
} tWiReceiveHandlerStates;




/*!
* \fn static inline void checkForPackStartReplacement(uint8_t* ptrToData, uint16_t dataCntr)
* \brief Checks for the PACK_START replacement in the data stream plus the start of a package itself.
*		(PACK_START is replaced by PACK_REP PACK_START PACK_REP in the header plus the data in order to be able to distinguish between the data and the start of a package.)
* \param[in,out] ptrToData: Pointer to the data buffer.
* \param[in,out] dataCntr: Pointer to the data counter.
* \param[in,out] patternReplaced: Pointer to number where the pattern was already replaced - to make sure we don't do it more than once at the same position.
* \return If true is returned, a start of a package has been detected and the state machine should restart to read the header.
*/
static inline bool checkForPackStartReplacement(uint8_t* ptrToData, uint16_t* dataCntr, uint16_t* patternReplaced)
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
* \fn static void readAndExtractWirelessData(Queue* pToQueueToReadFrom)
* \brief Function that reads the incoming data from the queue and generates receive acknowledges from it plus sends the valid data to the corresponding devices.
* \param pToQueueToReadFrom: Pointer to queue where the data can be read from.
* \param wirelessConnNr: Serial connection of wireless interface. Needs to be between 0 and 3.
*/
static void readAndExtractWirelessData(Queue* pToQueueToReadFrom, uint8_t wirelessConnNr)
{
	/* Some static variables in order to save status and data for every wireless connection */
	static uint8_t data[NUM_OF_WIRELESS_CONNECTIONS][PACKAGE_MAX_PAYLOAD_SIZE + sizeof(uint16_t)]; /* space for payload plus crc16 */
	static uint16_t dataCntr[NUM_OF_WIRELESS_CONNECTIONS];
	static tWirelessPackage currentWirelessPackage[NUM_OF_WIRELESS_CONNECTIONS];
	static tWiReceiveHandlerStates currentRecHandlerState[NUM_OF_WIRELESS_CONNECTIONS];
	static uint32_t timestampLastValidPackage[NUM_OF_DEVICE_CONNECTIONS];
	static uint8_t sessionNumberLastValidPackage[NUM_OF_DEVICE_CONNECTIONS];
	static uint16_t patternReplaced[NUM_OF_WIRELESS_CONNECTIONS];
	static uint16_t dataCntToAddAfterReadPayload[NUM_OF_WIRELESS_CONNECTIONS];
	uint8_t chr;
	static sWiReceiveAck recAck;
	/* check if parameters are valid */
	if ((wirelessConnNr >= NUM_OF_WIRELESS_CONNECTIONS) || (pToQueueToReadFrom == NULL))
	{
		showError(__FUNCTION__, "invalid parameter");
	}
	/* read incoming character and react based on the state of the state machine */
	while (pToQueueToReadFrom->pull(&chr))
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
				/* finish reading header. Check if he's valid */
				/* IMPROVE: Copy stuff around that much isn't very performant */
				static uint8_t packHeaderBuf[PACKAGE_HEADER_SIZE - 1] = { PACK_START, 0, 0, 0, 0, 0, 0, 0, 0 };
				packHeaderBuf[1] = currentWirelessPackage[wirelessConnNr].packType;
				packHeaderBuf[2] = currentWirelessPackage[wirelessConnNr].devNum;
				packHeaderBuf[3] = currentWirelessPackage[wirelessConnNr].sessionNr;
				packHeaderBuf[4] = *((uint8_t*)(&currentWirelessPackage[wirelessConnNr].sysTime) + 3);
				packHeaderBuf[5] = *((uint8_t*)(&currentWirelessPackage[wirelessConnNr].sysTime) + 2);
				packHeaderBuf[6] = *((uint8_t*)(&currentWirelessPackage[wirelessConnNr].sysTime) + 1);
				packHeaderBuf[7] = *((uint8_t*)(&currentWirelessPackage[wirelessConnNr].sysTime) + 0);
				packHeaderBuf[8] = *((uint8_t*)(&currentWirelessPackage[wirelessConnNr].payloadSize) + 1);
				packHeaderBuf[9] = *((uint8_t*)(&currentWirelessPackage[wirelessConnNr].payloadSize) + 0);
				FastCRC8 crc8;
				if (true) /*(currentWirelessPackage[wirelessConnNr].crc8Header == crc8.smbus(packHeaderBuf, PACKAGE_HEADER_SIZE - 1))*/
				{
					/* CRC is valid - also check if the header parameters are within the valid range */
					if ((currentWirelessPackage[wirelessConnNr].packType > PACK_TYPE_REC_ACKNOWLEDGE) ||
						(currentWirelessPackage[wirelessConnNr].packType == 0) ||
						(currentWirelessPackage[wirelessConnNr].devNum >= NUM_OF_DEVICE_CONNECTIONS) ||
						(currentWirelessPackage[wirelessConnNr].payloadSize > PACKAGE_MAX_PAYLOAD_SIZE))
					{
						/* at least one of the parameters is out of range..reset state machine */
						showWarning(__FUNCTION__, "invalid header, but CRC8 was right - implementation error?");
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
          Serial.println("Invalid Header -> Reset state machine");
					currentRecHandlerState[wirelessConnNr] = STATE_START;
					numOfInvalidRecWirelessPack[wirelessConnNr]++;
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
				FastCRC16 crc16;
				currentWirelessPackage[wirelessConnNr].crc16payload = data[wirelessConnNr][dataCntr[wirelessConnNr] - 1];
				currentWirelessPackage[wirelessConnNr].crc16payload |= (data[wirelessConnNr][dataCntr[wirelessConnNr] - 2] << 8);
				if (true) /*(currentWirelessPackage[wirelessConnNr].crc16payload == crc16.ccitt(&data[wirelessConnNr][0], currentWirelessPackage[wirelessConnNr].payloadSize))*/
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
						recAck.devNum = currentWirelessPackage[wirelessConnNr].devNum;
						recAck.sysTime = *((uint32_t*)&data[wirelessConnNr][dataCntr[wirelessConnNr] - 6]);
						if (queueRecAck.push(&recAck) == false)
						{
							/* queue is full */
							showWarning(__FUNCTION__, "received acknowledge but unable to push this messaege to the send handler");
						}
						numOfValidRecWirelessAckPack[wirelessConnNr]++;
					}
					else if (currentWirelessPackage[wirelessConnNr].packType == PACK_TYPE_DATA_PACKAGE)
					{
						/* received data package - send data to corresponding devices plus inform package generator to prepare a receive acknowledge */
#if GENERATE_DEBUG_OUTPUT > 0
						char infoBuf[128];
						sprintf(infoBuf, "received data package, device %u; timestamp package: %lu; systemtime: %lu", 
							currentWirelessPackage[wirelessConnNr].devNum, currentWirelessPackage[wirelessConnNr].sysTime, millis());
						showInfo(__FUNCTION__, infoBuf);
#endif /* GENERATE_DEBUG_OUTPUT */
						/* check if acknowledge needs to be created */
						static const uint8_t sendAckWirelessConn[] = SEND_ACK_PER_WIRELESS_CONN;
						if (sendAckWirelessConn[wirelessConnNr] > 0)
						{
							/* yes, send acknowledge */
							recAck.devNum = currentWirelessPackage[wirelessConnNr].devNum;
							recAck.sysTime = currentWirelessPackage[wirelessConnNr].sysTime;
							recAck.wirNum = wirelessConnNr;
							if (queueSendAck.push(&recAck) == false)
							{
								/* queue is full */
								showWarning(__FUNCTION__, "received data package but unable to generate acknowledge message");
							}
						}
						numOfValidRecWirelessDataPack[wirelessConnNr]++;
						/* update average size of received payload packages */
						updateAvPayloadSizeRecDataPack(wirelessConnNr, currentWirelessPackage[wirelessConnNr].payloadSize);
						/* check if it's the same session number as before */
						if (sessionNumberLastValidPackage[currentWirelessPackage[wirelessConnNr].devNum] != currentWirelessPackage[wirelessConnNr].sessionNr)
						{
							/* session number changed. Reset timestamp and assign new session number. */
							sessionNumberLastValidPackage[currentWirelessPackage[wirelessConnNr].devNum] = currentWirelessPackage[wirelessConnNr].sessionNr;
							timestampLastValidPackage[currentWirelessPackage[wirelessConnNr].devNum] = 0;
						}
						/* make sure to not send old data to the device - but also make sure overflow is handled */
						if ((currentWirelessPackage[wirelessConnNr].sysTime > timestampLastValidPackage[currentWirelessPackage[wirelessConnNr].devNum]) ||
							((timestampLastValidPackage[currentWirelessPackage[wirelessConnNr].devNum] - currentWirelessPackage[wirelessConnNr].sysTime) > (UINT32_MAX / 2)))
						{
							/* package OK, send it to device */
							timestampLastValidPackage[currentWirelessPackage[wirelessConnNr].devNum] = currentWirelessPackage[wirelessConnNr].sysTime;
							Queue* sendQueue;
							sendQueue = &queueDeviceTransmitUart[currentWirelessPackage[wirelessConnNr].devNum];
							for (uint16_t cnt = 0; cnt < currentWirelessPackage[wirelessConnNr].payloadSize; cnt++)
							{
								if (sendQueue->push(&data[wirelessConnNr][cnt]) == false)
								{
									char warnBuf[128];
									sprintf(warnBuf, "Unable to send data to device number %u, queue is full", currentWirelessPackage[wirelessConnNr].devNum);
									showWarning(__FUNCTION__, warnBuf);
									break;
								}
							}
						}
						else
						{
							/* received old package */
							/* also can happen when we have two redundant streams.. */
							/*static char infoBuf[128];
							sprintf(infoBuf, 
								"received old package, device %u - check configuration if this message occurres often",
								currentWirelessPackage[wirelessConnNr].devNum);
							showInfo(__FUNCTION__, infoBuf);*/
						}
					}
					else
					{
						/* something went wrong - invalid package type. Reset state machine and send out error. */
						showWarning(__FUNCTION__, "invalid package type. Mustn't happen at this stage, there is probably an error in the implementation");
					}
				}
				else
				{
          Serial.println("Invalid crc16 in payload");
					/* received invalid payload */
					numOfInvalidRecWirelessPack[wirelessConnNr]++;
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
			showError(__FUNCTION__, "invalid state in state machine");
			break;
		}
	}
}



/*!
* \fn void wirelessPackageExtractor_TaskEntry(void)
* \brief Task that reads the incoming data from the wireless connections and generates receive acknowledges from it plus sends the valid data to the corresponding devices.
*/
void wirelessPackageExtractor_TaskEntry(void)
{
	/* call function that handles this stuff for every wireless connection */
	for (uint8_t cnt = 0; cnt < NUM_OF_WIRELESS_CONNECTIONS; cnt++)
	{
		readAndExtractWirelessData(&queueWirelessReceiveUart[cnt], cnt);
	}
}


