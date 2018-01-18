// 
// 
// 

#include "wirelessSendHandler.h"
#include "serialSwitch_General.h"
#include "hwBufferInterface.h"
#include "serialSwitch_Config.h"
#include "errorAndWarningOutput.h"
#include "packageGenerator.h"
#include "throughputPrintout.h"




/*! \def QUEUE_NUM_OF_ACK
*  \brief Number of elements that should find space within the receive acknowledge queue.
*/
#define QUEUE_NUM_OF_ACK						8



/*! \struct sWiSendHandInternalPackBuf
*  \brief Structure that holds all the required information of a wireless package.
*/
typedef struct sWiSendHandInternalPackBuf
{
	tWirelessPackage wirelessPackage;
	uint8_t currentPrioConnection;
	uint8_t sendAttemptsLeftPerWirelessConnection[NUM_OF_WIRELESS_CONNECTIONS];
	uint32_t lastTimePackWasSentMs[NUM_OF_WIRELESS_CONNECTIONS];	/* holds the timestamp when the packet was sent the last time for every wireless connection */
	uint16_t totalNumberOfSendAttemptsPerWirelessConnection[NUM_OF_WIRELESS_CONNECTIONS];		/* to save the total number of send attempts that were needed for this package */
} tWiSendHandInternalPackBuf;



/*! \var prioWirelessConn
*  \brief Array to save the priority of the different wireless connections from the viewpoint of the devices.
*/
static uint8_t prioWirelessConn[4][4] = { PRIO_WIRELESS_CONN_DEV_0, PRIO_WIRELESS_CONN_DEV_1, PRIO_WIRELESS_CONN_DEV_2, PRIO_WIRELESS_CONN_DEV_3 };

/*! \var sendCntWirelessConn
*  \brief Number of times a single package should be tried to sent over a single connection.
*/
static uint8_t sendCntWirelessConn[4][4] = { SEND_CNT_WIRELESS_CONN_DEV_0, SEND_CNT_WIRELESS_CONN_DEV_1, SEND_CNT_WIRELESS_CONN_DEV_2, SEND_CNT_WIRELESS_CONN_DEV_3 };

/*! \var resendDelayPerDeviceAndWcMs
*  \brief Resend delay per device and wireless connection.
*/
static uint16_t resendDelayPerDeviceAndWcMs[4][4] = { RESEND_DELAY_WIRELESS_CONN_DEV_0, RESEND_DELAY_WIRELESS_CONN_DEV_1, RESEND_DELAY_WIRELESS_CONN_DEV_2, RESEND_DELAY_WIRELESS_CONN_DEV_3 };


/*! \var nextDataPacketToSend
*  \brief To save the next packet for every device that should be sent via wireless.
*/
static tWiSendHandInternalPackBuf nextDataPacketToSend[NUM_OF_DEVICE_CONNECTIONS];

/*! \var nextDataPacketToSendAvailable
*  \brief Array of flags to indicate for which devices a next packet is available and ready to be sent.
*/
static bool nextDataPacketToSendAvailable[NUM_OF_DEVICE_CONNECTIONS] = { false, false, false, false };



/* initialize required queues */
Queue queueWirelessDataPackPerDev[NUM_OF_DEVICE_CONNECTIONS] = 
	{ Queue(sizeof(tWirelessPackage), QUEUE_NUM_OF_WL_PACK), Queue(sizeof(tWirelessPackage), QUEUE_NUM_OF_WL_PACK), 
	Queue(sizeof(tWirelessPackage), QUEUE_NUM_OF_WL_PACK), Queue(sizeof(tWirelessPackage), QUEUE_NUM_OF_WL_PACK) };
Queue queueWirelessAckPack(sizeof(tWirelessAckSendPackSt), QUEUE_NUM_OF_WL_PACK);
Queue queueRecAck(sizeof(sWiReceiveAck), QUEUE_NUM_OF_ACK);



