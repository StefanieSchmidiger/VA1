/** ###################################################################
**     Filename    : Events.h
**     Project     : ProcessorExpert
**     Processor   : MKL25Z128VLK4
**     Component   : Events
**     Version     : Driver 01.00
**     Compiler    : GNU C Compiler
**     Date/Time   : 2012-10-04, 09:56, # CodeGen: 0
**     Abstract    :
**         This is user's event module.
**         Put your event handler code here.
**     Settings    :
**     Contents    :
**         Cpu_OnNMIINT - void Cpu_OnNMIINT(void);
**
** ###################################################################*/

#ifndef __Events_H
#define __Events_H
/* MODULE Events */

#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "WAIT1.h"
#include "UTIL1.h"
#include "FAT1.h"
#include "TmDt1.h"
#include "SD1.h"
#include "SS1.h"
#include "SPI2.h"
#include "Clock1.h"
#include "BitIoLdd1.h"
#include "Input1.h"
#include "BitIoLdd2.h"
#include "Output1.h"
#include "BitIoLdd3.h"
#include "I2C2.h"
#include "SDA1.h"
#include "BitIoLdd4.h"
#include "SCL1.h"
#include "BitIoLdd5.h"
#include "TRG1.h"
#include "EVNT1.h"
#include "CLS1.h"
#include "AS1.h"
#include "ASerialLdd1.h"
#include "S191.h"
#include "RNG2.h"
#include "ACCEL1.h"
#include "AD1.h"
#include "AdcLdd1.h"
#include "MMA1.h"
#include "GI2C1.h"
#include "I2C3.h"
#include "CS1.h"
#include "SM1.h"
#include "TMOUT1.h"
#include "PE_LDD.h"

void Cpu_OnNMIINT(void);
/*
** ===================================================================
**     Event       :  Cpu_OnNMIINT (module Events)
**
**     Component   :  Cpu [MKL25Z128LK4]
**     Description :
**         This event is called when the Non maskable interrupt had
**         occurred. This event is automatically enabled when the <NMI
**         interrrupt> property is set to 'Enabled'.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/


/*
** ===================================================================
**     Event       :  SM1_OnBlockSent (module Events)
**
**     Component   :  SM1 [SPIMaster_LDD]
*/
/*!
**     @brief
**         This event is called after the last character from the
**         output buffer is moved to the transmitter. This event is
**         available only if the SendBlock method is enabled.
**     @param
**         UserDataPtr     - Pointer to the user or
**                           RTOS specific data. The pointer is passed
**                           as the parameter of Init method. 
*/
/* ===================================================================*/
void SM1_OnBlockSent(LDD_TUserData *UserDataPtr);


void EVNT1_AppHandleEvent(byte event);
/*
** ===================================================================
**     Event       :  EVNT1_AppHandleEvent (module Events)
**
**     Component   :  EVNT1 [SimpleEvents]
**     Description :
**         
**     Parameters  :
**         NAME            - DESCRIPTION
**         event           - Event (event number) to be processed.
**     Returns     : Nothing
** ===================================================================
*/

void S191_OnSRecord(byte *returnCode, byte type, dword addr, byte *dataBuf, byte dataBufSize, void *data);
/*
** ===================================================================
**     Event       :  S191_OnSRecord (module Events)
**
**     Component   :  S191 [S19]
**     Description :
**         Event called for every S-Record
**     Parameters  :
**         NAME            - DESCRIPTION
**       * returnCode      - Pointer to error code
**         type            - type of S-Record (as character), e.g. '3'
**         addr            - Address of data
**       * dataBuf         - Pointer to buffer of S-Record data
**                           (in binary form)
**         dataBufSize     - Size in bytes of the data
**                           buffer
**       * data            - Pointer to private data
**     Returns     : Nothing
** ===================================================================
*/

void S191_OnError(S191_ErrorCode errorCode, S191_ParserStruct *iteratorInfo);
/*
** ===================================================================
**     Event       :  S191_OnError (module Events)
**
**     Component   :  S191 [S19]
**     Description :
**         Event called in case of an error
**     Parameters  :
**         NAME            - DESCRIPTION
**         errorCode       - 
**       * iteratorInfo    - Pointer to parser info
**                           struct
**     Returns     : Nothing
** ===================================================================
*/

void AD1_OnEnd(void);
/*
** ===================================================================
**     Event       :  AD1_OnEnd (module Events)
**
**     Component   :  AD1 [ADC]
**     Description :
**         This event is called after the measurement (which consists
**         of <1 or more conversions>) is/are finished.
**         The event is available only when the <Interrupt
**         service/event> property is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void AD1_OnCalibrationEnd(void);
/*
** ===================================================================
**     Event       :  AD1_OnCalibrationEnd (module Events)
**
**     Component   :  AD1 [ADC]
**     Description :
**         This event is called when the calibration has been finished.
**         User should check if the calibration pass or fail by
**         Calibration status method./nThis event is enabled only if
**         the <Interrupt service/event> property is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/


void Ptrc1_OnTraceWrap(void);
/*
** ===================================================================
**     Event       :  Ptrc1_OnTraceWrap (module Events)
**
**     Component   :  Ptrc1 [PercepioTrace]
**     Description :
**         Called for trace ring buffer wrap around. This gives the
**         application a chance to dump the trace buffer.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

/* END Events */
#endif /* __Events_H*/

/*
** ###################################################################
**
**     This file was created by Processor Expert 10.0 [05.03]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
