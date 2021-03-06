
#include "SPI.h"
#include "SpiHandler.h" // queues, tasks, semaphores
#include <stdio.h> // sprintf
#include "Config.h" // baudrates
#include "nResetDeviceSide.h" // pin configuration
#include "nResetWirelessSide.h" // pin configuration
#include "nIrqDeviceSide.h" // pin configuration
#include "nIrqWirelessSide.h" // pin configuration

#define CS_DEVICE 			0
#define CS_WIRELESS 		1

#define WRITE_TRANSFER 		true
#define READ_TRANSFER 		false
#define SINGLE_BYTE			1

// global variables, only used in this file
LDD_TDeviceData* spiDevice; /* For different functions to access SPI device */
static xQueueHandle TxWirelessBytes[NUMBER_OF_UARTS]; /* Incoming data from wireless side stored here */
static xQueueHandle RxWirelessBytes[NUMBER_OF_UARTS]; /* Outgoing data to wireless side stored here */
static xQueueHandle TxDeviceBytes[NUMBER_OF_UARTS]; /* Incoming data from device side stored here */
static xQueueHandle RxDeviceBytes[NUMBER_OF_UARTS];  /* Outgoing data to device side stored here */
xSemaphoreHandle spiRxMutex; /* Semaphore given in SPI_OnBlockReceived */
xSemaphoreHandle spiTxMutex; /* Semaphore given in SPI_OnBlockSent */

// prototypes, only used in this file
void spiHandler_TaskInit(void);
bool spiTransfer(tSpiSlaves spiSlave, tUartNr uartNr, tMax14830Reg reg, bool write, uint8_t* pData, uint8_t numOfTransfers);
void spiWriteToAllUartInterfaces(tMax14830Reg reg, uint8_t data);
bool spiSingleWriteTransfer(tSpiSlaves spiSlave, tUartNr uartNr, tMax14830Reg reg, uint8_t data);
uint8_t spiSingleReadTransfer(tSpiSlaves spiSlave, tUartNr uartNr, tMax14830Reg reg);
void configureHwBufBaudrate(tSpiSlaves spiSlave, tUartNr uartNr, unsigned int baudRateToSet);
void initSpiHandlerQueues(void);
static uint16_t readHwBufAndWriteToQueue(tSpiSlaves spiSlave, tUartNr uartNr, xQueueHandle queue);
static uint16_t readQueueAndWriteToHwBuf(tSpiSlaves spiSlave, tUartNr uartNr, xQueueHandle queue, uint8_t numOfBytesToWrite);


/*!
* \fn void spiHandler_TaskEntry(void)
* \brief Task initializes SPI, used queues and MAX14830.
* Periodically reads and writes bytes to and from byte queue.
*/
void spiHandler_TaskEntry(void* p)
{
	TickType_t lastWakeTime;
	const TickType_t taskInterval = pdMS_TO_TICKS(config.SpiHandlerTaskInterval);
	spiHandler_TaskInit();
	for(;;)
	{
		lastWakeTime = xTaskGetTickCount(); /* Initialize the xLastWakeTime variable with the current time. */
		/* read all data and write it to queue */
		for(int uartNr = 0; uartNr < NUMBER_OF_UARTS; uartNr++)
		{
			/* read data from device spi interface */
			readHwBufAndWriteToQueue(MAX_14830_DEVICE_SIDE, uartNr, RxDeviceBytes[uartNr]);
			/* write data from queue to device spi interface */
			readQueueAndWriteToHwBuf(MAX_14830_DEVICE_SIDE, uartNr, TxDeviceBytes[uartNr], HW_FIFO_SIZE);
			/* read data from wireless spi interface */
			readHwBufAndWriteToQueue(MAX_14830_WIRELESS_SIDE, uartNr, RxWirelessBytes[uartNr]);
			/* write data from queue to wireless spi interface */
			readQueueAndWriteToHwBuf(MAX_14830_WIRELESS_SIDE, uartNr, TxWirelessBytes[uartNr], HW_FIFO_SIZE);
		}
		vTaskDelayUntil( &lastWakeTime, taskInterval ); /* Wait for the next cycle */
	}
}


