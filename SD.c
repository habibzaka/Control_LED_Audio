/**
* \file SD.c
* \brief  definition file for SD.c
* \author Habib Zakaria
* \version 1.0
* \date 2019/06/06
*/


//-----------------------------------------------------------------------------
// Header files
//-----------------------------------------------------------------------------
#include "SD.h"
#include "Spi.h"

//-----------------------------------------------------------------------------
// Private macros
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Private enumerations
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Private structures
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Private definitions
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Private variables
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Private functions prototype
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Private functions
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Public functions
//-----------------------------------------------------------------------------


uint8_t SD_init(void)
{
	uint8_t i;
	CS_DISABLE();
	// ]r:10
	for(i=0; i<10; i++) // idle for 1 bytes / 80 clocks
	SPI_Write(0xFF);
	char response = 0x01;
	//Send Command 0 to put SD in SPI mode
	SD_Command(0x40, 0x00000000, 0x95, 8);    // crc has to be 0x95 for the first interaction and after that it doesn't matter
	//Now wait for READY RESPONSE
	if(SD_GetResponse() != 0x01){
		return 0x04;
	}
	while(response == 0x01)
	{
		SD_Command(0x41, 0x00000000, 0xff, 8);
		response = SD_GetResponse();
	}
	SPI_Write(0xFF);
	return 0;
}

void SD_Command(uint8_t cmd, unsigned long arg,uint8_t crc, uint8_t read)
{
	
	uint8_t index;
	uint8_t buffer[8];
	CS_ENABLE();
	SPI_Write(cmd);
	SPI_Write(arg>>24);
	SPI_Write(arg>>16);
	SPI_Write(arg>>8);
	SPI_Write(arg);
	SPI_Write(crc);
	for(index=0; index<read; index++)
	{
	SPI_Write(0xFF);
	buffer[index] = SPI_Read();
	}
	// print out read bytes
	CS_DISABLE();
}


uint8_t SD_GetResponse(void)
{
	//Response comes 1-8bytes after command
	//the first bit will be a 0
	//followed by an error code
	//data will be 0xff until response
	int i = 0;
	uint8_t response;
	while(i<=64)
	{   SPI_Write(0xFF);
		response = SPI_Read();
		if(response == 0x00)break;
		if(response == 0x01)break;
		i++;
	}
	return response;
}