/**
  ******************************************************************************
  * @file    hal_light.h
  * @author  SUN Wentao
  * @version V0.0.1
  * @date    30-DEC-2018
  * @brief   
   ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2018 OKMCU</center></h2>
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

#ifndef __HAL_LIGHT_H__
#define __HAL_LIGHT_H__

#include "stdint.h"

#define HAL_LIGHT_R     0
#define HAL_LIGHT_G     1
#define HAL_LIGHT_B     2

extern void hal_light_init( void );
extern void hal_light_set( uint8_t light, uint8_t bright );

#endif /* __HAL_LIGHT_H__ */

