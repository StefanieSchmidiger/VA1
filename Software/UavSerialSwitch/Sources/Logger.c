#include "Logger.h"
#include "FAT1.h"
#include "CLS1.h"
#include "FRTOS.h"
#include "Config.h"
#include "UTIL1.h"
#include "XF1.h"
#include "PackageHandler.h" /* tWirelessPackage */
#include "SpiHandler.h" /* tUartNr, tSpiSlave */

#define FILENAME_ARRAY_SIZE (35)

/* global variables, only used in this file */
const char* queueNameReceivedPackages[] = {"ReceivedPackagesForLogging0", "ReceivedPackagesForLogging1", "ReceivedPackagesForLogging2", "ReceivedPackagesForLogging3"};
const char* queueNameSentPackages[] = {"SentPackagesForLogging0", "SentPackagesForLogging1", "SentPackagesForLogging2", "SentPackagesForLogging3"};
char filenameReceivedPackagesLogger[NUMBER_OF_UARTS][FILENAME_ARRAY_SIZE];
char filenameSentPackagesLogger[NUMBER_OF_UARTS][FILENAME_ARRAY_SIZE];
static xQueueHandle queuePackagesToLog[2][NUMBER_OF_UARTS];  /* queuePackagesToLog[0] = received packages, queuePackagesToLog[1] = sent packages */
static FIL fp;

/* prototypes */
void initLoggerQueues(void);
static bool WriteToFile(char* fileName, char* logEntry);
static bool writeLogHeader(char* fileName);
static void packageToLogString(tWirelessPackage pack, char* logEntry, int logEntryStrSize);


void logger_TaskEntry(void* p)
{
	UINT buffLen = 100;
	char buf[FILENAME_ARRAY_SIZE];
	static tWirelessPackage pack;
	static char logString[500];

	const TickType_t taskInterval = pdMS_TO_TICKS(config.LoggerTaskInterval); /* task interval  */
	TickType_t lastWakeTime = xTaskGetTickCount(); /* Initialize the xLastWakeTime variable with the current time. */

	for(int uartNr = 0; uartNr < NUMBER_OF_UARTS; uartNr++) /* write log header into all files */
	{
		writeLogHeader(filenameSentPackagesLogger[uartNr]);
		writeLogHeader(filenameReceivedPackagesLogger[uartNr]);
	}

	for(;;) /* endless loop */
	{
		vTaskDelayUntil( &lastWakeTime, taskInterval ); /* Wait for the next cycle */
		for(int uartNr = 0; uartNr < NUMBER_OF_UARTS; uartNr++)
		{
			while(xQueueReceive(queuePackagesToLog[SENT_PACKAGE][uartNr], &pack, ( TickType_t ) pdMS_TO_TICKS(MAX_DELAY_LOGGER_MS) ) == pdTRUE)
			{
				packageToLogString(pack, logString, sizeof(logString));
				WriteToFile(filenameSentPackagesLogger[uartNr], logString); // Todo: dont do write in every task interval
				vPortFree(pack.payload);
			}
			while(xQueueReceive(queuePackagesToLog[RECEIVED_PACKAGE][uartNr], &pack, ( TickType_t ) pdMS_TO_TICKS(MAX_DELAY_LOGGER_MS) ) == pdTRUE)
			{
				packageToLogString(pack, logString, sizeof(logString));
				WriteToFile(filenameReceivedPackagesLogger[uartNr], logString); // Todo: dont do write in every task interval
				vPortFree(pack.payload);
			}
		}
	}
}

