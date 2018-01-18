// wirelessSendHandler.h

#ifndef _WIRELESSSENDHANDLER_h
#define _WIRELESSSENDHANDLER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <Queue.h>



/*! \def QUEUE_NUM_OF_WL_PACK
*  \brief Number of wireless packages that should have find space within a single queue.
*/
#define QUEUE_NUM_OF_WL_PACK					8



/*! \struct sWiReceiveAck
*  \brief Structure that holds all the required information of a successfully received acknowledge.
*/
typedef struct sWiReceiveAck
{
	uint8_t wirNum;	/* only needed in the case of queueSendAck messages */
	uint8_t devNum;
	uint32_t sysTime;
} tWiReceiveAck;



/*! \var queueWirelessDataPack
*  \brief Queue that holds the wireless data packages that needs to be sent.
*/
extern Queue queueWirelessDataPackPerDev[];

/*! \var queueWirelessAckPack
*  \brief Queue that holds the wireless receive acknowledge packages that needs to be sent.
*/
extern Queue queueWirelessAckPack;

/*! \var queueRecAck
*  \brief Queue where the received valid receive acknowledge packages are put.
*/
extern Queue queueRecAck;


/*!
* \fn void wirelessDataSendHandler_TaskEntry(void)
* \brief Task that takes care that the packages created by the package generator are sent via the corresponding wireless interface(s) based on the configuration.
*/
void wirelessDataSendHandler_TaskEntry(void);

/*!
* \fn void wirelessAckSendHandler_TaskEntry(void)
* \brief Task that takes care that the receive acknowledges are sent back as fast as possible.
*/
void wirelessAckSendHandler_TaskEntry(void);


#endif

