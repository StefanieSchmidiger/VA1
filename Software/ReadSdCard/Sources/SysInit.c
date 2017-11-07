#include "FAT1.h"
#include "Config.h"
#include "Shell.h"
#include "FRTOS1.h"
#include "CLS1.h"
#include <stdbool.h> //true/false

bool createAllTasks(void);


void SysInitTask(void* p)
{
  bool cardMounted = false;
  static FAT1_FATFS fileSystemObject;
  if(FAT1_Init() != 0)
    {for(;;){}} /* SD Card could not be mounted */
  //FAT1_CheckCardPresence(&cardMounted, (unsigned char*)"0" /*volume*/, &fileSystemObject, CLS1_GetStdio());
  //readConfig();
  //createAllTasks();
  for(;;)
  {
	  vTaskDelay(500/portTICK_RATE_MS);
  }
  vTaskDelete(NULL); // task deletes itself
}

bool createAllTasks(void)
{

}
