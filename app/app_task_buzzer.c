/******************************************************************************

 @file  app_task_buzzer.c

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
#include "stdmacro.h"

#if APP_BUZZER_EN > 0
/**************************************************************************************************
 * TYPES
 **************************************************************************************************/

/**************************************************************************************************
 * CONSTANTS
 **************************************************************************************************/
#define BEEP_SHORT_ON_TIME              100
#define BEEP_LONG_ON_TIME               1000
#define BEEP_DOUBLE_SHORT_ON_TIME       100
#define BEEP_DOUBLE_SHORT_OFF_TIME      100
#define BEEP_DOUBLE_SHORT_x2_INTERVAL   300
#define BEEP_TRIPLE_SHORT_ON_TIME       100
#define BEEP_TRIPLE_SHORT_OFF_TIME      100
/**************************************************************************************************
 * MACROS
 **************************************************************************************************/
                                           
/**************************************************************************************************
 * LOCAL FUNCTION DECLARATION
 **************************************************************************************************/

/**************************************************************************************************
 * GLOBAL VARIABLES
 **************************************************************************************************/
static uint8_t beep_cnt;

extern void app_task_buzzer_init( void )
{
    beep_cnt = 0;
}


extern void app_task_buzzer ( uint8_t task_id, uint8_t event_id )
{
    task_id = task_id;
    
    switch (event_id)
    {
        case TASK_EVT_APP_BUZZER_BEEP_UPDATE:
        {
            hal_buzzer_off();
            osal_timer_event_delete( TASK_ID_APP_BUZZER, TASK_EVT_APP_BUZZER_BEEP_OFF );
            osal_timer_event_delete( TASK_ID_APP_BUZZER, TASK_EVT_APP_BUZZER_BEEP_ON );
            beep_cnt = 0;
            if( app_info.buzzer_beep != BUZZER_BEEP_OFF )
                osal_event_set( TASK_ID_APP_BUZZER, TASK_EVT_APP_BUZZER_BEEP_ON );
        }
        break;

        case TASK_EVT_APP_BUZZER_BEEP_ON:
        {
            hal_buzzer_on();
            if( app_info.buzzer_beep == BUZZER_BEEP_SHORT )
            {
                osal_timer_event_create( TASK_ID_APP_BUZZER, TASK_EVT_APP_BUZZER_BEEP_OFF, BEEP_SHORT_ON_TIME );
            }
            else if( app_info.buzzer_beep == BUZZER_BEEP_LONG )
            {
                osal_timer_event_create( TASK_ID_APP_BUZZER, TASK_EVT_APP_BUZZER_BEEP_OFF, BEEP_LONG_ON_TIME );
            }
            else if( app_info.buzzer_beep == BUZZER_BEEP_DOUBLE_SHORT )
            {
                osal_timer_event_create( TASK_ID_APP_BUZZER, TASK_EVT_APP_BUZZER_BEEP_OFF, BEEP_DOUBLE_SHORT_ON_TIME );
            }
            else if( app_info.buzzer_beep == BUZZER_BEEP_DOUBLE_SHORT_x2 )
            {
                osal_timer_event_create( TASK_ID_APP_BUZZER, TASK_EVT_APP_BUZZER_BEEP_OFF, BEEP_DOUBLE_SHORT_ON_TIME );
            }
            else if( app_info.buzzer_beep == BUZZER_BEEP_TRIPLE_SHORT )
            {
                osal_timer_event_create( TASK_ID_APP_BUZZER, TASK_EVT_APP_BUZZER_BEEP_OFF, BEEP_TRIPLE_SHORT_ON_TIME );
            }
            else
            {
                hal_buzzer_off();
            }
            beep_cnt++;
        }
        break;

        case TASK_EVT_APP_BUZZER_BEEP_OFF:
        {
            hal_buzzer_off();
            if( app_info.buzzer_beep == BUZZER_BEEP_SHORT )
            {
                //just off the buzzer, do nothing
            }
            else if( app_info.buzzer_beep == BUZZER_BEEP_LONG )
            {
                //just off the buzzer, do nothing
            }
            else if( app_info.buzzer_beep == BUZZER_BEEP_DOUBLE_SHORT )
            {
                if( beep_cnt == 1 )
                    osal_timer_event_create( TASK_ID_APP_BUZZER, TASK_EVT_APP_BUZZER_BEEP_ON, BEEP_DOUBLE_SHORT_OFF_TIME );
            }
            else if( app_info.buzzer_beep == BUZZER_BEEP_DOUBLE_SHORT_x2 )
            {
                if( beep_cnt == 1 || beep_cnt == 5 )
                    osal_timer_event_create( TASK_ID_APP_BUZZER, TASK_EVT_APP_BUZZER_BEEP_ON, BEEP_DOUBLE_SHORT_OFF_TIME );
                else if( beep_cnt == 3 )
                    osal_timer_event_create( TASK_ID_APP_BUZZER, TASK_EVT_APP_BUZZER_BEEP_ON, BEEP_DOUBLE_SHORT_x2_INTERVAL );
            }
            else if( app_info.buzzer_beep == BUZZER_BEEP_TRIPLE_SHORT )
            {
                if( beep_cnt == 1 || beep_cnt == 3 )
                    osal_timer_event_create( TASK_ID_APP_BUZZER, TASK_EVT_APP_BUZZER_BEEP_ON, BEEP_TRIPLE_SHORT_OFF_TIME );
            }
            else
            {
                hal_buzzer_off();
            }
            beep_cnt++;
        }
        break;
        
        default:
            APP_ASSERT_FORCED();
        break;
    }
}




#endif
/**************************************************************************************************
**************************************************************************************************/

