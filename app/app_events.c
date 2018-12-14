/**
  ******************************************************************************
  * @file    app_events.c
  * @author  SUN Wentao
  * @version V0.0.1
  * @date    9-AUG-2017
  * @brief   This file contains the implementations of tri-color LED control.
   ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2017 OKMCU</center></h2>
  *
  * Licensed under OKMCU Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.okmcu.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */ 


/* Includes ------------------------------------------------------------------*/
#include "..\app\app_tasksched.h"
#include "..\app\app_light.h"
#include "..\app\app_spray.h"
#include "..\app\app_buzzer.h"
#include "..\app\app_led.h"
#include "..\app\app_events.h"
#include "..\app\app_button.h"
#include "..\app\app_freqhop.h"
/** @addtogroup Template_Project
  * @{
  */

#if APP_EVENTS_EN > 0

/* Private typedef -----------------------------------------------------------*/
#define APP_EVT_SprayLowPwrOnTime      (uint8_t)5  //in ms
#define APP_EVT_SprayLowPwrOffTime     (uint8_t)16 //in ms
#define APP_EVT_SprayHighPwrOnTime     (uint8_t)200  //in ms
#define APP_EVT_SprayHighPwrOffTime   (uint8_t)1  //in ms
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static xdata uint8_t lightButtonCnt = 0;
static xdata uint8_t mistButtonCnt = 0;
static xdata uint8_t porButtonState = 0;
static code  APP_SPRAY_PROFILE_t sprayProfile[5] = {
    {0, 0, 0},  //spray always off
    {1, 0, 0},  //spray always on
    {1, 0, 60}, //1 //spray on for 1 hour
    {1, 0, 180},//spray on for 3 hours
    {1, 0, 360},//spray on for 6 hours
};
static bool sprayLowPwrMode = FALSE;
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
static void appEvent_InCaseErrorBeepFailed(void)
{
    appBuzzerBeep(APP_BUZZ_ERROR);
}
/* Public functions ----------------------------------------------------------*/
void appEventPowerOnReset(void)
{
    porButtonState = appButtonGetCurrentState();
    if(porButtonState == APP_BUTTON_STATE_MIST)
    {
    }
    else
    {
        appBuzzerBeep(APP_BUZZ_ERROR);
    }
    sprayLowPwrMode = FALSE;
    appSpraySetPower(APP_EVT_SprayHighPwrOnTime, APP_EVT_SprayHighPwrOffTime);
}
void appEventLightButtonPress(void)
{
    porButtonState = 0;
    lightButtonCnt++;
    if(lightButtonCnt > COLOR_TABLE_SEL_SIZE + 3)
        lightButtonCnt = 0;
    
    appLightSetMode(lightButtonCnt);
}
void appEventMistButtonPress(void)
{
    porButtonState = 0;
    mistButtonCnt++;
    appLedOff(LED_NORMAL_G);
    appLedOff(LED_6H);
    appLedOff(LED_3H);
    appLedOff(LED_1H);
    
    if(mistButtonCnt == 1)//work continuously
    {
        appLedOn(LED_NORMAL_G);
        lightButtonCnt = 1;
        appLightSetMode(lightButtonCnt);
    }
    else if(mistButtonCnt == 2)// 1 hour
    {
        appLedOn(LED_NORMAL_G);
        appLedOn(LED_1H);
    }
    else if(mistButtonCnt == 3)// 3 hours
    {
        appLedOn(LED_NORMAL_G);
        appLedOn(LED_3H);
    }
    else if(mistButtonCnt == 4)// 6 hours
    {
        appLedOn(LED_NORMAL_G);
        appLedOn(LED_6H);
    }
    else
    {
        appTaskSchedCreate(500, appEvent_InCaseErrorBeepFailed);
        mistButtonCnt = 0;
        lightButtonCnt = 0;
        appLightSetMode(lightButtonCnt);
    }
    appSpraySet(&sprayProfile[mistButtonCnt]);
}
void appEventLightButtonTouchEnter(void)
{
    appBuzzerBeep(APP_BUZZ_BUTTON);
}
void appEventMistButtonTouchEnter(void)
{
    appBuzzerBeep(APP_BUZZ_BUTTON);
}
void appEventLightMistButtonTouchEnter(void)
{
    appBuzzerBeep(APP_BUZZ_BUTTON);
}
void appEventLightButtonLongPress(void)
{
    porButtonState = 0;
    lightButtonCnt = 0;
    appLightSetMode(lightButtonCnt);
}
void appEventMistButtonLongPress(void)
{
    if(porButtonState == APP_BUTTON_STATE_MIST)
    {
        porButtonState = 0;
        appBuzzerBeep(APP_BUZZ_FACTORY);
        appFreqHop_SetEnable();
        appSprayResetWaterChkData();
    }
    else
    {
        if(sprayLowPwrMode == FALSE)
        {
            sprayLowPwrMode = TRUE;
            appSpraySetPower(APP_EVT_SprayLowPwrOnTime, APP_EVT_SprayLowPwrOffTime);
            appBuzzerBeep(APP_BUZZ_LOWPOWER);
        }
        else
        {
            sprayLowPwrMode = FALSE;
            appSpraySetPower(APP_EVT_SprayHighPwrOnTime, APP_EVT_SprayHighPwrOffTime);
            appBuzzerBeep(APP_BUZZ_HIGHPOWER);
        }
    }
}
void appEventLightMistButtonVLongPress(void)
{
//    if(porButtonState == APP_BUTTON_STATE_LIGHT + APP_BUTTON_STATE_MIST)
//    {
//        appBuzzerBeep(APP_BUZZ_FACTORY);
//        appFreqHop_SetEnable();
//        appSprayResetWaterChkData();
//    }
}
void appEventFreqHopCfm(void)
{
    appFreqHop_SaveFreqToFlash();
    mistButtonCnt = 0;
    lightButtonCnt = 0;
    appLightSetMode(8);//white
    appSpraySet(&sprayProfile[mistButtonCnt]);
    appBuzzerBeep(APP_BUZZ_FACTORY);
    appLedOn(LED_NORMAL_G);
    appLedOn(LED_6H);
    appLedOn(LED_3H);
    appLedOn(LED_1H);
}

void appEventNoWater(void)
{
    mistButtonCnt = 0;
    lightButtonCnt = 0;
    appLightSetMode(lightButtonCnt);
    appSpraySet(&sprayProfile[mistButtonCnt]);
    appTaskSchedCreate(500, appEvent_InCaseErrorBeepFailed);
    appLedOff(LED_NORMAL_G);
    appLedOff(LED_6H);
    appLedOff(LED_3H);
    appLedOff(LED_1H);
}

#endif /* APP_EVENTS_EN > 0 */

/**
  * @}
  */


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
