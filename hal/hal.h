/******************************************************************************

 @file  hal.h

 @brief Describe the purpose and contents of the file.

 Group: 
 Target Device: 

 ******************************************************************************

 ******************************************************************************
 Release Name: 
 Release Date: 
 *****************************************************************************/

#ifndef __HAL_H__
#define __HAL_H__

#include "hal_config.h"

#if HAL_ASSERT_EN > 0
#include "hal_assert.h"
#endif

#include "hal_drivers.h"
#include "hal_mcu.h"

#if HAL_CLI_EN > 0
#include "hal_cli.h"
#endif

#if HAL_MIST_EN > 0
#include "hal_mist.h"
#endif

#if HAL_KEY_EN > 0
#include "hal_key.h"
#endif

#if HAL_LED_EN > 0
#include "hal_led.h"
#endif

#if HAL_FREQDET_EN > 0
#include "hal_freqdet.h"
#endif

#if HAL_WATERDET_EN > 0
#include "hal_waterdet.h"
#endif

#if HAL_LIGHT_EN > 0
#include "hal_light.h"
#endif

#if HAL_BUZZER_EN > 0
#include "hal_buzzer.h"
#endif

#if HAL_FAN_EN > 0
#include "hal_fan.h"
#endif


/* ------------------------------------------------------------------------------------------------
 *                                           Macros
 * ------------------------------------------------------------------------------------------------
 */

/* ------------------------------------------------------------------------------------------------
 *                                          Prototypes
 * ------------------------------------------------------------------------------------------------
 */

/**************************************************************************************************
 */

/**************************************************************************************************
 *                                        FUNCTIONS - API
 **************************************************************************************************/
//extern void hal_init( void );

#endif

