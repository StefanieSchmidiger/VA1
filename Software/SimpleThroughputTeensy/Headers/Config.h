#ifndef HEADERS_CONFIG_H
#define HEADERS_CONFIG_H

#include <stdbool.h>
#include "SpiHandler.h"

typedef struct Configurations {
	/* BaudRateConfiguration */
   int BaudRatesWirelessConn[NUMBER_OF_UARTS]; //
   int BaudRatesDeviceConn[NUMBER_OF_UARTS]; //
   /* ConnectionConfiguration */
   int PrioWirelessConnDev0[NUMBER_OF_UARTS];
   int PrioWirelessConnDev1[NUMBER_OF_UARTS];
   int PrioWirelessConnDev2[NUMBER_OF_UARTS];
   int PrioWirelessConnDev3[NUMBER_OF_UARTS];
   int SendCntWirelessConnDev0[NUMBER_OF_UARTS];
   int SendCntWirelessConnDev1[NUMBER_OF_UARTS];
   int SendCntWirelessConnDev2[NUMBER_OF_UARTS];
   int SendCntWirelessConnDev3[NUMBER_OF_UARTS];
   /* TransmissionConfiguration */
   int ResendDelayWirelessConnDev0[NUMBER_OF_UARTS];
   int ResendDelayWirelessConnDev1[NUMBER_OF_UARTS];
   int ResendDelayWirelessConnDev2[NUMBER_OF_UARTS];
   int ResendDelayWirelessConnDev3[NUMBER_OF_UARTS];
   int MaxThroughputWirelessConn[NUMBER_OF_UARTS];
   int UsualPacketSizeDeviceConn[NUMBER_OF_UARTS]; //
   int PackageGenMaxTimeout[NUMBER_OF_UARTS]; //
   int DelayDismissOldPackagePerDev[NUMBER_OF_UARTS];
   bool SendAckPerWirelessConn[NUMBER_OF_UARTS];
   bool UseCtsPerWirelessConn[NUMBER_OF_UARTS];

   bool TestHwLoopbackOnly;
   bool GenerateDebugOutput;
   int SpiHandlerTaskInterval;
   int PackageHandlerTaskInterval;
   int NetworkHandlerTaskInterval;
   int ToggleGreenLedInterval;
} Configuration;

extern Configuration config;

bool readConfig(void);
bool readTestConfig(void);

#endif