/*!
* \fn void spiHandler_TaskInit(void)
* \brief Initializes all components used in spiHandler_TaskEntry(): Queues, SPI, Semaphores and gets MAX14830 ready for usage
*/
void spiHandler_TaskInit(void)
{
	spiDevice = SPI_Init(NULL); /* no auto-init in SPIMaster_LDD used because this variable is needed for ChangeConfiguration */
	initSpiHandlerQueues();

	spiRxMutex = FRTOS_xSemaphoreCreateBinary(); // Waits on Spi_ReceiveBlock
	spiTxMutex = FRTOS_xSemaphoreCreateBinary(); // Waits for previous Spi_SendBlock to finish

	/* http://www.freertos.org/xSemaphoreCreateBinary.html:
	 * The semaphore is created in the 'empty' state, meaning the semaphore must first be given using the xSemaphoreGive()
	 * before it can subsequently be taken (obtained) using the xSemaphoreTake() function. */
	xSemaphoreGive(spiTxMutex); /* make sure Semaphore is given by default and can be taken for first SPI_send() */


	/*
	Initialize MAX14830's:
	- Reset (pull reset signal down)
	- Wait until IRQ is high (after this, MAX14830's communication interface is ready)
	- Set BRGConfig to 0 and CLKSource[CrystalEn] to 1 to select crystal as clock source
	- Wait on STSInt (clock stable)
	- Program UART baud rates
	*/

	/* Reset the two MAX14830 */
	nResetWirelessSide_SetOutput();
	nResetDeviceSide_SetOutput();
	nResetWirelessSide_PutVal(0);
	nResetDeviceSide_PutVal(0);

	vTaskDelay(pdMS_TO_TICKS(200)); /* Wait for the next cycle */

	/* There are external pull ups available, so here we switch them back in high impedance mode */
	nResetWirelessSide_PutVal(1);
	nResetDeviceSide_PutVal(1);
	nResetDeviceSide_SetInput();
	nResetWirelessSide_SetInput();


	/* Wait until both IRQ's are high (means that the MAX14830 are ready to be written to) */
	while ((nIrqWirelessSide_GetVal() == false) || (nIrqDeviceSide_GetVal() == false))
	{
		vTaskDelay(pdMS_TO_TICKS(20)); /* Wait for the next cycle */
	}

	/* Set PLL devider and multiplier */
	spiWriteToAllUartInterfaces(MAX_REG_PLL_CONFIG, 0x06);	/* 0x06: Multiply by 6, factor 6 => freq_in*1 in PLL */

	/* Set devider in baud rate register */
	/* Input is 3.686 MHZ when PLL factor is 1. Baud rate is this clock /16 => /2 = 115200 baud; /4 = 57600; .. */
	configureHwBufBaudrate(MAX_14830_DEVICE_SIDE, MAX_UART_0, config.BaudRatesDeviceConn[0]);
	configureHwBufBaudrate(MAX_14830_DEVICE_SIDE, MAX_UART_1, config.BaudRatesDeviceConn[1]);
	configureHwBufBaudrate(MAX_14830_DEVICE_SIDE, MAX_UART_2, config.BaudRatesDeviceConn[2]);
	configureHwBufBaudrate(MAX_14830_DEVICE_SIDE, MAX_UART_3, config.BaudRatesDeviceConn[3]);
	configureHwBufBaudrate(MAX_14830_WIRELESS_SIDE, MAX_UART_0, config.BaudRatesWirelessConn[0]);
	configureHwBufBaudrate(MAX_14830_WIRELESS_SIDE, MAX_UART_1, config.BaudRatesWirelessConn[1]);
	configureHwBufBaudrate(MAX_14830_WIRELESS_SIDE, MAX_UART_2, config.BaudRatesWirelessConn[2]);
	configureHwBufBaudrate(MAX_14830_WIRELESS_SIDE, MAX_UART_3, config.BaudRatesWirelessConn[3]);

	/* configure hardware flow control (CTS only) if configured */
	spiWriteToAllUartInterfaces(MAX_REG_MODE1, 0x02);	/* TX needs to be disabled before changing anything on the CTS behaviour */
	if (config.UseCtsPerWirelessConn[0] > 0)		spiSingleWriteTransfer(MAX_14830_WIRELESS_SIDE, MAX_UART_0, MAX_REG_FLOW_CTRL, 0x02);
	if (config.UseCtsPerWirelessConn[1] > 0)		spiSingleWriteTransfer(MAX_14830_WIRELESS_SIDE, MAX_UART_1, MAX_REG_FLOW_CTRL, 0x02);
	if (config.UseCtsPerWirelessConn[2] > 0)		spiSingleWriteTransfer(MAX_14830_WIRELESS_SIDE, MAX_UART_2, MAX_REG_FLOW_CTRL, 0x02);
	if (config.UseCtsPerWirelessConn[3] > 0)		spiSingleWriteTransfer(MAX_14830_WIRELESS_SIDE, MAX_UART_3, MAX_REG_FLOW_CTRL, 0x02);
	//spiWriteToAllUartInterfaces(MAX_REG_MODE1, 0x00);	/* enable TX again */

	/* PLL bypass disable, PLL enable, external crystal enable */
	spiWriteToAllUartInterfaces(MAX_REG_CLK_SOURCE, 0x06);

	/* Set word length and number of stop bits */
	spiWriteToAllUartInterfaces(MAX_REG_LCR, 0x03);
}



