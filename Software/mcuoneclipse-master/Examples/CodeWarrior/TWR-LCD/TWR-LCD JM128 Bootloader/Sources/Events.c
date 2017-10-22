/** ###################################################################
**     Filename  : Events.c
**     Project   : ProcessorExpert
**     Processor : MCF51JM128VLH
**     Component : Events
**     Version   : Driver 01.02
**     Compiler  : CodeWarrior ColdFireV1 C Compiler
**     Date/Time : 2011-03-12, 10:15, # CodeGen: 0
**     Abstract  :
**         This is user's event module.
**         Put your event handler code here.
**     Settings  :
**     Contents  :
**         No public methods
**
** ###################################################################*/
/* MODULE Events */

#include "Cpu.h"
#include "Events.h"

/* User includes (#include below this line is not maintained by Processor Expert) */
#include "Bootloader.h"

/*
** ===================================================================
**     Event       :  S191_OnSRecord (module Events)
**
**     Component   :  S191 [S19]
**     Description :
**         Event called for every S-Record
**     Parameters  :
**         NAME            - DESCRIPTION
**         type            - type of S-Record (as character), e.g. '3'
**       * dataBuf         - Pointer to buffer of S-Record data
**                           (in binary form)
**         dataBufLenght   - Size in bytes of the
**                           data buffer
**     Returns     : Nothing
** ===================================================================
*/
void S191_OnSRecord(uint8_t *returnCode, uint8_t type, uint32_t addr, uint8_t *dataBuf, uint8_t dataBufSize, void *data)
{
  BL_OnSRecord(returnCode, type, addr, dataBuf, dataBufSize, data);
}

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
void S191_OnError(S191_ErrorCode errorCode, S191_ParserStruct *iteratorInfo)
{
  /* place breakpoint in error hook */
}

/* END Events */

/*
** ###################################################################
**
**     This file was created by Processor Expert 5.00 [04.48]
**     for the Freescale ColdFireV1 series of microcontrollers.
**
** ###################################################################
*/
