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

    hal_cli_print_str( "Firmware Version " );
    hal_cli_print_str( FIRMWARE_VER );
    hal_cli_print_str( "\r\n" );

    hal_cli_print_str( "Hardware Version " );
    hal_cli_print_str( HARDWARE_VER );
    hal_cli_print_str( "\r\n" );
#endif
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

/**************************************************************************************************
**************************************************************************************************/

