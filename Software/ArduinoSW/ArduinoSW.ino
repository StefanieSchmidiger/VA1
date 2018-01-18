

/*
 Name:		SerialSwitchFirmware.ino
 Created:	3/30/2017 7:50:03 AM
 Author:	AndreasAlbisser
*/

#include "golay.h"
#include "throughputPrintout.h"
#include "wirelessPackageExtractor.h"
#include "wirelessSendHandler.h"
#include <Queue.h>			/* Installed as arduino library. See https://github.com/SMFSW/Queue */
#include <TaskScheduler.h>	/* Installed as arduino library. See https://github.com/arkhipenko/TaskScheduler */
#include "errorAndWarningOutput.h"
#include "serialSwitch_General.h"
#include "serialSwitch_Config.h"
#include "hwBufferInterface.h"
#include "spiInterface.h"
#include "packageGenerator.h"
#include "avr/wdt.h"




/*!
* \fn static void toggleGreenLed_TaskEntry(void)
* \brief Function that is called from the scheduler every TOGGLE_GREEN_LED_INTERVAL, just to show to the outside world that the scheduler is still running.
*/
static void toggleGreenLed_TaskEntry(void)
{
	/* toggle green LED */
	static bool greenLedStatus = false;
	if (greenLedStatus)
	{
		digitalWrite(LED_GREEN_PIN, HIGH);
		greenLedStatus = false;
	}
	else
	{
		digitalWrite(LED_GREEN_PIN, LOW);
		greenLedStatus = true;
	}
}




/*!
* \fn static void testLoopback_TaskEntry(void)
* \brief Task for loopback of the serial communication on all serial interfaces in order to test the hardware.
*/
void testLoopback_TaskEntry(void)
{
	uint8_t ch;
	uint8_t cnt;

	/* just for test purposes make loopback on device side */
	for (cnt = 0; cnt < NUM_OF_DEVICE_CONNECTIONS; cnt++)
	{
		while (queueDeviceReceiveUart[cnt].pull(&ch))
		{
			queueDeviceTransmitUart[cnt].push(&ch);
		}
	}

	/* also make loopback on wireless side */
	for (cnt = 0; cnt < NUM_OF_WIRELESS_CONNECTIONS; cnt++)
	{
		while (queueWirelessReceiveUart[cnt].pull(&ch))
		{
			queueWirelessTransmitUart[cnt].push(&ch);
		}
	}
}




/*!
* \fn static void testDataGenerator_TaskEntry(void)
* \brief Test task to be able to generate some test data.
*/
static void testDataGenerator_TaskEntry(void)
{
	/* Send some test data to the package generator, valid packets on the wireless side will be produced. */
	/* Also, flash the LED just to be able to make measurements external to validate the send frequendy. */
	digitalWrite(LED_GREEN_PIN, HIGH);
	uint8_t charToSend;
	for (uint16_t cnt = 0; cnt < 5; cnt++)
	{
		charToSend = (cnt % 10) + '0';
		for (uint8_t cnt = 0; cnt < NUM_OF_DEVICE_CONNECTIONS; cnt++)
		{
			queueDeviceReceiveUart[cnt].push(&charToSend);
		}
	}
	digitalWrite(LED_GREEN_PIN, LOW);
}