/*!
* \fn void initQueues(void)
* \brief This function initializes the array of queues
*/
void initSpiHandlerQueues(void)
{
	for(int uartNr=0; uartNr<NUMBER_OF_UARTS; uartNr++)
	{
		RxWirelessBytes[uartNr] = xQueueCreate( QUEUE_NUM_OF_CHARS_WL_RX_QUEUE, sizeof(uint8_t));
		RxDeviceBytes[uartNr] = xQueueCreate( QUEUE_NUM_OF_CHARS_DEV_RX_QUEUE, sizeof(uint8_t));
		TxWirelessBytes[uartNr] = xQueueCreate( QUEUE_NUM_OF_CHARS_WL_TX_QUEUE, sizeof(uint8_t));
		TxDeviceBytes[uartNr] = xQueueCreate( QUEUE_NUM_OF_CHARS_DEV_TX_QUEUE, sizeof(uint8_t));
	}
}

/*!
* \fn uint8_t spiSingleReadTransfer(tSpiSlaves spiSlave, tUartNr uartNr, tMax14830Reg reg)
* \brief Reads a single byte from the desired register.
* \param spiSlave: SPI slave where the data should be written to.
* \param uartNr: The number of the UART of the MAX14830 chip.
* \param reg: The register the data should be written to.
* \return Data that was read from the desired register.
*/
uint8_t spiSingleReadTransfer(tSpiSlaves spiSlave, tUartNr uartNr, tMax14830Reg reg)
{
	static uint8_t readData[2]; /* spi transfer needs one extra byte for commando */
	spiTransfer(spiSlave, uartNr, reg, READ_TRANSFER, readData, SINGLE_BYTE);
	return readData[1]; /* readData[0] holds answer to commando byte and no data for user */
}



/*!
* \fn bool spiSingleWriteTransfer(tSpiSlaves spiSlave, tUartNr uartNr, tMax14830Reg reg, uint8_t data)
* \brief Writes a single byte to the desired register.
* \param spiSlave: SPI slave where the data should be written to.
* \param uartNr: The number of the UART of the MAX14830 chip.
* \param reg: The register the data should be written to.
* \param data: Data byte that is written to the corresponding register.
* \return true if the data could be written, false otherwise.
*/
bool spiSingleWriteTransfer(tSpiSlaves spiSlave, tUartNr uartNr, tMax14830Reg reg, uint8_t data)
{
	static uint8_t writeData[2];
	writeData[1] = data; /* write[0] will be filled with commando */
	return spiTransfer(spiSlave, uartNr, reg, WRITE_TRANSFER, writeData, SINGLE_BYTE);
}



/*!
* \fn void spiWriteToAllUartInterfaces(bool write, tMax14830Reg reg, uint8_t data)
* \brief SPI transfer that writes the corresponding data to all UART interfaces.
* \param reg: The register the data should be written to.
* \param data: Data that should be written to the corresponding register.
*/
void spiWriteToAllUartInterfaces(tMax14830Reg reg, uint8_t data)
{
	for(int uartNr = 0; uartNr < NUMBER_OF_UARTS; uartNr ++)
	{
		spiSingleWriteTransfer(MAX_14830_WIRELESS_SIDE, uartNr, reg, data);
		spiSingleWriteTransfer(MAX_14830_DEVICE_SIDE, uartNr, reg, data);
	}
}



