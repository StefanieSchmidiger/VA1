/** ###################################################################
**     Filename  : ProcessorExpert.c
**     Project   : ProcessorExpert
**     Processor : MCF52259CAG80
**     Version   : Driver 01.00
**     Compiler  : CodeWarrior MCF C Compiler
**     Date/Time : 2011-06-26, 07:45, # CodeGen: 0
**     Abstract  :
**         Main module.
**         This module contains user's application code.
**     Settings  :
**     Contents  :
**         No public methods
**
** ###################################################################*/
/* MODULE ProcessorExpert */


/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
#include "UTIL1.h"
#include "FRTOS1.h"
#include "Inhr3.h"
#include "RTOSSWI1.h"
#include "TickCntr1.h"
#include "I2C1.h"
#include "SDA1.h"
#include "SCL1.h"
#include "WAIT1.h"
#include "PCA1.h"
#include "PCA2.h"
#include "TRG1.h"
#include "RFEET.h"
#include "Inhr2.h"
#include "RHIP.h"
#include "Inhr4.h"
#include "LHIP.h"
#include "Inhr5.h"
#include "LFEET.h"
#include "Inhr6.h"
#include "SM1.h"
#include "CS1.h"
#include "IADDR01.h"
#include "FLASH_CS.h"
#include "FLASH_WP.h"
#include "AS1.h"
#include "CLS1.h"
#include "CS2.h"
#include "ACCEL.h"

/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"

/* User includes (#include below this line is not maintained by Processor Expert) */
#include "Application.h"

void main(void) {
  /* Write your local variable definition here */

  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/
  APP_Start();

  /*** Don't write any code pass this line, or it will be deleted during code generation. ***/
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;){}
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

/* END ProcessorExpert */
/*
** ###################################################################
**
**     This file was created by Processor Expert 5.00 [04.48]
**     for the Freescale MCF series of microcontrollers.
**
** ###################################################################
*/
