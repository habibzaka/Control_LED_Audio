/**
 * \file UART1.c
 * \author HABIB Zakaria
 * \version 1.0
 * \date 2019/05/24
 */

//-----------------------------------------------------------------------------
// Header files
//-----------------------------------------------------------------------------

#include <avr/io.h>
#include <avr/interrupt.h>
#include "UART1.h"

//-----------------------------------------------------------------------------
// Private macros
//-----------------------------------------------------------------------------

//Defining the frequency of Atmega128.
#define F_CP 16000000 
//Set speed 38400 bauds
#define BAUD 38400 
//Calculate value of UBRR (asynchrone normale mode)
#define UBRR (F_CP / 8 / BAUD ) -1 
//Set number max of data to be received
#define NB_DATA_MAX			255

//-----------------------------------------------------------------------------
// Public enumerations
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Public definitions
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Private structures & union
//-----------------------------------------------------------------------------

/**
* \union Uart1Flag_u
* \brief Uart1Flag byte management
*/
union Uart1Flag_u
{   /*! Buffer of the error frame */
	uint8_t AllError;
	struct
	{   /*! First bit - parity error */
		uint8_t ParityError:1;
		/*! Second bit - pause error */
		uint8_t PauseError:1;
		/*! Third bit - OverLoad Buffer error */
		uint8_t OverLoadBuffer:1;
		/*! Fourth bit - Frame error */
		uint8_t FrameError:1;
		/*! Sixth bit */
		uint8_t :1;
		/*! Seventh bit  */
		uint8_t :1;
		/*! Eighth bit */
		uint8_t :1;
		/*! Ninth bit */
		uint8_t :1;
	};
};
/*!
* \typedef Uart1Flag_t
* \brief Definition of Uart1Flag_u union
*/
typedef union Uart1Flag_u Uart1Flag_t;

//-----------------------------------------------------------------------------
// Private variables
//-----------------------------------------------------------------------------

/*! Private variable : buffer of received data */
uint8_t   Rxbuffer[NB_DATA_MAX];
/*! Private variable : pointer of buffer of received data */
uint8_t*  RxbufferPointer=Rxbuffer;
/*! Private variable : buffer of transmitted data */
uint8_t Txbuffer[NB_DATA_MAX];
/*! Private variable :pointer of buffer of transmitted data */
uint8_t *TxbufferPointer=Txbuffer;
/*! Private variable : index of Transmitted data */
uint8_t IndexBufferTx;
/*! Private variable : length of Transmitted data */
uint8_t NbdataTx;
/*! Private variable of the Flag buffer */
Uart1Flag_t Uart1Flag;
/*! Private variable of number of received data */
uint8_t NbdataRx;

//-----------------------------------------------------------------------------
// Private functions prototypes
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Private functions
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Public functions
//-----------------------------------------------------------------------------

void UART1_Init(void)
{
UBRR1H =0;
//Set speed 38400 baud
UBRR1L =UBRR ; 
// Normal Baud rate(no doubling), Single processor communication                        
UCSR1A= 0x00;        
// Enable receiver and transmitter                  
UCSR1B = (1<<RXEN1)|(1<<RXCIE1)|(1<<TXEN1)|(1<<TXCIE1)|(1<<UDRIE1); 
//Set frame format: 8data, 1 stop bit        
UCSR1C = (1<<UCSZ11)| (1<<UCSZ10);                  
//sei();	
//RXC=0 (only read) TXC=1 (clear tx flag) UDRE (only read)
//FE (only read) DOR (only read) UPE (only read)
//U2X=1 (set the baud rate *2) MPCM=0 (pas de multiproc com)										
UCSR1A=0x42;  
//NC () UMSEL=0 (Asynchron mode) UPM11-UPM10=10 (parity paire)
//USBS1=0 (i bit stop) UCZ11-UCZ10=11 (8 bit) UCPOL don t care      
UCSR1C=0x26;
//RXCIE=1 (enable Rx Int) TXCIE=0 ( disable Tx Int)
//UDRIE=0 (pas int sur Tx buffer empty)
//RXEN = 1 (receive enable) TXEN ( Tx enable )
//UCRZ12 = 0 ( 8 bit ) TXB8-RXB8 don t care		
UCSR1B=0x98;		
//Reset index of tX buffer
IndexBufferTx=0;
//Reset counter of number of received data
UART1_ResetNumdataRX();
//Reset counter of number of transmitted data
NbdataTx=0;
//Reset All error's flag in uart1
Uart1Flag.AllError=0;
}