/*!
* \fn bool spiTransfer(tSpiSlaves spiSlave, tUartNr uartNr, tMax14830Reg reg, bool write, uint8_t* pData, uint8_t numOfTransfers)
* \brief Writes numOfTransfers bytes to the desired register, in the desired SPI slave and UART interface.
* \param spiSlave: SPI slave where the data should be written to.
* \param uartNr: The number of the UART of the MAX14830 chip.
* \param reg: The register the data should be written to.
* \param write: Set to true to write to the SPI slave, false to read.
* \param pData: This array holds read/write data. Important: needs to be 1 byte bigger than numOfTransfers! Leave Byte0 empty! Commando will be stored in that byte!
* \param numOfTransfers: Number of transfers. If bigger than 1, an SPI burst access will be performed. x * 16 Bit! Not in bytes!
* \return true if the data could be written/read, false otherwise.
*/
bool spiTransfer(tSpiSlaves spiSlave, tUartNr uartNr, tMax14830Reg reg, bool write, uint8_t* pData, uint8_t numOfTransfers)
{
	uint8_t transferCnt = 0;
	int maxDelay = 5; // [ms] ToDo: make relative to selected baud rate!
	static uint8_t data[HW_FIFO_SIZE + 1]; /* MAX14830 can hold a maximum of HW_FIFO_SIZE bytes, 1 byte is command. Make static to ensure memory for SPI is still here when SPI master actually sends the data! */
	/* See MAX14830 data sheet; 16 bits per word:
	* 15 (MSB): W/!R
	* 14: UART number, bit 1
	* 13: UART number, bit 0
	* 12: Register address, bit 4
	* 11: Register address, bit 3
	* 10: Register address, bit 2
	* 9: Register address, bit 1
	* 8: Register address, bit 0
	* 7: Data, bit 7
	* 6: Data, bit 6
	* 5: Data, bit 5
	* 4: Data, bit 4
	* 3: Data, bit 3
	* 2: Data, bit 2
	* 1: Data, bit 1
	* 0 (LSB): Data, bit 0 */
	if ((numOfTransfers < 1) || (pData == NULL))
	{
		return false;
	}
	/* Add 1 byte of overhead for MAX14830 commando */
	if(write)
	{
		pData[0] = 0x80;
		pData[0] |= (uartNr << 5);
		pData[0] |= (0x1F & reg);
	}
	else
	{
		data[0] = 0x0;
		data[0] |= (uartNr << 5);
		data[0] |= (0x1F & reg);
	}
	/* Select the correct slave */
	if (spiSlave == MAX_14830_WIRELESS_SIDE)
	{
		SPI_SelectConfiguration(spiDevice, CS_WIRELESS, 0);
	}
	else if (spiSlave == MAX_14830_DEVICE_SIDE)
	{
		SPI_SelectConfiguration(spiDevice, CS_DEVICE, 0);
	}
	else
	{
		/* invalid/not implemented argument */
		return false;
	}
	if (write)
	{
		/* write transfer */
		xSemaphoreTake(spiTxMutex, maxDelay / portTICK_PERIOD_MS); /* wait for last write to complete */
		SPI_SendBlock(spiDevice, pData, numOfTransfers+1); /* wait for SPI to get ready for sending, add 1 byte for command */
	}
	else
	{
		/* read transfer */
		xSemaphoreTake(spiTxMutex, maxDelay / portTICK_PERIOD_MS); /* wait for last write to complete */
		SPI_ReceiveBlock(spiDevice, pData, numOfTransfers+1); /* add 1 byte for command */
		SPI_SendBlock(spiDevice, data, numOfTransfers+1); /* add 1 byte for command */
		xSemaphoreTake(spiRxMutex, maxDelay / portTICK_PERIOD_MS); /* wait for read to be completed so that variable holds valid information when returning from this function */
	}
	return true;
}


