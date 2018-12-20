/******************************************************************************

 @file  app_event_key.c

 @brief 

 Group: 
 Target Device: 

 ******************************************************************************
 

 ******************************************************************************
 Release Name: 
 Release Date: 2016-06-09 06:57:09
 *****************************************************************************/

/**************************************************************************************************
 * INCLUDES
 **************************************************************************************************/
#include "osal.h"
#include "hal.h"
#include "app.h"

#include "main.h"

#include "stdstr.h"
#include "stringx.h"

#if (APP_KEY_EN > 0)
/**************************************************************************************************
 * TYPE DEFINES
 **************************************************************************************************/

 /**************************************************************************************************
 * LOCAL API DECLARATION
 **************************************************************************************************/

/**************************************************************************************************
 * CONSTANTS
 **************************************************************************************************/

/**************************************************************************************************
 * GLOBAL VARIABLES
 **************************************************************************************************/
#if (APP_CLI_EN > 0)
static void app_cli_print_key( uint8_t keyValue, uint8_t keyEvent )
{
    uint8_t i;
    uint8_t cnt;

    FLASH char *pKeyEvent[] = {
        "LEAVE",
        "ENTER",
        "SHORT",
        "LONG",
        "VLONG"
    };

    FLASH char *pKeyName[HAL_KEY_MAX] = {
        "LIGHT",
        "MIST"
    };
    
    hal_cli_print_str( "KEY=" );
    for( i = 0, cnt = 0; i < HAL_KEY_MAX; i++ )
    {
        if( keyValue & BV(i) )
        {
            if( cnt != 0 )
            {
                putchar( '+' );
            }
            hal_cli_print_str( pKeyName[i] );
            cnt++;
        }
    }
    putchar( ' ' );
    hal_cli_print_str( pKeyEvent[keyEvent] );
    hal_cli_print_str( "\r\n" );
}
#endif //(APP_CLI_EN > 0)


extern void app_event_key_update( uint8_t keyValue, uint8_t keyEvent )
{
    uint16_t keyMerge;
    int8_t s8_tmp;
    
#if (APP_CLI_EN > 0)
    app_cli_print_key( keyValue, keyEvent );
#endif

    keyMerge = BUILD_UINT16( keyValue, keyEvent );

    switch( keyMerge )
    {
        case BUILD_UINT16( HAL_KEY_MIST, KEY_EVENT_ENTER ):
        {
            hal_led_set( HAL_LED_ALL, HAL_LED_MODE_ON );
            if( app_info.mist_state == MIST_STATE_OFF )
            {
                app_info.mist_state = MIST_STATE_ON;
                hal_mist_on();
            }
            else
            {
                s8_tmp = hal_mcu_hsi_trim_get();
                s8_tmp++;
                hal_mcu_hsi_trim_set( s8_tmp );
            }
        }
        break;

        case BUILD_UINT16( HAL_KEY_MIST, KEY_EVENT_SHORT ):
        {
            hal_led_set( HAL_LED_ALL, HAL_LED_MODE_OFF );
        }
        break;

        case BUILD_UINT16( HAL_KEY_MIST, KEY_EVENT_LONG ):
        {
            if( app_info.mist_state == MIST_STATE_ON )
            {
                app_info.mist_state = MIST_STATE_OFF;
                hal_mist_off();
            }
        }
        break;
        
        case BUILD_UINT16( HAL_KEY_MIST, KEY_EVENT_VLONG ):
        {
            keyMerge = 3;
        }
        break;

        case BUILD_UINT16( HAL_KEY_MIST, KEY_EVENT_LEAVE ):
        {
            hal_led_set( HAL_LED_ALL, HAL_LED_MODE_OFF );
        }
        break;

        case BUILD_UINT16( HAL_KEY_LIGHT, KEY_EVENT_ENTER ):
        {
            hal_led_set( HAL_LED_ALL, HAL_LED_MODE_ON );
            if( app_info.mist_state == MIST_STATE_OFF )
            {
                app_info.mist_state = MIST_STATE_ON;
                hal_mist_on();
            }
            else
            {
                s8_tmp = hal_mcu_hsi_trim_get();
                s8_tmp--;
                hal_mcu_hsi_trim_set( s8_tmp );
            }
        }
        break;

        case BUILD_UINT16( HAL_KEY_LIGHT, KEY_EVENT_SHORT ):
        {
            hal_led_set( HAL_LED_ALL, HAL_LED_MODE_OFF );
        }
        break;

        case BUILD_UINT16( HAL_KEY_LIGHT, KEY_EVENT_LONG ):
        {
            hal_mcu_hsi_trim_set( 0 );
        }
        break;
        
        case BUILD_UINT16( HAL_KEY_LIGHT, KEY_EVENT_VLONG ):
        {
            keyMerge = 7;
        }
        break;

        case BUILD_UINT16( HAL_KEY_LIGHT, KEY_EVENT_LEAVE ):
        {
            hal_led_set( HAL_LED_ALL, HAL_LED_MODE_OFF );
        }
        break;

        case BUILD_UINT16( HAL_KEY_MIST + HAL_KEY_LIGHT, KEY_EVENT_LONG ):
        {
            keyMerge = 8;
        }
        break;
        
        case BUILD_UINT16( HAL_KEY_MIST + HAL_KEY_LIGHT, KEY_EVENT_VLONG ):
        {
            keyMerge = 9;
        }
        break;

        default:
        break;
    }
}

#endif //(APP_KEY_EN > 0)


/**************************************************************************************************
**************************************************************************************************/

