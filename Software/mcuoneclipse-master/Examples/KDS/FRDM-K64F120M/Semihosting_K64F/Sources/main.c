/* ###################################################################
**     Filename    : main.c
**     Project     : Semihosting_K64F
**     Processor   : MK64FN1M0VLQ12
**     Version     : Driver 01.01
**     Compiler    : GNU C Compiler
**     Date/Time   : 2014-04-05, 18:56, # CodeGen: 0
**     Abstract    :
**         Main module.
**         This module contains user's application code.
**     Settings    :
**     Contents    :
**         No public methods
**
** ###################################################################*/
/*!
** @file main.c
** @version 01.01
** @brief
**         Main module.
**         This module contains user's application code.
*/         
/*!
**  @addtogroup main_module main module documentation
**  @{
*/         
/* MODULE main */


/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
#include "Pins1.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "PDD_Includes.h"
#include "Init_Config.h"

/* User includes (#include below this line is not maintained by Processor Expert) */
#include <stdio.h>
#include <math.h>
#include <malloc.h>

/*lint -save  -e970 Disable MISRA rule (6.3) checking. */
static double d = 3.56;
static float f = 12.3456;

#if 0
void *_sbrk ( uint32_t delta ) {
extern char _end; /* Defined by the linker */
static char *heap_end;
char *prev_heap_end;

  if (heap_end == 0) {
    heap_end = &_end;
  }

  prev_heap_end = heap_end;
  heap_end += delta;
  return (void *) prev_heap_end;
}
#endif

int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{

  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

#if 1
//  p = malloc(100);
  {
	 int i;
	 char buffer[64];

	 for(i=0; i<100; i++) {
#if 1
     printf("Hello world!013456\r\n"); /* 20 characters */
     d = sin(3.5);
     i++; d++;
     printf("double: %f\r\n", d);
     printf("float: %f\r\n", f);
   //  ch = getc();
#endif
#if 0
     buffer[0] = '\0';
     i = scanf("%s", buffer);
     if (i==1) {
       printf("i: %d\r\n", i);
     }
     //ch = getchar();
     //printf("ch: %c\r\n", ch);
#endif
#if 0
     if (gets(buffer)!=NULL) {
       printf("%s\r\n", buffer);
     }
#endif
   }
   printf("****FINISHED****\n"); /* 2000 characters finished */
  }
#endif
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

/* END main */
/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.4 [05.09]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
