// 
// 
// 

#include "throughputPrintout.h"
#include "serialSwitch_General.h"
#include "errorAndWarningOutput.h"



/*! \var numOfSentBytesWirelessConn
*  \brief To save the number of sent bytes per wireless connection.
*/
uint32_t numOfSentBytesWirelessConn[NUM_OF_WIRELESS_CONNECTIONS];

/*! \var numOfRecBytesWirelessConn
*  \brief To save the number of received bytes per wireless connection.
*/
uint32_t numOfRecBytesWirelessConn[NUM_OF_WIRELESS_CONNECTIONS];



/*! \var numOfSentWirelessDataPack
*  \brief To save the number of sent wireless data packages.
*/
uint32_t numOfSentWirelessDataPack[NUM_OF_WIRELESS_CONNECTIONS];

/*! \var numOfSentWirelessAckPack
*  \brief To save the number of sent wireless acknowledge packages.
*/
uint32_t numOfSentWirelessAckPack[NUM_OF_WIRELESS_CONNECTIONS];

/*! \var numOfValidRecWirelessDataPack
*  \brief To save the number valid wireless data packages, that were received.
*/
uint32_t numOfValidRecWirelessDataPack[NUM_OF_WIRELESS_CONNECTIONS];

/*! \var numOfValidRecWirelessAckPack
*  \brief To save the number valid wireless acknowledge packages, that were received.
*/
uint32_t numOfValidRecWirelessAckPack[NUM_OF_WIRELESS_CONNECTIONS];

/*! \var numOfInvalidRecWirelessPack
*  \brief To save the number invalid wireless packages, that were received.
*/
uint32_t numOfInvalidRecWirelessPack[NUM_OF_WIRELESS_CONNECTIONS];



/*! \var avPayloadSizeSentDataPack
*  \brief To save the average payload size of the sent data packages per wireless connection.
*			Because we're using fix comma, the content will be saved as average payload size*1000
*/
static uint32_t avPayloadSizeSentDataPack[NUM_OF_WIRELESS_CONNECTIONS];

/*! \var avPayloadSizeRecDataPack
*  \brief To save the average payload size of the received data packages per wireless connection.
*			Because we're using fix comma, the content will be saved as average payload size*1000
*/
static uint32_t avPayloadSizeRecDataPack[NUM_OF_WIRELESS_CONNECTIONS];


/*! \var avSentAttemptsWirelessDataPack
*  \brief To save the average sent attempts per wireless connection.
*			Because we're using fix comma, the content will be saved as average sent attempts*1000
*/
static uint16_t avSentAttemptsWirelessDataPack[NUM_OF_WIRELESS_CONNECTIONS];



/*!
* \fn void updateAvPayloadSizeSentDataPack(uint8_t wirelessConnection, uint16_t payloadPackage)
* \brief Updates the average payload of the sent data packages.
*			This function should be called from the wireless send handler.
* \param wirelessConnection: Used wireless connection, needs to be between 0 and NUM_OF_WIRELESS_CONNECTIONS - 1.
* \param payloadSizePackage: Payload size of current package.
*/
void updateAvPayloadSizeSentDataPack(uint8_t wirelessConnection, uint16_t payloadSizePackage)
{
	/* check validty of parameters */
	if ((wirelessConnection >= NUM_OF_WIRELESS_CONNECTIONS) || (payloadSizePackage >= PACKAGE_MAX_PAYLOAD_SIZE))
	{
		showError(__FUNCTION__, "invalid parameter, probably an implementation error");
	}
	/* check if average was already assigned a first time */
	if (avPayloadSizeSentDataPack[wirelessConnection] > 0)
	{
		/* yes, init was done - average is built using an IIR filter with coefficients b0 = 0.95 and a1 = 0.05 (all *1000 because we're using fix comma) */
		avPayloadSizeSentDataPack[wirelessConnection] = (avPayloadSizeSentDataPack[wirelessConnection] * 950 + 500) / 1000  + payloadSizePackage * 50;	/* +500 to round properly */
	}
	else
	{
		/* not assigned yet => init variable */
		avPayloadSizeSentDataPack[wirelessConnection] = payloadSizePackage*1000;
	}
}




