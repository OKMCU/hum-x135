/******************************************************************************

 @file  hal_drivers.c

 @brief Describe the purpose and contents of the file.

 Group: 
 Target Device: 

 ******************************************************************************
 

 ******************************************************************************
 Release Name: 
 Release Date: 
 *****************************************************************************/


/* ------------------------------------------------------------------------------------------------
 *                                          Includes
 * ------------------------------------------------------------------------------------------------
 */
#include "osal.h"
#include "hal.h"

#include "main.h"

#include "stdint.h"

/* ------------------------------------------------------------------------------------------------
 *                                       Local Prototypes
 * ------------------------------------------------------------------------------------------------
 */
#if HAL_CLI_EN > 0
extern void hal_cli_driver_handle_rxne( void );
#endif
/**************************************************************************************************
 * @fn          hal_driver_init
 *
 * @brief       
 *
 * @param       none
 *
 * @return      none
 **************************************************************************************************
 */
extern void hal_driver_init( void )
{
    hal_mcu_init();

#if (HAL_CLI_EN > 0)
    hal_cli_init();
#endif

#if (HAL_MIST_EN > 0)
    hal_mist_init();
#endif

#if (HAL_KEY_EN > 0)
    hal_key_init();
#endif

#if (HAL_LED_EN > 0)
    hal_led_init();
    hal_led_set( HAL_LED_ALL, HAL_LED_MODE_OFF );
#endif

}

/**************************************************************************************************
 * @fn          hal_task_driver_basic
 *
 * @brief       
 *
 * @param       none
 *
 * @return      none
 **************************************************************************************************
 */
extern void hal_task_driver_basic ( uint8_t task_id, uint8_t event_id )
{
    task_id = task_id;
    
    switch ( event_id )
    {
#if HAL_CLI_EN > 0
        case TASK_EVT_HAL_DRIVER_BASIC_CLI_RXNE:
            hal_cli_driver_handle_rxne();
        break;
#endif
        //case TASK_EVT_HAL_DRIVER_BASIC_CLI_TXE:
        //    hal_cli_driver_handle_txe();
        //break;
        
        default:
            HAL_ASSERT_FORCED();
        break;
    }
}


/**************************************************************************************************
*/
