/******************************************************************************

 @file  main.c

 @brief 

 Group: 
 Target Device: 

 ******************************************************************************
 

 ******************************************************************************
 Release Name: 
 Release Date: 
 *****************************************************************************/

#include "osal.h"
#include "hal.h"
#include "app.h"
#include "main.h"

#include "stdstr.h"

FLASH OSAL_TASK_t osal_task_list[OSAL_TASK_MAX] = {
    hal_task_driver_basic,

#if APP_CLI_EN > 0
    app_task_cli,
#else
    NULL,
#endif

#if APP_FHOP_EN > 0
    app_task_fhop,
#else
    NULL,
#endif

#if APP_WATERDET_EN > 0
    app_task_waterdet,
#else
    NULL,
#endif

#if APP_KEY_EN > 0
    app_task_key,
#else
    NULL,
#endif

#if APP_BUZZER_EN > 0
    app_task_buzzer,
#else
    NULL,
#endif

#if APP_LIGHT_EN > 0
    app_task_light,
#else
    NULL,
#endif

#if APP_MIST_EN > 0
    app_task_mist,
#else
    NULL,
#endif

    app_task_main
};

int main( void )
{
    /* Disable Interrupts */
    OSAL_ENTER_CRITICAL();
    
    /* Initialize the OS's vars */
    osal_system_init();
    
    /* Initialize mcu and devices */
    hal_driver_init();
    
#if APP_CLI_EN > 0
    app_task_cli_init();
#endif

#if APP_FHOP_EN > 0
    app_task_fhop_init();
#endif

#if APP_WATERDET_EN > 0
    app_task_waterdet_init();
#endif

#if APP_KEY_EN > 0
    app_task_key_init();
#endif

#if APP_LIGHT_EN > 0
    app_task_light_init();
#endif

#if APP_MIST_EN > 0
    app_task_mist_init();
#endif

    app_task_main_init();

    /* Enable Interrupts */
    OSAL_EXIT_CRITICAL();
    /* Start OSAL */
    osal_system_start(); // No Return from here

    return 0;

}