/*!
* \fn void configureHwBufBaudrate(tSpiSlaves spiSlave, tUartNr uartNr, unsigned int baudRateToSet)
* \brief Configures the desired baud rate at the chosen serial connection.
* \param spiSlave: SPI slave that should be configured.
* \param uartNr: UART number that should be configured.
* \param baudRateToSet: The baud rate to set for this serial interface. See implementation for supported baud rates.
*/
void configureHwBufBaudrate(tSpiSlaves spiSlave, tUartNr uartNr, unsigned int baudRateToSet)
{
	char warnBuf[128];
	switch (baudRateToSet)
	{
	case 115200:
		spiSingleWriteTransfer(spiSlave, uartNr, MAX_REG_DIVLSB, 0x02);
		spiSingleWriteTransfer(spiSlave, uartNr, MAX_REG_DIVMSB, 0x00);
		break;
	case 57600:
		spiSingleWriteTransfer(spiSlave, uartNr, MAX_REG_DIVLSB, 0x04);
		spiSingleWriteTransfer(spiSlave, uartNr, MAX_REG_DIVMSB, 0x00);
		break;
	case 38400:
		spiSingleWriteTransfer(spiSlave, uartNr, MAX_REG_DIVLSB, 0x06);
		spiSingleWriteTransfer(spiSlave, uartNr, MAX_REG_DIVMSB, 0x00);
		break;
	case 9600:
		spiSingleWriteTransfer(spiSlave, uartNr, MAX_REG_DIVLSB, 0x18);
		spiSingleWriteTransfer(spiSlave, uartNr, MAX_REG_DIVMSB, 0x00);
		break;
	default:
		if (spiSlave == MAX_14830_WIRELESS_SIDE)
		{
			sprintf(warnBuf, "Unsupported baud rate on wireless side at UART number %u", (unsigned int)uartNr);
		}
		else
		{
			sprintf(warnBuf, "Unsupported baud rate on device side at UART number %u", (unsigned int)uartNr);
		}
		//showWarning(__FUNCTION__, warnBuf);
		return;
	}
	char infoBuf[128];
	if (spiSlave == MAX_14830_WIRELESS_SIDE)
	{
		sprintf(infoBuf, "Set baud rate on UART %u on wireless side: %u baud", (unsigned int)uartNr, baudRateToSet);
	}
	else
	{
		sprintf(infoBuf, "Set baud rate on UART %u on device side: %u baud", (unsigned int)uartNr, baudRateToSet);
	}
	//showInfo(__FUNCTION__, infoBuf);
}




/*!
* \fn static void readHwBufAndWriteToQueue(tSpiSlaves spiSlave, tUartNr uartNr, Queue* queuePtr)
* \brief Reads all data from the hardware FIFO of the chosen interface and puts the data into the chosen queue.
* \param spiSlave: SPI slave the data should be read from.
* \param uartNr: UART number the data should be read from.
* \param queuePtr: Pointer to the queue where the read data should be written.
* \return The number of read bytes.
*/
static uint16_t readHwBufAndWriteToQueue(tSpiSlaves spiSlave, tUartNr uartNr, xQueueHandle queue)
{
	uint8_t buffer[HW_FIFO_SIZE+1]; /* needs to be one byte bigger just in case we read HW_FIFO_SIZE number of bytes -> one additional byte received for sending command byte */
	uint16_t dataToRead = 0;
	uint16_t totalNumOfReadBytes = 0;
	uint8_t fifoLevel = 0;

	while(true)
	{
		/* check how much characters there are to read in the hardware FIFO */
		fifoLevel = spiSingleReadTransfer(spiSlave, uartNr, MAX_REG_RX_FIFO_LVL);
		if (fifoLevel == 0)
		{
			/* nothing left to read, leave this loop */
			break;
		}
		else if (fifoLevel > HW_FIFO_SIZE)
		{
			/* there is more data to read than there is space in the buffer - just read that much */
			dataToRead = HW_FIFO_SIZE;
		}
		else
		{
			/* read all the available data, there is enough room in the buffer */
			dataToRead = fifoLevel;
		}

		/* read the data from the HW buffer */
		spiTransfer(spiSlave, uartNr, MAX_REG_RHR_THR, false, buffer, dataToRead);


		/* send the read data to the corresponding queue */
		/* cnt starts at 1 because buffer[0] is left empty for commando, therefore it needs to count up to dataToRead+1 */
		for (unsigned int cnt = 1; cnt < dataToRead+1; cnt++)
		{
			if (xQueueSendToBack(queue, &buffer[cnt], ( TickType_t ) 0 ) == errQUEUE_FULL)
			{
				/* queue is full - flush queue, send character again and set error */
				xQueueReset(queue);
				xQueueSendToBack(queue, &buffer[cnt], ( TickType_t ) 0 );
				if (spiSlave == MAX_14830_WIRELESS_SIDE)
				{
					char warnBuf[128];
					sprintf(warnBuf, "cleaning full queue on wireless side, UART number %u", (unsigned int)uartNr);
					//showWarning(__FUNCTION__, warnBuf);
				}
				else /* spiSlave == MAX_14830_DEVICE_SIDE */
				{
					char warnBuf[128];
					sprintf(warnBuf, "cleaning full queue on device side, UART number %u", (unsigned int)uartNr);
					//showWarning(__FUNCTION__, warnBuf);
				}
			}
		}
		totalNumOfReadBytes += dataToRead;
		dataToRead = 0;
	}
	return totalNumOfReadBytes;
}



