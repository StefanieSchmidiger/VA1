/** ###################################################################
**     Filename    : Events.c
**     Project     : ProcessorExpert
**     Processor   : MKL25Z128VLK4
**     Component   : Events
**     Version     : Driver 01.00
**     Compiler    : GNU C Compiler
**     Date/Time   : 2013-01-08, 20:25, # CodeGen: 0
**     Abstract    :
**         This is user's event module.
**         Put your event handler code here.
**     Settings    :
**     Contents    :
**         Cpu_OnNMIINT - void Cpu_OnNMIINT(void);
**
** ###################################################################*/
/* MODULE Events */

#include "Cpu.h"
#include "Events.h"

/* User includes (#include below this line is not maintained by Processor Expert) */
#include "Radio.h"

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
void Cpu_OnNMIINT(void)
{
  /* Write your code here ... */
}

/*
** ===================================================================
**     Event       :  SMAC1_ResetIndication (module Events)
**
**     Component   :  TRSVR1 [MC13192]
**     Description :
**         Event in case of transceiver reset.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void SMAC1_ResetIndication(void)
{
  RADIO_ResetIndication();
}

/*
** ===================================================================
**     Event       :  PHY1_DataIndicationPacket (module Events)
**
**     Component   :  PHY1 [SPHY]
**     Description :
**         
**     Parameters  :
**         NAME            - DESCRIPTION
**         sRxPacket       - 
**     Returns     : Nothing
** ===================================================================
*/
void PHY1_DataIndicationPacket(tRxPacket *sRxPacket)
{
  RADIO_DataIndicationPacket(sRxPacket);
}

/*
** ===================================================================
**     Event       :  SMAC1_OnInterrupt (module Events)
**
**     Component   :  TRSVR1 [MC13192]
**     Description :
**         Event raised in case of transceiver interrupt.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void SMAC1_OnInterrupt(void)
{
  /* Write your code here ... */
}

/*
** ===================================================================
**     Event       :  TRSVR1_DataIndication (module Events)
**
**     Component   :  TRSVR1 [MC13192]
**     Description :
**         Event in case a data packet has been received.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void TRSVR1_DataIndication(void)
{
  /* Write your code here ... */
}

/*
** ===================================================================
**     Event       :  TRSVR1_ResetIndication (module Events)
**
**     Component   :  TRSVR1 [MC13192]
**     Description :
**         Event in case of transceiver reset.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void TRSVR1_ResetIndication(void)
{
  /* Write your code here ... */
}

/* END Events */

/*
** ###################################################################
**
**     This file was created by Processor Expert 10.0 [05.03]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
