#ifndef HEADERS_NETWORKHANDLER_H_
#define HEADERS_NETWORKHANDLER_H_

#include "SpiHandler.h"
#include "PackageHandler.h"
#include "FRTOS.h"

/*! \def QUEUE_NUM_OF_WL_PACK
*  \brief Number of wireless packages that should have find space within a single queue.
*/
#define QUEUE_NUM_OF_WL_PACK					10

void networkHandler_TaskEntry(void* p);
void networkHandler_TaskInit(void);
uint16_t numberOfPackagesReadyToSend(tUartNr uartNr);


/*!
* \fn ByseType_t popReadyToSendPackFromQueue(tUartNr uartNr, tWirelessPackage *pPackage)
* \brief Stores a single byte from the selected queue in pData.
* \param uartNr: UART number the package should be transmitted to.
* \param pPackage: The location where the package should be stored
* \return Status if xQueueReceive has been successful, NULL if uartNr was invalid
*/
BaseType_t popReadyToSendPackFromQueue(tUartNr uartNr, tWirelessPackage *pPackage);


#endif
