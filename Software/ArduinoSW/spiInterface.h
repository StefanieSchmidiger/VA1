// spiInterface.h

#ifndef _SPIINTERFACE_h
#define _SPIINTERFACE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <SPI.h>

#define PIN_CS_WIRELESS_SIDE			15
#define PIN_RESET_WIRELESS_SIDE			16
#define PIN_IRQ_WIRELESS_SIDE			17
#define PIN_CS_DEVICE_SIDE				10
#define PIN_RESET_DEVICE_SIDE			8
#define PIN_IRQ_DEVICE_SIDE				9


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





/*!
* \fn void spiInitialize(void)
* \brief Initializes the SPI interface.
*/
void spiInitialize(void);


/*!
* \fn bool spiTransfer(tSpiSlaves spiSlave, tUartNr uartNr, tMax14830Reg reg, bool write, uint8_t* pData, uint8_t numOfTransfers)
* \brief Writes numOfTransfers bytes to the desired register, in the desired SPI slave and UART interface.
* \param spiSlave: SPI slave where the data should be written to.
* \param uartNr: The number of the UART of the MAX14830 chip.
* \param reg: The register the data should be written to.
* \param write: Set to true to write to the SPI slave, false to read.
* \param pData: Pointer to data that should be written in the write case or where the answer is saved in read case. Needs to be of numOfTransfers size.
* \param numOfTransfers: Number of transfers. If bigger than 1, an SPI burst access will be performed.
* \return true if the data could be written/read, false otherwise.
*/
bool spiTransfer(tSpiSlaves spiSlave, tUartNr uartNr, tMax14830Reg reg, bool write, uint8_t* pData, uint8_t numOfTransfers);


/*!
* \fn bool spiSingleWriteTransfer(tSpiSlaves spiSlave, tUartNr uartNr, tMax14830Reg reg, uint8_t data)
* \brief Writes a single byte to the desired register.
* \param spiSlave: SPI slave where the data should be written to.
* \param uartNr: The number of the UART of the MAX14830 chip.
* \param reg: The register the data should be written to.
* \param data: Data byte that is written to the corresponding register.
* \return true if the data could be written, false otherwise.
*/
bool spiSingleWriteTransfer(tSpiSlaves spiSlave, tUartNr uartNr, tMax14830Reg reg, uint8_t data);


/*!
* \fn uint8_t spiSingleReadTransfer(tSpiSlaves spiSlave, tUartNr uartNr, tMax14830Reg reg)
* \brief Reads a single byte from the desired register.
* \param spiSlave: SPI slave where the data should be written to.
* \param uartNr: The number of the UART of the MAX14830 chip.
* \param reg: The register the data should be written to.
* \return Data that was read from the desired register.
*/
uint8_t spiSingleReadTransfer(tSpiSlaves spiSlave, tUartNr uartNr, tMax14830Reg reg);


/*!
* \fn void spiWriteToAllUartInterfaces(bool write, tMax14830Reg reg, uint8_t data)
* \brief SPI transfer that writes the corresponding data to all UART interfaces.
* \param reg: The register the data should be written to.
* \param data: Data that should be written to the corresponding register.
*/
void spiWriteToAllUartInterfaces(tMax14830Reg reg, uint8_t data);



#endif

