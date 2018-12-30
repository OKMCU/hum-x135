/**
  ******************************************************************************
  * @file    hal_light.c
  * @author  SUN Wentao
  * @version V0.0.1
  * @date    14-OCT-2017
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
#include "hal_light.h"

#include "main.h"

#if HAL_LIGHT_EN > 0

#define AUTO_RELOAD_VALUE 120   //PWM frequency, the larger value, the lower frequency

static IRAM uint8_t color[3];
static IRAM uint8_t count;

extern void hal_light_init(void)
{   
    color[0] = 0;
    color[1] = 0;
    color[2] = 0;

    count = 0;
    
    spl_gpio_write_pin( SPL_GPIO_PIN_P00, 0 );//R
    spl_gpio_write_pin( SPL_GPIO_PIN_P01, 0 );//B
    spl_gpio_write_pin( SPL_GPIO_PIN_P12, 0 );//G
    
    SPL_GPIO_SET_MODE_P00_OUTPUT();
    SPL_GPIO_SET_MODE_P01_OUTPUT();
    SPL_GPIO_SET_MODE_P12_OUTPUT();

    TIMER1_MODE2_ENABLE;
    TH1 = 256-AUTO_RELOAD_VALUE;
    TL1 = 256-AUTO_RELOAD_VALUE;
    //set_T1M;
    set_ET1;
    set_TR1;
}

extern void hal_light_set( uint8_t light, uint8_t bright )
{
    //color[light] = bright>>1;
    HAL_ASSERT( light < 3 );
    color[light] = bright;
    switch( light )
    {
        case HAL_LIGHT_R:
            spl_gpio_write_pin( SPL_GPIO_PIN_P00, count < color[0] ? 1 : 0 );//R
        break;
        case HAL_LIGHT_G:
            spl_gpio_write_pin( SPL_GPIO_PIN_P12, count < color[1] ? 1 : 0 );//G
        break;
        case HAL_LIGHT_B:
            spl_gpio_write_pin( SPL_GPIO_PIN_P01, count < color[2] ? 1 : 0 );//B
        break;
    }
}

extern void hal_light_update( void )
{
    count++;

    spl_gpio_write_pin( SPL_GPIO_PIN_P00, count < color[0] ? 1 : 0 );//R
    spl_gpio_write_pin( SPL_GPIO_PIN_P12, count < color[1] ? 1 : 0 );//G
    spl_gpio_write_pin( SPL_GPIO_PIN_P01, count < color[2] ? 1 : 0 );//B
}

#endif /* HAL_LIGHT_EN > 0 */

