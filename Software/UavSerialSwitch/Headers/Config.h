#ifndef HEADERS_CONFIG_H
#define HEADERS_CONFIG_H

#include <stdbool.h>
#include "SpiHandler.h"

typedef struct Configurations {
	/* BaudRateConfiguration */
   int BaudRatesWirelessConn[NUMBER_OF_UARTS]; //
   int BaudRatesDeviceConn[NUMBER_OF_UARTS]; //
   /* ConnectionConfiguration */
   int PrioWirelessConnDev[NUMBER_OF_UARTS][NUMBER_OF_UARTS]; /* [uartNr][prioPerUart] */
   int SendCntWirelessConnDev[NUMBER_OF_UARTS][NUMBER_OF_UARTS]; /* [uartNr][numberOfSendAttempts] */
   /* TransmissionConfiguration */
   int ResendDelayWirelessConnDev[NUMBER_OF_UARTS][NUMBER_OF_UARTS]; /* [uartNr][DelayPerUart] */
   int MaxThroughputWirelessConn[NUMBER_OF_UARTS]; // ToDo: unused!!
   int UsualPacketSizeDeviceConn[NUMBER_OF_UARTS];
   int PackageGenMaxTimeout[NUMBER_OF_UARTS];
   int DelayDismissOldPackagePerDev[NUMBER_OF_UARTS]; //ToDo: unused!!
   bool SendAckPerWirelessConn[NUMBER_OF_UARTS];
   bool UseCtsPerWirelessConn[NUMBER_OF_UARTS];
   /* SoftwareConfiguration */
   bool TestHwLoopbackOnly;
   bool GenerateDebugOutput;
   bool LoggingEnabled;
   int SpiHandlerTaskInterval; // [ms]
   int PackageHandlerTaskInterval; // [ms]
   int NetworkHandlerTaskInterval; // [ms]
   int ToggleGreenLedInterval; // [ms]
   int ThroughputPrintoutTaskInterval; // [sec]
   int ShellTaskInterval; // [ms]
   int LoggerTaskInterval; // [ms]
} Configuration;

extern Configuration config;

/*!
* \fn uint16_t numberOfBytesInRxByteQueue(tSpiSlaves spiSlave, tUartNr uartNr)
* \brief Reads config file and stores it in global variable
*/
bool readConfig(void);

/*!
* \fn bool readTestConfig(void)
* \brief Reads "TestConfiguration.ini" file -> to check if above functions work correctly
* \return true if test config was read successfully
*/
bool readTestConfig(void);

#endif
