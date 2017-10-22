/*
 * Copyright (c) 2013 - 2016, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * This is template for main module created by New Kinetis SDK 2.x Project Wizard. Enjoy!
 **/

#include "board.h"
#include "pin_mux.h"
#include "clock_config.h"

#include "LED1.h"
#include "LED2.h"
#include "LED3.h"
#include "WAIT1.h"
#include "fsl_port.h"

#define USE_FREERTOS   1 /* turns on using FreeRTOS */

#if USE_FREERTOS
#include "FreeRTOS.h"
#include "FRTOS1.h"

void FRTOS1_vApplicationStackOverflowHook(xTaskHandle pxTask, char *pcTaskName) {
  /* This will get called if a stack overflow is detected during the context
     switch.  Set configCHECK_FOR_STACK_OVERFLOWS to 2 to also check for stack
     problems within nested interrupts, but only do this for debug purposes as
     it will increase the context switch time. */
  (void)pxTask;
  (void)pcTaskName;
  taskDISABLE_INTERRUPTS();
  /* Write your code here ... */
  for(;;) {}
}

void FRTOS1_vApplicationTickHook(void) {
  /* Called for every RTOS tick. */
  /* Write your code here ... */
}

void FRTOS1_vApplicationIdleHook(void) {
  /* Called whenever the RTOS is idle (from the IDLE task).
     Here would be a good place to put the CPU into low power mode. */
  /* Write your code here ... */
}

void FRTOS1_vApplicationMallocFailedHook(void)
{
  /* Called if a call to pvPortMalloc() fails because there is insufficient
     free memory available in the FreeRTOS heap.  pvPortMalloc() is called
     internally by FreeRTOS API functions that create tasks, queues, software
     timers, and semaphores.  The size of the FreeRTOS heap is set by the
     configTOTAL_HEAP_SIZE configuration constant in FreeRTOSConfig.h. */
  taskDISABLE_INTERRUPTS();
  /* Write your code here ... */
  for(;;) {}
}
#endif

static void AppTask(void *pvParameters) {
  (void)pvParameters;
  for(;;) {
    LED1_Neg();
    vTaskDelay(pdMS_TO_TICKS(100));
  }
}

/*!
 * @brief Application entry point.
 */

#if configSUPPORT_STATIC_ALLOCATION
  #if configUSE_HEAP_SECTION_NAME
    #define SECTION __attribute__((section (configHEAP_SECTION_NAME_STRING)))
  #else
    #define SECTION /* empty */
  #endif
  static StaticTask_t SECTION xTaskTCBBuffer;
  static StackType_t SECTION xStack[configMINIMAL_STACK_SIZE];
#endif


int main(void) {
  /* Init board hardware. */
  BOARD_InitPins();
  BOARD_BootClockRUN();
  BOARD_InitDebugConsole();

  /* init components */
  LED1_Init();
  LED2_Init();
  LED3_Init();

  /* run the code */
  RTT1_Init(); /* initialize SEGGER RTT */
#if configUSE_SEGGER_SYSTEM_VIEWER_HOOKS /* using SEGGER SystemViewer Trace */
  SYS1_Init();
#elif configUSE_TRACE_HOOKS /* using Percepio FreeRTOS+Trace */
  #if TRC_CFG_RECORDER_MODE==TRC_RECORDER_MODE_SNAPSHOT
    PTRC1_Init(TRC_START); /* snapshot trace, from startup */
  #elif TRC_CFG_RECORDER_MODE==TRC_RECORDER_MODE_STREAMING
    vTraceEnable(TRC_START_AWAIT_HOST); /* from startup, Blocks! */
  #else
    #error "invalid configuration!"
  #endif
#endif

  #if USE_FREERTOS
  FRTOS1_Init();
#if configSUPPORT_STATIC_ALLOCATION
  if (xTaskCreateStatic(AppTask, "App", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY+1, &xStack[0], &xTaskTCBBuffer)==NULL) {
    for(;;){} /* task creation failed */
  }
#else /* configSUPPORT_DYNAMIC_ALLOCATION */
  if (xTaskCreate(AppTask, "App", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY+1, NULL) != pdPASS) {
    for(;;){} /* error */
  }
#endif
  vTaskStartScheduler();
#else
  for(;;) {
#if 0
    LED1_Neg();
    LED2_Neg();
    LED3_Neg();
#else
    LED1_On(); WAIT1_Waitms(500); LED1_Off();
    LED2_On(); WAIT1_Waitms(500); LED2_Off();
    LED3_On(); WAIT1_Waitms(500); LED3_Off();
#endif
  }
#endif

  for(;;) { /* Infinite loop to avoid leaving the main function */
    __asm("NOP"); /* something to use as a breakpoint stop while looping */
  }
}
