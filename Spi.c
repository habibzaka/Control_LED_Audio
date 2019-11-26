/**
* \file Spi.c
* \brief  definition file for Spi.c
* \author Habib Zakaria
* \version 1.0
* \date 2019/06/06
*/

//-----------------------------------------------------------------------------
// Header files
//-----------------------------------------------------------------------------

#include <avr/io.h>
#include "Spi.h"

//-----------------------------------------------------------------------------
// Public variables
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Public functions
//-----------------------------------------------------------------------------

void SPI_Init(void)
{   
	// Set MOSI and SCK output, all others input 
	DDRB|=MOSI|SCK;
	// Enable SPI, Master, set clock rate Fosc/16 
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0)|(1<<SPR1);
	//Clear the MISO pin
	PORTB &= 0xF7;
	PORTC &= 0x00;
}

//-----------------------------------------------------------------------------

uint8_t SPI_Read(void)
{
	uint8_t data = 0;
	// Read data the line
	data = SPDR;
	// Clear the MISO pin
	DDRB &= 0xF7;
	return data;
}

//-----------------------------------------------------------------------------

void SPI_Write(uint8_t data)
{
	if (data != 0)
	{
		// Active MISO pin for the send
		DDRB |= 0x08;
	}

	/* SPI Control Register (SPCR):
	 Bit0,1 = SPR0,1: SPI Clock rate 0,1 - fosc/64
	 Bit2 = CPHA : Clock Phase (1)
	 Bit3 = CPOL: Clock Polarity - High when idle
	 Bit4 = MSTR: Master/Slave Select - Slave Select
	 Bit5 = DORD: Data Order - LSB first
	 Bit6 = SPE: SPI Enable - Enable
	 Bit7 = SPIE: SPI Interrupt Enable - Enable
	 */
	SPCR &= 0xBF;
	SPCR |= 0x40;

	// Start data transmission
	SPDR = data;
}
