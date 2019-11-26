/**
 * \file UART1.h
 * \brief Header file of UART1.c
 * \author HABIB Zakaria
 * \version 1.0
 * \date 2019/05/24
 */

#ifndef __UART1_H
#define __UART1_H

//-----------------------------------------------------------------------------
// Header files
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Public macros
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Public enumerations
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Public definitions
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Public structures & union
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Public variables
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Public functions
//-----------------------------------------------------------------------------

 /**
 * \fn void UART1_Init(void);	
 * \function to initialize uart1
 */
void UART1_Init(void);	

 /**
 * \fn void UART1_Reset_NumdataRX(void);	
 * \function to initialize Number of data received
 */
void UART1_ResetNumdataRX(void);


 /**
 * \fn uint8_t UART1_CheckFlag(void);;	
 * \function that return all flag state in uart1
 */
uint8_t UART1_CheckFlag(void);

 /**
 * \fn void UART1_ResetFlag(void);	
 * \function to reset all flag in uart1
 */
void UART1_ResetFlag(void);

/**
* \fn void UART1_ReceivedData(uint8_t* buffer); ;
* \brief management of received data
* \param[in] buffer): the buffer of received data
* \param[in] bufferlength): the number of received data
*/
void UART1_ReceivedData(uint8_t* buffer , uint8_t* bufferlength);


/**
* \fn void  UART1_SendData( uint8_t* buffer , uint8_t bufferlength);
* \brief Management of the Transmitted data
* \param [in] *buffer: Buffer of the Transmitted data
* \param [in] bufferlength: Number of data received (in byte)
*/
void  UART1_SendData( uint8_t* buffer , uint8_t bufferlength);

#endif /* DEF_H_ */