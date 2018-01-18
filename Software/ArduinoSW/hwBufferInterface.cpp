// 
// 
// 

#include "serialSwitch_General.h"
#include "serialSwitch_Config.h"
#include "hwBufferInterface.h"
#include "spiInterface.h"
#include "errorAndWarningOutput.h"
#include "throughputPrintout.h"
#include "golay.h"




/* Initialize queues */
Queue queueWirelessReceiveUart[NUM_OF_WIRELESS_CONNECTIONS] = 
	{ Queue(sizeof(uint8_t), QUEUE_NUM_OF_CHARS_WL_RX_QUEUE), Queue(sizeof(uint8_t), QUEUE_NUM_OF_CHARS_WL_RX_QUEUE), Queue(sizeof(uint8_t), QUEUE_NUM_OF_CHARS_WL_RX_QUEUE), Queue(sizeof(uint8_t), QUEUE_NUM_OF_CHARS_WL_RX_QUEUE) };
Queue queueDeviceReceiveUart[NUM_OF_DEVICE_CONNECTIONS] = 
	{ Queue(sizeof(uint8_t), QUEUE_NUM_OF_CHARS_DEV_RX_QUEUE), Queue(sizeof(uint8_t), QUEUE_NUM_OF_CHARS_DEV_RX_QUEUE), Queue(sizeof(uint8_t), QUEUE_NUM_OF_CHARS_DEV_RX_QUEUE), Queue(sizeof(uint8_t), QUEUE_NUM_OF_CHARS_DEV_RX_QUEUE) };
Queue queueWirelessTransmitUart[NUM_OF_WIRELESS_CONNECTIONS] =
	{ Queue(sizeof(uint8_t), QUEUE_NUM_OF_CHARS_WL_TX_QUEUE), Queue(sizeof(uint8_t), QUEUE_NUM_OF_CHARS_WL_TX_QUEUE), Queue(sizeof(uint8_t), QUEUE_NUM_OF_CHARS_WL_TX_QUEUE), Queue(sizeof(uint8_t), QUEUE_NUM_OF_CHARS_WL_TX_QUEUE) };
Queue queueDeviceTransmitUart[NUM_OF_DEVICE_CONNECTIONS] =
	{ Queue(sizeof(uint8_t), QUEUE_NUM_OF_CHARS_DEV_TX_QUEUE), Queue(sizeof(uint8_t), QUEUE_NUM_OF_CHARS_DEV_TX_QUEUE), Queue(sizeof(uint8_t), QUEUE_NUM_OF_CHARS_DEV_TX_QUEUE), Queue(sizeof(uint8_t), QUEUE_NUM_OF_CHARS_DEV_TX_QUEUE) };



