/******************************************************************************

 @file  app_task_waterdet.h

 @brief 

 Group: 
 Target Device: 

 ******************************************************************************
 

 ******************************************************************************
 Release Name: 
 Release Date: 
 *****************************************************************************/
#ifndef __APP_TASK_WATERDET_H__
#define __APP_TASK_WATERDET_H__


/**************************************************************************************************
 * INCLUDES
 **************************************************************************************************/

#include "stdint.h"
#include "app_config.h"

/**************************************************************************************************
 * TYPEDEF
 **************************************************************************************************/

/**************************************************************************************************
 * CONSTANTS
 **************************************************************************************************/

/**************************************************************************************************
 * GLOBAL VARIABLES
 **************************************************************************************************/

/**************************************************************************************************
 * FUNCTIONS - API
 **************************************************************************************************/
extern void app_task_waterdet_init( void );
extern void app_task_waterdet ( uint8_t task_id, uint8_t event_id );

#endif

/**************************************************************************************************
**************************************************************************************************/
