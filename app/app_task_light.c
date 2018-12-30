/******************************************************************************

 @file  app_task_light.c

 @brief 

 Group: 
 Target Device: 

 ******************************************************************************
 

 ******************************************************************************
 Release Name: 
 Release Date: 
 *****************************************************************************/

/**************************************************************************************************
 * INCLUDES
 **************************************************************************************************/
#include "osal.h"
#include "hal.h"
#include "app.h"

#include "main.h"

#if APP_LIGHT_EN > 0
/**************************************************************************************************
 * TYPES
 **************************************************************************************************/
typedef struct {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
} APP_LIGHT_COLOR_t;
/**************************************************************************************************
 * CONSTANTS
 **************************************************************************************************/
#define COLOR_UPDATE_INTERVAL 5300
#define COLOR_UPDATE_PAUSE    1000
#define COLOR_TABLE_VAR_SIZE  7

/**************************************************************************************************
 * LOCAL FUNCTION DECLARATION
 **************************************************************************************************/
static void app_task_light_handle_set_mode( void );
static uint8_t delta(uint8_t val1, uint8_t val2);
static uint16_t calcUpdColorInterval(uint8_t delta);
static void appLightUpdateColorStart(void);
static void appLightUpdateColorStop(void);
static void appLightUpdateColorR(void);
static void appLightUpdateColorG(void);
static void appLightUpdateColorB(void);
/**************************************************************************************************
 * GLOBAL VARIABLES
 **************************************************************************************************/
static FLASH APP_LIGHT_COLOR_t colorTableSel[LIGHT_COLOR_SEL_SIZE] = {
    {0, 255, 0},
    {0, 127, 0},
    {0, 0, 255},
    {0, 0, 127},
    {255, 0, 0},
    {127, 0, 0},
    {255, 255,  0},
    {127, 127,  0},
    {170, 170, 255},
    {85,  85,  127},
    {255, 255, 255},
    {127, 127, 127},
};

static FLASH APP_LIGHT_COLOR_t colorTableVar[COLOR_TABLE_VAR_SIZE] = {
    {255, 0, 0},
    {255, 255, 0},
    {0, 255, 0},
    {0, 255, 255},
    {0, 0, 255},
    {255, 0, 255},
    {255, 255, 255},
};

static FLASH uint16_t colorTableVarTime[COLOR_TABLE_VAR_SIZE] = {
    COLOR_UPDATE_PAUSE,
    COLOR_UPDATE_PAUSE,
    COLOR_UPDATE_PAUSE,
    COLOR_UPDATE_PAUSE,
    COLOR_UPDATE_PAUSE,
    COLOR_UPDATE_PAUSE,
    COLOR_UPDATE_PAUSE,
};

static XRAM APP_LIGHT_COLOR_t curColor;
static XRAM int8_t curColorId;
static XRAM int8_t nxtColorId;
static XRAM uint16_t updColorRInterval;
static XRAM uint16_t updColorGInterval;
static XRAM uint16_t updColorBInterval;

extern void app_task_light_init( void )
{
    curColor.red = 0;
    curColor.green = 0;
    curColor.blue = 0;
    curColorId = -1;
    nxtColorId = -1;
    updColorRInterval = 0;
    updColorGInterval = 0;
    updColorBInterval = 0;
}


extern void app_task_light ( uint8_t task_id, uint8_t event_id )
{
    task_id = task_id;
    
    switch (event_id)
    {
        case TASK_EVT_APP_LIGHT_SET_MODE:
        {
            app_task_light_handle_set_mode();
        }
        break;
        
        case TASK_EVT_APP_LIGHT_UPD_START:
        {
            appLightUpdateColorStart();
        }
        break;

        case TASK_EVT_APP_LIGHT_UPD_R:
        {
            appLightUpdateColorR();
        }
        break;

        case TASK_EVT_APP_LIGHT_UPD_G:
        {
            appLightUpdateColorG();
        }
        break;

        case TASK_EVT_APP_LIGHT_UPD_B:
        {
            appLightUpdateColorB();
        }
        break;
        
        default:
            APP_ASSERT_FORCED();
        break;
    }
}

