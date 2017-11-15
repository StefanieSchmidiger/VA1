/*
 * PackageHandler.h
 *
 *  Created on: 07.11.2017
 *      Author: Stefanie
 */

#ifndef HEADERS_PACKAGEHANDLER_H_
#define HEADERS_PACKAGEHANDLER_H_

#include <stdint.h>
#include "SpiHandler.h"


/*! \def PACK_TYPE_XX
*  \brief Definition for the different available package types.
*/
#define PACK_TYPE_DATA_PACKAGE						(0x01)
#define PACK_TYPE_REC_ACKNOWLEDGE					(0x02)

/*! \def PACK_START
*  \brief Definition of the mark of a beginn of a wireless package.
*/
#define PACK_START									((uint8_t)'\e')

/*! \def PACK_REP
*  \brief If a PACK_START character is within the data, it will be replaced by PACK_REP PACK_START PACK_REP.
*/
#define PACK_REP									((uint8_t)'"')

/*! \def PACK_FILL
*  \brief Filling character if some is needed.
*/
#define PACK_FILL									((uint8_t)' ')




/*! \def PACKAGE_HEADER_SIZE
*  \brief Size of wireless package header in bytes - see tWirelessPackage without payload stuff plus sizeof PACK_START
*/
#define PACKAGE_HEADER_SIZE							(11)



/*! \def PACKAGE_MAX_PAYLOAD_SIZE
*  \brief Maximal size of payload.
*/
#define PACKAGE_MAX_PAYLOAD_SIZE					(512)




/*! \struct sWirelessPackage
*  \brief Structure that holds all the required information of a wireless package.
*/
typedef struct sWirelessPackage
{
	/* --- payload of package --- */
	// header
	uint8_t packType;
	uint8_t devNum;
	uint8_t sessionNr;
	uint32_t sysTime;
	uint16_t payloadSize;
	uint8_t crc8Header;
	// data
	uint8_t* payload;
	uint16_t crc16payload;
	/* internal information, needed for (re)sending package */
	uint8_t currentPrioConnection;
	uint8_t sendAttemptsLeftPerWirelessConnection[NUMBER_OF_UARTS];
	uint32_t timestampLastSendAttempt[NUMBER_OF_UARTS];	/* holds the timestamp when the packet was sent the last time for every wireless connection */
	uint16_t totalNumberOfSendAttemptsPerWirelessConnection[NUMBER_OF_UARTS];		/* to save the total number of send attempts that were needed for this package */

} tWirelessPackage;



void packageHandler_TaskEntry(void* p);
void packageHandler_TaskInit(void);
BaseType_t popReceivedPackFromQueue(tUartNr uartNr, tWirelessPackage *pPackage);
uint16_t numberOfPacksInReceivedPacksQueue(tUartNr uartNr);



#endif /* HEADERS_PACKAGEHANDLER_H_ */