/*!
* \fn static void readQueueAndWriteToHwBuf(tSpiSlaves spiSlave, tUartNr uartNr, xQueueHandle queue)
* \brief Writes up to numOfBytesToWrite bytes to the hardware buffer, ruading the data from the queue.
* \param spiSlave: SPI slave the data should be written to.
* \param uartNr: UART number the data should be written to.
* \param queue: Queue where the data is stored that should be written to the HW buffer.
* \param numOfBytesToWrite: The number of bytes that should be written to the hardware buffer if there is space enough in the buffer.
* \return The number of written bytes.
*/
static uint16_t readQueueAndWriteToHwBuf(tSpiSlaves spiSlave, tUartNr uartNr, xQueueHandle queue, uint8_t numOfBytesToWrite)
{
	uint8_t buffer[HW_FIFO_SIZE+1];
	uint16_t cnt = 1;
	/* check how much space there is left in hardware buffer */
	uint8_t spaceLeft = 0;
	uint8_t spaceTaken = spiSingleReadTransfer(spiSlave, uartNr, MAX_REG_TX_FIFO_LVL);
	spaceLeft = HW_FIFO_SIZE - spaceTaken;
	/* check if there is enough space to write the number of bytes that should be written */
	if (spaceLeft < numOfBytesToWrite)
	{
		/* There isn't enough space to write the desired amount of data - just write that much that is possible */
		numOfBytesToWrite = spaceLeft;
	}
	/* write those bytes.. */
	if (numOfBytesToWrite > 0)
	{
		/* put together an array that can be written to the hardware buffer */
		if (numOfBytesToWrite > HW_FIFO_SIZE)
		{
			numOfBytesToWrite = HW_FIFO_SIZE;
		}
		/* pop bytes from queue and store them in buffer array. cnt starts at 1 because buffer[0] needs to be empty for commando byte */
		for (cnt = 1; cnt < numOfBytesToWrite+1; cnt++)
		{
			if (xQueueReceive(queue, &buffer[cnt], ( TickType_t ) 0 ) == errQUEUE_EMPTY)
			{
				/* queue is empty, no data to read - leave for-loop without incrementing cnt */
				break;
			}
		}

		/*
			From the MAX14830 data sheet:
				"Note that an error can occur in the TxFIFO when a character is written into THR at the same time as the transmitter is
				 transmitting out data via TX. In the event of this error condition, the result is that a character will not be transmitted.
				 In order to avoid this, stop the transmitter when writing data to the THR. This can be done via the TxDisable bit in the
				 MODE1 register."
			So it seems as TX needs to be disabled while writing to the FIFO (set TxDisabl to 1 in MODE1 to disable transmission).
			=> Don't do this when hardware flow control is enabled! In this case, transmitting is controlled by the CTS pin.
		*/
		if (spiSlave != MAX_14830_WIRELESS_SIDE)
			spiSingleWriteTransfer(spiSlave, uartNr, MAX_REG_MODE1, 0x02);
		else
		{
			if (config.UseCtsPerWirelessConn[(uint8_t)uartNr] > 0)
			{
				/* When hardware flow control is enabled, disable it temporary */
				spiSingleWriteTransfer(spiSlave, uartNr, MAX_REG_FLOW_CTRL, 0x00);
			}
			else
			{
				/* only do it here when hardware flow control is disabled */
				spiSingleWriteTransfer(spiSlave, uartNr, MAX_REG_MODE1, 0x02);
			}
		}
		/* transfer data popped from queue. cnt=numberOfTransfers-1 */
		spiTransfer(spiSlave, uartNr, MAX_REG_RHR_THR, true, buffer, cnt-1);
		/* reenable transmission */
		if (spiSlave != MAX_14830_WIRELESS_SIDE)
			spiSingleWriteTransfer(spiSlave, uartNr, MAX_REG_MODE1, 0x00);
		else
		{
			if (config.UseCtsPerWirelessConn[(uint8_t)uartNr] > 0)
			{
				/* Enable hardware flow control again */
				spiSingleWriteTransfer(spiSlave, uartNr, MAX_REG_FLOW_CTRL, 0x02);
			}
			else
			{
				/* only do it here when hardware flow control is disabled */
				spiSingleWriteTransfer(spiSlave, uartNr, MAX_REG_MODE1, 0x00);
			}
		}
	}
	return cnt;
}



