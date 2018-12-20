/******************************************************************************

 @file  hal_led.h

 @brief This file contains the interface to the LED Service.

 Group: 
 Target Device: 

 ******************************************************************************

 ******************************************************************************
 Release Name: 
 Release Date: 
 *****************************************************************************/

#ifndef __HAL_LED_H__
#define __HAL_LED_H__

/*********************************************************************
 * INCLUDES
 */
#include "stdint.h"
#include "stdmacro.h"
#include "hal_config.h"

#if HAL_LED_EN > 0
/*********************************************************************
 * MACROS
 */

/*********************************************************************
 * CONSTANTS
 */
#define HAL_LED_MAX_LEDS      4

/* LEDS - The LED number is the same as the bit position */
#define HAL_LED_0     BV(0)
#define HAL_LED_1     BV(1)
#define HAL_LED_2     BV(2)
#define HAL_LED_3     BV(3)
//#define HAL_LED_4     BV(4)
//#define HAL_LED_5     BV(5)
//#define HAL_LED_6     BV(6)
//#define HAL_LED_7     BV(7)

#define HAL_LED_ALL   ( HAL_LED_0 | HAL_LED_1 | HAL_LED_2 | HAL_LED_3 )

/* Modes */
#define HAL_LED_MODE_OFF     0x00
#define HAL_LED_MODE_ON      0x01

/* Defaults */

/*********************************************************************
 * TYPEDEFS
 */


/*********************************************************************
 * GLOBAL VARIABLES
 */

/*
 * Initialize LED Service.
 */
extern void hal_led_init( void );

/*
 * Set the LED ON/OFF/TOGGLE.
 */
extern void hal_led_set( uint8_t led, uint8_t mode );


#endif
/*********************************************************************
*********************************************************************/

#endif
