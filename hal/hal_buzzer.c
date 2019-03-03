/**
  ******************************************************************************
  * @file    hal_buzzer.c
  * @author  SUN Wentao
  * @version V0.0.1
  * @date    15-OCT-2017
  * @brief   
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

#include "osal.h"
#include "spl.h"

#include "hal_config.h"
#include "hal_assert.h"
#include "hal_buzzer.h"

#include "main.h"


#if HAL_BUZZER_EN > 0

#define AUTO_RELOAD_VALUE   290            //about 5kHz intterrupt, 2.5kHz to drive buzzer
extern void hal_buzzer_init(void)
{
    spl_gpio_write_pin( SPL_GPIO_PIN_P05, 0 );
    SPL_GPIO_SET_MODE_P05_QUASI();
    TIMER0_MODE1_ENABLE;
}
extern void hal_buzzer_on(void)
{
    TH0 = ((65536-AUTO_RELOAD_VALUE) >> 8) & 0xFF;
    TL0 = (65536-AUTO_RELOAD_VALUE) & 0xFF;
    set_ET0;
    set_TR0;
}
extern void hal_buzzer_off(void)
{
    clr_ET0;
    clr_TR0;
    spl_gpio_write_pin( SPL_GPIO_PIN_P05, 0 );
}

extern void hal_buzzer_toggle(void)
{
    clr_TR0;
    TH0 = ((65536-AUTO_RELOAD_VALUE) >> 8) & 0xFF;
    TL0 = (65536-AUTO_RELOAD_VALUE) & 0xFF;
    set_TR0;
    spl_gpio_write_pin( SPL_GPIO_PIN_P05, !spl_gpio_read_pin(SPL_GPIO_PIN_P05));
}
#endif /* HAL_BUZZER_EN > 0 */