/*!
* \fn ByseType_t popFromByteQueue(tSpiSlaves spiSlave, tUartNr uartNr, uint8_t *pData)
* \brief Stores a single byte from the selected queue in pData.
* \param spiSlave: SPI slave the data should be read from.
* \param uartNr: UART number the data should be read from.
* \param pData: The location where the byte should be stored
* \return Status if xQueueReceive has been successful
*/
BaseType_t popFromByteQueue(tSpiSlaves spiSlave, tUartNr uartNr, uint8_t *pData)
{
	if(spiSlave == MAX_14830_WIRELESS_SIDE)
	{
		if(uartNr < NUMBER_OF_UARTS)
		{
			return xQueueReceive(RxWirelessBytes[uartNr], pData, ( TickType_t ) 0 );
		}
	}
	else
	{
		if(uartNr < NUMBER_OF_UARTS)
		{
			return xQueueReceive(RxDeviceBytes[uartNr], pData, ( TickType_t ) 0 );
		}
	}
	return pdFAIL; /* if uartNr was not in range */
}


/*!
* \fn ByseType_t pushToByteQueue(tSpiSlaves spiSlave, tUartNr uartNr, uint8_t *pData)
* \brief Stores pData in queue
* \param spiSlave: SPI slave the data should be written to.
* \param uartNr: UART number the data should be written to.
* \param pData: The location where the byte should be read
* \return Status if xQueueSendToBack has been successful
*/
BaseType_t pushToByteQueue(tSpiSlaves spiSlave, tUartNr uartNr, uint8_t* pData)
{
	if(spiSlave == MAX_14830_WIRELESS_SIDE)
	{
		if(uartNr < NUMBER_OF_UARTS)
		{
			return xQueueSendToBack(TxWirelessBytes[uartNr], pData, ( TickType_t ) 0 );
		}
	}
	else
	{
		if(uartNr < NUMBER_OF_UARTS)
		{
			return xQueueSendToBack(TxDeviceBytes[uartNr], pData, ( TickType_t ) 0 );
		}
	}
	return pdFAIL; /* if uartNr was not in range */
}

/*!
* \fn uint16_t numberOfBytesInRxByteQueue(tSpiSlaves spiSlave, tUartNr uartNr)
* \brief Returns the number of bytes stored in the queue that are ready to be received/processed by this program
* \param uartNr: UART number the bytes should be read from.
* \param spiSlave: spiSlave byte should be read from.
* \return Number of packages waiting to be processed/received
*/
uint16_t numberOfBytesInRxByteQueue(tSpiSlaves spiSlave, tUartNr uartNr)
{
	if(uartNr < NUMBER_OF_UARTS)
		return (spiSlave == MAX_14830_WIRELESS_SIDE)? (uint16_t) uxQueueMessagesWaiting(RxWirelessBytes[uartNr]) :  (uint16_t) uxQueueMessagesWaiting(RxDeviceBytes[uartNr]);
	return 0; /* if uartNr was not in range */
}

/*!
* \fn uint16_t numberOfBytesInTxByteQueue(tSpiSlaves spiSlave, tUartNr uartNr)
* \brief Returns the number of bytes stored in the queue that are ready to be sent to the corresponding MAX14830
* \param uartNr: UART number the bytes should be transmitted to.
* \param spiSlave: spiSlave byte should be sent to.
* \return Number of packages waiting to be sent out
*/
uint16_t numberOfBytesInTxByteQueue(tSpiSlaves spiSlave, tUartNr uartNr)
{
	if(uartNr < NUMBER_OF_UARTS)
		return (spiSlave == MAX_14830_WIRELESS_SIDE)? (uint16_t) uxQueueMessagesWaiting(TxWirelessBytes[uartNr]) :  (uint16_t) uxQueueMessagesWaiting(TxDeviceBytes[uartNr]);
	return 0; /* if uartNr was not in range */
}