void logger_TaskInit(void)
{
	CLS1_StdIOType* io = CLS1_GetStdio();
	static FAT1_FATFS fileSystemObject;
	tWirelessPackage pack;
	bool cardMounted = 0;

	initLoggerQueues();

	(void)FAT1_CheckCardPresence(&cardMounted, (unsigned char*)"0" /*volume*/, &fileSystemObject, io);
	FAT1_MountFileSystem(&fileSystemObject, "", io);

	if(FAT1_ChangeDirectory("LogFiles", io) != ERR_OK) /* logging directory doesn't exist? */
	{
		if(FAT1_MakeDirectory("LogFiles", io) != ERR_OK) /* create logging directory */
			while(1){} /* unable to create directory */
		if(FAT1_ChangeDirectory("LogFiles", io) != ERR_OK) /* switch to logging directory */
			while(1){} /* could not switch to logging directory */
	}
	FAT1_ChangeDirectory("..", io); /* change back into root directory because changing directory is done upon write to SD card */

	/* create variable for filenames for future use within this task */
	for(char uartNr = '0'; uartNr < NUMBER_OF_UARTS + '0'; uartNr++)
	{
		if(XF1_xsprintf(filenameReceivedPackagesLogger[(int)(uartNr-'0')], "./receivedPackagesForConn%c", uartNr) <= 0)
			while(1){}
		if(XF1_xsprintf(filenameSentPackagesLogger[(int)(uartNr-'0')], "./sentPackagesForConn%c", uartNr) <= 0)
			while(1){}
	}

	/* debug: add a package to queue to see if it will be logged correctly */
	pack.packType = 1;
	pack.sessionNr = 0x12;
	pack.devNum = 2;
	pack.crc8Header = 0x88;
	pack.sysTime = 0x123456;
	pack.payloadSize = 0x04;
	pack.payload = (uint8_t*) FRTOS_pvPortMalloc(4*sizeof(int8_t));
	pack.payload[0] = 0x00;
	pack.payload[1] = 0x01;
	pack.payload[2] = 0x02;
	pack.payload[3] = 0x03;
	pack.crc16payload = 0x1616;
	pushPackageToLoggerQueue(pack, SENT_PACKAGE, 2);
}

/*!
* \fn void initLoggerQueues(void)
* \brief This function initializes the array of queues
*/
void initLoggerQueues(void)
{
	for(int uartNr = 0; uartNr<NUMBER_OF_UARTS; uartNr++)
	{
		queuePackagesToLog[SENT_PACKAGE][uartNr] = xQueueCreate( QUEUE_NUM_OF_LOG_ENTRIES, sizeof(tWirelessPackage));
		if(queuePackagesToLog[SENT_PACKAGE][uartNr] == NULL)
			while(true){} /* malloc for queue failed */
		vQueueAddToRegistry(queuePackagesToLog[SENT_PACKAGE][uartNr], queueNameSentPackages[uartNr]);

		queuePackagesToLog[RECEIVED_PACKAGE][uartNr] = xQueueCreate( QUEUE_NUM_OF_LOG_ENTRIES, sizeof(tWirelessPackage));
		if(queuePackagesToLog[RECEIVED_PACKAGE][uartNr] == NULL)
			while(true){} /* malloc for queue failed */
		vQueueAddToRegistry(queuePackagesToLog[RECEIVED_PACKAGE][uartNr], queueNameReceivedPackages[uartNr]);
	}
}