/*!
* \fn void updateAvPayloadSizeRecDataPack(uint8_t wirelessConnection, uint16_t payloadPackage)
* \brief Updates the average payload of the received data packages.
*			This function should be called from the wireless package extractor.
* \param wirelessConnection: Used wireless connection, needs to be between 0 and NUM_OF_WIRELESS_CONNECTIONS - 1.
* \param payloadSizePackage: Payload size of current package.
*/
void updateAvPayloadSizeRecDataPack(uint8_t wirelessConnection, uint16_t payloadSizePackage)
{
	/* check validty of parameters */
	if ((wirelessConnection >= NUM_OF_WIRELESS_CONNECTIONS) || (payloadSizePackage >= PACKAGE_MAX_PAYLOAD_SIZE))
	{
		showError(__FUNCTION__, "invalid parameter, probably an implementation error");
	}
	/* check if average was already assigned a first time */
	if (avPayloadSizeRecDataPack[wirelessConnection] > 0)
	{
		/* yes, init was done - average is built using an IIR filter with coefficients b0 = 0.95 and a1 = 0.05 (all *1000 because we're using fix comma) */
		avPayloadSizeRecDataPack[wirelessConnection] = (avPayloadSizeRecDataPack[wirelessConnection] * 950 + 500) / 1000 + payloadSizePackage * 50;	/* +500 to round properly */
	}
	else
	{
		/* not assigned yet => init variable */
		avPayloadSizeRecDataPack[wirelessConnection] = payloadSizePackage;
	}
}




/*!
* \fn void updateAvSentAttemptsPerWirelessConnection(uint8_t wirelessConnection, uint16_t sentAttempts)
* \brief Updates the average sent attempts that were executed per wireless connection per package.
*			This function should be called from the wireless send handler.
*			This function should only be called if sentAttempts is > 0
* \param wirelessConnection: Used wireless connection, needs to be between 0 and NUM_OF_WIRELESS_CONNECTIONS - 1.
* \param sentAttempts: Number of sent attempts of this wireless connection.
*/
void updateAvSentAttemptsPerWirelessConnection(uint8_t wirelessConnection, uint16_t sentAttempts)
{
	/* check validty of parameters */
	if ((wirelessConnection >= NUM_OF_WIRELESS_CONNECTIONS) || (sentAttempts == 0))
	{
		showError(__FUNCTION__, "invalid parameter, probably an implementation error");
	}
	/* check if average was already assigned a first time */
	if (avSentAttemptsWirelessDataPack[wirelessConnection] > 0)
	{
		/* yes, init was done - average is built using an IIR filter with coefficients b0 = 0.95 and a1 = 0.05 (all *1000 because we're using fix comma) */
		avSentAttemptsWirelessDataPack[wirelessConnection] = (avSentAttemptsWirelessDataPack[wirelessConnection] * 950 + 500) / 1000 + sentAttempts * 50;	/* +500 to round properly */
	}
	else
	{
		/* not assigned yet => init variable */
		avSentAttemptsWirelessDataPack[wirelessConnection] = sentAttempts * 1000;
	}
}