/*!
* \fn static void readAllDataFromHwBufAndWriteItToQueue(tSpiSlaves spiSlave, tUartNr uartNr, Queue* queuePtr)
* \brief Reads all data from the hardware FIFO of the chosen interface and puts the data into the chosen queue.
* \param spiSlave: SPI slave the data should be read from.
* \param uartNr: UART number the data should be read from.
* \param queuePtr: Pointer to the queue where the read data should be written.
* \return The number of read bytes.
*/
static uint16_t readAllDataFromHwBufAndWriteItToQueue(tSpiSlaves spiSlave, tUartNr uartNr, Queue* queuePtr)
{
	const int bufferSize = HW_FIFO_SIZE;
	static uint8_t buffer[bufferSize];
#if USE_GOLAY_ERROR_CORRECTING_CODING > 0
	static uint8_t codeBuf[bufferSize];
#endif /* USE_GOLAY_ERROR_CORRECTING_CODING */
	uint16_t dataToRead = 0;
	uint16_t totalNumOfReadBytes = 0;
	uint8_t fifoLevel;
	while (true)
	{
		/* check how much characters there are to read in the hardware FIFO */
		fifoLevel = spiSingleReadTransfer(spiSlave, uartNr, MAX_REG_RX_FIFO_LVL);
		if (fifoLevel == 0)
		{
			/* nothing left to read, leave this loop */
			break;
		}
		else if (fifoLevel > bufferSize)
		{
			/* there is more data to read than there is space in the buffer - just read that much */
			dataToRead = bufferSize;
		}
		else
		{
			/* read all the available data, there is enough room in the buffer */
			dataToRead = fifoLevel;
		}
		/* read data and decode it if coding is enabled */
#if USE_GOLAY_ERROR_CORRECTING_CODING > 0
		/* decode only on the wireless side */
		if (spiSlave == MAX_14830_WIRELESS_SIDE)
		{
			/*
			There's a tradeoff here: the number of data to be decoded needs to be a multiple of 6.
			So we can either just read out as many as there is multiple of 6, risking that we delay some of the chars quite long.
			Or we can read out all chars, fill up with pseudo chars and destroy some of the codewords this way.
			=> decided to read out only multiples of 6
			*/
			while ((dataToRead % 6) > 0)	dataToRead--;
			/* read the data from the HW buffer */
			spiTransfer(spiSlave, uartNr, MAX_REG_RHR_THR, false, codeBuf, dataToRead);
			/* decode the data, length needs to be multiple of 6 */
			golay_decode(dataToRead, codeBuf, buffer);
			dataToRead = dataToRead / 2;
		}
		else
		{
			/* read the data from the HW buffer */
			spiTransfer(spiSlave, uartNr, MAX_REG_RHR_THR, false, buffer, dataToRead);
		}
#else
		/* read the data from the HW buffer */
		spiTransfer(spiSlave, uartNr, MAX_REG_RHR_THR, false, buffer, dataToRead);
#endif /* USE_GOLAY_ERROR_CORRECTING_CODING */
		/* send the read data to the corresponding queue */
    /*const char* buf = (const char*) &buffer[0]; */
    for (unsigned int cnt = 0; cnt < dataToRead; cnt++)
		{
			if ((*queuePtr).push(&buffer[cnt]) == false)
			{
				/* queue is full - flush queue, send character again and set error */
				(*queuePtr).clean();
				(*queuePtr).push(&buffer[cnt]);
				if (spiSlave == MAX_14830_WIRELESS_SIDE)
				{
					char warnBuf[128];
					sprintf(warnBuf, "cleaning full queue on wireless side, UART number %u", (unsigned int)uartNr);
					showWarning(__FUNCTION__, warnBuf);
				}
				else
				{
					/* spiSlave == MAX_14830_DEVICE_SIDE */
					char warnBuf[128];
					sprintf(warnBuf, "cleaning full queue on device side, UART number %u", (unsigned int)uartNr);
					showWarning(__FUNCTION__, warnBuf);
				}
			}
		}
		totalNumOfReadBytes += dataToRead;
		dataToRead = 0;
	}
	return totalNumOfReadBytes;
}