/*!
* \fn static inline void sendNonPackStartCharacter(Queue* pSendQueue, uint8_t charToSend)
* \brief Replaces all outgoing PACK_START characters in the stream by "PACK_START" to be able to distinguish them at the receive side.
* \param pSendQueue: Queue that should be used to send the characters.
* \param pCharToSend: Pointer to the char that needs to be sent.
*/
static inline void sendNonPackStartCharacter(Queue* pSendQueue, uint8_t* pCharToSend)
{
	if ((*pCharToSend) == PACK_START)
	{
		static uint8_t repChar = PACK_REP;
		pSendQueue->push(&repChar);
		pSendQueue->push(pCharToSend);
		pSendQueue->push(&repChar);
	}
	else
	{
		pSendQueue->push(pCharToSend);
	}
}

/*!
* \fn static void sendPackageToWirelessQueue(Queue* pToWirelessQueue, tWirelessPackage* pToWirelessPackage)
* \brief Function to send the desired package to the desired queue character for character.
* \param pToWirelessQueue: Queue that should be used to send the characters.
* \param tWirelessPackage: Pointer to wireless package that needs to be sent.
*/
static void sendPackageToWirelessQueue(Queue* pToWirelessQueue, tWirelessPackage* pToWirelessPackage)
{
	if ((pToWirelessQueue == NULL) || (pToWirelessPackage == NULL) || (pToWirelessPackage->payloadSize > PACKAGE_MAX_PAYLOAD_SIZE))
	{
		showError(__FUNCTION__, "package won't be sent, error occurred");
		return;
	}
	static uint8_t startChar = PACK_START;
	pToWirelessQueue->push(&startChar);
	sendNonPackStartCharacter(pToWirelessQueue, &pToWirelessPackage->packType);
	sendNonPackStartCharacter(pToWirelessQueue, &pToWirelessPackage->devNum);
	sendNonPackStartCharacter(pToWirelessQueue, &pToWirelessPackage->sessionNr);
	sendNonPackStartCharacter(pToWirelessQueue, (uint8_t*)(&pToWirelessPackage->sysTime) + 3);
	sendNonPackStartCharacter(pToWirelessQueue, (uint8_t*)(&pToWirelessPackage->sysTime) + 2);
	sendNonPackStartCharacter(pToWirelessQueue, (uint8_t*)(&pToWirelessPackage->sysTime) + 1);
	sendNonPackStartCharacter(pToWirelessQueue, (uint8_t*)(&pToWirelessPackage->sysTime) + 0);
	sendNonPackStartCharacter(pToWirelessQueue, (uint8_t*)(&pToWirelessPackage->payloadSize) + 1);
	sendNonPackStartCharacter(pToWirelessQueue, (uint8_t*)(&pToWirelessPackage->payloadSize) + 0);
	sendNonPackStartCharacter(pToWirelessQueue, &pToWirelessPackage->crc8Header);
	for (uint16_t cnt = 0; cnt < pToWirelessPackage->payloadSize; cnt++)
	{
		sendNonPackStartCharacter(pToWirelessQueue, &pToWirelessPackage->payload[cnt]);
	}
	sendNonPackStartCharacter(pToWirelessQueue, (uint8_t*)(&pToWirelessPackage->crc16payload) + 1);
	sendNonPackStartCharacter(pToWirelessQueue, (uint8_t*)(&pToWirelessPackage->crc16payload) + 0);
	/* also send two fill bytes at the end - just that we're able to make sure on the receive side that we got all replacements */
	/* TODO this is "dirty" workaround that leads to more traffic, to be replaced with better solution (but in this case also the wireless package extractor needs to be adjusted) */
	static uint8_t repChar = PACK_FILL;
	sendNonPackStartCharacter(pToWirelessQueue, &repChar);
	sendNonPackStartCharacter(pToWirelessQueue, &repChar);
}



