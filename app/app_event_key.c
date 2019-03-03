/******************************************************************************

 @file  app_event_key.c

 @brief 

 Group: 
 Target Device: 

 ******************************************************************************
 

 ******************************************************************************
 Release Name: 
 Release Date: 
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
 * MACROS
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
                hal_cli_putchar( '+' );
            }
            hal_cli_print_str( pKeyName[i] );
            cnt++;
        }
    }
    hal_cli_putchar( ' ' );
    hal_cli_print_str( pKeyEvent[keyEvent] );
    hal_cli_print_str( "\r\n" );
}
#endif //(APP_CLI_EN > 0)


extern void app_event_key_update( uint8_t keyValue, uint8_t keyEvent )
{
    uint16_t keyMerge;
    
#if (APP_CLI_EN > 0)
    app_cli_print_key( keyValue, keyEvent );
#endif

    keyMerge = BUILD_UINT16( keyValue, keyEvent );

    switch( keyMerge )
    {
        case BUILD_UINT16( HAL_KEY_MIST, KEY_EVENT_ENTER ):
        {
            //BEEP BUZZER
            
            //hal_led_set( HAL_LED_ALL, HAL_LED_MODE_ON );
            //if( !(app_info.sys_flags & SYS_FLAGS_MIST_ON) )
            //{
            //    app_info.sys_flags |= SYS_FLAGS_MIST_ON;
            //    hal_mist_on();
            //
            //    osal_event_set( TASK_ID_APP_WATERDET, TASK_EVT_APP_WATERDET_RESET );
            //    osal_event_set( TASK_ID_APP_FHOP, TASK_EVT_APP_FHOP_RESET );
            //    
            //    if( (app_info.sys_flags & SYS_FLAGS_FREQ_FOUND) )
            //        app_info.sys_flags |= SYS_FLAGS_WATERDET_ON;
            //}
        }
        break;

        case BUILD_UINT16( HAL_KEY_MIST, KEY_EVENT_SHORT ):
        {
            app_info.mist_mode++;
            if( app_info.mist_mode > MIST_MODE_4 )
            {
                app_info.mist_mode = MIST_MODE_OFF;
            }

            if      ( app_info.mist_mode == MIST_MODE_OFF )   LED_IND_MIST_MODE_OFF();
            else if ( app_info.mist_mode == MIST_MODE_1   )   LED_IND_MIST_MODE_1();
            else if ( app_info.mist_mode == MIST_MODE_2   )   LED_IND_MIST_MODE_2();
            else if ( app_info.mist_mode == MIST_MODE_3   )   LED_IND_MIST_MODE_3();
            else if ( app_info.mist_mode == MIST_MODE_4   )   LED_IND_MIST_MODE_4();

            osal_event_set( TASK_ID_APP_MIST, TASK_EVT_APP_MIST_SET_MODE );

            #if 0
            if( app_info.sys_flags & SYS_FLAGS_FREQ_FOUND )
            {
                osal_event_set( TASK_ID_APP_MIST, TASK_EVT_APP_MIST_SET_MODE );
            }
            else
            {
                if( app_info.mist_mode == MIST_MODE_OFF )
                {
                    osal_event_set( TASK_ID_APP_MIST, TASK_EVT_APP_MIST_SET_MODE );
                }
                else
                {
                    hal_mist_on();
                    app_info.sys_flags |= SYS_FLAGS_MIST_ON;
                    #if APP_WATERDET_EN > 0
                    osal_event_set( TASK_ID_APP_WATERDET, TASK_EVT_APP_WATERDET_RESET );
                    #endif
                    #if APP_FHOP_EN > 0
                    osal_event_set( TASK_ID_APP_FHOP, TASK_EVT_APP_FHOP_RESET );
                    #endif
                }
            }
            #endif
            
        }
        break;

        case BUILD_UINT16( HAL_KEY_MIST, KEY_EVENT_LONG ):
        {
            //if( app_info.sys_flags & SYS_FLAGS_MIST_ON )
            //{
            //    app_info.sys_flags &= ~SYS_FLAGS_MIST_ON;
            //    hal_mist_off();
            //}
            app_info.mist_mode = MIST_MODE_OFF;
            osal_event_set( TASK_ID_APP_MIST, TASK_EVT_APP_MIST_SET_MODE );
        }
        break;
        
        case BUILD_UINT16( HAL_KEY_MIST, KEY_EVENT_VLONG ):
        {
            
        }
        break;

        case BUILD_UINT16( HAL_KEY_MIST, KEY_EVENT_LEAVE ):
        {
            
        }
        break;

        case BUILD_UINT16( HAL_KEY_LIGHT, KEY_EVENT_ENTER ):
        {
            app_info.light_mode++;
            if( app_info.light_mode >= LIGHT_MODE_SEL + LIGHT_COLOR_SEL_SIZE )
            {
                app_info.light_mode = LIGHT_MODE_OFF;
            }
            osal_event_set( TASK_ID_APP_LIGHT,  TASK_EVT_APP_LIGHT_SET_MODE );
        }
        break;

        case BUILD_UINT16( HAL_KEY_LIGHT, KEY_EVENT_SHORT ):
        {
        }
        break;

        case BUILD_UINT16( HAL_KEY_LIGHT, KEY_EVENT_LONG ):
        {
            app_info.light_mode = LIGHT_MODE_OFF;
            osal_event_set( TASK_ID_APP_LIGHT,  TASK_EVT_APP_LIGHT_SET_MODE );
        }
        break;
        
        case BUILD_UINT16( HAL_KEY_LIGHT, KEY_EVENT_VLONG ):
        {
        }
        break;

        case BUILD_UINT16( HAL_KEY_LIGHT, KEY_EVENT_LEAVE ):
        {
        }
        break;

        case BUILD_UINT16( HAL_KEY_MIST + HAL_KEY_LIGHT, KEY_EVENT_LONG ):
        {
        }
        break;
        
        case BUILD_UINT16( HAL_KEY_MIST + HAL_KEY_LIGHT, KEY_EVENT_VLONG ):
        {
        }
        break;

        default:
        break;
    }
}

#endif //(APP_KEY_EN > 0)


/**************************************************************************************************
**************************************************************************************************/

