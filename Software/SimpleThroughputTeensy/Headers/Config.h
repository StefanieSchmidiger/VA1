#ifndef CONFIG_H
#define CONFIG_H

#include <stdbool.h>

typedef struct Configurations {
   int BaudRatesWirelessConn[4];
   int BaudRatesDeviceConn[4];
   int PrioWirelessConnDev0[4];
   int PrioWirelessConnDev1[4];
   int PrioWirelessConnDev2[4];
   int PrioWirelessConnDev3[4];
   int SendCntWirelessConnDev0[4];
   int SendCntWirelessConnDev1[4];
   int SendCntWirelessConnDev2[4];
   int SendCntWirelessConnDev3[4];
   int ResendDelayWirelessConnDev0[4];
   int ResendDelayWirelessConnDev1[4];
   int ResendDelayWirelessConnDev2[4];
   int ResendDelayWirelessConnDev3[4];
   int MaxThroughputWirelessConn[4];
   int UsualPacketSizeDeviceConn[4];
   int PackageGenMaxTimeout[4];
   int DelayDismissOldPackagePerDev[4];
   bool SendAckPerWirelessConn[4];
   bool UseCtsPerWirelessConn[4];
   bool UseGolayErrorCorrectingCode;
   bool TestHwLoopbackOnly;
   bool EnableTestDataGen;
   bool GenerateDebugOutput;
   bool GenerateThroughputOutput;
   int HwBufIfDataReaderTaskInterval;
   int HwBufIfDeviceDataWriterTaskInterval;
   int PackageGeneratorTaskInterval;
   int WirelessDataSendHandlerTaskInterval;
   int WirelessAckSendHandlerTaskInterval;
   int WirelessPackageExtractorTaskInterval;
   int ToggleGreenLedInterval;
   int TestDataGeneratorTaskInterval;
   int GenerateThroughputOutputInterval;
} Configuration;

extern Configuration config;

bool readConfig(void);
bool readTestConfig(void);

#endif
