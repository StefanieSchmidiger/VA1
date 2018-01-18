// 
// 
// 

#include "packageGenerator.h"
#include <Queue.h>
#include "hwBufferInterface.h"
#include "serialSwitch_General.h"
#include "serialSwitch_Config.h"
#include "wirelessSendHandler.h"
#include "errorAndWarningOutput.h"
#include "FastCRC.h"	/* examples: https://github.com/FrankBoesing/FastCRC */





/*! \def QUEUE_NUM_OF_ACK
*  \brief Number of elements that should find space within the send acknowledge queue.
*/
#define QUEUE_NUM_OF_ACK						8



/*! \def dataPayloadBuffers
*  \brief Buffers used to store the payload for the data packages.
*/
static uint8_t dataPayloadBuffers[QUEUE_NUM_OF_WL_PACK][PACKAGE_MAX_PAYLOAD_SIZE];

/*! \def isDataPayloadBufferFree
*  \brief Array to store the information which data buffers are currently free.
*/
static bool isDataPayloadBufferFree[QUEUE_NUM_OF_WL_PACK];


/*! \def ackPayloadBuffers
*  \brief Buffers used to store the payload for the acknowledge packages.
*/
static uint8_t ackPayloadBuffers[QUEUE_NUM_OF_WL_PACK][sizeof(uint32_t)];

/*! \def isAckPayloadBufferFree
*  \brief Array to store the information which data buffers are currently free.
*/
static bool isAckPayloadBufferFree[QUEUE_NUM_OF_WL_PACK];

/*! \def sessionNumber
*  \brief Variable to store the session number.
*/
static uint8_t sessionNumber;



/* initialize required queue */
Queue queueSendAck(sizeof(sWiReceiveAck), QUEUE_NUM_OF_ACK);




/*!
* \fn static uint8_t* getDataBuffer(void)
* \brief Gets the pointer to a free buffer to store payload data for a data package.
* \return Pointer to the data buffer of size PACKAGE_MAX_PAYLOAD_SIZE.
*/
static uint8_t* getDataBuffer(void)
{
	uint8_t* retVal = NULL;
	for (uint8_t cnt = 0; cnt < QUEUE_NUM_OF_WL_PACK; cnt++)
	{
		if (isDataPayloadBufferFree[cnt] == true)
		{
			/* found free buffer, return it */
			isDataPayloadBufferFree[cnt] = false;
			retVal = &dataPayloadBuffers[cnt][0];
			break;
		}
	}
	if (retVal == NULL)
	{
		showError(__FUNCTION__, "no more free data buffers!!");
	}
	return retVal;
}

/*!
* \fn void setDataBufferFree(uint8_t* pDataBuffer)
* \brief Frees a data buffer.
* \return pDataBuffer: Pointer to the data buffer that isn't used any more.
*/
void setDataBufferFree(uint8_t* pDataBuffer)
{
	for (uint8_t cnt = 0; cnt < QUEUE_NUM_OF_WL_PACK; cnt++)
	{
		if (pDataBuffer == &dataPayloadBuffers[cnt][0])
		{
			memset(&dataPayloadBuffers[cnt][0], 0, sizeof(PACKAGE_MAX_PAYLOAD_SIZE));
			isDataPayloadBufferFree[cnt] = true;
			return;
		}
	}
	showError(__FUNCTION__, "unable to find data buffer to free!!");
}



/*!
* \fn static uint8_t* getAckBuffer(void)
* \brief Gets the pointer to a free buffer to store payload data for a ack package.
* \return Pointer to the data buffer of size uint32_t.
*/
static uint8_t* getAckBuffer(void)
{
	uint8_t* retVal = NULL;
	for (uint8_t cnt = 0; cnt < QUEUE_NUM_OF_WL_PACK; cnt++)
	{
		if (isAckPayloadBufferFree[cnt] == true)
		{
			/* found free buffer, return it */
			isAckPayloadBufferFree[cnt] = false;
			retVal = &ackPayloadBuffers[cnt][0];
			break;
		}
	}
	if (retVal == NULL)
	{
		showError(__FUNCTION__, "no more free acknowledge buffers!!");
	}
	return retVal;
}

/*!
* \fn void setAckBufferFree(uint8_t* pDataBuffer)
* \brief Frees a acknowledge data buffer.
* \return pDataBuffer: Pointer to the ack data buffer that isn't used any more.
*/
void setAckBufferFree(uint8_t* pDataBuffer)
{
	for (uint8_t cnt = 0; cnt < QUEUE_NUM_OF_WL_PACK; cnt++)
	{
		if (pDataBuffer == &ackPayloadBuffers[cnt][0])
		{
			memset(&ackPayloadBuffers[cnt][0], 0, sizeof(uint32_t));
			isAckPayloadBufferFree[cnt] = true;
			return;
		}
	}
	showError(__FUNCTION__, "unable to find acknowledge buffer to free!!");
}








