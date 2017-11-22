#include "NetworkHandler.h"
#include "PackageHandler.h"
#include "SpiHandler.h" // pushToQueue and popFromQueue, numberOfUarts
#include "Config.h"
#include "CRC1.h"
#include "FRTOS.h" // malloc/free
#include "RNG.h" // for random sessionNr


// global variables, only used in this file
static uint8_t sessionNr;
static xQueueHandle queuePackagesToSend[NUMBER_OF_UARTS]; /* Incoming data from wireless side stored here */
static LDD_TDeviceData* crcNH;
static tWirelessPackage unacknowledgedPackages[MAX_NUMBER_OF_UNACK_PACKS_STORED];
static bool unacknowledgedPackagesOccupiedAtIndex[MAX_NUMBER_OF_UNACK_PACKS_STORED];

// prototypes
static bool generateDataPackage(tUartNr deviceNr, tWirelessPackage* pPackage, uint8_t sessionNr);
void initNetworkHandlerQueues(void);
void networkHandler_TaskInit(void);
bool processReceivedPackage(tUartNr wirelessConnNr);
bool sendAndStoreGeneratedWlPackage(tWirelessPackage* pPackage, tUartNr rawDataUartNr);
static bool storeNewPackageInUnacknowledgedPackagesArray(tWirelessPackage* pPackage);
static char* queueName[] = {"queuePackagesToSend0", "queuePackagesToSend1", "queuePackagesToSend2", "queuePackagesToSend3"};
uint8_t getWlConnectionToUse(tUartNr uartNr, uint8_t desiredPrio);
static bool generateAckPackage(tWirelessPackage* pReceivedDataPack, tWirelessPackage* pAckPack);

/*!
* \fn void networkHandler_TaskEntry(void)
* \brief Task generates packages from received bytes (received on device side) and sends those down to
* the packageHandler for transmission.
* When acknowledges are configured, resending is handled here.
*/
void networkHandler_TaskEntry(void* p)
{
	TickType_t xLastWakeTime;
	const TickType_t taskInterval = pdMS_TO_TICKS(config.NetworkHandlerTaskInterval);
	tWirelessPackage package;

	for(;;)
	{
		xLastWakeTime = xTaskGetTickCount(); /* Initialize the lastWakeTime variable with the current time. */
		/* generate data packages and put those into the package queue */
		for(int deviceNr = 0; deviceNr<NUMBER_OF_UARTS; deviceNr++)
		{
			/* generate packages from raw data bytes and send to correct packagesToSend queue */
			if(generateDataPackage(deviceNr, &package, sessionNr)) /* generate package from raw device data bytes */
				sendAndStoreGeneratedWlPackage(&package, deviceNr); /* send the generated package to the correct queue and store it internally if ACK is configured */

			/* extract data from received packages, send ACK and send raw data to corresponding UART interface */
			if(numberOfPacksInReceivedPacksQueue(deviceNr) > 0)
				processReceivedPackage(deviceNr);

			/* handle resend in case acknowledge not received */
		}
		vTaskDelayUntil( &xLastWakeTime, taskInterval ); /* Wait for the next cycle */
	}
}

void networkHandler_TaskInit(void)
{
	initNetworkHandlerQueues();
	crcNH = CRC1_Init(NULL);
	LDD_TDeviceData* rng = RNG_Init(NULL);
	uint32_t randomNumber;

	/* generate random 8bit session number */
	if(rng == NULL)
		while(true){} /* RNG could not be initialized */
	RNG_GetRandomNumber(rng, &randomNumber);
	sessionNr = (uint8_t) randomNumber;
}

/*!
* \fn void initNetworkHandlerQueues(void)
* \brief This function initializes the array of queues
*/
void initNetworkHandlerQueues(void)
{
	for(int uartNr=0; uartNr<NUMBER_OF_UARTS; uartNr++)
	{
		queuePackagesToSend[uartNr] = xQueueCreate( QUEUE_NUM_OF_WL_PACK_TO_SEND, sizeof(tWirelessPackage));
		if(queuePackagesToSend[uartNr] == NULL)
			while(true){} /* malloc for queue failed */
		vQueueAddToRegistry(queuePackagesToSend[uartNr], queueName[uartNr]);
	}
}