/*!
* \fn static bool sendWirelessDataPackage(tWiSendHandInternalPackBuf packageToSend, Queue* pToQueueToUseToSend)
* \brief Function to send a wireless data packet to the wireless connection according to the configuration or discard it.
* \param pToPackageToSend: Pointer to internal structure that holds the package plus routing information.
* \param deviceNr: Device number, source of this package, needs to be between 0 and 3.
* \return true it the packet can be discarded, false if a package was sent to the queue or the package wasn't sent but should be kept in the internal buffer.
*/
static bool sendWirelessDataPackage(tWiSendHandInternalPackBuf* pToPackageToSend, uint8_t deviceNr)
{
	bool discardPackage = false;
	bool decrementPrio = true;
	uint8_t cnt;
	Queue* pWirelessSendQueue;
	uint32_t lastPackSentSystime = 0;
	uint8_t resendDelayWirelessConnLastPackSent = 0;
	/* check if prio needs to be decremented */
	for (cnt = 0; cnt < NUM_OF_WIRELESS_CONNECTIONS; cnt++)
	{
		/* check if there are send attempts left */
		if (pToPackageToSend->sendAttemptsLeftPerWirelessConnection[cnt] > 0)
		{
			decrementPrio = false;
		}
		/* to handle the case that the resend delay also should be waited at the decrement prio case */
		if (pToPackageToSend->lastTimePackWasSentMs[cnt] > lastPackSentSystime)
		{
			lastPackSentSystime = pToPackageToSend->lastTimePackWasSentMs[cnt];
			resendDelayWirelessConnLastPackSent = resendDelayPerDeviceAndWcMs[deviceNr][cnt];
		}
	}
	/* if prio needs to be decremented, assign number of send attempts per connection. */
	if ((decrementPrio == true) && (millis() - lastPackSentSystime >= resendDelayWirelessConnLastPackSent))
	{
		discardPackage = true;
		pToPackageToSend->currentPrioConnection++;
		for (cnt = 0; cnt < NUM_OF_WIRELESS_CONNECTIONS; cnt++)
		{
			/* set resend counters */
			if (pToPackageToSend->currentPrioConnection == prioWirelessConn[deviceNr][cnt])
			{
				pToPackageToSend->sendAttemptsLeftPerWirelessConnection[cnt] = sendCntWirelessConn[deviceNr][cnt];
				/* there is at least one wireless connection with this priority => don't discard package */
				discardPackage = false;
			}
			else
			{
				pToPackageToSend->sendAttemptsLeftPerWirelessConnection[cnt] = 0;
			}
			/* reset time when package was sent the last time over a wireless connections */
			pToPackageToSend->lastTimePackWasSentMs[cnt] = 0;
		}
	}
	/* find wireless connections where this package needs to be sent to */
	for (cnt = 0; cnt < NUM_OF_WIRELESS_CONNECTIONS; cnt++)
	{
		if ((pToPackageToSend->currentPrioConnection == prioWirelessConn[deviceNr][cnt]) && 
			(pToPackageToSend->sendAttemptsLeftPerWirelessConnection[cnt] > 0) && 
			(millis() - pToPackageToSend->lastTimePackWasSentMs[cnt] >= resendDelayPerDeviceAndWcMs[deviceNr][cnt]))
		{
			/* set time when packet was sent the last time */
			pToPackageToSend->lastTimePackWasSentMs[cnt] = millis();
			/* get queue this package needs to be sent to */
			pWirelessSendQueue = &queueWirelessTransmitUart[cnt];
			/* send package if there is enough space in the queue */
			if ((QUEUE_NUM_OF_CHARS_WL_TX_QUEUE - pWirelessSendQueue->nbRecs()) > (PACKAGE_HEADER_SIZE + pToPackageToSend->wirelessPackage.payloadSize + 10)) /* header size plus payload plus 8 bytes reserve for replecement chars and 2 byte crc16 payload*/
			{
				/* send package to queue */
				sendPackageToWirelessQueue(pWirelessSendQueue, &pToPackageToSend->wirelessPackage);
#if GENERATE_DEBUG_OUTPUT > 0
				char infoBuf[128];
				sprintf(infoBuf, "sending data package, device %u; wireless connection %u; timestamp package: %lu; systemtime: %lu",
					deviceNr, cnt, pToPackageToSend->wirelessPackage.sysTime, millis());
				showInfo(__FUNCTION__, infoBuf);
#endif /* GENERATE_DEBUG_OUTPUT */
				numOfSentWirelessDataPack[cnt]++;
				/* update average payload size */
				updateAvPayloadSizeSentDataPack(cnt, pToPackageToSend->wirelessPackage.payloadSize);
			}
			else
			{
				/* there wasn't enough space in the queue */
				char warnBuf[128];
				sprintf(warnBuf, "Discard wireless data package, not enough space in wireless transmit queue, device number %u, wireless connection %u", deviceNr, cnt);
				showWarning(__FUNCTION__, warnBuf);
			}
			/* decrement number of send attempts */
			pToPackageToSend->sendAttemptsLeftPerWirelessConnection[cnt]--;
			pToPackageToSend->totalNumberOfSendAttemptsPerWirelessConnection[cnt]++;
		}
	}
	return discardPackage;
}