/*!
* \fn static inline void generateRecAckPackage(sWiReceiveAck ackData)
* \brief Function to generate a receive acknowledge package, reading data from the data source.
* \param pAckData: Pointer to structure with required information in order to generate the package.
* \param pWirPackageSendPack: Pointer to the structure that holds the wireless package plus information where the package needs to be sent.
* \return true if a package was generated and saved in wPackage, false otherwise.
*/
static inline bool generateRecAckPackage(sWiReceiveAck* pAckData, tWirelessAckSendPackSt* pWirPackageSendPack)
{
	/* buffer in order to be able to save the header for CRC calculation. -1 in length of buffer because we don't need the CRC itself in the buffer */
	static uint8_t packHeaderBuf[PACKAGE_HEADER_SIZE - 1] = { PACK_START, PACK_TYPE_REC_ACKNOWLEDGE, 0, 0, 0, 0, 0, 0, 0, 0 };
	/* assign wireless connection number */
	pWirPackageSendPack->wirelessConnToSendTo = pAckData->wirNum;
	/* prepare wireless package */
	pWirPackageSendPack->wirelessPackage.packType = PACK_TYPE_REC_ACKNOWLEDGE;
	pWirPackageSendPack->wirelessPackage.devNum = pAckData->devNum;
	pWirPackageSendPack->wirelessPackage.sessionNr = sessionNumber;
	pWirPackageSendPack->wirelessPackage.sysTime = millis();
	pWirPackageSendPack->wirelessPackage.payloadSize = sizeof(uint32_t);	/* as payload, the timestamp of the package to be acknowledged is saved */
	/* prepare buffer in order to be able to calculate crc */
	/* IMPROVE: Copy stuff around that much isn't very performant */
	packHeaderBuf[2] = pWirPackageSendPack->wirelessPackage.devNum;
	packHeaderBuf[3] = pWirPackageSendPack->wirelessPackage.sessionNr;
	packHeaderBuf[4] = *((uint8_t*)(&pWirPackageSendPack->wirelessPackage.sysTime) + 3);
	packHeaderBuf[5] = *((uint8_t*)(&pWirPackageSendPack->wirelessPackage.sysTime) + 2);
	packHeaderBuf[6] = *((uint8_t*)(&pWirPackageSendPack->wirelessPackage.sysTime) + 1);
	packHeaderBuf[7] = *((uint8_t*)(&pWirPackageSendPack->wirelessPackage.sysTime) + 0);
	packHeaderBuf[8] = *((uint8_t*)(&pWirPackageSendPack->wirelessPackage.payloadSize) + 1);
	packHeaderBuf[9] = *((uint8_t*)(&pWirPackageSendPack->wirelessPackage.payloadSize) + 0);
	FastCRC8 crc8;
	pWirPackageSendPack->wirelessPackage.crc8Header = crc8.smbus(packHeaderBuf, PACKAGE_HEADER_SIZE - 1);
	/* get space for acknowladge payload */
	uint8_t* ackBuf = getAckBuffer();
	if (ackBuf == NULL)	return false;
	pWirPackageSendPack->wirelessPackage.payload = ackBuf;
	uint32_t* pPayl = (uint32_t*)pWirPackageSendPack->wirelessPackage.payload;
	*pPayl = pAckData->sysTime;
	FastCRC16 crc16;
	pWirPackageSendPack->wirelessPackage.crc16payload = crc16.ccitt(&pWirPackageSendPack->wirelessPackage.payload[0], sizeof(uint32_t));
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
static bool generateDataPackage(uint8_t deviceNumber, Queue* dataSource, tWirelessPackage* wPackage)
{
	static uint16_t usualPacketSizes[] = USUAL_PACKET_SIZE_DEVICE_CONN;
	static uint8_t maxTimeout[] = PACKAGE_GEN_MAX_TIMEOUT;
	static uint32_t lastTimestampDataAv[NUM_OF_DEVICE_CONNECTIONS];
	static bool updatedTimestamp[NUM_OF_DEVICE_CONNECTIONS];
	static uint8_t packHeaderBuf[PACKAGE_HEADER_SIZE - 1] = { PACK_START, PACK_TYPE_DATA_PACKAGE, 0, 0, 0, 0, 0, 0, 0, 0 };
	/* check if there is data to send, also based on the configuration */
	if (((*dataSource).nbRecs() >= usualPacketSizes[deviceNumber]) ||
		((*dataSource).nbRecs() >= PACKAGE_MAX_PAYLOAD_SIZE) ||
		((updatedTimestamp[deviceNumber] == true) && (millis()-lastTimestampDataAv[deviceNumber] >= maxTimeout[deviceNumber])))
	{
		/* reached usual packet size or timeout, generate package */
		/* Put together package */
		/* put together payload by allocating memory and copy data */
		wPackage->payloadSize = (*dataSource).nbRecs();
		uint8_t* dataBuf = getDataBuffer();
		if (dataBuf == NULL)	return false;
		wPackage->payload = dataBuf;
		/* get data from queue and calculate CRC */
		for (uint16_t cnt = 0; cnt < wPackage->payloadSize; cnt++)
		{
			(*dataSource).pull(&wPackage->payload[cnt]);
		}
		FastCRC16 crc16;
		wPackage->crc16payload = crc16.ccitt(&wPackage->payload[0], wPackage->payloadSize);
		/* put together the rest of the header */
		wPackage->packType = PACK_TYPE_DATA_PACKAGE;
		wPackage->devNum = deviceNumber;
		wPackage->sessionNr = sessionNumber;
		wPackage->sysTime = millis();
		/* copy header to buffer, calculate crc */
		/* IMPROVE: Copy stuff around that much isn't very performant */
		packHeaderBuf[2] = wPackage->devNum;
		packHeaderBuf[3] = wPackage->sessionNr;
		packHeaderBuf[4] = *((uint8_t*)(&wPackage->sysTime) + 3);
		packHeaderBuf[5] = *((uint8_t*)(&wPackage->sysTime) + 2);
		packHeaderBuf[6] = *((uint8_t*)(&wPackage->sysTime) + 1);
		packHeaderBuf[7] = *((uint8_t*)(&wPackage->sysTime) + 0);
		packHeaderBuf[8] = *((uint8_t*)(&wPackage->payloadSize) + 1);
		packHeaderBuf[9] = *((uint8_t*)(&wPackage->payloadSize) + 0);
		FastCRC8 crc8;
		wPackage->crc8Header = crc8.smbus(packHeaderBuf, PACKAGE_HEADER_SIZE - 1);
		/* reset last timestamp */
		lastTimestampDataAv[deviceNumber] = 0;
		/* reset flag that timestamp was updated */
		updatedTimestamp[deviceNumber] = false;
		return true;
	}
	else if((*dataSource).isEmpty() == false)
	{
		/* there is data available, update timestamp that data is available (but only if the timestamp wasn't already updated) */
		if (updatedTimestamp[deviceNumber] == false)
		{
			lastTimestampDataAv[deviceNumber] = millis();
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
* \fn void packageGenerator_TaskEntry(void)
* \brief Task that reads the incoming data from the devices from the corresponding queues and put together packages to be sent via wireless.
*/
void packageGenerator_TaskEntry(void)
{
	sWiReceiveAck ackData;
	tWirelessPackage wirelessPackage;
	tWirelessAckSendPackSt wirelessAckPackage;

	/* initialize some variables in the first call */
	if (packageGeneratorTask.isFirstIteration() == true)
	{
		/* initialize session number - random number */
		/* generate seed by reading floating analog pin */
		pinMode(PIN_A0, INPUT);
		srand(analogRead(PIN_A0));
		sessionNumber = (uint8_t)(rand() % 0xFF);
		char infoBuf[64];
		sprintf(infoBuf, "session number (random): %u", sessionNumber);
		showInfo(__FUNCTION__, infoBuf);

		/* initialize payload buffer size */
		for (uint8_t cnt = 0; cnt < QUEUE_NUM_OF_WL_PACK; cnt++)
		{
			isDataPayloadBufferFree[cnt] = true;
			isAckPayloadBufferFree[cnt] = true;
		}
	}
	
	/* check if there are some receive acknowledge packages that needs to be created */
	while (queueSendAck.pull(&ackData))
	{
		if (generateRecAckPackage(&ackData, &wirelessAckPackage))
		{
			queueWirelessAckPack.push(&wirelessAckPackage);
		}
	}

	/* generate data packages and put those into the package queue */
	if (generateDataPackage(0, &queueDeviceReceiveUart[0], &wirelessPackage))
	{
		queueWirelessDataPackPerDev[0].push(&wirelessPackage);
	}
	if (generateDataPackage(1, &queueDeviceReceiveUart[1], &wirelessPackage))
	{
		queueWirelessDataPackPerDev[1].push(&wirelessPackage);
	}
	if (generateDataPackage(2, &queueDeviceReceiveUart[2], &wirelessPackage))
	{
		queueWirelessDataPackPerDev[2].push(&wirelessPackage);
	}
	if (generateDataPackage(3, &queueDeviceReceiveUart[3], &wirelessPackage))
	{
		queueWirelessDataPackPerDev[3].push(&wirelessPackage);
	}
}