//-------------------------------------------------------------------------------------------------

void UART1_ReceivedData(uint8_t* buffer,uint8_t* bufferlength)
{ 
	//set the pointer in the buffer of received data 
	RxbufferPointer=buffer;
	//return the number of received data
	*bufferlength=NbdataRx;
}

//-------------------------------------------------------------------------------------------------

void UART1_ResetNumdataRX(void)
{
	//Reset counter of number of received data
	NbdataRx=0;  
}

//-------------------------------------------------------------------------------------------------

uint8_t UART1_CheckFlag(void)
{
	//return flag state
	return Uart1Flag.AllError;
}

void UART1_ResetFlag(void)
{		
	//Reset all error's flag
	Uart1Flag.AllError=0;
}

//-------------------------------------------------------------------------------------------------

void  UART1_SendData(uint8_t* buffer, uint8_t bufferlength)
{
	TxbufferPointer=buffer;
	//set the number of data to transmit
	NbdataTx=bufferlength;
}

//-----------------------------------------------------------------------------
// Interrupts
//-----------------------------------------------------------------------------

//#pragma vector = 0x3c*2
//__interrupt void RX485(void)       //int on USART1
//ISR(_VECTOR(0x3c)) // USART1, RX - USART1, Rx Complete

ISR(USART1_RX_vect)
  {
  //Overflow int disable ?
  if (~(TIMSK&(1<<TOIE0)))         
  //enable overflow int
  TIMSK|=(1<<TOIE0);             
  //test if + de T1.5 car + 1car
  else if (TCNT0>(0xff-(218-93)))        
  //Flag Pause during message
   Uart1Flag.PauseError=1;                  
  //start tempo T3.5 end of frame                                
 //value of  T3.5 125 ; 1.750ms 218 ;
  TCNT0=0xFF-218;                  
  //Clear Timer 1 overFlow flag
  TIFR|=(1<<TOV0);                 
  // error overrun or frame ?
  if ((UCSR1A&(1<<FE1))||(UCSR1A&(1<<DOR1))) 
  // flag error de frame
  Uart1Flag.FrameError=1;                            
  if (UCSR1A&(1<<UPE1)) 
  //error ParitY ?                     
  Uart1Flag.ParityError=1;                           
  // save value RX in buffer et inc pointer
  RxbufferPointer[NbdataRx]=UDR1;
  NbdataRx++;
  //if number of data superior of 256
  if (NbdataRx>NB_DATA_MAX+1)
  //flag overload buffer
  Uart1Flag.OverLoadBuffer=1;          
    
  }
  
//-------------------------------------------------------------------------------------------

//Interrupt on Buffer Empty USART1
//#pragma vector = 0x3E*2            
//__interrupt void TX485(void)
//ISR(_VECTOR(0x3E)) // USART1, UDRE - USART1 Data Register Empty

ISR(USART1_UDRE_vect)
  {
  //Number of data to send 
  if(IndexBufferTx!=NbdataTx)       
  UDR1=TxbufferPointer[IndexBufferTx++];
  else
    {
	//Reset received data counter
    UART1_ResetNumdataRX();  
	//Reset transmitted data counter
	NbdataTx=0; 
	//Reset the index of Tx buffer               
    IndexBufferTx=0;
	//disable int on buffer empty
    UCSR1B&=~(1<<UDRIE1); 
	//clear TXC1 flag in TX       
    UCSR1A|=(1<<TXC1);  
	//Interrupt on the TXC1() flag.           
    UCSR1B|=(1<<TXCIE1);           
    }
  }
  
//-------------------------------------------------------------------------------------------

//#pragma vector = 0x40*2
//__interrupt void TX485E(void)  //Interrupt on TX end USART1
//ISR(_VECTOR(0x40)) // USART1, TX - USART1, Tx Complete

ISR(USART1_TX_vect)
  {
	 //Disable TX RS485 after send DATA
	 PORTD&=~(1<<4);  
	 //Disable Interrupt on the TXC1() flag. 
	 //TXC1 is set when there is no more data in buffer (UDR1)           
	 UCSR1B&=~(1<<TXCIE1);        
   }
