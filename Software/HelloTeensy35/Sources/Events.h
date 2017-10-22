/* ###################################################################
**     Filename    : Events.h
**     Project     : HelloTeensy35
**     Processor   : MK64FX512VLQ12
**     Component   : Events
**     Version     : Driver 01.00
**     Compiler    : GNU C Compiler
**     Date/Time   : 2017-10-04, 11:14, # CodeGen: 12
**     Abstract    :
**         This is user's event module.
**         Put your event handler code here.
**     Contents    :
**         Timer_1sec - void Timer_1sec(LDD_TUserData *UserDataPtr);
**         Cpu_OnNMI  - void Cpu_OnNMI(void);
**
** ###################################################################*/
/*!
** @file Events.h
** @version 01.00
** @brief
**         This is user's event module.
**         Put your event handler code here.
*/         
/*!
**  @addtogroup Events_module Events module documentation
**  @{
*/         

#ifndef __Events_H
#define __Events_H
/* MODULE Events */

#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "TU1.h"
#include "Led.h"
#include "BitIoLdd1.h"
#include "SDHC1.h"

#ifdef __cplusplus
extern "C" {
#endif 

/*
** ===================================================================
**     Event       :  Timer_1sec (module Events)
**
**     Component   :  TU1 [TimerUnit_LDD]
*/
/*!
**     @brief
**         Called if counter overflow/underflow or counter is
**         reinitialized by modulo or compare register matching.
**         OnCounterRestart event and Timer unit must be enabled. See
**         [SetEventMask] and [GetEventMask] methods. This event is
**         available only if a [Interrupt] is enabled.
**     @param
**         UserDataPtr     - Pointer to the user or
**                           RTOS specific data. The pointer passed as
**                           the parameter of Init method.
*/
/* ===================================================================*/
void Timer_1sec(LDD_TUserData *UserDataPtr);

/*
** ===================================================================
**     Event       :  Cpu_OnNMI (module Events)
**
**     Component   :  Cpu [MK64FN1M0LQ12]
*/
/*!
**     @brief
**         This event is called when the Non maskable interrupt had
**         occurred. This event is automatically enabled when the [NMI
**         interrupt] property is set to 'Enabled'.
*/
/* ===================================================================*/
void Cpu_OnNMI(void);


/*
** ===================================================================
**     Event       :  SDHC1_OnCardInserted (module Events)
**
**     Component   :  SDHC1 [SDHC_LDD]
*/
/*!
**     @brief
**         This event is called when a card is inserted into the slot.
**         The card identification number is retrieved and it is passed
**         to the event. If card detection pin is not available, the
**         DetectCards method calls this event.
**     @param
**         UserDataPtr     - Pointer to the user data
**                           structure.
**     @param
**         Id              - Card identification number of the inserted
**                           card.
*/
/* ===================================================================*/
void SDHC1_OnCardInserted(LDD_TUserData *UserDataPtr, uint8_t Id);

/*
** ===================================================================
**     Event       :  SDHC1_OnCardRemoved (module Events)
**
**     Component   :  SDHC1 [SDHC_LDD]
*/
/*!
**     @brief
**         This event is called after a card is removed. The card
**         identification number is retrieved and it is passed to the
**         event. If card detection pin is not available, the
**         SelectCard method calls this event after a try to select the
**         removed card.
**     @param
**         UserDataPtr     - Pointer to the user data
**                           structure.
**     @param
**         Id              - Card identification number of the removed
**                           card.
*/
/* ===================================================================*/
void SDHC1_OnCardRemoved(LDD_TUserData *UserDataPtr, uint8_t Id);

/*
** ===================================================================
**     Event       :  SDHC1_OnFinished (module Events)
**
**     Component   :  SDHC1 [SDHC_LDD]
*/
/*!
**     @brief
**         This event is called after an operation, initiated by user,
**         has finished.
**     @param
**         UserDataPtr     - Pointer to the user data
**                           structure.
*/
/* ===================================================================*/
void SDHC1_OnFinished(LDD_TUserData *UserDataPtr);

/* END Events */

#ifdef __cplusplus
}  /* extern "C" */
#endif 

#endif 
/* ifndef __Events_H*/
/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.5 [05.21]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