static bool WriteToFile(char* fileName, char* logEntry)
{
  uint8_t timestamp[FILENAME_ARRAY_SIZE];
  UINT bw;
  TIMEREC time;
  CLS1_StdIOType* io = CLS1_GetStdio();
  static char fullFileName[FILENAME_ARRAY_SIZE];

  UTIL1_strcpy(fullFileName, FILENAME_ARRAY_SIZE, fileName);
  UTIL1_strcat(fullFileName, FILENAME_ARRAY_SIZE, ".log");

  FAT1_ChangeDirectory("LogFiles", io); /* change into log folder */
  /* check file size */
  if (FAT1_open(&fp, fullFileName, FA_OPEN_ALWAYS|FA_WRITE)!=FR_OK) /* open file */
	  return false;
  if(FAT1_f_size(&fp) > MAX_LOG_FILE_SIZE_BYTES) /* max 10MB per file */
  {
	  static char oldFileEnding[6];
	  static char newFileEnding[6];
	  static char oldFileName[FILENAME_ARRAY_SIZE];
	  static char newFileName[FILENAME_ARRAY_SIZE];
	  (void)FAT1_close(&fp); /* closing file */
	  /* rename all log files by incrementing their count number, e.g. filename_3.log will be filename_4.log */
	  for(int oldFileNumber = MAX_NUMBER_OF_OLD_LOG_FILES_KEPT-2; oldFileNumber >= 0; oldFileNumber--)
	  {
		  XF1_xsprintf(oldFileEnding, "_%u.log", oldFileNumber);
		  XF1_xsprintf(newFileEnding, "_%u.log", oldFileNumber+1);
		  UTIL1_strcpy(oldFileName, FILENAME_ARRAY_SIZE, fileName);
		  UTIL1_strcpy(newFileName, FILENAME_ARRAY_SIZE, fileName);
		  UTIL1_strcat(oldFileName, FILENAME_ARRAY_SIZE, oldFileEnding);
		  UTIL1_strcat(newFileName, FILENAME_ARRAY_SIZE, newFileEnding);
		  FAT1_DeleteFile(newFileName, io);
		  FAT1_RenameFile(oldFileName, newFileName, io);
	  }
	  FAT1_DeleteFile(oldFileName, io); /* delete filename_0.log */
	  FAT1_RenameFile(fullFileName, oldFileName, io); /* rename filename.log to filename_0.log */
	  if (FAT1_open(&fp, fullFileName, FA_OPEN_ALWAYS|FA_WRITE)!=FR_OK) /* create new file and open file */
	  	  return false;
  }

  if (FAT1_lseek(&fp, FAT1_f_size(&fp)) != FR_OK || fp.fptr != FAT1_f_size(&fp)) /* move to the end of the file */
	return false;
	#if 0
	  if (TmDt1_GetTime(&time)!=ERR_OK) /* get time */
		  return false;
	  timestamp[0] = '\0';
	  UTIL1_strcatNum8u(timestamp, sizeof(timestamp), time.Hour);
	  UTIL1_chcat(timestamp, sizeof(timestamp), ':');
	  UTIL1_strcatNum8u(timestamp, sizeof(timestamp), time.Min);
	  UTIL1_chcat(timestamp, sizeof(timestamp), ':');
	  UTIL1_strcatNum8u(timestamp, sizeof(timestamp), time.Sec);
	  UTIL1_chcat(timestamp, sizeof(timestamp), ';');
	  if (FAT1_write(&fp, timestamp, UTIL1_strlen((char*)timestamp), &bw)!=FR_OK)
	  {
		(void)FAT1_close(&fp);
		return false;
	  }
	#endif

	if (FAT1_write(&fp, logEntry, UTIL1_strlen((char*)logEntry), &bw)!=FR_OK) /* write data */
	{
	  (void)FAT1_close(&fp);
	  return false;
	}
	(void)FAT1_close(&fp); /* closing file */
	return true;
}


static bool writeLogHeader(char* fileName)
{
	static char logHeader[] = "\r\nRunningTime;PackageType;DeviceNumber;SessionNumber;SystemTime;PayloadSize;CRC8_Header;Payload;CRC16_Payload\r\n";
	return WriteToFile(fileName, logHeader);
}

