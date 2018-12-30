/******************************************************************************

 @file  hal_led.c

 @brief This file contains the interface to the HAL LED Service.

 Group: 
 Target Device: 

 ******************************************************************************
 

 ******************************************************************************
 Release Name: 
 Release Date: 
 *****************************************************************************/

/***************************************************************************************************
 * INCLUDES
 ***************************************************************************************************/

#include "osal.h"
#include "spl.h"

#include "hal_config.h"
#include "hal_assert.h"
#include "hal_led.h"

#include "main.h"

#include "stdstr.h"
#include "stringx.h"
#include "bufmgr.h"

#if HAL_LED_EN > 0
/***************************************************************************************************
 * MACROS
 ***************************************************************************************************/
#define HAL_LED_IO_INIT()        st(SPL_GPIO_SET_MODE_P13_OUTPUT();\
                                    SPL_GPIO_SET_MODE_P14_OUTPUT();\
                                    SPL_GPIO_SET_MODE_P17_OUTPUT();\
                                    SPL_GPIO_SET_MODE_P30_OUTPUT();)

#define HAL_TURN_ON_LED0()       spl_gpio_write_pin(SPL_GPIO_PIN_P13, 1)
#define HAL_TURN_ON_LED1()       spl_gpio_write_pin(SPL_GPIO_PIN_P14, 1)
#define HAL_TURN_ON_LED2()       spl_gpio_write_pin(SPL_GPIO_PIN_P17, 1)
#define HAL_TURN_ON_LED3()       spl_gpio_write_pin(SPL_GPIO_PIN_P30, 1)
#define HAL_TURN_ON_LED4()       //spl_gpio_write_pin(SPL_GPIO_PORT_2, SPL_GPIO_PIN_4, 0)
#define HAL_TURN_ON_LED5()       //spl_gpio_write_pin(SPL_GPIO_PORT_3, SPL_GPIO_PIN_6, 0)
#define HAL_TURN_ON_LED6()       //spl_gpio_write_pin(SPL_GPIO_PORT_3, SPL_GPIO_PIN_7, 0)
#define HAL_TURN_ON_LED7()       //spl_gpio_write_pin(SPL_GPIO_PORT_0, SPL_GPIO_PIN_6, 0)

#define HAL_TURN_OFF_LED0()      spl_gpio_write_pin(SPL_GPIO_PIN_P13, 0)
#define HAL_TURN_OFF_LED1()      spl_gpio_write_pin(SPL_GPIO_PIN_P14, 0)
#define HAL_TURN_OFF_LED2()      spl_gpio_write_pin(SPL_GPIO_PIN_P17, 0)
#define HAL_TURN_OFF_LED3()      spl_gpio_write_pin(SPL_GPIO_PIN_P30, 0)
//#define HAL_TURN_OFF_LED4()      spl_gpio_write_pin(SPL_GPIO_PORT_2, SPL_GPIO_PIN_4, 1)
//#define HAL_TURN_OFF_LED5()      spl_gpio_write_pin(SPL_GPIO_PORT_3, SPL_GPIO_PIN_6, 1)
//#define HAL_TURN_OFF_LED6()      spl_gpio_write_pin(SPL_GPIO_PORT_3, SPL_GPIO_PIN_7, 1)
//#define HAL_TURN_OFF_LED7()      spl_gpio_write_pin(SPL_GPIO_PORT_0, SPL_GPIO_PIN_6, 1)

#define HAL_STATE_LED0()         spl_gpio_read_pin(SPL_GPIO_PIN_P13)
#define HAL_STATE_LED1()         spl_gpio_read_pin(SPL_GPIO_PIN_P14)
#define HAL_STATE_LED2()         spl_gpio_read_pin(SPL_GPIO_PIN_P17)
#define HAL_STATE_LED3()         spl_gpio_read_pin(SPL_GPIO_PIN_P30)
//#define HAL_STATE_LED4()        (spl_gpio_read_pin(SPL_GPIO_PORT_2, SPL_GPIO_PIN_4) ? 0 : 1)
//#define HAL_STATE_LED5()        (spl_gpio_read_pin(SPL_GPIO_PORT_3, SPL_GPIO_PIN_6) ? 0 : 1)
//#define HAL_STATE_LED6()        (spl_gpio_read_pin(SPL_GPIO_PORT_3, SPL_GPIO_PIN_7) ? 0 : 1)
//#define HAL_STATE_LED7()        (spl_gpio_read_pin(SPL_GPIO_PORT_0, SPL_GPIO_PIN_6) ? 0 : 1)

/***************************************************************************************************
 * TYPEDEFS
 ***************************************************************************************************/


/***************************************************************************************************
 * GLOBAL VARIABLES
 ***************************************************************************************************/

/***************************************************************************************************
 * LOCAL FUNCTIONS
 ***************************************************************************************************/

/***************************************************************************************************
 * FUNCTIONS - API
 ***************************************************************************************************/

/***************************************************************************************************
 * @fn      hal_led_init
 *
 * @brief   Initialize LED Service
 *
 * @param   init - pointer to void that contains the initialized value
 *
 * @return  None
 ***************************************************************************************************/
void hal_led_init (void)
{
    HAL_LED_IO_INIT();
}

/***************************************************************************************************
 * @fn      HalLedSet
 *
 * @brief   Tun ON/OFF/TOGGLE given LEDs
 *
 * @param   led - bit mask value of leds to be turned ON/OFF/TOGGLE
 *          mode - BLINK, FLASH, TOGGLE, ON, OFF
 * @return  None
 ***************************************************************************************************/
void hal_led_set (uint8_t leds, uint8_t mode)
{
  if (leds & HAL_LED_0)
  {
    if (mode == HAL_LED_MODE_ON)
    {
      HAL_TURN_ON_LED0();
    }
    else
    {
      HAL_TURN_OFF_LED0();
    }
  }

  if (leds & HAL_LED_1)
  {
    if (mode == HAL_LED_MODE_ON)
    {
      HAL_TURN_ON_LED1();
    }
    else
    {
      HAL_TURN_OFF_LED1();
    }
  }

  if (leds & HAL_LED_2)
  {
    if (mode == HAL_LED_MODE_ON)
    {
      HAL_TURN_ON_LED2();
    }
    else
    {
      HAL_TURN_OFF_LED2();
    }
  }

  if (leds & HAL_LED_3)
  {
    if (mode == HAL_LED_MODE_ON)
    {
      HAL_TURN_ON_LED3();
    }
    else
    {
      HAL_TURN_OFF_LED3();
    }
  }
}

#endif
/***************************************************************************************************
***************************************************************************************************/




