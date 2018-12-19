/**
  ******************************************************************************
  * @file    hal_spray.c
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
#include "hal_spray.h"

#include "main.h"

#if HAL_SPRAY_EN > 0

//#define IO_SPRAY          P10

extern void hal_spray_init(void)
{
    bool BIT_TMP;
    
    spl_gpio_write_pin( SPL_GPIO_PIN_P10, 0 );
    SPL_GPIO_SET_MODE_P10_OUTPUT();
    set_P1SR_0;
    //PWM2_P10_OUTPUT_ENABLE;
    PWM_IMDEPENDENT_MODE;
    
    clr_PWMRUN;
    set_CLRPWM;
    while(CLRPWM == 1);
    
    // PWM frequency = Fpwm/((PWMPH,PWMPL) + 1), where Fpwm = Fsys/PWM_CLOCK_DIV
    //               = (15MHz/1)/(0x0004 + 1)
    //               = 3.0MHz
    //PWM_CLOCK_DIV_1;
    //PWM_CLOCK_DIV_1;
    PWMPH = 0x00;
    PWMPL = 0x06;
    
    //  PWM duty = 50%
    PWM2H = 0x00;						
    PWM2L = 0x04;

    set_PWMRUN;
}


extern void hal_spray_on(void)
{
    PWM2_P10_OUTPUT_ENABLE;
}
extern void hal_spray_off(void)
{
    PWM2_P10_OUTPUT_DISABLE;
}

#endif /* HAL_SPRAY_EN > 0 */

