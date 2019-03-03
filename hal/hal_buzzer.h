/**
  ******************************************************************************
  * @file    hal_buzzer.h
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

#ifndef __HAL_BUZZER_H__
#define __HAL_BUZZER_H__

#include "stdint.h"
#include "hal_config.h"

extern void hal_buzzer_init(void);
extern void hal_buzzer_on(void);
extern void hal_buzzer_off(void);


#endif /* __HAL_BUZZER_H__ */

