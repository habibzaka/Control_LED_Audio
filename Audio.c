/**
* \file Audio.c
* \brief  definition file for LedRgb.c
* \author Habib Zakaria
* \version 1.0
* \date 2019/06/06
*/

//-----------------------------------------------------------------------------
// Header files
//-----------------------------------------------------------------------------

#include <avr/interrupt.h>
#include "Audio.h"
#include "Spi.h"
#include "Sound.h"
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

void Audio_Init(void)
{
	 //set PE3(OC3A) in Output
 	 DDRE|=(1<<DDE3);
	 //Clear OC3A on compare match, set OC3A at TOP
     //Fast PWM
	 TCCR3A|=(1<<COM3A1)|(1<<WGM30);
	 //Freq_out=Freq_Clk/(Prescaler*(OC3A)
	 //ClkI/8/(8 prescaling) : 16MHz/8 = 2MHz
     TCCR3B|=(1<<WGM32)|(1<<CS31);
	 // Enable global interrupts by setting global interrupt enable bit in SREG
	 sei();          
	 // Enable timer3 overflow interrupt(TOIE3)
     ETIMSK|=(1<<TOIE3) ;
	 //Set 16Khz
	 // (Time=Prescaler*TCNT3/Freq) Time=62.5us(16Khz)
	 TCNT3 = 135; 
 
	 
}

//-----------------------------------------------------------------------------
// Interrupts
//-----------------------------------------------------------------------------

//Interrupt on timer 3 overflow
//ISR(_VECTOR(0x25)) // TIMER3 OVF - Timer/Counter3 Overflow
//(Time=Prescaler*OC3B/Freq) Time=62.5us

ISR(TIMER3_OVF_vect)
{
	//Output for audio
    //OCR3A=pcm[counter] ;
	//counter++;
	//if(counter>1998)counter=0;
	//Set 16Khz
	// (Time=Prescaler*TCNT3/Freq) Time=62.5us(16Khz)
	TCNT3 = 135; 
}
