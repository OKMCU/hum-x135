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
static void app_task_fhop_handle_reset( void );
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
        case TASK_EVT_APP_FHOP_UPDATE:
        {
            app_task_fhop_handle_update();
        }
        break;

        case TASK_EVT_APP_FHOP_RESET:
        {
            app_task_fhop_handle_reset();
        }
        break;
        
        default:
            APP_ASSERT_FORCED();
        break;
    }
}

static void app_task_fhop_handle_reset( void )
{
    freq_index_iir = 0;
    freq_index_iir_cnt = 0;
    fine_tune_cnt = 0;
}

static void app_task_fhop_handle_update( void )
{
    int32_t delta1;
    int32_t delta2;
    uint16_t freq_index_iir_prev;
    int8_t trim;

    if( fine_tune_cnt < FHOP_FINE_TUNE_CNT )
    {
        freq_index_iir_prev = freq_index_iir;
        if( freq_index_iir )
        {
            freq_index_iir = FREQ_INDEX_IIR( freq_index_iir, app_info.freq_index );
        }
        else
        {
            freq_index_iir = app_info.freq_index;
            freq_index_iir_cnt = FREQ_INDEX_IIR_CNT;
        }

        if( freq_index_iir_cnt )
        {
            freq_index_iir_cnt--;
            if( !freq_index_iir_cnt )
            {
                freq_index_iir_cnt = FREQ_INDEX_IIR_CNT;

                if( freq_index_iir_prev && freq_index_iir )
                {
                    delta1 = (int32_t)(freq_index_iir_prev - FREQ_INDEX_TARGET);
                    delta2 = (int32_t)(freq_index_iir - FREQ_INDEX_TARGET);
                    if( delta1*delta2 <= 0 )
                    {
                        if( !fine_tune_cnt )
                        {
                            app_event_fhop_rough_tune_finish();
                        }
                        fine_tune_cnt++;
                        if( fine_tune_cnt >= FHOP_FINE_TUNE_CNT )
                        {
                            app_event_fhop_fine_tune_finish();
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
                    }
                }
            }
        }
    }
    
}


#endif
/**************************************************************************************************
**************************************************************************************************/

