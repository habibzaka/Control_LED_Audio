/**
* \file LedRgb.c
* \brief  definition file for LedRgb.c
* \author Habib Zakaria
* \version 1.0
* \date 2019/06/03
*/


//-----------------------------------------------------------------------------
// Header files
//-----------------------------------------------------------------------------

#include "LedRgb.h"

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

void LedRgb_Init(void)
{
	
	//setup pwm on timer 1
	//Clear OC1 on compare match, set OC1 at TOP
	//Fast PWM
	TCCR1A|=(1<<COMA1)|(1<<COMB1)|(1<<WGM10)|(1<<COMC1);
	//ClkI/O/(No prescaling) on timer1
	TCCR1B|=(1<<WGM12)|(1<<CS10);
	//set PB7(OC2), PB6(OC1B), PB5(OC1A) in Output
	DDRB|=(1<<DDB7)|(1<<DDB6)|(1<<DDB5);
	//set PC2 in Output to turn on led
	DDRC|=(1<<DDC2);
}

//-------------------------------------------------------------------------------

void LedRgb_Command(uint8_t red, uint8_t green, uint8_t blue, uint8_t brightness)
{   
	//set red value between 0 and 255
	OCR1C=(red*brightness)/100;
	//set green value between 0 and 255
	OCR1A=(green*brightness)/100;
	//set blue value between 0 and 255
	OCR1B=(blue*brightness)/100;
		
}

//--------------------------------------------------------------------------------

void LedRgb_Start(void)
{
	//Set PC2
	PORTC|=(1<<PC2);
	
}

//---------------------------------------------------------------------------------

void LedRgb_Stop(void)
{   
	//Reset PC2
	PORTC|=~(1<<PC2);
}