static void app_task_light_handle_set_mode( void )
{
    uint8_t sel;

    appLightUpdateColorStop();
    
    switch ( app_info.light_mode )
    {
        case LIGHT_MODE_OFF:
        {
            curColor.red = 0;
            curColor.green = 0;
            curColor.blue = 0;
            hal_light_set( HAL_LIGHT_R, 0 );
            hal_light_set( HAL_LIGHT_G, 0 );
            hal_light_set( HAL_LIGHT_B, 0 );
        }
        break;

        case LIGHT_MODE_VAR_START:
        {
            curColorId = 0;
            nxtColorId = 0;
            curColor.red = colorTableVar[curColorId].red;
            curColor.green = colorTableVar[curColorId].green;
            curColor.blue = colorTableVar[curColorId].blue;
            hal_light_set( HAL_LIGHT_R, curColor.red );
            hal_light_set( HAL_LIGHT_G, curColor.green );
            hal_light_set( HAL_LIGHT_B, curColor.blue );
            //updColorStartTid = appTaskSchedCreate(colorTableVarTime[curColorId], appLightUpdateColorStart);
            if( colorTableVarTime[curColorId] ) osal_timer_event_create( TASK_ID_APP_LIGHT, TASK_EVT_APP_LIGHT_UPD_START, colorTableVarTime[curColorId] );
            else                                osal_event_set( TASK_ID_APP_LIGHT, TASK_EVT_APP_LIGHT_UPD_START );
            
        }
        break;

        case LIGHT_MODE_VAR_STOP:
        {
            //appLightUpdateColorStop();
        }
        break;

        case LIGHT_MODE_HALF:
        {
            curColor.red >>= 1;
            curColor.green >>= 1;
            curColor.blue >>= 1;
            //appLightSet(&curColor);
            hal_light_set( HAL_LIGHT_R, curColor.red );
            hal_light_set( HAL_LIGHT_G, curColor.green );
            hal_light_set( HAL_LIGHT_B, curColor.blue );
        }
        break;

        default:
        {
            sel = app_info.light_mode-LIGHT_MODE_SEL;
            if( sel < LIGHT_COLOR_SEL_SIZE )
            {
                curColor.red = colorTableSel[sel].red;
                curColor.green = colorTableSel[sel].green;
                curColor.blue = colorTableSel[sel].blue;
            }
            else
            {
                curColor.red = 0;
                curColor.green = 0;
                curColor.blue = 0;
            }
            hal_light_set( HAL_LIGHT_R, curColor.red );
            hal_light_set( HAL_LIGHT_G, curColor.green );
            hal_light_set( HAL_LIGHT_B, curColor.blue );
        }
        break;
    }
}

static uint8_t delta(uint8_t val1, uint8_t val2)
{
    return val1 > val2 ? (val1-val2) : (val2-val1);
}
static uint16_t calcUpdColorInterval(uint8_t delta)
{
    if(delta == 0)
        return 0;
    return (uint16_t)(COLOR_UPDATE_INTERVAL / (uint16_t)delta);
    //return colorTableVarTime[curColorId];
}

static void appLightUpdateColorStart(void)
{
    uint8_t flag = 0;

    //updColorStartTid = -1;
    //osal_timer_event_delete( TASK_ID_APP_LIGHT, TASK_EVT_APP_LIGHT_UPD_START );

    if( osal_timer_event_query( TASK_ID_APP_LIGHT, TASK_EVT_APP_LIGHT_UPD_R ) )
        flag |= 0x01;
    
    if( osal_timer_event_query( TASK_ID_APP_LIGHT, TASK_EVT_APP_LIGHT_UPD_G ) )
        flag |= 0x02;

    if( osal_timer_event_query( TASK_ID_APP_LIGHT, TASK_EVT_APP_LIGHT_UPD_B ) )
        flag |= 0x04;
    
    //if(updColorRTid < 0 && updColorGTid < 0 && updColorBTid < 0)
    if( flag == 0 )
    {
        curColorId = nxtColorId;
        nxtColorId++;
        if(nxtColorId >= sizeof(colorTableVar)/sizeof(APP_LIGHT_COLOR_t))
        {
            nxtColorId = 0;
        }
        updColorRInterval = calcUpdColorInterval(delta(curColor.red, colorTableVar[nxtColorId].red));
        updColorGInterval = calcUpdColorInterval(delta(curColor.green, colorTableVar[nxtColorId].green));
        updColorBInterval = calcUpdColorInterval(delta(curColor.blue, colorTableVar[nxtColorId].blue));
        
        //updColorRTid = appTaskSchedCreate(updColorRInterval, appLightUpdateColorR);
        //updColorGTid = appTaskSchedCreate(updColorGInterval, appLightUpdateColorG);
        //updColorBTid = appTaskSchedCreate(updColorBInterval, appLightUpdateColorB);
        if( updColorRInterval ) osal_timer_event_create( TASK_ID_APP_LIGHT, TASK_EVT_APP_LIGHT_UPD_R, updColorRInterval );
        else                    osal_event_set( TASK_ID_APP_LIGHT, TASK_EVT_APP_LIGHT_UPD_R );
        if( updColorGInterval ) osal_timer_event_create( TASK_ID_APP_LIGHT, TASK_EVT_APP_LIGHT_UPD_G, updColorGInterval );
        else                    osal_event_set( TASK_ID_APP_LIGHT, TASK_EVT_APP_LIGHT_UPD_G );
        if( updColorBInterval ) osal_timer_event_create( TASK_ID_APP_LIGHT, TASK_EVT_APP_LIGHT_UPD_B, updColorBInterval );
        else                    osal_event_set( TASK_ID_APP_LIGHT, TASK_EVT_APP_LIGHT_UPD_B );
        
    }
}

