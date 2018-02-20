#include "FAT1.h"
#include "Config.h"
#include "Shell.h" // to create task
#include "FRTOS.h"
#include "SpiHandler.h" // to create spi handler task, bool
#include "PackageHandler.h"
#include "NetworkHandler.h"
#include "Blinky.h"
#include "ThroughputPrintout.h"
#include "Logger.h"

/* prototypes for functions that are only within this file scope */
bool createAllTasks(void);

/*!
* \fn void SysInit_TaskEntry(void* param)
* \brief Reads config file and creates all other tasks afterwards (because other tasks need config file)
*/
void SysInit_TaskEntry(void* param)
{
  bool cardMounted = false;
  static FAT1_FATFS fileSystemObject;

  /* mount SD card so config file can be read */
  if(FAT1_Init() != 0)
    {for(;;){}} /* SD Card could not be mounted */
  FAT1_CheckCardPresence(&cardMounted, (unsigned char*)"0" /*volume*/, &fileSystemObject, CLS1_GetStdio());
  readConfig(); /* global config variable is needed for all other tasks -> read it before starting other tasks */
  createAllTasks(); /* start all other tasks */
  vTaskDelete(NULL); /* task deletes itself */
}

/*!
* \fn bool createAllTasks(void)
* \brief Initializes and creates all tasks for serial switch
* \return true if all tasks were created successfully
*/
bool createAllTasks(void)
{
	/* make sure all queues are initialized before being accessed from other tasks */
	Shell_TaskInit();
	logger_TaskInit();
	spiHandler_TaskInit();
	packageHandler_TaskInit();
	networkHandler_TaskInit();

	/* create Shell task */
	if (xTaskCreate(Shell_TaskEntry, "Shell", 2000/sizeof(StackType_t), NULL, tskIDLE_PRIORITY+1, NULL) != pdPASS) {
	  	    for(;;) {}} /* error */


	/* create SPI handler task */
	if (xTaskCreate(spiHandler_TaskEntry, "SPI_Handler", 2000/sizeof(StackType_t), NULL, tskIDLE_PRIORITY+3, NULL) != pdPASS) {
	    for(;;) {}} /* error */


	/* create package handler task */
	if (xTaskCreate(packageHandler_TaskEntry, "Package_Handler", 2000/sizeof(StackType_t), NULL, tskIDLE_PRIORITY+2, NULL) != pdPASS) {
		for(;;) {}} /* error */


	/* create network handler task */
	if (xTaskCreate(networkHandler_TaskEntry, "Network_Handler", 2000/sizeof(StackType_t), NULL, tskIDLE_PRIORITY+2, NULL) != pdPASS) {
		for(;;) {}} /* error */

	/* create network handler task */
	if (xTaskCreate(throughputPrintout_TaskEntry, "Throughput_Printout", 2000/sizeof(StackType_t), NULL, tskIDLE_PRIORITY+1, NULL) != pdPASS) {
		for(;;) {}} /* error */

	/* create logger task */
	if (xTaskCreate(logger_TaskEntry, "Logger", 2000/sizeof(StackType_t), NULL, tskIDLE_PRIORITY+1, NULL) != pdPASS) {
		for(;;) {}} /* error */

	/* create blinky task last to let user know that all init methods and mallocs were successful when LED blinks */
	if (xTaskCreate(blinky_TaskEntry, "Blinky", 400/sizeof(StackType_t), NULL, tskIDLE_PRIORITY+1, NULL) != pdPASS) {
	    for(;;) {}} /* error */

	return true;
}
