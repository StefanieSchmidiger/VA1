// packageGenerator.h

#ifndef _PACKAGEGENERATOR_h
#define _PACKAGEGENERATOR_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "serialSwitch_General.h"
#include <Queue.h>
#include <TaskScheduler.h>



/*! \struct sWirelessAckSendPackSt
*  \brief Structure that holds the wireless package plus the wireless connection the receive acknowledge needs to be sent to.
*/
typedef struct sWirelessAckSendPackSt
{
	tWirelessPackage wirelessPackage;
	uint8_t wirelessConnToSendTo;
} tWirelessAckSendPackSt;



/*! \var packageGeneratorTask
*  \brief Task handle of package generator task.
*/
extern Task packageGeneratorTask;



/*! \var queueSendAck
*  \brief Queue where acknowledges are placed which should be sent out.
*/
extern Queue queueSendAck;



/*!
* \fn void setDataBufferFree(uint8_t* pDataBuffer)
* \brief Frees a data buffer.
* \return pDataBuffer: Pointer to the data buffer that isn't used any more.
*/
void setDataBufferFree(uint8_t* pDataBuffer);

/*!
* \fn void setAckBufferFree(uint8_t* pDataBuffer)
* \brief Frees a acknowledge data buffer.
* \return pDataBuffer: Pointer to the ack data buffer that isn't used any more.
*/
void setAckBufferFree(uint8_t* pDataBuffer);

/*!
* \fn void packageGenerator_TaskEntry(void)
* \brief Task that reads the incoming data from the devices from the corresponding queues and put together packages to be sent via wireless.
*/
void packageGenerator_TaskEntry(void);


#endif

