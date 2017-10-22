/** ###################################################################
**     Filename  : ProcessorExpert.c
**     Project   : ProcessorExpert
**     Processor : MCF52259CAG80
**     Version   : Driver 01.00
**     Compiler  : CodeWarrior MCF C Compiler
**     Date/Time : 2010-11-02, 12:47, # CodeGen: 0
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
#include "LCD1.h"
#include "D_Cpin1.h"
#include "SCEpin1.h"
#include "WAIT1.h"
#include "UTIL1.h"
#include "SM1.h"
#include "GDisp1.h"
#include "FRTOS1.h"
#include "RTOSSWI1.h"
#include "TickCntr1.h"
#include "LED2.h"
#include "LEDpin1.h"
#include "LED3.h"
#include "LEDpin2.h"
#include "LED4.h"
#include "LEDpin3.h"
#include "EVNT1.h"
#include "TRG1.h"
#include "BuzzerPPG.h"
#include "Helv08n.h"
#include "Helv10n.h"
#include "Helv12n.h"
#include "Helv14n.h"
#include "Helv18n.h"
#include "Helv24n.h"
#include "Cour08n.h"
#include "Cour08b.h"
#include "Cour10n.h"
#include "FDisp1.h"
#include "TmDt1.h"
#include "UICalendar1.h"
#include "UI1.h"
#include "KEY2.h"
#include "Inhr1.h"
#include "Inhr2.h"
#include "AD1.h"
#include "ACCEL1.h"
#include "TCHS1.h"
#include "Sensor1.h"
#include "Xminus1.h"
#include "Yminus1.h"
#include "Xplus1.h"
#include "Yplus1.h"
#include "I2C1.h"
#include "SDA1.h"
#include "SCL1.h"
#include "FSSH1.h"
#include "AS1.h"
#include "UIG1.h"
#include "CS1.h"
#include "KSDK1.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"

/* User includes (#include below this line is not maintained by Processor Expert) */
#include "Boot.h"

void main(void)
{
  BOOT_PreInit();

  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  /* Write your code here */
  BOOT_Start();

  /*** Don't write any code pass this line, or it will be deleted during code generation. ***/
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;){}
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

/* END ProcessorExpert */
/*
** ###################################################################
**
**     This file was created by Processor Expert 5.00 Beta [04.46]
**     for the Freescale MCF series of microcontrollers.
**
** ###################################################################
*/