/*!
* \fn static inline void incrementSentAttemptCounters(tWiSendHandInternalPackBuf* pToInternalPackBuf)
* \brief This function should be called before a data packet will be deleted in order to update the statistical counters regarding the needed sent attempts.
* \param pToInternalPackBuf: Pointer to internal element that should be deleted afterwards.
*/
static inline void incrementSentAttemptCounters(tWiSendHandInternalPackBuf* pToInternalPackBuf)
{
	if (pToInternalPackBuf->totalNumberOfSendAttemptsPerWirelessConnection[0] > 0)
	{
		updateAvSentAttemptsPerWirelessConnection(0, pToInternalPackBuf->totalNumberOfSendAttemptsPerWirelessConnection[0]);
	}
	if (pToInternalPackBuf->totalNumberOfSendAttemptsPerWirelessConnection[1] > 0)
	{
		updateAvSentAttemptsPerWirelessConnection(1, pToInternalPackBuf->totalNumberOfSendAttemptsPerWirelessConnection[1]);
	}
	if (pToInternalPackBuf->totalNumberOfSendAttemptsPerWirelessConnection[2] > 0)
	{
		updateAvSentAttemptsPerWirelessConnection(2, pToInternalPackBuf->totalNumberOfSendAttemptsPerWirelessConnection[2]);
	}
	if (pToInternalPackBuf->totalNumberOfSendAttemptsPerWirelessConnection[3] > 0)
	{
		updateAvSentAttemptsPerWirelessConnection(3, pToInternalPackBuf->totalNumberOfSendAttemptsPerWirelessConnection[3]);
	}
}


