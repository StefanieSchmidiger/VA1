/*
 * Application.c
 *
 *  Created on: 10.10.2017
 *      Author: Erich Styger Local
 */
#include "LED1.h"
#include "WAIT1.h"
#include "FRTOS1.h"
#include "Shell.h"
#include <stdlib.h> // atoi
#include <stdbool.h> //true/false
#include "MINI.h" //read SD card



void csvToInt(char inputString[], int outputArray[])
{
	int indexLastDigit = 0;
	int indexFirstDigit = 0;
	int count = 0;
	for (int i=0; inputString[i]; i++)
	  count += (inputString[i] == ','); // find number of integers saved as csv
	for(int i=0; i<(count+1); i++)
	{
		while((inputString[indexFirstDigit] < '0') || (inputString[indexFirstDigit] > '9')) // fast foreward to the beginning of number
		{
			indexFirstDigit++;
			indexLastDigit++;
		}
		while((inputString[indexLastDigit] >= '0') && (inputString[indexLastDigit] <= '9')) // find the last digit that is part of one number
			indexLastDigit++;
		inputString[indexLastDigit] = '\0';
		outputArray[i] = atoi(&inputString[indexFirstDigit]);
		indexFirstDigit = indexLastDigit+1;
		indexLastDigit = indexLastDigit+1;
	}
}

bool readTestConfig(void)
{
	char sectionName[] = "TestConfiguration";
  	char intKey[] = "myInt";
  	char boolKey[] = "myBool";
  	char arrKey[] = "myArray";
  	char fooValue[] = "0, 0, 0, 0";
  	int arrSize = 30;
  	char arrStringValue[30];
  	int arrInt[4];
  	char fileName[] = "TestConfig.ini";
  	long int valInt = MINI_ini_getl(sectionName, intKey, 0, fileName);
  	bool valBool = MINI_ini_getbool(sectionName, boolKey, 0, fileName);
  	int numberOfCharsCopied = MINI_ini_gets(sectionName, arrKey, fooValue, arrStringValue, arrSize, fileName);
  	csvToInt(arrStringValue, arrInt);
  	return true;
}


static void MainTask(void *p) {
  for(;;) {
    LED1_Neg();
    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}

void APP_Run(void) {
  SHELL_Init();
  if (xTaskCreate(
      MainTask,  /* pointer to the task */
      "Main", /* task name for kernel awareness debugging */
      configMINIMAL_STACK_SIZE+500, /* task stack size */
      (void*)NULL, /* optional task startup argument */
      tskIDLE_PRIORITY,  /* initial priority */
      (xTaskHandle*)NULL /* optional task handle to create */
    ) != pdPASS) {
  /*lint -e527 */

     for(;;){} /* error! probably out of memory */
    /*lint +e527 */
  }
  readTestConfig();
  vTaskStartScheduler();
  for(;;) {}
#if 0
  for(;;) {
    LED1_Neg();
    WAIT1_Waitms(500);
  }
#endif
}

