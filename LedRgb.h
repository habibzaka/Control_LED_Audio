/**
* \file LedRgb.h
* \brief  definition file for LedRgb.h
* \author Habib Zakaria
* \version 1.0
* \date 2019/06/03
*/

#ifndef LEDRGB_H_
#define LEDRGB_H_

//-----------------------------------------------------------------------------
// Header files
//-----------------------------------------------------------------------------

#include <avr/io.h>

//-----------------------------------------------------------------------------
// Public macros
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Public enumerations
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Public structures
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Public definitions
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Public variables
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Public functions
//-----------------------------------------------------------------------------

/**
 * \fn void LedRgb_Init(void)
 * \brief initialization of led
 */
void LedRgb_Init(void);

/**
* \fn void  void LedRgb_Command(uint8_t red, uint8_t green, uint8_t blue, uint8_t brightness)
* \brief Management of the Transmitted data
* \param [in] red: value of red color between 0 and 255
* \param [in] green: value of red color between 0 and 255
* \param [in] blue: value of green color between 0 and 255
* \param [in] brightness: Brightness of led betweeen 0 and 100%
*/
void LedRgb_Command(uint8_t red, uint8_t green, uint8_t blue, uint8_t brightness);

/**
 * \fn void LedRgb_TurnOff(void);
 * \function to turn off led
 */
void LedRgb_Stop(void);

/**
 * \fn void LedRgb_TurnOn(void);
 * \function to turn on led
 */
void LedRgb_Start(void);

#endif /* LEDRGB_H_ */