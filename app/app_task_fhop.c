/******************************************************************************

 @file  app_task_fhop.c

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

#if APP_FHOP_EN > 0
/**************************************************************************************************
 * TYPES
 **************************************************************************************************/

/**************************************************************************************************
 * CONSTANTS
 **************************************************************************************************/

/**************************************************************************************************
 * LOCAL FUNCTION DECLARATION
 **************************************************************************************************/
static void app_task_fhop_handle_update( void );
/**************************************************************************************************
 * GLOBAL VARIABLES
 **************************************************************************************************/
static uint16_t freq_index_iir;
static uint8_t  freq_index_iir_cnt;
static uint8_t  fine_tune_cnt;

extern void app_task_fhop_init( void )
{
    freq_index_iir = 0;
    freq_index_iir_cnt = 0;
    fine_tune_cnt = 0;
}


extern void app_task_fhop ( uint8_t task_id, uint8_t event_id )
{
    task_id = task_id;
    
    switch (event_id)
    {
        case TASK_EVT_APP_FHOP_RESET:
        {
            app_task_fhop_init();
        }
        break;
        
        case TASK_EVT_APP_FHOP_UPDATE:
        {
            app_task_fhop_handle_update();
        }
        break;

        case TASK_EVT_APP_FHOP_START:
        {
            app_info.sys_flags |= SYS_FLAGS_FHOP_ON;
        }
        break;
        
        default:
            APP_ASSERT_FORCED();
        break;
    }
}

static void app_task_fhop_handle_update( void )
{
    int16_t delta1;
    int16_t delta2;
    uint16_t freq_index_iir_prev;
    int8_t trim;

    freq_index_iir_prev = freq_index_iir;
    if( freq_index_iir )
        freq_index_iir = FREQ_INDEX_IIR( freq_index_iir, app_info.freq_index );     //IIR calculation
    else
        freq_index_iir = app_info.freq_index;                                       //IIR init

    if( freq_index_iir_cnt < FREQ_INDEX_IIR_CNT )
    {
        freq_index_iir_cnt++;
    }
    else
    {
        freq_index_iir_cnt = 0;

        if( freq_index_iir_prev && freq_index_iir )
        {
            delta1 = (int16_t)(freq_index_iir_prev - FREQ_INDEX_TARGET);
            delta2 = (int16_t)(freq_index_iir - FREQ_INDEX_TARGET);
            if( (delta1 < 0 && delta2 > 0) || 
                (delta1 > 0 && delta2 < 0) ||
                (delta1 == 0)              ||
                (delta2 == 0) )
            {
                fine_tune_cnt++;
                if( fine_tune_cnt >= FHOP_FINE_TUNE_CNT )
                {
                    app_info.sys_flags |= SYS_FLAGS_FREQ_FINISH;
                    app_info.sys_flags &= ~SYS_FLAGS_FHOP_ON;
                    app_event_fhop_finish_freq_found();
                }
            }
        }

        if( fine_tune_cnt < FHOP_FINE_TUNE_CNT )
        {
            trim = hal_mcu_hsi_trim_get();
            if( freq_index_iir > FREQ_INDEX_TARGET )
                trim++;
            else
                trim--;
            trim = hal_mcu_hsi_trim_set( trim );

            if( trim == HAL_MCU_TRIM_MAX )
            {
                app_info.sys_flags |= SYS_FLAGS_FREQ_FINISH;
                app_info.sys_flags &= ~SYS_FLAGS_FHOP_ON;
                app_event_fhop_finish_freq_max();
            }
            else if( trim == HAL_MCU_TRIM_MIN )
            {
                app_info.sys_flags |= SYS_FLAGS_FREQ_FINISH;
                app_info.sys_flags &= ~SYS_FLAGS_FHOP_ON;
                app_event_fhop_finish_freq_min();
            }
        }
    }
    
}


#endif
/**************************************************************************************************
**************************************************************************************************/

