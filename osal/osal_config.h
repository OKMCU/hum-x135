/******************************************************************************

 @file  

 @brief 

 Group: 
 Target Device: 

 ******************************************************************************
 

 ******************************************************************************
 Release Name: 
 Release Date: 2016-06-09 06:57:09
 *****************************************************************************/
#ifndef __OSAL_CONFIG_H__
#define __OSAL_CONFIG_H__



#define     OSAL_ASSERT_EN          1
#define     OSAL_FIFO_EN            0
#define     OSAL_MSG_EN             0
#define     OSAL_TIMER_EN           1
#define     OSAL_TIMER_STATIC_EN    1
#define     OSAL_TIMER_MAX          8   //meaningless if OSAL_TIMER_STATIC_EN == 0
#define     OSAL_MEM_EN             0

#define     OSAL_TASK_MAX           4
#define     OSAL_EVENT_MAX          8      //must be 8, 16 or 32
#define     OSAL_FIFO_PAGE_SIZE     64





#endif //__OSAL_CONFIG_H__
