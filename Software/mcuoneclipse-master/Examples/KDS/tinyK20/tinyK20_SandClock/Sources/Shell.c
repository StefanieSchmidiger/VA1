/*
 * Shell.c
 *
 *  Created on: 04.08.2011
 *      Author: Erich Styger
 */

#include "Platform.h"
#include "Application.h"
#include "FRTOS1.h"
#include "Shell.h"
#include "CLS1.h"
#include "TmDt1.h"
#include "KIN1.h"
#include "Plotclock.h"
#include "Servo.h"
#include "PCA9685.h"
#include "RTC2.h"
#include "CDC1.h"

static const CLS1_ParseCommandCallback CmdParserTable[] =
{
  CLS1_ParseCommand,
  FRTOS1_ParseCommand,
  KIN1_ParseCommand,
  RTC2_ParseCommand,
  TmDt1_ParseCommand,
  PCA9685_ParseCommand,
  SERVO_ParseCommand,
  PlotClock_ParseCommand,
  NULL /* sentinel */
};

static void ShellTask(void *pvParameters) {
  (void)pvParameters; /* not used */
  CLS1_DefaultShellBuffer[0] = '\0';
  CDC1_DefaultShellBuffer[0] = '\0';
  (void)CLS1_ParseWithCommandTable((unsigned char*)CLS1_CMD_HELP, CLS1_GetStdio(), CmdParserTable);
  for(;;) {
    (void)CLS1_ReadAndParseWithCommandTable(CLS1_DefaultShellBuffer, sizeof(CLS1_DefaultShellBuffer), CLS1_GetStdio(), CmdParserTable);
    (void)CLS1_ReadAndParseWithCommandTable(CDC1_DefaultShellBuffer, sizeof(CDC1_DefaultShellBuffer), CDC1_GetStdio(), CmdParserTable);
    vTaskDelay(pdMS_TO_TICKS(10));
  }
}

void SHELL_Init(void) {
  if (xTaskCreate(ShellTask, "Shell", configMINIMAL_STACK_SIZE+300, NULL, tskIDLE_PRIORITY+1, NULL) != pdPASS) {
    for(;;){} /* error */
  }
}

