#ifndef SPIHANDLER_H
#define SPIHANDLER_H


#include "SPI.h"
#include <stdbool.h>
#include "FRTOS.h" // queues

/*! \def HW_FIFO_SIZE
*  \brief Number of elements that fit into the hardware FIFO.
*/
#define HW_FIFO_SIZE				128

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



/*! \enum eMax14830Reg
*  \brief Registers of the MAX14830, see MAX14830 data sheet.
*/
typedef enum eMax14830Reg
{
	/* FIFO DATA */
	MAX_REG_RHR_THR = 0x00,
	/* INTERRUPTS */
	MAX_REG_IRQ_EN = 0x01,
	MAX_REG_ISR = 0x02,
	MAX_REG_LSR_INT_EN = 0x03,
	MAX_REG_LSR = 0x04,
	MAX_REG_SPCL_CHR_INT_EN = 0x05,
	MAX_REG_SPCL_CHAR_INT = 0x06,
	MAX_REG_STS_INT_EN = 0x07,
	MAX_REG_STS_INT = 0x08,
	/* UART MODES */
	MAX_REG_MODE1 = 0x09,
	MAX_REG_MODE2 = 0x0A,
	MAX_REG_LCR = 0x0B,
	MAX_REG_RX_TIME_OUT = 0x0C,
	MAX_REG_H_DPLX_DELAY = 0x0D,
	MAX_REG_IR_DA = 0x0E,
	/* FIFOs CONTROL */
	MAX_REG_FLOW_LVL = 0x0F,
	MAX_REG_FIFO_TRG_LVL = 0x10,
	MAX_REG_TX_FIFO_LVL = 0x11,
	MAX_REG_RX_FIFO_LVL = 0x12,
	/* FLOW CONTROL */
	MAX_REG_FLOW_CTRL = 0x13,
	MAX_REG_XON1 = 0x14,
	MAX_REG_XON2 = 0x15,
	MAX_REG_XOFF1 = 0x16,
	MAX_REG_XOFF2 = 0x17,
	/* GPIOs */
	MAX_REG_GPIO_CONFIG = 0x18,
	MAX_REG_GPIO_DATA = 0x19,
	/* CLOCK CONFIGURATION */
	MAX_REG_PLL_CONFIG = 0x1A,
	MAX_REG_BRG_CONFIG = 0x1B,
	MAX_REG_DIVLSB = 0x1C,
	MAX_REG_DIVMSB = 0x1D,
	MAX_REG_CLK_SOURCE = 0x1E,
	/* GLOBAL REGISTERS */
	MAX_REG_GLOBAL_IRQ_COMND = 0x1F,
	/* SYNCHRONIZATION REGISTERS */
	MAX_REG_TX_SYNC = 0x20,
	MAX_REG_SYNCH_DELAY_1 = 0x21,
	MAX_REG_SYNCH_DELAY_2 = 0x22,
	/* TIMER REGISTER */
	MAX_REG_TIMER_1 = 0x23,
	MAX_REG_TIMER_2 = 0x24,
	/* REVISION */
	MAX_REG_REVID = 0x25
} tMax14830Reg;


/*! \enum eUartNr
*  \brief Enumeration of the different UART interfaces within one MAX14830 chip.
*/
typedef enum eUartNr
{
	MAX_UART_0 = 0x0,
	MAX_UART_1 = 0x1,
	MAX_UART_2 = 0x2,
	MAX_UART_3 = 0x3
} tUartNr;


/*! \enum eSpiSlaves
*  \brief Enumeration of the different available SPI slaves.
*/
typedef enum eSpiSlaves
{
	MAX_14830_WIRELESS_SIDE,
	MAX_14830_DEVICE_SIDE
} tSpiSlaves;


/* Semaphore for SPI Interface -> given back in SPI_OnBlockReceived/Sent */
extern xSemaphoreHandle spiRxMutex;
extern xSemaphoreHandle spiTxMutex;


/*!
* \fn void spiHandler_TaskEntry(void* p)
* \brief This task handles the HW interface (SPI)
*/
void spiHandler_TaskEntry(void* p);

#endif
