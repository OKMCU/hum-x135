/******************************************************************************

 @file  app_task_waterdet.c

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

#if APP_WATERDET_EN > 0
/**************************************************************************************************
 * TYPES
 **************************************************************************************************/

/**************************************************************************************************
 * CONSTANTS
 **************************************************************************************************/

/**************************************************************************************************
 * LOCAL FUNCTION DECLARATION
 **************************************************************************************************/
static void app_task_waterdet_handle_update( void );
static void app_task_waterdet_handle_reset( void );
/**************************************************************************************************
 * GLOBAL VARIABLES
 **************************************************************************************************/
static uint16_t water_index_iir;
static uint8_t water_index_iir_cnt;

extern void app_task_waterdet_init( void )
{
    water_index_iir = 0;
    water_index_iir_cnt = 0;
}


extern void app_task_waterdet ( uint8_t task_id, uint8_t event_id )
{
    task_id = task_id;
    
    switch (event_id)
    {
        case TASK_EVT_APP_WATERDET_UPDATE:
        {
            app_task_waterdet_handle_update();
        }
        break;

        case TASK_EVT_APP_WATERDET_RESET:
        {
            app_task_waterdet_handle_reset();
        }
        break;
        
        default:
            APP_ASSERT_FORCED();
        break;
    }
}

static void app_task_waterdet_handle_update( void )
{
    if( water_index_iir )
        water_index_iir = WATER_INDEX_IIR( water_index_iir, app_info.water_index );
    else
        water_index_iir = app_info.water_index;

    if( water_index_iir_cnt < WATER_INDEX_IIR_CNT )
    {
        water_index_iir_cnt++;
    }
    else
    {
        if( water_index_iir < WATER_INDEX_NO_WATER_THRESHOLD )
        {
            app_event_waterdet_no_water();
        }
    }
}

static void app_task_waterdet_handle_reset( void )
{
    water_index_iir = 0;
    water_index_iir_cnt = 0;
}

#endif
/**************************************************************************************************
**************************************************************************************************/

