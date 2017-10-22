/*
 * Shell.c
 *
 *  Created on: 04.08.2011
 *      Author: Erich Styger
 */

#include "Platform.h"
#include "FRTOS1.h"
#include "Shell.h"
#include "CLS1.h"
#if PL_CONFIG_HAS_SEGGER_RTT
  #include "RTT1.h"
#endif
#if PL_CONFIG_HAS_RADIO
  #include "RNET1.h"
  #include "RApp.h"
  #include "RNet_App.h"
  #include "RNetConf.h"
#endif
#if PL_CONFIG_HAS_USB_CDC
  #include "CDC1.h"
#endif
#if PL_CONFIG_HAS_RADIO && RNET_CONFIG_REMOTE_STDIO
  #include "RStdIO.h"
#endif

static const CLS1_ParseCommandCallback CmdParserTable[] =
{
  CLS1_ParseCommand,
  FRTOS1_ParseCommand,
#if PL_CONFIG_HAS_RADIO
#if RNET1_PARSE_COMMAND_ENABLED
  RNET1_ParseCommand,
#endif
  RNETA_ParseCommand,
#endif
  NULL /* sentinel */
};

#if PL_CONFIG_HAS_SEGGER_RTT
static CLS1_ConstStdIOType RTT_Stdio = {
  (CLS1_StdIO_In_FctType)RTT1_StdIOReadChar, /* stdin */
  (CLS1_StdIO_OutErr_FctType)RTT1_StdIOSendChar, /* stdout */
  (CLS1_StdIO_OutErr_FctType)RTT1_StdIOSendChar, /* stderr */
  RTT1_StdIOKeyPressed /* if input is not empty */
};
#endif

#if PL_CONFIG_HAS_USB_CDC
static CLS1_ConstStdIOType CDC_stdio = {
  (CLS1_StdIO_In_FctType)CDC1_StdIOReadChar, /* stdin */
  (CLS1_StdIO_OutErr_FctType)CDC1_StdIOSendChar, /* stdout */
  (CLS1_StdIO_OutErr_FctType)CDC1_StdIOSendChar, /* stderr */
  CDC1_StdIOKeyPressed /* if input is not empty */
};
#endif

static void ShellTask(void *pvParameters) {
#if PL_CONFIG_HAS_USB_CDC
  static unsigned char cdc_buf[48];
#endif
#if PL_CONFIG_HAS_RADIO && RNET_CONFIG_REMOTE_STDIO
  static unsigned char radio_cmd_buf[48];
  CLS1_ConstStdIOType *ioRemote = RSTDIO_GetStdio();
#endif
#if PL_CONFIG_HAS_SEGGER_RTT
  static unsigned char rtt_buf[48];
#endif
  unsigned char buf[48];

  (void)pvParameters; /* not used */
  buf[0] = '\0';
#if PL_CONFIG_HAS_USB_CDC
  cdc_buf[0] = '\0';
#endif
#if PL_CONFIG_HAS_RADIO && RNET_CONFIG_REMOTE_STDIO
  radio_cmd_buf[0] = '\0';
#endif
#if PL_CONFIG_HAS_SEGGER_RTT
  rtt_buf[0] = '\0';
#endif
  (void)CLS1_ParseWithCommandTable((unsigned char*)CLS1_CMD_HELP, CLS1_GetStdio(), CmdParserTable);
  for(;;) {
    (void)CLS1_ReadAndParseWithCommandTable(buf, sizeof(buf), CLS1_GetStdio(), CmdParserTable);
#if PL_CONFIG_HAS_USB_CDC
    (void)CLS1_ReadAndParseWithCommandTable(cdc_buf, sizeof(cdc_buf), &CDC_stdio, CmdParserTable);
#endif
#if PL_CONFIG_HAS_RADIO && RNET_CONFIG_REMOTE_STDIO
    RSTDIO_Print(CLS1_GetStdio()); /* dispatch incoming messages */
    (void)CLS1_ReadAndParseWithCommandTable(radio_cmd_buf, sizeof(radio_cmd_buf), ioRemote, CmdParserTable);
#endif
#if PL_CONFIG_HAS_SEGGER_RTT
    (void)CLS1_ReadAndParseWithCommandTable(rtt_buf, sizeof(rtt_buf), &RTT_Stdio, CmdParserTable);
#endif
    FRTOS1_vTaskDelay(pdMS_TO_TICKS(10));
  }
}

void SHELL_Init(void) {
  if (FRTOS1_xTaskCreate(ShellTask, "Shell", configMINIMAL_STACK_SIZE+150, NULL, tskIDLE_PRIORITY+2, NULL) != pdPASS) {
    for(;;){} /* error */
  }
}

