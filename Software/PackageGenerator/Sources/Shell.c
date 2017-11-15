/**
 * \file
 * \brief Shell and console interface implementation.
 * \author Erich Styger
 *
 * This module implements the front to the console/shell functionality.
 */

#include "Platform.h"
#if PL_HAS_SHELL
#include "Shell.h"
#include "CLS1.h"
#include "Application.h"
#include "FRTOS.h"
#if PL_HAS_TEENSY_LED
	#include "LedTeensy.h"
#else
	#include "LedGreen.h"
#endif
#if PL_HAS_SD_CARD
  #include "FAT1.h"
  #include "TmDt1.h"
#endif
#include "KIN1.h"

/* prototypes */
void SHELL_TaskInit(void);
void SHELL_Deinit(void);



void SHELL_SendString(unsigned char *msg) {
  CLS1_SendStr(msg, CLS1_GetStdio()->stdOut);
}

static const CLS1_ParseCommandCallback CmdParserTable[] =
{
  CLS1_ParseCommand,
#if FRTOS1_PARSE_COMMAND_ENABLED
  FRTOS1_ParseCommand,
#endif
#if LED_TEENSY_PARSE_COMMAND_ENABLED
  LedTeensy_ParseCommand,
#else
  LedGreen_ParseCommand,
#endif
#if PL_HAS_SD_CARD
#if FAT1_PARSE_COMMAND_ENABLED
  FAT1_ParseCommand,
#endif
#endif
#if TmDt1_PARSE_COMMAND_ENABLED
  TmDt1_ParseCommand,
#endif
#if KIN1_PARSE_COMMAND_ENABLED
  KIN1_ParseCommand,
#endif
  NULL /* Sentinel */
};

static unsigned char localConsole_buf[48];

void Shell_TaskEntry (void *pvParameters)
{
	SHELL_TaskInit();
	#if CLS1_DEFAULT_SERIAL
		CLS1_ConstStdIOTypePtr ioLocal = CLS1_GetStdio();
	#endif
	#if PL_HAS_SD_CARD
			bool cardMounted = FALSE;
			static FAT1_FATFS fileSystemObject;
	#endif
	(void)pvParameters; /* not used */
	for(;;)
	{
		#if PL_HAS_SD_CARD
			(void)FAT1_CheckCardPresence(&cardMounted, (unsigned char*)"0" /*volume*/, &fileSystemObject, CLS1_GetStdio());
		#endif
		#if CLS1_DEFAULT_SERIAL
			(void)CLS1_ReadAndParseWithCommandTable(localConsole_buf, sizeof(localConsole_buf), ioLocal, CmdParserTable);
		#endif
		vTaskDelay(50/portTICK_RATE_MS);
	} /* for */
}

void SHELL_TaskInit(void) {
  localConsole_buf[0] = '\0';
  CLS1_Init();
  #if PL_HAS_SD_CARD
  FAT1_Init();
  #endif
}

void SHELL_Deinit(void) {
  CLS1_Deinit();
}
#endif /* PL_HAS_SHELL */