/*!
* \fn static void sendResendOrDiscardDataPackage(sWiReceiveAck ackArray[], uint8_t numOfElementsInAckArray, uint8_t deviceNr)
* \brief Goes through the internal buffer and - depending on the configuration and if an acknowledge was received - resends or discards the package.
* \param ackArray: Array that holds all the received acknowledges.
* \param numOfElementsInAckArray: Number of elements in the acknowledge array.
* \param deviceNr: Device number, source of this package, needs to be between 0 and 3.
*/
static void sendResendOrDiscardDataPackage(sWiReceiveAck ackArray[], uint8_t numOfElementsInAckArray, uint8_t deviceNr)
{
	static tWiSendHandInternalPackBuf currElementPerDevice[NUM_OF_DEVICE_CONNECTIONS];
	static bool elementAvailable[NUM_OF_DEVICE_CONNECTIONS] = { false, false, false, false };
	static const uint8_t delayTillDismissPack[NUM_OF_DEVICE_CONNECTIONS] = DELAY_DISMISS_OLD_PACK_PER_DEV;
	uint8_t cnt;
	bool discardPackage = false;
	/* check if the device number is valid */
	if (deviceNr >= NUM_OF_DEVICE_CONNECTIONS)
	{
		showError(__FUNCTION__, "Invalid device number");
	}
	/* loop until finished */
	while (true)
	{
		/* check if there is still an element available */
		if (elementAvailable[deviceNr] == true)
		{
			/* yes, an element is available */
			/* check first if a newer element is available since more than it is configured in DELAY_DISMISS_OLD_PACK_PER_DEV */
			if ((nextDataPacketToSendAvailable[deviceNr] == true) && (nextDataPacketToSend[deviceNr].wirelessPackage.sysTime + delayTillDismissPack[deviceNr] < millis()))
			{
				/* yes, time is over for this packet - remove it, take next package */
				elementAvailable[deviceNr] = false;
				/* free its data buffer */
				setDataBufferFree(currElementPerDevice[deviceNr].wirelessPackage.payload);
				/* increment statistical counters */
				incrementSentAttemptCounters(&currElementPerDevice[deviceNr]);
				/* print out warning that an package had to be deleted */
				static char infoBuf[128];	/* check parameter DELAY_DISMISS_OLD_PACK_PER_DEV if this message occurs often */
				sprintf(infoBuf, "deleted package because a newer package is available on device %u, check configuration if this message occurs often", deviceNr);
				showInfo(__FUNCTION__, infoBuf);
				/* continue with next loop iteration to get the next element */
				continue;
			}
			/* check if an acknowledge for this package has been received */
			discardPackage = false;
			for (cnt = 0; cnt < numOfElementsInAckArray; cnt++)
			{
				/* check if an acknowledge was received for this package */
				if ((currElementPerDevice[deviceNr].wirelessPackage.devNum == ackArray[cnt].devNum) && (currElementPerDevice[deviceNr].wirelessPackage.sysTime == ackArray[cnt].sysTime))
				{
					/* received acknowledge for this package */
					discardPackage = true;
					break;
				}
			}
			if (discardPackage == true)
			{
				/* package can be discarded, because acknowledge has been received */
				elementAvailable[deviceNr] = false;
				setDataBufferFree(currElementPerDevice[deviceNr].wirelessPackage.payload);
				/* increment statistical counters */
				incrementSentAttemptCounters(&currElementPerDevice[deviceNr]);
				/* continue with next loop iteration to get the next element */
				continue;
			}
			else
			{
				/* send wireless package if it should be sent again, depending on the configuration */
				if (sendWirelessDataPackage(&currElementPerDevice[deviceNr], deviceNr) == true)
				{
					/* package can be discarded, free up memory */
					elementAvailable[deviceNr] = false;
					setDataBufferFree(currElementPerDevice[deviceNr].wirelessPackage.payload);
					/* increment statistical counters */
					incrementSentAttemptCounters(&currElementPerDevice[deviceNr]);
					/* continue with next loop iteration to get the next element */
					continue;
				}
				else
				{
					/* nothing to do currently, leave this loop */
					break;
				}
			}
		}
		else
		{
			/* no element available => check if there is one in the buffer that we can get */
			if (nextDataPacketToSendAvailable[deviceNr] == true)
			{
				/* there is one available, get this and reset the flag */
				currElementPerDevice[deviceNr] = nextDataPacketToSend[deviceNr];
				nextDataPacketToSendAvailable[deviceNr] = false;
				/* got element */
				elementAvailable[deviceNr] = true;
			}
			else
			{
				/* no element available, leave loop */
				break;
			}
		}
	}
}


/*!
* \fn static void sendWirelessAckPackage(tWirelessAckSendPackSt* pWirAckPack)
* \brief Sends a single receive acknowledge packet to the desired wireless connection.
* \param pWirAckPack: Pointer to acknowledge packet structure.
*/
static void sendWirelessAckPackage(tWirelessAckSendPackSt* pWirAckPack)
{
	/* get queue this package needs to be sent to */
	Queue* pWirelessSendQueue = &queueWirelessTransmitUart[pWirAckPack->wirelessConnToSendTo];

	/* check if there is enough space in the queue. If so, send the data. */
	if ((QUEUE_NUM_OF_CHARS_WL_TX_QUEUE - pWirelessSendQueue->nbRecs()) > (PACKAGE_HEADER_SIZE + pWirAckPack->wirelessPackage.payloadSize + 10)) /* header size plus payload plus 8 bytes reserve for replecement chars and 2 byte crc16 payload*/
	{
		/* send package to queue */
		sendPackageToWirelessQueue(pWirelessSendQueue, &pWirAckPack->wirelessPackage);
#if GENERATE_DEBUG_OUTPUT > 0
		char infoBuf[128];
		sprintf(infoBuf, "sending ACK package, device %u; systemtime: %lu", pWirAckPack->wirelessPackage.devNum, millis());
		showInfo(__FUNCTION__, infoBuf);
#endif /* GENERATE_DEBUG_OUTPUT */
		numOfSentWirelessAckPack[pWirAckPack->wirelessConnToSendTo]++;
	}
	else
	{
		/* there wasn't enough space in the queue */
		char warnBuf[128];
		sprintf(warnBuf, "Discard wireless acknowledge package, not enough space in wireless transmit queue, wireless connection %u", (unsigned int)pWirAckPack->wirelessConnToSendTo);
		showWarning(__FUNCTION__, warnBuf);
	}
	/* free allocated memory */
	setAckBufferFree(pWirAckPack->wirelessPackage.payload);
}


