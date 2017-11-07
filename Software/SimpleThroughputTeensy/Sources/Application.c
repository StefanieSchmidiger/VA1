/*
 * Application.c
 *
 *  Created on: 10.10.2017
 *      Author: Erich Styger Local
 */

#include "WAIT1.h"
#include "FRTOS.h"
#include "Shell.h"
#include <stdlib.h> // atoi
#include <stdbool.h> //true/false
#include "MINI.h" //read SD card
#include "SysInit.h" // init task, reads config



void APP_Run(void)
{
  if (xTaskCreate(SysInit_TaskEntry, "Init", 2000/sizeof(StackType_t), NULL, tskIDLE_PRIORITY+1,  NULL) != pdPASS) {
          for(;;){}} /* error */

  /* create shell task */


  vTaskStartScheduler();
  for(;;) {}
}

