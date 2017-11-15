#include "NetworkHandler.h"
#include "PackageHandler.h"
#include "SpiHandler.h" // pushToQueue and popFromQueue, numberOfUarts
#include "Config.h"
#include "CRC1.h"
#include "FRTOS.h" // malloc/free


// global variables, only used in this file
static uint8_t sessionNr;
static xQueueHandle queuePackagesToSend[NUMBER_OF_UARTS]; /* Incoming data from wireless side stored here */
static LDD_TDeviceData* crcNH;

// prototypes
static bool generateDataPackage(tUartNr deviceNumber, tWirelessPackage* wPackage, uint8_t sessionNr);
void initNetworkHandlerQueues(void);
void networkHandler_TaskInit(void);



void networkHandler_TaskEntry(void* p)
{
	TickType_t xLastWakeTime;
	const TickType_t taskInterval = pdMS_TO_TICKS(config.NetworkHandlerTaskInterval);
	sessionNr = 1; // ToDo: generate random number!
	tWirelessPackage package;

	networkHandler_TaskInit();

	for(;;)
	{
		xLastWakeTime = xTaskGetTickCount(); /* Initialize the lastWakeTime variable with the current time. */
		/* generate data packages and put those into the package queue */
		for(int deviceNr = 0; deviceNr<NUMBER_OF_UARTS; deviceNr++)
		{
			/* generate packages from raw data bytes */
			if(generateDataPackage(deviceNr, &package, sessionNr)) /* put package in queue if it was generated */
			{
				while(xQueueSendToBack(queuePackagesToSend[deviceNr], &package, ( TickType_t ) 0) != pdTRUE)
					vTaskDelay(pdMS_TO_TICKS(10)); /* queue full */
			// ToDo: handle acknowledges and resend per connection
			}
			/* extract data from received packages and send it to corresponding UART interface */
			if(numberOfPacksInReceivedPacksQueue(deviceNr) > 0)
			{
				tWirelessPackage package;
				package.payload = (uint8_t*) FRTOS_pvPortMalloc(512*sizeof(int8_t));
				popReceivedPackFromQueue(deviceNr, &package);
				for(uint16_t cnt=0; cnt<package.payloadSize; cnt++)
				{
					pushToByteQueue(MAX_14830_DEVICE_SIDE, deviceNr, &package.payload[cnt]);
				}
				FRTOS_vPortFree(package.payload);
			}
		}
		vTaskDelayUntil( &xLastWakeTime, taskInterval ); /* Wait for the next cycle */
	}
}

void networkHandler_TaskInit(void)
{
	initNetworkHandlerQueues();
	crcNH = CRC1_Init(NULL);
}

/*!
* \fn void initNetworkHandlerQueues(void)
* \brief This function initializes the array of queues
*/
void initNetworkHandlerQueues(void)
{
	for(int uartNr=0; uartNr<NUMBER_OF_UARTS; uartNr++)
	{
		queuePackagesToSend[uartNr] = xQueueCreate( QUEUE_NUM_OF_WL_PACK, sizeof(tWirelessPackage) );
	}
}



