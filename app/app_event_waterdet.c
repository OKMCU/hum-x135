/******************************************************************************

 @file  app_event_waterdet.c

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

#if APP_WATERDET_EN > 0
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

extern void app_event_waterdet_no_water( void )
{   
#if APP_CLI_EN > 0
    hal_cli_print_str( "No Water" );
    hal_cli_print_str( ".\r\n" );
#endif

    app_info.mist_mode = MIST_MODE_OFF;
    osal_event_set( TASK_ID_APP_MIST, TASK_EVT_APP_MIST_SET_MODE );
    LED_IND_MIST_MODE_OFF();

    app_info.light_mode = LIGHT_MODE_OFF;
    osal_event_set( TASK_ID_APP_LIGHT, TASK_EVT_APP_LIGHT_SET_MODE );
    
    osal_event_set( TASK_ID_APP_FHOP, TASK_EVT_APP_FHOP_RESET );
}

#endif
/**************************************************************************************************
**************************************************************************************************/

