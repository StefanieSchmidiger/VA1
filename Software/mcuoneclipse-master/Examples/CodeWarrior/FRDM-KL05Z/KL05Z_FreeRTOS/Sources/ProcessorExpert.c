/** ###################################################################
**     Filename    : ProcessorExpert.c
**     Project     : ProcessorExpert
**     Processor   : MKL05Z32VFM4
**     Version     : Driver 01.01
**     Compiler    : GNU C Compiler
**     Date/Time   : 2013-03-06, 08:00, # CodeGen: 0
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
#include "LEDR.h"
#include "Inhr1.h"
#include "PwmLdd1.h"
#include "LEDG.h"
#include "Inhr2.h"
#include "PwmLdd2.h"
#include "LEDB.h"
#include "Inhr3.h"
#include "PwmLdd3.h"
#include "FRTOS1.h"
#include "UTIL1.h"
#include "CLS1.h"
#include "AS1.h"
#include "ASerialLdd1.h"
#include "TU1.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"

/* User includes (#include below this line is not maintained by Processor Expert) */
#include "Shell.h"

#define USE_LED_PWM  1
#define LEDR_DUTY   (0xffff/2) /* duty */

static portTASK_FUNCTION(LedTask, pvParameters) {
  (void)pvParameters; /* parameter not used */
  SHELL_Init();
  for(;;) {
    SHELL_Parse();
#if USE_LED_PWM /* using on-off */
    LEDR_SetRatio16(LEDR_DUTY);
    FRTOS1_vTaskDelay(50/portTICK_RATE_MS);
    LEDR_SetRatio16(0);
    FRTOS1_vTaskDelay(50/portTICK_RATE_MS);
#else
    LEDR_Neg();
    FRTOS1_vTaskDelay(100/portTICK_RATE_MS);
#endif
  }
}

/*lint -save  -e970 Disable MISRA rule (6.3) checking. */
int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
  /* Write your local variable definition here */

  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  /* Write your code here */
  if (FRTOS1_xTaskCreate(
        LedTask,  /* pointer to the task */
        (signed portCHAR *)"Led", /* task name for kernel awareness debugging */
        configMINIMAL_STACK_SIZE, /* task stack size */
        (void*)NULL, /* optional task startup argument */
        tskIDLE_PRIORITY+1,  /* initial priority */
        (xTaskHandle*)NULL /* optional task handle to create */
      ) != pdPASS) {
    /*lint -e527 */
    for(;;){} /* error! probably out of memory */
    /*lint +e527 */
  }

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
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.0 [05.03]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