/*!
* \fn static void writeAsMuchAsPossibleDataToHwBuf(tSpiSlaves spiSlave, tUartNr uartNr, Queue* queuePtr)
* \brief Writes up to numOfBytesToWrite bytes to the hardware buffer, ruading the data from the queue.
* \param spiSlave: SPI slave the data should be written to.
* \param uartNr: UART number the data should be written to.
* \param queuePtr: Pointer to the queue where the data is stored that should be written to the HW buffer.
* \param numOfBytesToWrite: The number of bytes that should be written to the hardware buffer if there is space enough in the buffer.
* \return The number of written bytes.
*/
static uint16_t writeDataToHwBuf(tSpiSlaves spiSlave, tUartNr uartNr, Queue* queuePtr, uint8_t numOfBytesToWrite)
{
	const int bufferSize = HW_FIFO_SIZE;
	static uint8_t buffer[bufferSize];
#if USE_GOLAY_ERROR_CORRECTING_CODING > 0
	static uint8_t codingBuf[bufferSize];
#endif /* USE_GOLAY_ERROR_CORRECTING_CODING */
	uint16_t cnt = 0;
	/* check how much space there is left in the hardware buffer */
	uint8_t spaceLeft = HW_FIFO_SIZE - spiSingleReadTransfer(spiSlave, uartNr, MAX_REG_TX_FIFO_LVL);
#if USE_GOLAY_ERROR_CORRECTING_CODING > 0
	if(spiSlave == MAX_14830_WIRELESS_SIDE) spaceLeft = spaceLeft / 2;	/* because golay coding doubles the data rate */
#endif /* USE_GOLAY_ERROR_CORRECTING_CODING */
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
		if (numOfBytesToWrite > bufferSize)
		{
			numOfBytesToWrite = bufferSize;
		}
		for (cnt = 0; cnt < numOfBytesToWrite; cnt++)
		{
			if ((*queuePtr).pull(&buffer[cnt]) == false)
			{
				/* queue is empty, no data to read - leave loop */
				break;
			}
		}

		/* encode data if golay coding is enabled */
#if USE_GOLAY_ERROR_CORRECTING_CODING > 0
		/* only do this on wireless side */
		if (spiSlave == MAX_14830_WIRELESS_SIDE)
		{
			/* buffer needs to be multiple of 3, add fill chars if necessary */
			while ((cnt % 3) > 0)
			{
				buffer[cnt++] = PACK_FILL;
			}
			golay_encode(cnt, buffer, codingBuf);
			cnt = cnt * 2;
		}
#endif /* USE_GOLAY_ERROR_CORRECTING_CODING */

		/*
			From the MAX14830 data sheet:
				"Note that an error can occur in the TxFIFO when a character is written into THR at the same time as the transmitter is
				 transmitting out data via TX. In the event of this error condition, the result is that a character will not be transmitted.
				 In order to avoid this, stop the transmitter when writing data to the THR. This can be done via the TxDisable bit in the
				 MODE1 register."
			So it seems as TX needs to be disabled while writing to the FIFO (set TxDisabl to 1 in MODE1 to disable transmission).
			=> Don't do this when hardware flow control is enabled! In this case, transmitting is controlled by the CTS pin.
		*/
		static const unsigned int ctsUsageWireless[] = USE_CTS_PER_WIRELESS_CONN;
		if (spiSlave != MAX_14830_WIRELESS_SIDE)	spiSingleWriteTransfer(spiSlave, uartNr, MAX_REG_MODE1, 0x02);
		else
		{
			if (ctsUsageWireless[(uint8_t)uartNr] > 0)
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

		/* write data to the hardware buffer if there is data to write */
#if USE_GOLAY_ERROR_CORRECTING_CODING > 0
		if (spiSlave == MAX_14830_WIRELESS_SIDE)	spiTransfer(spiSlave, uartNr, MAX_REG_RHR_THR, true, codingBuf, cnt);
		else										spiTransfer(spiSlave, uartNr, MAX_REG_RHR_THR, true, buffer, cnt);
#else
		spiTransfer(spiSlave, uartNr, MAX_REG_RHR_THR, true, buffer, cnt);
#endif /* USE_GOLAY_ERROR_CORRECTING_CODING */

		/* enable transmission again */
		if (spiSlave != MAX_14830_WIRELESS_SIDE)	spiSingleWriteTransfer(spiSlave, uartNr, MAX_REG_MODE1, 0x00);
		else
		{
			if (ctsUsageWireless[(uint8_t)uartNr] > 0)
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
* \fn void hwBufIfDataReader_TaskEntry(void)
* \brief Task to read the data from the hardware buffers from all interfaces on wireless and device side.
*/
void hwBufIfDataReader_TaskEntry(void)
{
	/* Read data from wireless side and put it in the corresponding queue */
	numOfRecBytesWirelessConn[0] += readAllDataFromHwBufAndWriteItToQueue(MAX_14830_WIRELESS_SIDE, MAX_UART_0, &queueWirelessReceiveUart[0]);
	numOfRecBytesWirelessConn[1] += readAllDataFromHwBufAndWriteItToQueue(MAX_14830_WIRELESS_SIDE, MAX_UART_1, &queueWirelessReceiveUart[1]);
	numOfRecBytesWirelessConn[2] += readAllDataFromHwBufAndWriteItToQueue(MAX_14830_WIRELESS_SIDE, MAX_UART_2, &queueWirelessReceiveUart[2]);
	numOfRecBytesWirelessConn[3] += readAllDataFromHwBufAndWriteItToQueue(MAX_14830_WIRELESS_SIDE, MAX_UART_3, &queueWirelessReceiveUart[3]);

	/* Read data from device side and put it in the corresponding queue */
	readAllDataFromHwBufAndWriteItToQueue(MAX_14830_DEVICE_SIDE, MAX_UART_0, &queueDeviceReceiveUart[0]);
	readAllDataFromHwBufAndWriteItToQueue(MAX_14830_DEVICE_SIDE, MAX_UART_1, &queueDeviceReceiveUart[1]);
	readAllDataFromHwBufAndWriteItToQueue(MAX_14830_DEVICE_SIDE, MAX_UART_2, &queueDeviceReceiveUart[2]);
	readAllDataFromHwBufAndWriteItToQueue(MAX_14830_DEVICE_SIDE, MAX_UART_3, &queueDeviceReceiveUart[3]);
}


/*!
* \fn void hwBufIfDataReader_TaskEntry(void)
* \brief Task to write the data to the corresponding hardware buffers on device side for all UART interfaces.
*/
void hwBufIfDeviceDataWriter_TaskEntry(void)
{
	writeDataToHwBuf(MAX_14830_DEVICE_SIDE, MAX_UART_0, &queueDeviceTransmitUart[0], HW_FIFO_SIZE);
	writeDataToHwBuf(MAX_14830_DEVICE_SIDE, MAX_UART_1, &queueDeviceTransmitUart[1], HW_FIFO_SIZE);
	writeDataToHwBuf(MAX_14830_DEVICE_SIDE, MAX_UART_2, &queueDeviceTransmitUart[2], HW_FIFO_SIZE);
	writeDataToHwBuf(MAX_14830_DEVICE_SIDE, MAX_UART_3, &queueDeviceTransmitUart[3], HW_FIFO_SIZE);
}


/*!
* \fn void hwBufIfWirelessDataWriter_UartX_TaskEntry(void)
* \brief Task to write the data to the corresponding hardware buffers on wireless side for UART X.
*/
void hwBufIfWirelessDataWriter_Uart0_TaskEntry(void)
{
	/* Based on MAX_THROUGHPUT_WIRELESS_CONN and the task interval, check how much data should be written */
	static unsigned int maxThroughputsWireless[] = MAX_THROUGHPUT_WIRELESS_CONN;
	static uint8_t maxBytesToWrite;
	if (hwBufIfWirelessDataWriterUart0Task.isFirstIteration())
	{
		maxBytesToWrite = (uint8_t)(ceilf(maxThroughputsWireless[0] * hwBufIfWirelessDataWriterUart0Task.getInterval() / 1000.0f));
	}
	/* Write that amount of data */
	numOfSentBytesWirelessConn[0] += writeDataToHwBuf(MAX_14830_WIRELESS_SIDE, MAX_UART_0, &queueWirelessTransmitUart[0], maxBytesToWrite);
}
void hwBufIfWirelessDataWriter_Uart1_TaskEntry(void)
{
	/* Based on MAX_THROUGHPUT_WIRELESS_CONN and the task interval, check how much data should be written */
	static unsigned int maxThroughputsWireless[] = MAX_THROUGHPUT_WIRELESS_CONN;
	static uint8_t maxBytesToWrite;
	if (hwBufIfWirelessDataWriterUart1Task.isFirstIteration())
	{
		maxBytesToWrite = (uint8_t)(ceilf(maxThroughputsWireless[1] * hwBufIfWirelessDataWriterUart1Task.getInterval() / 1000.0f));
	}
	/* Write that amount of data */
	numOfSentBytesWirelessConn[1] += writeDataToHwBuf(MAX_14830_WIRELESS_SIDE, MAX_UART_1, &queueWirelessTransmitUart[1], maxBytesToWrite);
}
void hwBufIfWirelessDataWriter_Uart2_TaskEntry(void)
{
	/* Based on MAX_THROUGHPUT_WIRELESS_CONN and the task interval, check how much data should be written */
	static unsigned int maxThroughputsWireless[] = MAX_THROUGHPUT_WIRELESS_CONN;
	static uint8_t maxBytesToWrite;
	if (hwBufIfWirelessDataWriterUart2Task.isFirstIteration())
	{
		maxBytesToWrite = (uint8_t)(ceilf(maxThroughputsWireless[2] * hwBufIfWirelessDataWriterUart2Task.getInterval() / 1000.0f));
	}
	/* Write that amount of data */
	numOfSentBytesWirelessConn[2] += writeDataToHwBuf(MAX_14830_WIRELESS_SIDE, MAX_UART_2, &queueWirelessTransmitUart[2], maxBytesToWrite);
}
void hwBufIfWirelessDataWriter_Uart3_TaskEntry(void)
{
	/* Based on MAX_THROUGHPUT_WIRELESS_CONN and the task interval, check how much data should be written */
	static unsigned int maxThroughputsWireless[] = MAX_THROUGHPUT_WIRELESS_CONN;
	static uint8_t maxBytesToWrite;
	if (hwBufIfWirelessDataWriterUart3Task.isFirstIteration())
	{
		maxBytesToWrite = (uint8_t)(ceilf(maxThroughputsWireless[3] * hwBufIfWirelessDataWriterUart3Task.getInterval() / 1000.0f));
	}
	/* Write that amount of data */
	numOfSentBytesWirelessConn[3] += writeDataToHwBuf(MAX_14830_WIRELESS_SIDE, MAX_UART_3, &queueWirelessTransmitUart[3], maxBytesToWrite);
}


/*!
* \fn void hwBufIfConfigureBaudRate(tSpiSlaves spiSlave, tUartNr uartNr, unsigned int baudRateToSet)
* \brief Configures the desired baud rate at the chosen serial connection.
* \param spiSlave: SPI slave that should be configured.
* \param uartNr: UART number that should be configured.
* \param baudRateToSet: The baud rate to set for this serial interface. See implementation for supported baud rates.
*/
void hwBufIfConfigureBaudRate(tSpiSlaves spiSlave, tUartNr uartNr, unsigned int baudRateToSet)
{
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
		char warnBuf[128];
		if (spiSlave == MAX_14830_WIRELESS_SIDE)
		{
			sprintf(warnBuf, "Unsupported baud rate on wireless side at UART number %u", (unsigned int)uartNr);
		}
		else
		{
			sprintf(warnBuf, "Unsupported baud rate on device side at UART number %u", (unsigned int)uartNr);
		}
		showWarning(__FUNCTION__, warnBuf);
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
	showInfo(__FUNCTION__, infoBuf);
}


