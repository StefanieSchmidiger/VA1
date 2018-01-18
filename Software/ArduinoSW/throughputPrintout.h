// throughputPrintout.h

#ifndef _THROUGHPUTPRINTOUT_h
#define _THROUGHPUTPRINTOUT_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif


/*! \var numOfSentBytesWirelessConn
*  \brief To save the number of sent bytes per wireless connection.
*/
extern uint32_t numOfSentBytesWirelessConn[];

/*! \var numOfRecBytesWirelessConn
*  \brief To save the number of received bytes per wireless connection.
*/
extern uint32_t numOfRecBytesWirelessConn[];


/*! \var numOfSentWirelessDataPack
*  \brief To save the number of sent wireless data packages.
*/
extern uint32_t numOfSentWirelessDataPack[];

/*! \var numOfSentWirelessAckPack
*  \brief To save the number of sent wireless acknowledge packages.
*/
extern uint32_t numOfSentWirelessAckPack[];

/*! \var numOfValidRecWirelessDataPack
*  \brief To save the number valid wireless data packages, that were received.
*/
extern uint32_t numOfValidRecWirelessDataPack[];

/*! \var numOfValidRecWirelessAckPack
*  \brief To save the number valid wireless acknowledge packages, that were received.
*/
extern uint32_t numOfValidRecWirelessAckPack[];

/*! \var numOfInvalidRecWirelessPack
*  \brief To save the number invalid wireless packages, that were received.
*/
extern uint32_t numOfInvalidRecWirelessPack[];





/*!
* \fn void updateAvPayloadSizeSentDataPack(uint8_t wirelessConnection, uint16_t payloadPackage)
* \brief Updates the average payload of the sent data packages.
*			This function should be called from the wireless send handler.
* \param wirelessConnection: Used wireless connection, needs to be between 0 and NUM_OF_WIRELESS_CONNECTIONS - 1.
* \param payloadSizePackage: Payload size of current package.
*/
void updateAvPayloadSizeSentDataPack(uint8_t wirelessConnection, uint16_t payloadSizePackage);

/*!
* \fn void updateAvPayloadSizeRecDataPack(uint8_t wirelessConnection, uint16_t payloadPackage)
* \brief Updates the average payload of the received data packages.
*			This function should be called from the wireless package extractor.
* \param wirelessConnection: Used wireless connection, needs to be between 0 and NUM_OF_WIRELESS_CONNECTIONS - 1.
* \param payloadSizePackage: Payload size of current package.
*/
void updateAvPayloadSizeRecDataPack(uint8_t wirelessConnection, uint16_t payloadSizePackage);

/*!
* \fn void updateAvSentAttemptsPerWirelessConnection(uint8_t wirelessConnection, uint16_t sentAttempts)
* \brief Updates the average sent attempts that were executed per wireless connection per package.
*			This function should be called from the wireless send handler.
*			This function should only be called if sentAttempts is > 0
* \param wirelessConnection: Used wireless connection, needs to be between 0 and NUM_OF_WIRELESS_CONNECTIONS - 1.
* \param sentAttempts: Number of sent attempts of this wireless connection.
*/
void updateAvSentAttemptsPerWirelessConnection(uint8_t wirelessConnection, uint16_t sentAttempts);



/*!
* \fn static void genThroughputPrintout_TaskEntry(void)
* \brief Task to printout throughput information if enabled.
*/
void genThroughputPrintout_TaskEntry(void);


#endif

