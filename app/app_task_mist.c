/******************************************************************************

 @file  app_task_mist.c

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

#if APP_MIST_EN > 0
/**************************************************************************************************
 * TYPES
 **************************************************************************************************/
typedef struct {
    osal_timer_timeout_t on_time;
    osal_timer_timeout_t off_time;
    osal_timer_timeout_t total_time;
} MIST_PROFILE_t;
/**************************************************************************************************
 * CONSTANTS
 **************************************************************************************************/

/**************************************************************************************************
 * MACROS
 **************************************************************************************************/
#define SECOND  1000uL
#define MINUTE  (60uL*SECOND)
#define HOUR    (60uL*MINUTE)
/**************************************************************************************************
 * LOCAL FUNCTION DECLARATION
 **************************************************************************************************/
static void app_task_mist_handle_set_mode( void );
static void app_task_mist_handle_on( void );
static void app_task_mist_handle_off( void );
/**************************************************************************************************
 * GLOBAL VARIABLES
 **************************************************************************************************/
static MIST_PROFILE_t mist_profile[] = {
    { 0, 0, 0 },
    { 1, 0, 0 },
    { 10000, 10000, 0 },
    { 1, 0, 1uL*HOUR },
    { 1, 0, 3uL*HOUR }
};

extern void app_task_mist_init( void )
{

}


extern void app_task_mist ( uint8_t task_id, uint8_t event_id )
{
    task_id = task_id;
    
    switch (event_id)
    {
        case TASK_EVT_APP_MIST_SET_MODE:
        {
            app_task_mist_handle_set_mode();
        }
        break;

        case TASK_EVT_APP_MIST_STOP:
        {
            app_event_mist_stop();
        }
        break;

        case TASK_EVT_APP_MIST_ON:
        {
            app_task_mist_handle_on();
        }
        break;

        case TASK_EVT_APP_MIST_OFF:
        {
            app_task_mist_handle_off();
        }
        break;
        
        default:
            APP_ASSERT_FORCED();
        break;
    }
}


static void app_task_mist_handle_set_mode( void )
{
    hal_mist_off();
    #if (HAL_FAN_EN > 0)
    hal_fan_off();
    #endif
    app_info.sys_flags &= ~SYS_FLAGS_MIST_ON;
    app_info.sys_flags &= ~SYS_FLAGS_WATERDET_ON;
    app_info.sys_flags &= ~SYS_FLAGS_FHOP_ON;
    
    osal_timer_event_delete( TASK_ID_APP_MIST, TASK_EVT_APP_MIST_STOP );
    osal_timer_event_delete( TASK_ID_APP_MIST, TASK_EVT_APP_MIST_ON );
    osal_timer_event_delete( TASK_ID_APP_MIST, TASK_EVT_APP_MIST_OFF );

    #if APP_WATERDET_EN > 0
    osal_timer_event_delete( TASK_ID_APP_WATERDET, TASK_EVT_APP_WATERDET_START );
    #endif

    #if APP_FHOP_EN > 0
    osal_timer_event_delete( TASK_ID_APP_FHOP, TASK_EVT_APP_FHOP_START );
    osal_event_set( TASK_ID_APP_FHOP, TASK_EVT_APP_FHOP_RESET );
    #endif
    
    if( app_info.mist_mode < sizeof(mist_profile)/sizeof(MIST_PROFILE_t) )
    {
        if( mist_profile[app_info.mist_mode].on_time )
        {
            hal_mist_on();
            app_info.sys_flags |= SYS_FLAGS_MIST_ON;
            #if (HAL_FAN_EN > 0)
            hal_fan_on();
            #endif
            
            #if APP_WATERDET_EN > 0
            osal_timer_event_create( TASK_ID_APP_WATERDET, TASK_EVT_APP_WATERDET_START, WATER_DETECTION_START_DELAY_MS );
            #endif

            #if APP_FHOP_EN > 0
            //if frequency is still not finished yet, then turn on frequency hopping
            if( !(app_info.sys_flags & SYS_FLAGS_FREQ_FINISH) )
                osal_timer_event_create( TASK_ID_APP_FHOP, TASK_EVT_APP_FHOP_START, FHOP_START_DELAY_MS );
            #endif
            
            if( mist_profile[app_info.mist_mode].total_time )
                osal_timer_event_create( TASK_ID_APP_MIST, TASK_EVT_APP_MIST_STOP, mist_profile[app_info.mist_mode].total_time );
            if( mist_profile[app_info.mist_mode].off_time )
                osal_timer_event_create( TASK_ID_APP_MIST, TASK_EVT_APP_MIST_OFF, mist_profile[app_info.mist_mode].on_time );
        }
    }
}

static void app_task_mist_handle_on( void )
{
    hal_mist_on();
    app_info.sys_flags |= SYS_FLAGS_MIST_ON;
    #if (HAL_FAN_EN > 0)
    hal_fan_on();
    #endif
    
    #if APP_WATERDET_EN > 0
    osal_timer_event_create( TASK_ID_APP_WATERDET, TASK_EVT_APP_WATERDET_START, WATER_DETECTION_START_DELAY_MS );
    #endif

    #if APP_FHOP_EN > 0
    //if frequency is still not finished yet, then turn on frequency hopping
    if( !(app_info.sys_flags & SYS_FLAGS_FREQ_FINISH) )
        osal_timer_event_create( TASK_ID_APP_FHOP, TASK_EVT_APP_FHOP_START, FHOP_START_DELAY_MS );
    #endif
    
    APP_ASSERT( mist_profile[app_info.mist_mode].on_time != 0 );
    osal_timer_event_create( TASK_ID_APP_MIST, TASK_EVT_APP_MIST_OFF, mist_profile[app_info.mist_mode].on_time );
        
}

static void app_task_mist_handle_off( void )
{
    hal_mist_off();
    #if (HAL_FAN_EN > 0)
    hal_fan_off();
    #endif
    app_info.sys_flags &= ~SYS_FLAGS_MIST_ON;
    app_info.sys_flags &= ~SYS_FLAGS_WATERDET_ON;
    app_info.sys_flags &= ~SYS_FLAGS_FHOP_ON;

    #if APP_WATERDET_EN > 0
    osal_timer_event_delete( TASK_ID_APP_WATERDET, TASK_EVT_APP_WATERDET_START );
    #endif

    #if APP_FHOP_EN > 0
    osal_timer_event_delete( TASK_ID_APP_FHOP, TASK_EVT_APP_FHOP_START );
    #endif
    
    APP_ASSERT( mist_profile[app_info.mist_mode].off_time != 0 );
    osal_timer_event_create( TASK_ID_APP_MIST, TASK_EVT_APP_MIST_ON, mist_profile[app_info.mist_mode].off_time );
}

#endif
/**************************************************************************************************
**************************************************************************************************/

