// hwBufferInterface.h

#ifndef _HWBUFFERINTERFACE_h
#define _HWBUFFERINTERFACE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <TaskScheduler.h>
#include "spiInterface.h"



/*! \def HW_FIFO_SIZE
*  \brief Number of elements that fit into the hardware FIFO.
*/
#define HW_FIFO_SIZE				128



/*! \var hwBufIfWirelessDataWriterUart0Task
*  \brief Declaration of wireless writer tasks
*/
extern Task hwBufIfWirelessDataWriterUart0Task;
extern Task hwBufIfWirelessDataWriterUart1Task;
extern Task hwBufIfWirelessDataWriterUart2Task;
extern Task hwBufIfWirelessDataWriterUart3Task;



/*! \def QUEUE_NUM_OF_CHARS_WL_TX_QUEUE
*  \brief Number of chars that should have find space within a single wireless transmit queue.
*/
#define QUEUE_NUM_OF_CHARS_WL_TX_QUEUE		2048

/*! \def QUEUE_NUM_OF_CHARS_DEV_TX_QUEUE
*  \brief Number of chars that should have find space within a single device transmit queue.
*/
#define QUEUE_NUM_OF_CHARS_DEV_TX_QUEUE		2048

/*! \def QUEUE_NUM_OF_CHARS_WL_RX_QUEUE
*  \brief Number of chars that should have find space within a single wireless receive queue.
*/
#define QUEUE_NUM_OF_CHARS_WL_RX_QUEUE		2048

/*! \def QUEUE_NUM_OF_CHARS_DEV_RX_QUEUE
*  \brief Number of chars that should have find space within a single device receive queue.
*/
#define QUEUE_NUM_OF_CHARS_DEV_RX_QUEUE		2048

/*! \var queueWirelessReceiveUart[X]
*  \brief Receive queue for received data on wireless UART X
*/
extern Queue queueWirelessReceiveUart[];

/*! \var queueDeviceReceiveUart[X]
*  \brief Receive queue for received data on device UART X
*/
extern Queue queueDeviceReceiveUart[];

/*! \var queueWirelessTransmitUart[X]
*  \brief Transmit queue for received data on wireless UART X
*/
extern Queue queueWirelessTransmitUart[];

/*! \var queueDeviceTransmitUart[X]
*  \brief Transmit queue for received data on device UART X
*/
extern Queue queueDeviceTransmitUart[];




/*!
* \fn void hwBufIfDataReader_TaskEntry(void)
* \brief Task to read the data from the hardware buffers from all interfaces on wireless and device side.
*/
void hwBufIfDataReader_TaskEntry(void);


/*!
* \fn void hwBufIfDataReader_TaskEntry(void)
* \brief Task to write the data to the corresponding hardware buffers on device side for all UART interfaces.
*/
void hwBufIfDeviceDataWriter_TaskEntry(void);

/*!
* \fn void hwBufIfWirelessDataWriter_UartX_TaskEntry(void)
* \brief Task to write the data to the corresponding hardware buffers on wireless side for UART X.
*/
void hwBufIfWirelessDataWriter_Uart0_TaskEntry(void);
void hwBufIfWirelessDataWriter_Uart1_TaskEntry(void);
void hwBufIfWirelessDataWriter_Uart2_TaskEntry(void);
void hwBufIfWirelessDataWriter_Uart3_TaskEntry(void);

/*!
* \fn void hwBufIfConfigureBaudRate(tSpiSlaves spiSlave, tUartNr uartNr, unsigned int baudRateToSet)
* \brief Configures the desired baud rate at the chosen serial connection.
* \param spiSlave: SPI slave that should be configured.
* \param uartNr: UART number that should be configured.
* \param baudRateToSet: The baud rate to set for this serial interface. See implementation for supported baud rates.
*/
void hwBufIfConfigureBaudRate(tSpiSlaves spiSlave, tUartNr uartNr, unsigned int baudRateToSet);


#endif