/* Declare and initialize task structures plus scheduler */
/* hardware buffer interface tasks */
Task hwBufIfDataReaderTask(HW_BUF_IF_DATA_READER_TASK_INTERVAL, TASK_FOREVER, &hwBufIfDataReader_TaskEntry);
Task hwBufIfDeviceDataWriterTask(HW_BUF_IF_DEVICE_DATA_WRITER_TASK_INTERVAL, TASK_FOREVER, &hwBufIfDeviceDataWriter_TaskEntry);
/* data writers and readers */
unsigned int maxThroughputsWireless[] = MAX_THROUGHPUT_WIRELESS_CONN;	/* calculate useful intervals for wireless data writer tasks depending on MAX_THROUGHPUT_WIRELESS_CONN */
Task hwBufIfWirelessDataWriterUart0Task((unsigned int)(ceilf(1000.0f / maxThroughputsWireless[0])), TASK_FOREVER, &hwBufIfWirelessDataWriter_Uart0_TaskEntry);
Task hwBufIfWirelessDataWriterUart1Task((unsigned int)(ceilf(1000.0f / maxThroughputsWireless[1])), TASK_FOREVER, &hwBufIfWirelessDataWriter_Uart1_TaskEntry);
Task hwBufIfWirelessDataWriterUart2Task((unsigned int)(ceilf(1000.0f / maxThroughputsWireless[2])), TASK_FOREVER, &hwBufIfWirelessDataWriter_Uart2_TaskEntry);
Task hwBufIfWirelessDataWriterUart3Task((unsigned int)(ceilf(1000.0f / maxThroughputsWireless[3])), TASK_FOREVER, &hwBufIfWirelessDataWriter_Uart3_TaskEntry);
/* package generator and extractor/handler */
Task packageGeneratorTask(PACKAGE_GENERATOR_TASK_INTERVAL, TASK_FOREVER, &packageGenerator_TaskEntry);
/* wireless send handler */
Task wirelessDataSendHandlerTask(WIRELESS_DATA_SEND_HANDLER_INTERVAL, TASK_FOREVER, &wirelessDataSendHandler_TaskEntry);
Task wirelessAckSendHandlerTask(WIRELESS_ACK_SEND_HANDLER_INTERVAL, TASK_FOREVER, &wirelessAckSendHandler_TaskEntry);
/* wireless package extractor */
Task wirelessPackageExtractorTask(WIRELESS_PACKAGE_EXTRACTOR_INTERVAL, TASK_FOREVER, &wirelessPackageExtractor_TaskEntry);
/* toggle green LED task */
Task toggleGreenLedTask(TOGGLE_GREEN_LED_INTERVAL, TASK_FOREVER, &toggleGreenLed_TaskEntry);
/* serial loopback task, enabled if TEST_HW_LOOPBACK_ONLY is set to 1 */
Task testLoopbackTask(1, TASK_FOREVER, &testLoopback_TaskEntry);
/* task for test purposes to generate data */
Task testDataGeneratorTask(TEST_DATA_GENERATOR_INTERVAL, TASK_FOREVER, &testDataGenerator_TaskEntry);
/* task to printout data and package throughput from time to time */
Task genThroughputPrintoutTask(GENERATE_THROUGHPUT_OUTPUT_INTERVAL, TASK_FOREVER, &genThroughputPrintout_TaskEntry);
/* scheduler */
Scheduler sched;





