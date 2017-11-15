#include "MINI.h"
#include "Config.h"
#include <stdlib.h> //atoi()
#include <stdbool.h>

#define TEMP_CSV_SIZE 50
#define DEFAULT_CSV_STRING "0, 0, 0, 0"
#define DEFAULT_BOOL 0
#define DEFAULT_INT 1000


// prototypes
void csvToInt(char inputString[], int outputArray[]);
void csvToBool(char inputString[], bool outputArray[]);

// global variables
Configuration config;


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

void csvToBool(char inputString[], bool outputArray[])
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
		outputArray[i] = atoi(&inputString[indexFirstDigit]) > 0 ? true : false;
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
  	char fooValue[] = "foo";
  	int arrSize = 30;
  	char arrStringValue[arrSize];
  	int arrInt[4];
  	char fileName[] = "TestConfig.ini";
  	long int valInt = MINI_ini_getl(sectionName, intKey, 0, fileName);
  	bool valBool = MINI_ini_getbool(sectionName, boolKey, 0, fileName);
  	int numberOfCharsCopied = MINI_ini_gets(sectionName, arrKey, fooValue, arrStringValue, arrSize, fileName);
  	csvToInt(arrStringValue, arrInt);
  	return true;
}

bool readConfig(void)
{
	int numberOfCharsCopied;
	char copiedCsv[TEMP_CSV_SIZE];
  	char fileName[] = "serialSwitch_Config.ini";

  	/* -------- BaudRateConfiguration -------- */
  	/* BAUD_RATES_WIRELESS_CONN */
  	numberOfCharsCopied = MINI_ini_gets("BaudRateConfiguration", "BAUD_RATES_WIRELESS_CONN",  DEFAULT_CSV_STRING, copiedCsv, TEMP_CSV_SIZE, "serialSwitch_Config.ini");
  	csvToInt(copiedCsv, config.BaudRatesWirelessConn);

  	/* BAUD_RATES_DEVICE_CONN */
    numberOfCharsCopied = MINI_ini_gets("BaudRateConfiguration", "BAUD_RATES_DEVICE_CONN",  DEFAULT_CSV_STRING, copiedCsv, TEMP_CSV_SIZE, "serialSwitch_Config.ini");
  	csvToInt(copiedCsv, config.BaudRatesDeviceConn);


  	/* -------- ConnectionConfiguration -------- */
  	/* PRIO_WIRELESS_CONN_DEV_0 */
  	numberOfCharsCopied = MINI_ini_gets("ConnectionConfiguration", "PRIO_WIRELESS_CONN_DEV_0",  DEFAULT_CSV_STRING, copiedCsv, TEMP_CSV_SIZE, "serialSwitch_Config.ini");
  	csvToInt(copiedCsv, config.PrioWirelessConnDev0);

  	/* PRIO_WIRELESS_CONN_DEV_1 */
  	numberOfCharsCopied = MINI_ini_gets("ConnectionConfiguration", "PRIO_WIRELESS_CONN_DEV_1",  DEFAULT_CSV_STRING, copiedCsv, TEMP_CSV_SIZE, "serialSwitch_Config.ini");
  	csvToInt(copiedCsv, config.PrioWirelessConnDev1);

  	/* PRIO_WIRELESS_CONN_DEV_2 */
  	numberOfCharsCopied = MINI_ini_gets("ConnectionConfiguration", "PRIO_WIRELESS_CONN_DEV_2",  DEFAULT_CSV_STRING, copiedCsv, TEMP_CSV_SIZE, "serialSwitch_Config.ini");
  	csvToInt(copiedCsv, config.PrioWirelessConnDev2);

  	/* PRIO_WIRELESS_CONN_DEV_3 */
    numberOfCharsCopied = MINI_ini_gets("ConnectionConfiguration", "PRIO_WIRELESS_CONN_DEV_3",  DEFAULT_CSV_STRING, copiedCsv, TEMP_CSV_SIZE, "serialSwitch_Config.ini");
  	csvToInt(copiedCsv, config.PrioWirelessConnDev3);

  	/* SEND_CNT_WIRELESS_CONN_DEV_0 */
  	numberOfCharsCopied = MINI_ini_gets("ConnectionConfiguration", "SEND_CNT_WIRELESS_CONN_DEV_0",  DEFAULT_CSV_STRING, copiedCsv, TEMP_CSV_SIZE, "serialSwitch_Config.ini");
  	csvToInt(copiedCsv, config.SendCntWirelessConnDev0);

  	/* SEND_CNT_WIRELESS_CONN_DEV_1 */
  	numberOfCharsCopied = MINI_ini_gets("ConnectionConfiguration", "SEND_CNT_WIRELESS_CONN_DEV_1",  DEFAULT_CSV_STRING, copiedCsv, TEMP_CSV_SIZE, "serialSwitch_Config.ini");
  	csvToInt(copiedCsv, config.SendCntWirelessConnDev1);

  	/* SEND_CNT_WIRELESS_CONN_DEV_2 */
  	numberOfCharsCopied = MINI_ini_gets("ConnectionConfiguration", "SEND_CNT_WIRELESS_CONN_DEV_2",  DEFAULT_CSV_STRING, copiedCsv, TEMP_CSV_SIZE, "serialSwitch_Config.ini");
  	csvToInt(copiedCsv, config.SendCntWirelessConnDev2);

  	/* SEND_CNT_WIRELESS_CONN_DEV_3 */
    numberOfCharsCopied = MINI_ini_gets("ConnectionConfiguration", "SEND_CNT_WIRELESS_CONN_DEV_3",  DEFAULT_CSV_STRING, copiedCsv, TEMP_CSV_SIZE, "serialSwitch_Config.ini");
    csvToInt(copiedCsv, config.SendCntWirelessConnDev3);

  	/* -------- TransmissionConfiguration -------- */
  	/* PRIO_WIRELESS_CONN_DEV_0 */
  	numberOfCharsCopied = MINI_ini_gets("TransmissionConfiguration", "RESEND_DELAY_WIRELESS_CONN_DEV_0",  DEFAULT_CSV_STRING, copiedCsv, TEMP_CSV_SIZE, "serialSwitch_Config.ini");
  	csvToInt(copiedCsv, config.ResendDelayWirelessConnDev0);

  	/* PRIO_WIRELESS_CONN_DEV_1 */
  	numberOfCharsCopied = MINI_ini_gets("TransmissionConfiguration", "RESEND_DELAY_WIRELESS_CONN_DEV_1",  DEFAULT_CSV_STRING, copiedCsv, TEMP_CSV_SIZE, "serialSwitch_Config.ini");
  	csvToInt(copiedCsv, config.ResendDelayWirelessConnDev1);

  	/* PRIO_WIRELESS_CONN_DEV_2 */
  	numberOfCharsCopied = MINI_ini_gets("TransmissionConfiguration", "RESEND_DELAY_WIRELESS_CONN_DEV_2",  DEFAULT_CSV_STRING, copiedCsv, TEMP_CSV_SIZE, "serialSwitch_Config.ini");
  	csvToInt(copiedCsv, config.ResendDelayWirelessConnDev2);

  	/* PRIO_WIRELESS_CONN_DEV_3 */
  	numberOfCharsCopied = MINI_ini_gets("TransmissionConfiguration", "RESEND_DELAY_WIRELESS_CONN_DEV_3",  DEFAULT_CSV_STRING, copiedCsv, TEMP_CSV_SIZE, "serialSwitch_Config.ini");
  	csvToInt(copiedCsv, config.ResendDelayWirelessConnDev3);

  	/* MAX_THROUGHPUT_WIRELESS_CONN */
  	numberOfCharsCopied = MINI_ini_gets("TransmissionConfiguration", "MAX_THROUGHPUT_WIRELESS_CONN",  DEFAULT_CSV_STRING, copiedCsv, TEMP_CSV_SIZE, "serialSwitch_Config.ini");
  	csvToInt(copiedCsv, config.MaxThroughputWirelessConn);

  	/* USUAL_PACKET_SIZE_DEVICE_CONN */
  	numberOfCharsCopied = MINI_ini_gets("TransmissionConfiguration", "USUAL_PACKET_SIZE_DEVICE_CONN",  DEFAULT_CSV_STRING, copiedCsv, TEMP_CSV_SIZE, "serialSwitch_Config.ini");
  	csvToInt(copiedCsv, config.UsualPacketSizeDeviceConn);

  	/* PACKAGE_GEN_MAX_TIMEOUT */
  	numberOfCharsCopied = MINI_ini_gets("TransmissionConfiguration", "PACKAGE_GEN_MAX_TIMEOUT",  DEFAULT_CSV_STRING, copiedCsv, TEMP_CSV_SIZE, "serialSwitch_Config.ini");
  	csvToInt(copiedCsv, config.PackageGenMaxTimeout);

  	/* DELAY_DISMISS_OLD_PACK_PER_DEV */
  	numberOfCharsCopied = MINI_ini_gets("TransmissionConfiguration", "DELAY_DISMISS_OLD_PACK_PER_DEV",  DEFAULT_CSV_STRING, copiedCsv, TEMP_CSV_SIZE, "serialSwitch_Config.ini");
  	csvToInt(copiedCsv, config.DelayDismissOldPackagePerDev);

  	/* SEND_ACK_PER_WIRELESS_CONN */
  	numberOfCharsCopied = MINI_ini_gets("TransmissionConfiguration", "SEND_ACK_PER_WIRELESS_CONN",  DEFAULT_CSV_STRING, copiedCsv, TEMP_CSV_SIZE, "serialSwitch_Config.ini");
  	csvToBool(copiedCsv, config.SendAckPerWirelessConn);

  	/* USE_CTS_PER_WIRELESS_CONN */
  	numberOfCharsCopied = MINI_ini_gets("TransmissionConfiguration", "USE_CTS_PER_WIRELESS_CONN",  DEFAULT_CSV_STRING, copiedCsv, TEMP_CSV_SIZE, "serialSwitch_Config.ini");
  	csvToBool(copiedCsv, config.UseCtsPerWirelessConn);


  	/* -------- SoftwareConfiguration -------- */
  	/* TEST_HW_LOOPBACK_ONLY */
  	config.TestHwLoopbackOnly = MINI_ini_getbool("SoftwareConfiguration", "TEST_HW_LOOPBACK_ONLY",  DEFAULT_BOOL, "serialSwitch_Config.ini");

  	/* GENERATE_DEBUG_OUTPUT */
  	config.GenerateDebugOutput = MINI_ini_getbool("SoftwareConfiguration", "GENERATE_DEBUG_OUTPUT",  DEFAULT_BOOL, "serialSwitch_Config.ini");

  	/* SPI_HANDLER_TASK_INTERVAL */
  	config.SpiHandlerTaskInterval = MINI_ini_getl("SoftwareConfiguration", "SPI_HANDLER_TASK_INTERVAL",  DEFAULT_INT, "serialSwitch_Config.ini");

  	/* PACKAGE_GENERATOR_TASK_INTERVAL */
  	config.PackageHandlerTaskInterval = MINI_ini_getl("SoftwareConfiguration", "PACKAGE_GENERATOR_TASK_INTERVAL",  DEFAULT_INT, "serialSwitch_Config.ini");

  	/* NETWORK_HANDLER_TASK_INTERVAL */
    config.NetworkHandlerTaskInterval = MINI_ini_getl("SoftwareConfiguration", "NETWORK_HANDLER_TASK_INTERVAL",  DEFAULT_INT, "serialSwitch_Config.ini");

  	/* TOGGLE_GREEN_LED_INTERVAL */
  	config.ToggleGreenLedInterval = MINI_ini_getl("SoftwareConfiguration", "TOGGLE_GREEN_LED_INTERVAL",  DEFAULT_INT, "serialSwitch_Config.ini");

  	return true;
}
