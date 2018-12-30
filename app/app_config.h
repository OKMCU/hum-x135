/******************************************************************************

 @file  app_config.h

 @brief 

 Group: 
 Target Device: 

 ******************************************************************************
 

 ******************************************************************************
 Release Name: 
 Release Date: 
 *****************************************************************************/

#ifndef __APP_CONFIG_H__
#define __APP_CONFIG_H__

#define FIRMWARE_VER            "V1.0.0"
#define HARDWARE_VER            "V1.0.0"
#define APP_ASSERT_EN                   1
#define APP_CLI_EN                      0
#define APP_CLI_CMD_TEST_EN             0
#define APP_CLI_CMD_SYSCLK_INC_EN       0
#define APP_CLI_CMD_SYSCLK_DEC_EN       0
#define APP_CLI_CMD_ON_EN               0
#define APP_CLI_CMD_OFF_EN              0
#define APP_KEY_EN                      1
#define APP_FHOP_EN                     1
#define APP_WATERDET_EN                 1
#define APP_LIGHT_EN                    1

#if APP_FHOP_EN > 0
#define FREQ_INDEX_IIR(old_idx, new_idx)     (uint16_t)(((uint32_t)old_idx*31+(uint32_t)new_idx)>>5)
#define FREQ_INDEX_IIR_CNT                   32
#define FREQ_INDEX_TARGET                    36000
#define FHOP_FINE_TUNE_CNT                   10
#endif

#if APP_WATERDET_EN > 0
#define WATER_INDEX_IIR(old_idx, new_idx)    (uint16_t)(((uint32_t)old_idx*3+(uint32_t)new_idx)>>2)
#define WATER_INDEX_IIR_CNT                  5
#define WATER_INDEX_NO_WATER_THRESHOLD       2500
#endif
/**************************************************************************************************
 *                                        FUNCTIONS - API
 **************************************************************************************************/

#endif

