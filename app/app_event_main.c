/******************************************************************************

 @file  app_event_main.c

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

extern void app_event_main_por( void )
{
#if APP_CLI_EN > 0
    hal_cli_print_str( "\r\nThis is OSAL demo project on Nuvoton 8051 series MCU.\r\n" );
    hal_cli_print_str( "Power on reset.\r\n" );

    hal_cli_print_str( "Free-OSAL Version " );
    hal_cli_print_str( OSAL_VERSION );
    hal_cli_print_str( "\r\n" );
    
    hal_cli_print_str( "Firmware Version " );
    hal_cli_print_str( FIRMWARE_VER );
    hal_cli_print_str( "\r\n" );

    hal_cli_print_str( "Hardware Version " );
    hal_cli_print_str( HARDWARE_VER );
    hal_cli_print_str( "\r\n" );
#endif

#if APP_KEY_EN > 0
    app_info.key_state = 0x00;
#endif
    app_info.sys_flags = 0x00;

#if APP_FHOP_EN > 0
    app_info.freq_index = 0;
#endif

#if APP_WATERDET_EN > 0
    app_info.water_index = 0;
#endif

#if APP_LIGHT_EN > 0
    app_info.light_mode = 0;
#endif

#if APP_MIST_EN > 0
    app_info.mist_mode = 0;
#endif

#if APP_BUZZER_EN > 0
    app_info.buzzer_beep = BUZZER_BEEP_DOUBLE_SHORT;
    osal_event_set( TASK_ID_APP_BUZZER, TASK_EVT_APP_BUZZER_BEEP_UPDATE );
#endif

    osal_event_set( TASK_ID_APP_MAIN, TASK_EVT_APP_MAIN_IDLE );
}


extern void app_event_main_app_exception( void )
{
#if (APP_CLI_EN > 0)
    hal_cli_print_str( "ERROR! " );
    hal_cli_print_str( "APP EXCEPTION!\r\n" );
#endif
}

extern void app_event_main_hal_exception( void )
{
#if (APP_CLI_EN > 0)
    hal_cli_print_str( "ERROR! " );
    hal_cli_print_str( "HAL EXCEPTION!\r\n" );
#endif
}

extern void app_event_main_osal_exception( void )
{
#if (APP_CLI_EN > 0)
    hal_cli_print_str( "ERROR! " );
    hal_cli_print_str( "OSAL_EXCEPTION!\r\n" );
#endif
}

extern void app_event_main_idle( void )
{
    uint8_t u8_tmp;

#if APP_KEY_EN > 0
    //polling the keys
    u8_tmp = hal_key_read();
    if( u8_tmp != app_info.key_state )
    {
        app_info.key_state = u8_tmp;
        osal_timer_event_create( TASK_ID_APP_KEY, TASK_EVT_APP_KEY_UPDATE, HAL_KEY_DEBOUNCE_TIME );
    }
#endif

    if( app_info.sys_flags & SYS_FLAGS_MIST_ON )
    {
        #if APP_FHOP_EN > 0
        if( !(app_info.sys_flags & SYS_FLAGS_FREQ_FINISH) &&
             (app_info.sys_flags & SYS_FLAGS_FHOP_ON) )
        {
            app_info.freq_index = hal_freqdet_read();
            osal_event_set( TASK_ID_APP_FHOP, TASK_EVT_APP_FHOP_UPDATE );
        }
        #endif

        #if APP_WATERDET_EN > 0
        if( app_info.sys_flags & SYS_FLAGS_WATERDET_ON )
        {
            app_info.water_index = hal_waterdet_read();
            osal_event_set( TASK_ID_APP_WATERDET, TASK_EVT_APP_WATERDET_UPDATE );
        }
        #endif
    }

    osal_event_set( TASK_ID_APP_MAIN, TASK_EVT_APP_MAIN_IDLE );
}

/**************************************************************************************************
**************************************************************************************************/