static void appLightUpdateColorStop(void)
{
    //appTaskSchedDelete(updColorRTid);
    //appTaskSchedDelete(updColorGTid);
    //appTaskSchedDelete(updColorBTid);
    //appTaskSchedDelete(updColorStartTid);
    //updColorStartTid = -1;
    //updColorRTid = -1;
    //updColorGTid = -1;
    //updColorBTid = -1;
    osal_timer_event_delete( TASK_ID_APP_LIGHT, TASK_EVT_APP_LIGHT_UPD_START );
    osal_timer_event_delete( TASK_ID_APP_LIGHT, TASK_EVT_APP_LIGHT_UPD_R );
    osal_timer_event_delete( TASK_ID_APP_LIGHT, TASK_EVT_APP_LIGHT_UPD_G );
    osal_timer_event_delete( TASK_ID_APP_LIGHT, TASK_EVT_APP_LIGHT_UPD_B );
    
    nxtColorId = -1;
    curColorId = -1;
}

static void appLightUpdateColorR(void)
{   
    uint8_t flag = 0;
    
    if(curColor.red == colorTableVar[nxtColorId].red)
    {
        //updColorRTid = -1;
        if( osal_timer_event_query( TASK_ID_APP_LIGHT, TASK_EVT_APP_LIGHT_UPD_R ) )
            flag |= 0x01;
        if( osal_timer_event_query( TASK_ID_APP_LIGHT, TASK_EVT_APP_LIGHT_UPD_G ) )
            flag |= 0x02;
        if( osal_timer_event_query( TASK_ID_APP_LIGHT, TASK_EVT_APP_LIGHT_UPD_B ) )
            flag |= 0x04;
        
        //if(updColorRTid < 0 && updColorGTid < 0 && updColorBTid < 0)
        if( flag == 0 )
        {
            //updColorStartTid = appTaskSchedCreate(colorTableVarTime[nxtColorId], appLightUpdateColorStart);
            if( colorTableVarTime[nxtColorId] ) osal_timer_event_create( TASK_ID_APP_LIGHT, TASK_EVT_APP_LIGHT_UPD_START, colorTableVarTime[nxtColorId] );
            else                                osal_event_set( TASK_ID_APP_LIGHT, TASK_EVT_APP_LIGHT_UPD_START );
        }
    }
    else
    {
        if(curColor.red > colorTableVar[nxtColorId].red)
        {
            curColor.red--;
        }
        else
        {
            curColor.red++;
        }
        //appLightSet(&curColor);
        hal_light_set( HAL_LIGHT_R, curColor.red );
        hal_light_set( HAL_LIGHT_G, curColor.green );
        hal_light_set( HAL_LIGHT_B, curColor.blue );
        //updColorRTid = appTaskSchedCreate(updColorRInterval, appLightUpdateColorR);
        if( updColorRInterval ) osal_timer_event_create( TASK_ID_APP_LIGHT, TASK_EVT_APP_LIGHT_UPD_R, updColorRInterval );
        else                    osal_event_set( TASK_ID_APP_LIGHT, TASK_EVT_APP_LIGHT_UPD_R );
    }
}

