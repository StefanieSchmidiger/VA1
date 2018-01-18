// 
// 
// 

#include "spiInterface.h"
#include "errorAndWarningOutput.h"






/*!
* \fn void spiInitialize(void)
* \brief Initializes the SPI interface.
*/
void spiInitialize(void)
{
	/* SPI settings for MAX14830: Up to 26 MHz, MSB first, sample on rising edge */
	SPISettings MAX14830_SETTINGS(26000000, MSBFIRST, SPI_MODE0);

	/* initialize SPI CS pins and disable both */
	pinMode(PIN_CS_WIRELESS_SIDE, OUTPUT);
	pinMode(PIN_CS_DEVICE_SIDE, OUTPUT);
	digitalWrite(PIN_CS_WIRELESS_SIDE, HIGH);
	digitalWrite(PIN_CS_DEVICE_SIDE, HIGH);

	/* initialize SPI */
	SPI.setSCK(13);       // SCK on pin 13
	SPI.setMOSI(11);      // MOSI on pin 11
	SPI.setMISO(12);      // MISO on pin 12
	SPI.begin();
	SPI.beginTransaction(MAX14830_SETTINGS);
}



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
bool spiTransfer(tSpiSlaves spiSlave, tUartNr uartNr, tMax14830Reg reg, bool write, uint8_t* pData, uint8_t numOfTransfers)
{
	uint8_t transferCnt = 0;
	uint16_t firstData;
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
	firstData = write ? 0x8000 : 0x0;
	firstData |= (uartNr << 13);
	firstData |= (reg << 8);
	firstData |= write ? (pData[0]) : (0x0);
	if (spiSlave == MAX_14830_WIRELESS_SIDE)
	{
		digitalWrite(PIN_CS_DEVICE_SIDE, HIGH);
		digitalWrite(PIN_CS_WIRELESS_SIDE, LOW);
	}
	else if (spiSlave == MAX_14830_DEVICE_SIDE)
	{
		digitalWrite(PIN_CS_WIRELESS_SIDE, HIGH);
		digitalWrite(PIN_CS_DEVICE_SIDE, LOW);
	}
	else
	{
		/* invalid/not implemented argument */
		return false;
	}
	if (write)
	{
		/* write transfer */
		SPI.transfer16(firstData);
		transferCnt++;
		while (transferCnt < numOfTransfers)
		{
			SPI.transfer(pData[transferCnt++]);
		}
	}
	else
	{
		/* read transfer */
		pData[0] = (uint8_t)((SPI.transfer16(firstData)) & 0xFF);
		transferCnt++;
		while (transferCnt < numOfTransfers)
		{
			pData[transferCnt++] = SPI.transfer(0x0);
		}
	}
	digitalWrite(PIN_CS_WIRELESS_SIDE, HIGH);
	digitalWrite(PIN_CS_DEVICE_SIDE, HIGH);
	return true;
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
	return spiTransfer(spiSlave, uartNr, reg, true, &data, 1);
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
	uint8_t readData;
	spiTransfer(spiSlave, uartNr, reg, false, &readData, 1);
	return readData;
}



/*!
* \fn void spiWriteToAllUartInterfaces(bool write, tMax14830Reg reg, uint8_t data)
* \brief SPI transfer that writes the corresponding data to all UART interfaces.
* \param reg: The register the data should be written to.
* \param data: Data that should be written to the corresponding register.
*/
void spiWriteToAllUartInterfaces(tMax14830Reg reg, uint8_t data)
{
	spiSingleWriteTransfer(MAX_14830_WIRELESS_SIDE, MAX_UART_0, reg, data);
	spiSingleWriteTransfer(MAX_14830_WIRELESS_SIDE, MAX_UART_1, reg, data);
	spiSingleWriteTransfer(MAX_14830_WIRELESS_SIDE, MAX_UART_2, reg, data);
	spiSingleWriteTransfer(MAX_14830_WIRELESS_SIDE, MAX_UART_3, reg, data);

	spiSingleWriteTransfer(MAX_14830_DEVICE_SIDE, MAX_UART_0, reg, data);
	spiSingleWriteTransfer(MAX_14830_DEVICE_SIDE, MAX_UART_1, reg, data);
	spiSingleWriteTransfer(MAX_14830_DEVICE_SIDE, MAX_UART_2, reg, data);
	spiSingleWriteTransfer(MAX_14830_DEVICE_SIDE, MAX_UART_3, reg, data);
}


