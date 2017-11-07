#include "FAT1.h"
#include "Config.h"
#include "Shell.h" // to create task
#include "FRTOS.h"
//#include <stdbool.h> //true/false
#include "SpiHandler.h" // to create spi handler task
#include "Blinky.h"


bool createAllTasks(void);


void SysInit_TaskEntry(void* param)
{
  bool cardMounted = false;
  static FAT1_FATFS fileSystemObject;

  if(FAT1_Init() != 0)
    {for(;;){}} /* SD Card could not be mounted */
  FAT1_CheckCardPresence(&cardMounted, (unsigned char*)"0" /*volume*/, &fileSystemObject, CLS1_GetStdio());
  readConfig();
  createAllTasks();
  vTaskDelete(NULL); // task deletes itself
}

bool createAllTasks(void)
{

	if (xTaskCreate(Shell_TaskEntry, "Shell", 2000/sizeof(StackType_t), NULL, tskIDLE_PRIORITY+1, NULL) != pdPASS) {
	  	    for(;;) {}} /* error */


	/* create SPI handler task */
	if (xTaskCreate(spiHandler_TaskEntry, "SPI_Handler", 2000/sizeof(StackType_t), NULL, tskIDLE_PRIORITY+1, NULL) != pdPASS) {
	    for(;;) {}} /* error */


	/* create blinky task */
	if (xTaskCreate(blinky_TaskEntry, "Blinky", 400/sizeof(StackType_t), NULL, tskIDLE_PRIORITY+1, NULL) != pdPASS) {
	    for(;;) {}} /* error */

	return true;
}
