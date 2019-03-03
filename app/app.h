#ifndef __APP_H__
#define __APP_H__

#include "app_config.h"
#include "app_assert.h"
#include "app_info.h"

#include "app_task_main.h"
#include "app_event_main.h"

#if APP_CLI_EN > 0
#include "app_task_cli.h"
#include "app_event_cli.h"
#endif

#if APP_KEY_EN > 0
#include "app_task_key.h"
#include "app_event_key.h"
#endif

#if APP_FHOP_EN > 0
#include "app_task_fhop.h"
#include "app_event_fhop.h"
#endif

#if APP_WATERDET_EN > 0
#include "app_task_waterdet.h"
#include "app_event_waterdet.h"
#endif

#if APP_LIGHT_EN > 0
#include "app_task_light.h"
#endif

#if APP_MIST_EN > 0
#include "app_task_mist.h"
#include "app_event_mist.h"
#endif

#if APP_BUZZER_EN > 0
#include "app_task_buzzer.h"
#endif

#endif