/*!
* \fn static void genThroughputPrintout_TaskEntry(void)
* \brief Task to printout throughput information if enabled.
*/
void genThroughputPrintout_TaskEntry(void)
{
	/* Print out throughput info */
	static char infoBuf[150];
	sprintf(infoBuf, "Wireless conn. 0-3. Sent bytes [bytes/s]: %lu,%lu,%lu,%lu; Received bytes: [bytes/s] %lu,%lu,%lu,%lu", 
		(uint32_t)((numOfSentBytesWirelessConn[0] * ((1000 << 16) / GENERATE_THROUGHPUT_OUTPUT_INTERVAL)) >> 16),	/* bitshifting stuff is workarount in order to prevent that float is needed */
		(uint32_t)((numOfSentBytesWirelessConn[1] * ((1000 << 16) / GENERATE_THROUGHPUT_OUTPUT_INTERVAL)) >> 16),
		(uint32_t)((numOfSentBytesWirelessConn[2] * ((1000 << 16) / GENERATE_THROUGHPUT_OUTPUT_INTERVAL)) >> 16),
		(uint32_t)((numOfSentBytesWirelessConn[3] * ((1000 << 16) / GENERATE_THROUGHPUT_OUTPUT_INTERVAL)) >> 16),
		(uint32_t)((numOfRecBytesWirelessConn[0] * ((1000 << 16) / GENERATE_THROUGHPUT_OUTPUT_INTERVAL)) >> 16),
		(uint32_t)((numOfRecBytesWirelessConn[1] * ((1000 << 16) / GENERATE_THROUGHPUT_OUTPUT_INTERVAL)) >> 16),
		(uint32_t)((numOfRecBytesWirelessConn[2] * ((1000 << 16) / GENERATE_THROUGHPUT_OUTPUT_INTERVAL)) >> 16),
		(uint32_t)((numOfRecBytesWirelessConn[3] * ((1000 << 16) / GENERATE_THROUGHPUT_OUTPUT_INTERVAL)) >> 16));
	showInfo(__FUNCTION__, infoBuf);

	/* reset counters to 0 */
	memset(numOfSentBytesWirelessConn, 0, sizeof(uint32_t)*NUM_OF_WIRELESS_CONNECTIONS);
	memset(numOfRecBytesWirelessConn, 0, sizeof(uint32_t)*NUM_OF_WIRELESS_CONNECTIONS);

	/* print out package info */
	sprintf(infoBuf, "Wireless conn. 0-3. Sent data packages: %lu,%lu,%lu,%lu; Sent acknowledges: %lu,%lu,%lu,%lu",
		numOfSentWirelessDataPack[0], numOfSentWirelessDataPack[1], numOfSentWirelessDataPack[2], numOfSentWirelessDataPack[3],
		numOfSentWirelessAckPack[0], numOfSentWirelessAckPack[1], numOfSentWirelessAckPack[2], numOfSentWirelessAckPack[3]);
	showInfo(__FUNCTION__, infoBuf);
	sprintf(infoBuf, "Wireless conn. 0-3. Received valid acknowledges: %lu,%lu,%lu,%lu; Received valid data packages: %lu,%lu,%lu,%lu; Received invalid packages: %lu,%lu,%lu,%lu",
		numOfValidRecWirelessAckPack[0], numOfValidRecWirelessAckPack[1], numOfValidRecWirelessAckPack[2], numOfValidRecWirelessAckPack[3],
		numOfValidRecWirelessDataPack[0], numOfValidRecWirelessDataPack[1], numOfValidRecWirelessDataPack[2], numOfValidRecWirelessDataPack[3],
		numOfInvalidRecWirelessPack[0], numOfInvalidRecWirelessPack[1], numOfInvalidRecWirelessPack[2], numOfInvalidRecWirelessPack[3]);
	showInfo(__FUNCTION__, infoBuf);

	/* print out average payload size */
	sprintf(infoBuf, "Wireless conn. 0-3. Average payload size [bytes] sent packages: %u.%u, %u.%u, %u.%u, %u.%u; received packages: %u.%u, %u.%u, %u.%u, %u.%u",
		(uint16_t)avPayloadSizeSentDataPack[0] / 1000, (uint16_t)(avPayloadSizeSentDataPack[0] % 1000) / 100,
		(uint16_t)avPayloadSizeSentDataPack[1] / 1000, (uint16_t)(avPayloadSizeSentDataPack[1] % 1000) / 100,
		(uint16_t)avPayloadSizeSentDataPack[2] / 1000, (uint16_t)(avPayloadSizeSentDataPack[2] % 1000) / 100,
		(uint16_t)avPayloadSizeSentDataPack[3] / 1000, (uint16_t)(avPayloadSizeSentDataPack[3] % 1000) / 100,
		(uint16_t)avPayloadSizeRecDataPack[0] / 1000, (uint16_t)(avPayloadSizeRecDataPack[0] % 1000) / 100,
		(uint16_t)avPayloadSizeRecDataPack[1] / 1000, (uint16_t)(avPayloadSizeRecDataPack[1] % 1000) / 100,
		(uint16_t)avPayloadSizeRecDataPack[2] / 1000, (uint16_t)(avPayloadSizeRecDataPack[2] % 1000) / 100,
		(uint16_t)avPayloadSizeRecDataPack[3] / 1000, (uint16_t)(avPayloadSizeRecDataPack[3] % 1000) / 100);
	showInfo(__FUNCTION__, infoBuf);

	/* print out average sent attempts per wireless connection */
	sprintf(infoBuf, "Wireless conn. 0-3. Average needed sent attempts per data package: %u.%u, %u.%u, %u.%u, %u.%u",
		(uint16_t)avSentAttemptsWirelessDataPack[0] / 1000, (uint16_t)(avSentAttemptsWirelessDataPack[0] % 1000) / 100,
		(uint16_t)avSentAttemptsWirelessDataPack[1] / 1000, (uint16_t)(avSentAttemptsWirelessDataPack[1] % 1000) / 100,
		(uint16_t)avSentAttemptsWirelessDataPack[2] / 1000, (uint16_t)(avSentAttemptsWirelessDataPack[2] % 1000) / 100,
		(uint16_t)avSentAttemptsWirelessDataPack[3] / 1000, (uint16_t)(avSentAttemptsWirelessDataPack[3] % 1000) / 100);
	showInfo(__FUNCTION__, infoBuf);

	/* print an empty line to improved the clarity */
	Serial.println("");
}

