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
#define APP_FHOP_FOUND_BEEP_EN          0
#define APP_WATERDET_EN                 1
#define APP_BUZZER_EN                   1
#define APP_LIGHT_EN                    1
#define APP_MIST_EN                     1

#if APP_FHOP_EN > 0
#define FREQ_INDEX_IIR(old_idx, new_idx)     (uint16_t)(((uint32_t)old_idx*31+(uint32_t)new_idx)>>5)
#define FREQ_INDEX_IIR_CNT                   64
#define FREQ_INDEX_TARGET                    36000
#define FHOP_FINE_TUNE_CNT                   5
#define FHOP_START_DELAY_MS                  1000
#endif

#if APP_WATERDET_EN > 0
#define WATER_INDEX_IIR(old_idx, new_idx)    (uint16_t)(((uint32_t)old_idx*3+(uint32_t)new_idx)>>2)
#define WATER_INDEX_IIR_CNT                  5
#define WATER_INDEX_NO_WATER_THRESHOLD       350
#define WATER_DETECTION_START_DELAY_MS       100
#endif

#if APP_LIGHT_EN > 0
#define LIGHT_MODE_OFF              0
#define LIGHT_MODE_VAR_START        1
#define LIGHT_MODE_VAR_STOP         2
#define LIGHT_MODE_HALF             3
#define LIGHT_MODE_SEL              4// >=4 will select colors from
#define LIGHT_COLOR_SEL_SIZE        12
#endif

#if APP_MIST_EN > 0
#define MIST_MODE_OFF               0
#define MIST_MODE_1                 1
#define MIST_MODE_2                 2
#define MIST_MODE_3                 3
#define MIST_MODE_4                 4
#endif

#if APP_BUZZER_EN > 0
#define BUZZER_BEEP_OFF             0
#define BUZZER_BEEP_SHORT           1   //bi
#define BUZZER_BEEP_LONG            2   //bi~~~~~
#define BUZZER_BEEP_DOUBLE_SHORT    3   //bi, bi
#define BUZZER_BEEP_DOUBLE_SHORT_x2 4   //bi, bi......bi, bi
#define BUZZER_BEEP_TRIPLE_SHORT    5   //bi, bi, bi
#endif

#define LED_IND_MIST_MODE_OFF()         hal_led_set( HAL_LED_ALL, HAL_LED_MODE_OFF )
#define LED_IND_MIST_MODE_1()           st(hal_led_set( HAL_LED_ALL, HAL_LED_MODE_OFF );\
                                           hal_led_set( HAL_LED_0  , HAL_LED_MODE_ON  );)
#define LED_IND_MIST_MODE_2()           st(hal_led_set( HAL_LED_ALL, HAL_LED_MODE_OFF );\
                                           hal_led_set( HAL_LED_0 + HAL_LED_3, HAL_LED_MODE_ON  );)
#define LED_IND_MIST_MODE_3()           st(hal_led_set( HAL_LED_ALL, HAL_LED_MODE_OFF );\
                                           hal_led_set( HAL_LED_0 + HAL_LED_2, HAL_LED_MODE_ON  );)
#define LED_IND_MIST_MODE_4()           st(hal_led_set( HAL_LED_ALL, HAL_LED_MODE_OFF );\
                                           hal_led_set( HAL_LED_0 + HAL_LED_1, HAL_LED_MODE_ON  );)
/**************************************************************************************************
 *                                        FUNCTIONS - API
 **************************************************************************************************/

#endif