static void appLightUpdateColorG(void)
{
    uint8_t flag = 0;
    
    if(curColor.green == colorTableVar[nxtColorId].green)
    {
        //updColorGTid = -1;
        if( osal_timer_event_query( TASK_ID_APP_LIGHT, TASK_EVT_APP_LIGHT_UPD_R ) )
            flag |= 0x01;
        if( osal_timer_event_query( TASK_ID_APP_LIGHT, TASK_EVT_APP_LIGHT_UPD_G ) )
            flag |= 0x02;
        if( osal_timer_event_query( TASK_ID_APP_LIGHT, TASK_EVT_APP_LIGHT_UPD_B ) )
            flag |= 0x04;
        
        //if(updColorRTid < 0 && updColorGTid < 0 && updColorBTid < 0)
        if( flag == 0 )
        {
            //updColorStartTid = appTaskSchedCreate(colorTableVarTime[nxtColorId], appLightUpdateColorStart);
            if( colorTableVarTime[nxtColorId] ) osal_timer_event_create( TASK_ID_APP_LIGHT, TASK_EVT_APP_LIGHT_UPD_START, colorTableVarTime[nxtColorId] );
            else                                osal_event_set( TASK_ID_APP_LIGHT, TASK_EVT_APP_LIGHT_UPD_START );
        }
    }
    else
    {
        if(curColor.green > colorTableVar[nxtColorId].green)
        {
            curColor.green--;
        }
        else
        {
            curColor.green++;
        }
        //appLightSet(&curColor);
        hal_light_set( HAL_LIGHT_R, curColor.red );
        hal_light_set( HAL_LIGHT_G, curColor.green );
        hal_light_set( HAL_LIGHT_B, curColor.blue );
        //updColorGTid = appTaskSchedCreate(updColorGInterval, appLightUpdateColorG);
        if( updColorGInterval ) osal_timer_event_create( TASK_ID_APP_LIGHT, TASK_EVT_APP_LIGHT_UPD_G, updColorGInterval );
        else                    osal_event_set( TASK_ID_APP_LIGHT, TASK_EVT_APP_LIGHT_UPD_G );
    }
}

static void appLightUpdateColorB(void)
{
    uint8_t flag = 0;
    
    if(curColor.blue == colorTableVar[nxtColorId].blue)
    {
        //updColorBTid = -1;
        if( osal_timer_event_query( TASK_ID_APP_LIGHT, TASK_EVT_APP_LIGHT_UPD_R ) )
            flag |= 0x01;
        if( osal_timer_event_query( TASK_ID_APP_LIGHT, TASK_EVT_APP_LIGHT_UPD_G ) )
            flag |= 0x02;
        if( osal_timer_event_query( TASK_ID_APP_LIGHT, TASK_EVT_APP_LIGHT_UPD_B ) )
            flag |= 0x04;
        
        //if(updColorRTid < 0 && updColorGTid < 0 && updColorBTid < 0)
        if( flag == 0 )
        {
            //updColorStartTid = appTaskSchedCreate(colorTableVarTime[nxtColorId], appLightUpdateColorStart);
            if( colorTableVarTime[nxtColorId] ) osal_timer_event_create( TASK_ID_APP_LIGHT, TASK_EVT_APP_LIGHT_UPD_START, colorTableVarTime[nxtColorId] );
            else                                osal_event_set( TASK_ID_APP_LIGHT, TASK_EVT_APP_LIGHT_UPD_START );
        }
    }
    else
    {
        if(curColor.blue > colorTableVar[nxtColorId].blue)
        {
            curColor.blue--;
        }
        else
        {
            curColor.blue++;
        }
        //appLightSet(&curColor);
        hal_light_set( HAL_LIGHT_R, curColor.red );
        hal_light_set( HAL_LIGHT_G, curColor.green );
        hal_light_set( HAL_LIGHT_B, curColor.blue );
        
        //updColorBTid = appTaskSchedCreate(updColorBInterval, appLightUpdateColorB);
        if( updColorBInterval ) osal_timer_event_create( TASK_ID_APP_LIGHT, TASK_EVT_APP_LIGHT_UPD_B, updColorBInterval );
        else                    osal_event_set( TASK_ID_APP_LIGHT, TASK_EVT_APP_LIGHT_UPD_B );
    }
}

#endif
/**************************************************************************************************
**************************************************************************************************/