/*!
* \fn static void packageToLogString(tWirelessPackage pack, char* logEntry, int logEntryStrSize)
* \brief Puts all data froma  wirelessPackage into a string for logging
* +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++6
* \param package: The wireless package itself
* \param rxTxPackage: Information weather this is a received package or a sent package
* \param wlConnNr: wireless connection number over which package was received/sent
* \return pdTRUE if successful, pdFAIL if unsuccessful:
*/
static void packageToLogString(tWirelessPackage pack, char* logEntry, int logEntryStrSize)
{
	static char strNum[8];
	logEntry[0] = 0;
	UTIL1_strcatNum8Hex(strNum, sizeof(strNum), pack.packType);
	UTIL1_strcat(logEntry, logEntryStrSize, strNum);
	UTIL1_strcat(logEntry, logEntryStrSize, ";");
	strNum[0] = 0;
	UTIL1_strcatNum8Hex(strNum, sizeof(strNum), pack.devNum);
	UTIL1_strcat(logEntry, logEntryStrSize, strNum);
	UTIL1_strcat(logEntry, logEntryStrSize, ";");
	strNum[0] = 0;
	UTIL1_strcatNum8Hex(strNum, sizeof(strNum), pack.sessionNr);
	UTIL1_strcat(logEntry, logEntryStrSize, strNum);
	UTIL1_strcat(logEntry, logEntryStrSize, ";");
	strNum[0] = 0;
	UTIL1_strcatNum32Hex(strNum, sizeof(strNum), pack.sysTime);
	UTIL1_strcat(logEntry, logEntryStrSize, strNum);
	UTIL1_strcat(logEntry, logEntryStrSize, ";");
	strNum[0] = 0;
	UTIL1_strcatNum16Hex(strNum, sizeof(strNum), pack.payloadSize);
	UTIL1_strcat(logEntry, logEntryStrSize, strNum);
	UTIL1_strcat(logEntry, logEntryStrSize, ";");
	strNum[0] = 0;
	UTIL1_strcatNum8Hex(strNum, sizeof(strNum), pack.crc8Header);
	UTIL1_strcat(logEntry, logEntryStrSize, strNum);
	UTIL1_strcat(logEntry, logEntryStrSize, ";");
	for(int i=0; i<pack.payloadSize; i++) // ToDo: payload is not logged
	{
		strNum[0] = 0;
		UTIL1_strcatNum8Hex(strNum, sizeof(strNum), pack.payload[i]);
		UTIL1_strcat(logEntry, logEntryStrSize, strNum);
	}
	UTIL1_strcat(logEntry, logEntryStrSize, ";");
	strNum[0] = 0;
	UTIL1_strcatNum16Hex(strNum, sizeof(strNum), pack.crc16payload);
	UTIL1_strcat(logEntry, logEntryStrSize, strNum);
	UTIL1_strcat(logEntry, logEntryStrSize, "\r\n");
}

/*!
* \fn BaseType_t pushPackageToLoggerQueue(tWirelessPackage package, tRxTxPackage rxTxPackage, tUartNr uartNr)
* \brief Logs package content and frees memory of package when it is popped from queue
* \param package: The wireless package itself
* \param rxTxPackage: Information weather this is a received package or a sent package
* \param wlConnNr: wireless connection number over which package was received/sent
* \return pdTRUE if successful, pdFAIL if unsuccessful:
*/
BaseType_t pushPackageToLoggerQueue(tWirelessPackage package, tRxTxPackage rxTxPackage, tUartNr wlConnNr)
{
	if((wlConnNr >= NUMBER_OF_UARTS) | (rxTxPackage > SENT_PACKAGE)) /* invalid arguments -> return immediately */
	{
		/* free memory before returning */
		FRTOS_vPortFree(package.payload); /* free memory allocated when message was pushed into queue */
		return pdFAIL;
	}
	/* push package to queue */
	if(xQueueSendToBack(queuePackagesToLog[rxTxPackage][wlConnNr], &package, ( TickType_t ) pdMS_TO_TICKS(MAX_DELAY_LOGGER_QUEUE_OPERATION_MS) ) != pdTRUE)
	{
		/* free memory before returning */
		FRTOS_vPortFree(package.payload); /* free memory allocated when message was pushed into queue */
		return pdFAIL;
	}
	return pdTRUE; /* return success*/
}

