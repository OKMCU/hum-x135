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

#if APP_FHOP_EN > 0
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

extern void app_event_fhop_finish_freq_found( void )
{
    volatile int8_t trim;

    trim = hal_mcu_hsi_trim_get();
#if APP_CLI_EN > 0
    hal_cli_print_str( "Freq found " );
    hal_cli_print_sint( trim );
    hal_cli_print_str( ". " );
    hal_cli_print_str( ".\r\n" );
#endif

#if (APP_FHOP_FOUND_BEEP_EN > 0) && (APP_BUZZER_EN > 0)
    app_info.buzzer_beep = BUZZER_BEEP_LONG;
    osal_event_set( TASK_ID_APP_BUZZER, TASK_EVT_APP_BUZZER_BEEP_UPDATE );
#endif
}

extern void app_event_fhop_finish_freq_max( void )
{
#if APP_CLI_EN > 0
    hal_cli_print_str( "Freq max " );
    hal_cli_print_sint( hal_mcu_hsi_trim_get() );
    hal_cli_print_str( ". " );
    hal_cli_print_str( ".\r\n" );
#endif
#if (APP_FHOP_FOUND_BEEP_EN > 0) && (APP_BUZZER_EN > 0)
    app_info.buzzer_beep = BUZZER_BEEP_TRIPLE_SHORT;
    osal_event_set( TASK_ID_APP_BUZZER, TASK_EVT_APP_BUZZER_BEEP_UPDATE );
#endif
}

extern void app_event_fhop_finish_freq_min( void )
{
#if APP_CLI_EN > 0
    hal_cli_print_str( "Freq min " );
    hal_cli_print_sint( hal_mcu_hsi_trim_get() );
    hal_cli_print_str( ". " );
    hal_cli_print_str( ".\r\n" );
#endif
#if (APP_FHOP_FOUND_BEEP_EN > 0) && (APP_BUZZER_EN > 0)
    app_info.buzzer_beep = BUZZER_BEEP_TRIPLE_SHORT;
    osal_event_set( TASK_ID_APP_BUZZER, TASK_EVT_APP_BUZZER_BEEP_UPDATE );
#endif
}

#endif
/**************************************************************************************************
**************************************************************************************************/