bool sendAndStoreGeneratedWlPackage(tWirelessPackage* pPackage, tUartNr rawDataUartNr)
{
	uint8_t wlConnectionToUse = 0;
	/* find configured WL connection number for first send of this package */
	for(int prio=1; prio <= NUMBER_OF_UARTS; prio++)
	{
		wlConnectionToUse = getWlConnectionToUse(rawDataUartNr, prio);
		if(wlConnectionToUse >= NUMBER_OF_UARTS)
			return false;
		/* send generated WL package to correct package queue */
		if(xQueueSendToBack(queuePackagesToSend[wlConnectionToUse], pPackage, ( TickType_t ) 0) != pdTRUE)
			break; /* try next priority -> go though for-loop again */
		/* store generated package in internal array if acknowledge is expected from this WL connection */
		if(config.SendAckPerWirelessConn[wlConnectionToUse])
		{
			pPackage->sendAttemptsLeftPerWirelessConnection[wlConnectionToUse]++;
			while(storeNewPackageInUnacknowledgedPackagesArray(pPackage) == false)
				vTaskDelay(pdMS_TO_TICKS(10)); /* array full */
			return true; /* success */
		}
	}
	return false;
}

uint8_t getWlConnectionToUse(tUartNr uartNr, uint8_t desiredPrio)
{
	uint8_t wlConnectionToUse = 0;
	switch(uartNr)
	{
		case MAX_UART_0:
			while ( wlConnectionToUse < NUMBER_OF_UARTS && config.PrioWirelessConnDev0[wlConnectionToUse] != desiredPrio ) ++wlConnectionToUse;
			break;
		case MAX_UART_1:
			while ( wlConnectionToUse < NUMBER_OF_UARTS && config.PrioWirelessConnDev1[wlConnectionToUse] != desiredPrio ) ++wlConnectionToUse;
			break;
		case MAX_UART_2:
			while ( wlConnectionToUse < NUMBER_OF_UARTS && config.PrioWirelessConnDev2[wlConnectionToUse] != desiredPrio ) ++wlConnectionToUse;
			break;
		case MAX_UART_3:
			while ( wlConnectionToUse < NUMBER_OF_UARTS && config.PrioWirelessConnDev3[wlConnectionToUse] != desiredPrio ) ++wlConnectionToUse;
			break;
	}
	return wlConnectionToUse;
}


bool processReceivedPackage(tUartNr wirelessConnNr)
{
	tWirelessPackage package;
	package.payload = (uint8_t*) FRTOS_pvPortMalloc(PACKAGE_MAX_PAYLOAD_SIZE*sizeof(int8_t));
	if(package.payload == NULL)
		return false;
	popReceivedPackFromQueue(wirelessConnNr, &package);
	if(package.packType == PACK_TYPE_DATA_PACKAGE) /* data package received */
	{
		/* check if data is valid */
		if(package.payloadSize > PACKAGE_MAX_PAYLOAD_SIZE)
			package.payloadSize = PACKAGE_MAX_PAYLOAD_SIZE;
		if(package.devNum > NUMBER_OF_UARTS)
			package.devNum = NUMBER_OF_UARTS-1;
		/* send data out at correct device side */
		for(uint16_t cnt=0; cnt<package.payloadSize; cnt++)
		{
			while(pushToByteQueue(MAX_14830_DEVICE_SIDE, package.devNum, &package.payload[cnt]) == pdFAIL)
				vTaskDelay(pdMS_TO_TICKS(10)); /* array full */
		}
		/* generate ACK if it is configured and send it to package queue */
		if(config.SendAckPerWirelessConn[wirelessConnNr])
		{
			tWirelessPackage ackPackage;
			generateAckPackage(&package, &ackPackage);
			if(xQueueSendToBack(queuePackagesToSend[wirelessConnNr], &ackPackage, ( TickType_t ) 0) != pdTRUE)
				vTaskDelay(pdMS_TO_TICKS(10)); /* array full */
			/* memory is freed when package in PackageHandler task */
		}
		else
			FRTOS_vPortFree(package.payload); /* because we do not send a package to PackageHandler task, we need to free memory here */
	}
	else /* acknowledge package received */
	{
		/* iterate though unacknowledged packages to find the corresponding one */
		for(int index=0; index < MAX_NUMBER_OF_UNACK_PACKS_STORED; index++)
		{
			/* check if this index holds an unacknowledged package */
			if(unacknowledgedPackagesOccupiedAtIndex[index])
			{
				uint32_t sysTime = package.payload[0];
				sysTime |= (package.payload[1] << 8);
				sysTime |= (package.payload[2] << 16);
				sysTime |= (package.payload[3] << 24);
				/* check if this is the package we got the acknowledge for */
				if(		unacknowledgedPackages[index].devNum == package.devNum &&
						unacknowledgedPackages[index].sysTime == package.sysTime   )
				{
					/* free memory if so and store this index as empty */
					FRTOS_vPortFree(unacknowledgedPackages[index].payload);
					unacknowledgedPackagesOccupiedAtIndex[index] = false;
				}
			}
		}
		FRTOS_vPortFree(package.payload); /* because we do not send a package to PackageHandler task, we need to free memory here */
	}
	return true;
}


