/*
 * Application.c
 *
 *  Created on: 10.10.2017
 *      Author: Erich Styger Local
 */
#include "WAIT1.h"
#include "FRTOS1.h"
#include "Shell.h"
#include <stdlib.h> // atoi
#include <stdbool.h> //true/false
#include "MINI.h" //read SD card
#include "SysInit.h" // init task, reads config
#include "SpiHandler.h"


static void BlinkyTask(void *p) {
  for(;;) {
    LED1_Neg();
    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}

void APP_Init(void)
{
	SHELL_Init(); // initializes FAT1
}

void APP_Run(void)
{
#if 0
  if (xTaskCreate(
      BlinkyTask,  /* pointer to the task */
      "Blinky", /* task name for kernel awareness debugging */
      configMINIMAL_STACK_SIZE+500, /* task stack size */
      (void*)NULL, /* optional task startup argument */
      tskIDLE_PRIORITY,  /* initial priority */
      (xTaskHandle*)NULL /* optional task handle to create */
    ) != pdPASS) {
  /*lint -e527 */
     for(;;){}} /* error! probably out of memory */
#endif

  if (xTaskCreate(SysInitTask, "Init", configMINIMAL_STACK_SIZE+500, NULL, tskIDLE_PRIORITY+1, NULL) != pdPASS) {
          for(;;){}} /* error */
  if (xTaskCreate(ShellTask, "Shell", configMINIMAL_STACK_SIZE+150, NULL, tskIDLE_PRIORITY+1, NULL) != pdPASS) {
  	    for(;;) {}} /* error */

  if (xTaskCreate(SpiHandler_TaskEntry, "SPI_Handler", configMINIMAL_STACK_SIZE+150, NULL, tskIDLE_PRIORITY+1, NULL) != pdPASS) {
    	    for(;;) {}} /* error */


  vTaskStartScheduler();
  for(;;) {}
}

