/** ###################################################################
**     Filename    : ProcessorExpert.c
**     Project     : ProcessorExpert
**     Processor   : MCF51JM128VLK
**     Version     : Driver 01.00
**     Compiler    : CodeWarrior ColdFireV1 C Compiler
**     Date/Time   : 2012-01-21, 18:57, # CodeGen: 0
**     Abstract    :
**         Main module.
**         This module contains user's application code.
**     Settings    :
**     Contents    :
**         No public methods
**
** ###################################################################*/
/* MODULE ProcessorExpert */


/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
#include "LEDM1.h"
#include "Inhr1.h"
#include "LEDpin1.h"
#include "Inhr2.h"
#include "LEDpin2.h"
#include "Inhr3.h"
#include "LEDpin3.h"
#include "Inhr4.h"
#include "LEDpin4.h"
#include "Inhr5.h"
#include "LEDpin5.h"
#include "Inhr6.h"
#include "LEDpin6.h"
#include "Inhr7.h"
#include "LEDpin7.h"
#include "MCUC1.h"
#include "GDisp1.h"
#include "WAIT1.h"
/* Include shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"

/* User includes (#include below this line is not maintained by Processor Expert) */
static void Update(void) {
  int i, j;	
  
  for(i=0;i<50;i++) {
	for(j=0;j<4;j++) {
      GDisp1_UpdateFull();
	}
    WAIT1_Waitms(5);
  }
}

void main(void)
{
  /* Write your local variable definition here */

  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  for(;;) {
	LEDM1_On(); /* turn whole matrix on */
	LEDM1_Off();  /* ... and off again */

	GDisp1_Clear();
    GDisp1_SetPixel(0,0);
	Update();
	
	GDisp1_ClrPixel(0,0);
	Update();

	GDisp1_SetPixel(3,0);
	Update();

	GDisp1_SetPixel(0,5);
	Update();

	GDisp1_Clear();
	GDisp1_DrawHLine(0,3,10,GDisp1_COLOR_WHITE);
	Update();
	
	GDisp1_DrawBox(0, 0, 4, 5, 1, GDisp1_COLOR_WHITE); /* black means LED turned off, GDisp1_COLOR_WHITE turn LED on */
	Update();
	
	GDisp1_Clear();
	GDisp1_DrawLine(0,0,GDisp1_GetWidth()-1, GDisp1_GetHeight()-1, GDisp1_COLOR_WHITE);
	GDisp1_DrawLine(0,GDisp1_GetHeight()-1,GDisp1_GetWidth()-1, 0, GDisp1_COLOR_WHITE);
	Update();
  }
/*** Don't write any code pass this line, or it will be deleted during code generation. ***/
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;){}
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

/* END ProcessorExpert */
/*
** ###################################################################
**
**     This file was created by Processor Expert 5.3 [05.01]
**     for the Freescale ColdFireV1 series of microcontrollers.
**
** ###################################################################
*/
