/* ###################################################################
**     Filename    : ProcessorExpert.c
**     Project     : ProcessorExpert
**     Processor   : MK64FN1M0VMD12
**     Version     : Driver 01.01
**     Compiler    : GNU C Compiler
**     Date/Time   : 2014-02-28, 17:34, # CodeGen: 0
**     Abstract    :
**         Main module.
**         This module contains user's application code.
**     Settings    :
**     Contents    :
**         No public methods
**
** ###################################################################*/
/*!
** @file ProcessorExpert.c
** @version 01.01
** @brief
**         Main module.
**         This module contains user's application code.
*/         
/*!
**  @addtogroup ProcessorExpert_module ProcessorExpert module documentation
**  @{
*/         
/* MODULE ProcessorExpert */


/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
#include "LED1.h"
#include "LEDpin1.h"
#include "BitIoLdd1.h"
#include "LED2.h"
#include "LEDpin2.h"
#include "BitIoLdd2.h"
#include "LED3.h"
#include "LEDpin3.h"
#include "BitIoLdd3.h"
#include "LED4.h"
#include "LEDpin4.h"
#include "BitIoLdd4.h"
#include "WAIT1.h"
#include "UTIL1.h"
#include "FRTOS1.h"
#include "TMOUT1.h"
#include "CS1.h"
#include "CLS1.h"
#include "AS1.h"
#include "ASerialLdd1.h"
#include "FAT1.h"
#include "TmDt1.h"
#include "KEY1.h"
#include "Inhr1.h"
#include "BitIoLdd7.h"
#include "Inhr2.h"
#include "BitIoLdd8.h"
#include "TRG1.h"
#include "MMA1.h"
#include "GI2C1.h"
#include "I2C.h"
#include "SD1.h"
#include "SS1.h"
#include "CD2.h"
#include "SM1.h"
#include "KSDK1.h"
#include "XF1.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "PDD_Includes.h"
#include "Init_Config.h"

/* User includes (#include below this line is not maintained by Processor Expert) */
#include "Application.h"

/*lint -save  -e970 Disable MISRA rule (6.3) checking. */
int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
  /* Write your local variable definition here */

  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  /* enable internal pull-ups */
  /* SD card detect: PTB20 */
  PORT_PDD_SetPinPullSelect(PORTB_BASE_PTR, 20, PORT_PDD_PULL_UP);
  PORT_PDD_SetPinPullEnable(PORTB_BASE_PTR, 20, PORT_PDD_PULL_ENABLE);
  /* SW1: PTC6 */
  PORT_PDD_SetPinPullSelect(PORTC_BASE_PTR, 6, PORT_PDD_PULL_UP);
  PORT_PDD_SetPinPullEnable(PORTC_BASE_PTR, 6, PORT_PDD_PULL_ENABLE);
  /* SW3: PTA4 */
  PORT_PDD_SetPinPullSelect(PORTA_BASE_PTR, 4, PORT_PDD_PULL_UP);
  PORT_PDD_SetPinPullEnable(PORTA_BASE_PTR, 4, PORT_PDD_PULL_ENABLE);

  LED1_Neg(); WAIT1_Waitms(50);
  LED2_Neg(); WAIT1_Waitms(50);
  LED3_Neg(); WAIT1_Waitms(50);
  LED4_Neg(); WAIT1_Waitms(50);
  APP_Start();

  /*** Don't write any code pass this line, or it will be deleted during code generation. ***/
  /*** RTOS startup code. Macro PEX_RTOS_START is defined by the RTOS component. DON'T MODIFY THIS CODE!!! ***/
  #ifdef PEX_RTOS_START
    PEX_RTOS_START();                  /* Startup of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
  /*** End of RTOS startup code.  ***/
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;){}
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

/* END ProcessorExpert */
/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.3 [05.08]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