/*!
* \fn void wirelessAckSendHandler_TaskEntry(void)
* \brief Task that takes care that the receive acknowledges are sent back as fast as possible.
*/
void wirelessAckSendHandler_TaskEntry(void)
{
	/* check if there are new receive acknowledges to send out. If so, send them out. */
	tWirelessAckSendPackSt wAckPackage;
	while (queueWirelessAckPack.pull(&wAckPackage))
	{
		sendWirelessAckPackage(&wAckPackage);
	}
}


/*!
* \fn void wirelessDataSendHandler_TaskEntry(void)
* \brief Task that takes care that the packages created by the package generator are sent via the corresponding wireless interface(s) based on the configuration.
*/
void wirelessDataSendHandler_TaskEntry(void)
{
	/* check if there are packages to be put in the send buffer */
	uint8_t cnt;
	for (cnt = 0; cnt < NUM_OF_DEVICE_CONNECTIONS; cnt++)
	{
		if ((nextDataPacketToSendAvailable[cnt] == false) && (queueWirelessDataPackPerDev[cnt].pull(&nextDataPacketToSend[cnt].wirelessPackage) == true))
		{
			/* there is space available plus there is a packet available */
			/* if everything is 0, the prio will be incrementet to 1 at the first call of sendWirelessPackage */
			nextDataPacketToSend[cnt].currentPrioConnection = 0;
			nextDataPacketToSend[cnt].sendAttemptsLeftPerWirelessConnection[0] = 0;
			nextDataPacketToSend[cnt].sendAttemptsLeftPerWirelessConnection[1] = 0;
			nextDataPacketToSend[cnt].sendAttemptsLeftPerWirelessConnection[2] = 0;
			nextDataPacketToSend[cnt].sendAttemptsLeftPerWirelessConnection[3] = 0;
			nextDataPacketToSend[cnt].totalNumberOfSendAttemptsPerWirelessConnection[0] = 0;
			nextDataPacketToSend[cnt].totalNumberOfSendAttemptsPerWirelessConnection[1] = 0;
			nextDataPacketToSend[cnt].totalNumberOfSendAttemptsPerWirelessConnection[2] = 0;
			nextDataPacketToSend[cnt].totalNumberOfSendAttemptsPerWirelessConnection[3] = 0;
			/* set flag that packet is available */
			nextDataPacketToSendAvailable[cnt] = true;
		}
	}

	/* check if there are some receive acknowledgements in the corresponding queue */
	sWiReceiveAck ackArray[QUEUE_NUM_OF_ACK];
	uint8_t numOfElementsInAckArray = 0;
	while (queueRecAck.pull(&ackArray[numOfElementsInAckArray]))
	{
		numOfElementsInAckArray++;
	}

	/* go through the internal buffer and check if some of those messages were acknowledged. */
	/* If not, try to send them again or dismiss the message, depending on the configuration, considering device priority. */
	for (cnt = 0; cnt < NUM_OF_DEVICE_CONNECTIONS; cnt++)
	{
		sendResendOrDiscardDataPackage(ackArray, numOfElementsInAckArray, cnt);
	}
}