/*!
* \fn void setup()
* \brief Called once at the beginning to initialize stuff.
*/
void setup()
{
	/* initialize reset and IRQ pins */
	pinMode(PIN_RESET_WIRELESS_SIDE, OUTPUT);
	pinMode(PIN_RESET_DEVICE_SIDE, OUTPUT);
	pinMode(PIN_IRQ_WIRELESS_SIDE, INPUT);
	pinMode(PIN_IRQ_DEVICE_SIDE, INPUT);

	/* configure and initialize LED pins, set them all high at the beginning (to be able to check that those all work) */
	pinMode(LED_GREEN_PIN, OUTPUT);
	pinMode(LED_ORANGE_PIN, OUTPUT);
	pinMode(LED_RED_PIN, OUTPUT);
	digitalWrite(LED_GREEN_PIN, HIGH);
	digitalWrite(LED_ORANGE_PIN, HIGH);
	digitalWrite(LED_RED_PIN, HIGH);

	/* initialize USB serial connection and print out data of firmware compilation */
	Serial.begin(115200);
	char infoBuf[128];
	sprintf(infoBuf, "Starting UAV Serial Switch, Firmware Compile Date and Time: %s  %s", __DATE__, __TIME__);
	showInfo(__FUNCTION__, infoBuf);

	/*
	Initialize MAX14830's:
	- Reset (pull reset signal down)
	- Wait until IRQ is high (after this, MAX14830's communication interface is ready)
	- Set BRGConfig to 0 and CLKSource[CrystalEn] to 1 to select crystal as clock source
	- Wait on STSInt (clock stable)
	- Program UART baud rates
	*/

	/* Reset the two MAX14830 */
	digitalWrite(PIN_RESET_WIRELESS_SIDE, LOW);
	digitalWrite(PIN_RESET_DEVICE_SIDE, LOW);
	delay(200);
	/* There are external pull ups available, so here we switch them back in high impedance mode */
	pinMode(PIN_RESET_WIRELESS_SIDE, INPUT);
	pinMode(PIN_RESET_DEVICE_SIDE, INPUT);

	/* Wait until both IRQ's are high (means that the MAX14830 are ready to be written to) */
	while ((digitalRead(PIN_IRQ_WIRELESS_SIDE) == LOW) || (digitalRead(PIN_IRQ_DEVICE_SIDE) == LOW)) delay(20);

	/* initialize SPI interface plus pins */
	spiInitialize();

	/* Set PLL devider and multiplier */
	spiWriteToAllUartInterfaces(MAX_REG_PLL_CONFIG, 0x06);	/* 0x06: Multiply by 6, factor 6 => freq_in*1 in PLL */

	/* Set devider in baud rate register */
	/* Input is 3.686 MHZ when PLL factor is 1. Baud rate is this clock /16 => /2 = 115200 baud; /4 = 57600; .. */
	unsigned int baudRateDevices[] = BAUD_RATES_DEVICE_CONN;
	unsigned int baudRateWireless[] = BAUD_RATES_WIRELESS_CONN;
	hwBufIfConfigureBaudRate(MAX_14830_DEVICE_SIDE, MAX_UART_0, baudRateDevices[0]);
	hwBufIfConfigureBaudRate(MAX_14830_DEVICE_SIDE, MAX_UART_1, baudRateDevices[1]);
	hwBufIfConfigureBaudRate(MAX_14830_DEVICE_SIDE, MAX_UART_2, baudRateDevices[2]);
	hwBufIfConfigureBaudRate(MAX_14830_DEVICE_SIDE, MAX_UART_3, baudRateDevices[3]);
	hwBufIfConfigureBaudRate(MAX_14830_WIRELESS_SIDE, MAX_UART_0, baudRateWireless[0]);
	hwBufIfConfigureBaudRate(MAX_14830_WIRELESS_SIDE, MAX_UART_1, baudRateWireless[1]);
	hwBufIfConfigureBaudRate(MAX_14830_WIRELESS_SIDE, MAX_UART_2, baudRateWireless[2]);
	hwBufIfConfigureBaudRate(MAX_14830_WIRELESS_SIDE, MAX_UART_3, baudRateWireless[3]);

	/* configure hardware flow control (CTS only) if configured */
	unsigned int ctsUsageWireless[] = USE_CTS_PER_WIRELESS_CONN;
	spiWriteToAllUartInterfaces(MAX_REG_MODE1, 0x02);	/* TX needs to be disabled before changing anything on the CTS behaviour */
	if (ctsUsageWireless[0] > 0)		spiSingleWriteTransfer(MAX_14830_WIRELESS_SIDE, MAX_UART_0, MAX_REG_FLOW_CTRL, 0x02);
	if (ctsUsageWireless[1] > 0)		spiSingleWriteTransfer(MAX_14830_WIRELESS_SIDE, MAX_UART_1, MAX_REG_FLOW_CTRL, 0x02);
	if (ctsUsageWireless[2] > 0)		spiSingleWriteTransfer(MAX_14830_WIRELESS_SIDE, MAX_UART_2, MAX_REG_FLOW_CTRL, 0x02);
	if (ctsUsageWireless[3] > 0)		spiSingleWriteTransfer(MAX_14830_WIRELESS_SIDE, MAX_UART_3, MAX_REG_FLOW_CTRL, 0x02);
	//spiWriteToAllUartInterfaces(MAX_REG_MODE1, 0x00);	/* enable TX again */

	/* PLL bypass disable, PLL enable, external crystal enable */
	spiWriteToAllUartInterfaces(MAX_REG_CLK_SOURCE, 0x06);

	/* Set word length and number of stop bits */
	spiWriteToAllUartInterfaces(MAX_REG_LCR, 0x03);

  delay(10000); /* wait 10sek */
  uint8_t readData = spiSingleReadTransfer(MAX_14830_DEVICE_SIDE, MAX_UART_0, MAX_REG_PLL_CONFIG); /* set to 6 in task init */
  delay(10000); /* wait 10sek */


	/* initialize scheduler and add tasks */
	sched.init();
	sched.addTask(hwBufIfDataReaderTask);
	sched.addTask(hwBufIfDeviceDataWriterTask);
	sched.addTask(hwBufIfWirelessDataWriterUart0Task);
	sched.addTask(hwBufIfWirelessDataWriterUart1Task);
	sched.addTask(hwBufIfWirelessDataWriterUart2Task);
	sched.addTask(hwBufIfWirelessDataWriterUart3Task);
	sched.addTask(packageGeneratorTask);
	sched.addTask(wirelessDataSendHandlerTask);
	sched.addTask(wirelessAckSendHandlerTask);
	sched.addTask(wirelessPackageExtractorTask);
	sched.addTask(toggleGreenLedTask);
	sched.addTask(testLoopbackTask);
	sched.addTask(testDataGeneratorTask);
	sched.addTask(genThroughputPrintoutTask);
	/* start tasks */
	hwBufIfDataReaderTask.enable();
	hwBufIfDeviceDataWriterTask.enable();
	hwBufIfWirelessDataWriterUart0Task.enable();
	hwBufIfWirelessDataWriterUart1Task.enable();
	hwBufIfWirelessDataWriterUart2Task.enable();
	hwBufIfWirelessDataWriterUart3Task.enable();
#if TEST_HW_LOOPBACK_ONLY > 0
	testLoopbackTask.enable();
	toggleGreenLedTask.enable();
	showInfo(__FUNCTION__, "Enable loopback on all serial interfaces in order to test the hardware");
#else /* TEST_HW_LOOPBACK_ONLY */
	packageGeneratorTask.enable();
	wirelessDataSendHandlerTask.enable();
	wirelessAckSendHandlerTask.enable();
	wirelessPackageExtractorTask.enable();
#endif /* TEST_HW_LOOPBACK_ONLY */
#if GENERATE_THROUGHPUT_OUTPUT > 0
	genThroughputPrintoutTask.enable();
#endif /* GENERATE_THROUGHPUT_OUTPUT */
#if ENABLE_TEST_DATA_GEN > 0
	testDataGeneratorTask.enable();
	showInfo(__FUNCTION__, "Enable test data generator");
#else
	toggleGreenLedTask.enable();
#endif /* ENABLE_TEST_DATA_GEN */

	/* enable watchdog */
	//wdt_enable(WDTO_250MS);// TODO does not work currently..why?
	//wdt_reset();

	/* print out info that setup is finished */
	showInfo(__FUNCTION__, "Initialization finished");

	/* switch off the LED's */
	digitalWrite(LED_GREEN_PIN, LOW);
	digitalWrite(LED_ORANGE_PIN, LOW);
	digitalWrite(LED_RED_PIN, LOW);
}

/*!
* \fn void loop()
* \brief Called continuesly after initialization.
*/
void loop()
{
	/* call scheduler */
	sched.execute();
}
