#include "FAT1.h"
#include "Config.h"
#include "Shell.h"
#include "FRTOS1.h"
#include "CLS1.h"
#include <stdbool.h> //true/false


void SysInitTask(void *p)
{
  bool cardMounted = false;
  static FAT1_FATFS fileSystemObject;
  if(FAT1_Init() != 0)
    {for(;;){}} /* SD Card could not be mounted */
  FAT1_CheckCardPresence(&cardMounted, (unsigned char*)"0" /*volume*/, &fileSystemObject, CLS1_GetStdio());
  readConfig();
  if (xTaskCreate(ShellTask, "Shell", configMINIMAL_STACK_SIZE+150, NULL, tskIDLE_PRIORITY+1, NULL) != pdPASS) {
    for(;;) {}} /* error */
  for(;;) {vTaskDelay(50/portTICK_RATE_MS);
  }
}