/*!
* \fn static void generateDataPackage(uint8_t deviceNumber, Queue* dataSource)
* \brief Function to generate a data package, reading data from the data source.
* \param deviceNumber: Number of device.
* \param dataSource: Pointer to the queue where the data where the data is read.
* \param wPackage: Pointer to package structure.
* \return true if a package was generated and saved in wPackage, false otherwise.
*/
static bool generateDataPackage(tUartNr deviceNumber, tWirelessPackage* wPackage, uint8_t sessionNr)
{
	static uint32_t lastTimestampDataAv[NUMBER_OF_UARTS]; /* static variables are initialized as 0 by default */
	static bool updatedTimestamp[NUMBER_OF_UARTS];
	static uint8_t packHeaderBuf[PACKAGE_HEADER_SIZE - 1] = { PACK_START, PACK_TYPE_DATA_PACKAGE, 0, 0, 0, 0, 0, 0, 0, 0 };
	uint16_t numberOfBytesInRxQueue = (uint16_t) numberOfBytesInRxByteQueue(MAX_14830_DEVICE_SIDE, deviceNumber);

	uint32_t dtToLastPackage = xTaskGetTickCount()-lastTimestampDataAv[deviceNumber];

	/* check if enough data to fill package or maximum wait time for full package done */
	if ((numberOfBytesInRxQueue >= config.UsualPacketSizeDeviceConn[deviceNumber]) ||
		(numberOfBytesInRxQueue >= PACKAGE_MAX_PAYLOAD_SIZE) ||
		((updatedTimestamp[deviceNumber] == true) && (dtToLastPackage >= pdMS_TO_TICKS(config.PackageGenMaxTimeout[deviceNumber]))))
	{
		/* reached usual packet size or timeout, generate package */
		/* Put together package */
		/* put together payload by allocating memory and copy data */
		wPackage->payloadSize = numberOfBytesInRxQueue;
		wPackage->payload = (uint8_t*) FRTOS_pvPortMalloc(numberOfBytesInRxQueue*sizeof(int8_t));
		if(wPackage->payload == NULL) /* malloc failed */
			return false;
		/* get data from queue */
		for (uint16_t cnt = 0; cnt < wPackage->payloadSize; cnt++)
		{
			popFromByteQueue(MAX_14830_DEVICE_SIDE, deviceNumber, &wPackage->payload[cnt]);
		}
		/* calculate CRC */
		uint32_t crc16;
		CRC1_ResetCRC(crcNH);
		CRC1_SetCRCStandard(crcNH, LDD_CRC_MODBUS_16); // ToDo: use LDD_CRC_MODBUS_16 afterwards, MODBUS only for backwards compatibility with old SW
		CRC1_GetBlockCRC(crcNH, wPackage->payload, wPackage->payloadSize, &crc16);
		wPackage->crc16payload = (uint16_t) crc16;
		/* put together the rest of the header */
		wPackage->packType = PACK_TYPE_DATA_PACKAGE;
		wPackage->devNum = deviceNumber;
		wPackage->sessionNr = sessionNr;
		wPackage->sysTime = xTaskGetTickCount();
		/* calculate crc */
		CRC1_ResetCRC(crcNH);
		CRC1_GetCRC8(crcNH, PACK_START);
		CRC1_GetCRC8(crcNH, PACK_TYPE_DATA_PACKAGE);
		CRC1_GetCRC8(crcNH, wPackage->devNum);
		CRC1_GetCRC8(crcNH, wPackage->sessionNr);
		CRC1_GetCRC8(crcNH, *((uint8_t*)(&wPackage->sysTime) + 3));
		CRC1_GetCRC8(crcNH, *((uint8_t*)(&wPackage->sysTime) + 2));
		CRC1_GetCRC8(crcNH, *((uint8_t*)(&wPackage->sysTime) + 1));
		CRC1_GetCRC8(crcNH, *((uint8_t*)(&wPackage->sysTime) + 0));
		CRC1_GetCRC8(crcNH, *((uint8_t*)(&wPackage->payloadSize) + 1));
		wPackage->crc8Header = CRC1_GetCRC8(crcNH, *((uint8_t*)(&wPackage->payloadSize) + 0));
		/* reset last timestamp */
		lastTimestampDataAv[deviceNumber] = 0;
		/* reset flag that timestamp was updated */
		updatedTimestamp[deviceNumber] = false;
		return true;
	}
	else if(numberOfBytesInRxQueue > 0)
	{
		/* there is data available, update timestamp that data is available (but only if the timestamp wasn't already updated) */
		if (updatedTimestamp[deviceNumber] == false)
		{
			lastTimestampDataAv[deviceNumber] = xTaskGetTickCount();
			updatedTimestamp[deviceNumber] = true;
		}
		return false;
	}
	else
	{
		/* package was not generated */
		return false;
	}
}

/*!
* \fn ByseType_t popReadyToSendPackFromQueue(tUartNr uartNr, tWirelessPackage *pPackage)
* \brief Stores a single byte from the selected queue in pData.
* \param uartNr: UART number the package should be transmitted to.
* \param pPackage: The location where the package should be stored
* \return Status if xQueueReceive has been successful, pdFAIL if uartNr was invalid or pop unsuccessful
*/
BaseType_t popReadyToSendPackFromQueue(tUartNr uartNr, tWirelessPackage *pPackage)
{
	if(uartNr < NUMBER_OF_UARTS)
	{
		return xQueueReceive(queuePackagesToSend[uartNr], pPackage, ( TickType_t ) 0 );
	}
	return pdFAIL; /* if uartNr was not in range */
}


/*!
* \fn uint16_t numberOfPackagesReadyToSend(tUartNr uartNr)
* \brief Returns the number of packages stored in the queue that are ready to be sent via Wireless
* \param uartNr: UART number the package should be transmitted to.
* \return Number of packages waiting to be sent out
*/
uint16_t numberOfPackagesReadyToSend(tUartNr uartNr)
{
	if(uartNr < NUMBER_OF_UARTS)
	{
		return uxQueueMessagesWaiting(queuePackagesToSend[uartNr]);
	}
	return 0; /* if uartNr was not in range */
}