/*!
* \fn static void generateDataPackage(uint8_t deviceNumber, Queue* dataSource)
* \brief Function to generate a data package, reading data from the data source.
* \param deviceNumber: Number of device.
* \param dataSource: Pointer to the queue where the data where the data is read.
* \param wPackage: Pointer to package structure.
* \return true if a package was generated and saved in wPackage, false otherwise.
*/
static bool generateDataPackage(tUartNr deviceNr, tWirelessPackage* pPackage, uint8_t sessionNr)
{
	static uint32_t tickTimeSinceFirstCharReceived[NUMBER_OF_UARTS]; /* static variables are initialized as 0 by default */
	static bool dataWaitingToBeSent[NUMBER_OF_UARTS];
	static uint8_t packHeaderBuf[PACKAGE_HEADER_SIZE - 1] = { PACK_START, PACK_TYPE_DATA_PACKAGE, 0, 0, 0, 0, 0, 0, 0, 0 };

	uint16_t numberOfBytesInRxQueue = (uint16_t) numberOfBytesInRxByteQueue(MAX_14830_DEVICE_SIDE, deviceNr);
	uint32_t timeWaitedForPackFull = xTaskGetTickCount()-tickTimeSinceFirstCharReceived[deviceNr];

	/* check if enough data to fill package or maximum wait time for full package done */
	if ((numberOfBytesInRxQueue >= config.UsualPacketSizeDeviceConn[deviceNr]) ||
		(numberOfBytesInRxQueue >= PACKAGE_MAX_PAYLOAD_SIZE) ||
		((dataWaitingToBeSent[deviceNr] == true) && (timeWaitedForPackFull >= pdMS_TO_TICKS(config.PackageGenMaxTimeout[deviceNr]))))
	{
		/* reached usual packet size or timeout, generate package */
		/* Put together package */
		/* put together payload by allocating memory and copy data */
		pPackage->payloadSize = numberOfBytesInRxQueue;
		pPackage->payload = (uint8_t*) FRTOS_pvPortMalloc(numberOfBytesInRxQueue*sizeof(int8_t));
		if(pPackage->payload == NULL) /* malloc failed */
			return false;
		/* get data from queue */
		for (uint16_t cnt = 0; cnt < pPackage->payloadSize; cnt++)
		{
			popFromByteQueue(MAX_14830_DEVICE_SIDE, deviceNr, &pPackage->payload[cnt]);
		}
		/* calculate CRC */
		uint32_t crc16;
		CRC1_ResetCRC(crcNH);
		CRC1_SetCRCStandard(crcNH, LDD_CRC_MODBUS_16); // ToDo: use LDD_CRC_MODBUS_16 afterwards, MODBUS only for backwards compatibility with old SW
		CRC1_GetBlockCRC(crcNH, pPackage->payload, pPackage->payloadSize, &crc16);
		pPackage->crc16payload = (uint16_t) crc16;
		/* put together the rest of the header */
		pPackage->packType = PACK_TYPE_DATA_PACKAGE;
		pPackage->devNum = deviceNr;
		pPackage->sessionNr = sessionNr;
		pPackage->sysTime = (uint32_t) xTaskGetTickCount();
		/* calculate crc */
		CRC1_ResetCRC(crcNH);
		CRC1_GetCRC8(crcNH, PACK_START);
		CRC1_GetCRC8(crcNH, PACK_TYPE_DATA_PACKAGE);
		CRC1_GetCRC8(crcNH, pPackage->devNum);
		CRC1_GetCRC8(crcNH, pPackage->sessionNr);
		CRC1_GetCRC8(crcNH, *((uint8_t*)(&pPackage->sysTime) + 3));
		CRC1_GetCRC8(crcNH, *((uint8_t*)(&pPackage->sysTime) + 2));
		CRC1_GetCRC8(crcNH, *((uint8_t*)(&pPackage->sysTime) + 1));
		CRC1_GetCRC8(crcNH, *((uint8_t*)(&pPackage->sysTime) + 0));
		CRC1_GetCRC8(crcNH, *((uint8_t*)(&pPackage->payloadSize) + 1));
		pPackage->crc8Header = CRC1_GetCRC8(crcNH, *((uint8_t*)(&pPackage->payloadSize) + 0));
		/* reset last timestamp */
		tickTimeSinceFirstCharReceived[deviceNr] = 0;
		/* reset flag that timestamp was updated */
		dataWaitingToBeSent[deviceNr] = false;
		return true;
	}
	else if(numberOfBytesInRxQueue > 0)
	{
		/* there is data available, update timestamp that data is available (but only if the timestamp wasn't already updated) */
		if (dataWaitingToBeSent[deviceNr] == false)
		{
			tickTimeSinceFirstCharReceived[deviceNr] = xTaskGetTickCount();
			dataWaitingToBeSent[deviceNr] = true;
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
* \fn static bool generateAckPackage(tWirelessPackage* pReceivedDataPack, tWirelessPackage* pAckPack)
* \brief Function to generate a receive acknowledge package, reading data from the data source.
* \param pAckPack: Pointer to acknowledge packet to be created
* \param pReceivedDataPack: Pointer to the structure that holds the wireless package that the acknowledge is generated for
* \return true if a package was generated and saved, false otherwise.
*/
static bool generateAckPackage(tWirelessPackage* pReceivedDataPack, tWirelessPackage* pAckPack)
{
	/* buffer in order to be able to save the header for CRC calculation. -1 in length of buffer because we don't need the CRC itself in the buffer */
	/* default header = { PACK_START, PACK_TYPE_REC_ACKNOWLEDGE, 0, 0, 0, 0, 0, 0, 0, 0 } */
	/* prepare wireless package */
	pAckPack->packType = PACK_TYPE_REC_ACKNOWLEDGE;
	pAckPack->devNum = pReceivedDataPack->devNum;
	pAckPack->sessionNr = sessionNr;
	pAckPack->sysTime = xTaskGetTickCount();
	pAckPack->payloadSize = sizeof(uint32_t);	/* as payload, the timestamp of the package to be acknowledged is saved */
	/* calculate crc for header */
	CRC1_ResetCRC(crcNH);
	CRC1_SetCRCStandard(crcNH, LDD_CRC_MODBUS_16); // ToDo: use LDD_CRC_MODBUS_16 afterwards, MODBUS only for backwards compatibility with old SW
	CRC1_GetCRC8(crcNH, PACK_START);
	CRC1_GetCRC8(crcNH, PACK_TYPE_REC_ACKNOWLEDGE);
	CRC1_GetCRC8(crcNH, pAckPack->devNum);
	CRC1_GetCRC8(crcNH, pAckPack->sessionNr);
	CRC1_GetCRC8(crcNH, *((uint8_t*)(&pAckPack->sysTime) + 3));
	CRC1_GetCRC8(crcNH, *((uint8_t*)(&pAckPack->sysTime) + 2));
	CRC1_GetCRC8(crcNH, *((uint8_t*)(&pAckPack->sysTime) + 1));
	CRC1_GetCRC8(crcNH, *((uint8_t*)(&pAckPack->sysTime) + 0));
	CRC1_GetCRC8(crcNH, *((uint8_t*)(&pAckPack->payloadSize) + 1));
	pAckPack->crc8Header = CRC1_GetCRC8(crcNH, *((uint8_t*)(&pAckPack->payloadSize) + 0));
	/* get space for acknowladge payload (which consists of sysTime of datapackage*/
	pAckPack->payload = (uint8_t*) FRTOS_pvPortMalloc(pAckPack->payloadSize*sizeof(int8_t));
	/* generate payload */
	for (uint16_t cnt = 0; cnt < pAckPack->payloadSize; cnt++)
	{
		pAckPack->payload[cnt] = *((uint8_t*)(&pReceivedDataPack->sysTime) + cnt);
	}
	/* generate CRC16 for payload */
	uint32_t crc16;
	CRC1_ResetCRC(crcNH);
	CRC1_GetBlockCRC(crcNH, pAckPack->payload, pAckPack->payloadSize, &crc16);
	pAckPack->crc16payload = (uint16_t) crc16;
	return true;
}


/*!
* \fn bool storeNewPackageInUnacknowledgedPackagesArray(tWirelessPackage* pPackage)
* \brief Finds free space in array and stores package in array for unacknowledged packages.
* \param pPackage: Pointer to package that should be stored
* \return true if successful, false if array is full
*/
static bool storeNewPackageInUnacknowledgedPackagesArray(tWirelessPackage* pPackage)
{
	for(int index=0; index < MAX_NUMBER_OF_UNACK_PACKS_STORED; index++)
	{
		if(unacknowledgedPackagesOccupiedAtIndex[index] == 0) /* there is no package stored at this index */
		{
			unacknowledgedPackages[index] = *pPackage;
			unacknowledgedPackages[index].payload = FRTOS_pvPortMalloc(unacknowledgedPackages[index].payloadSize*sizeof(int8_t));
			// ToDo: copy payload into package
			unacknowledgedPackagesOccupiedAtIndex[index] = 1;
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