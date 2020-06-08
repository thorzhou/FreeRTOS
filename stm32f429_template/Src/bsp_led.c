/** @defgroup <Module_Name>
 *  @addtogroup <Module_Name>(If this is a sub-module, add it father module here)
 *  @design <Document link>
 *  @testspec <Document link>
 *
 *  @{
 */
//------------------------------------------------------------------------------
//  $Header$
//
//  Company    : 
//
//  Project    : 
//
//  Filename   : 
//
//  Programmer : ZYQ
//                             
//  Description   : 
//
//              ***  Confidential property of Company name ***
//                             Copyright(c) Company name, 2020
//------------------------------------------------------------------------------

//-------------------- pragmas ----------------------------------------------

//-------------------- include files ----------------------------------------
#include "bsp_led.h"
//-------------------- local definitions ------------------------------------
#define INTERVAL_TIME 200U
//-------------------- private data -----------------------------------------
static uint32_t Led_Cnt = 0;
//-------------------- private functions declare ----------------------------

//-------------------- public data ------------------------------------------
FunctionalState LedFlash = DISABLE;
//-------------------- public functions -------------------------------------
/*! \fn			void function(UNSIGNED32 u32Param1)
 *  \brief 		每INTERVAL_TIME ms闪烁一次
 *  \param 		param1: Description of parameter
 *  \param 		param2: Description of parameter
 *  \exception (None non-reentrant code)
 *  \return 	TRUE: success FALSE: unsuccess
 */
void Led_Processing(void)
{
    if(LedFlash == DISABLE)
    {
        return;
    }
    LedFlash = DISABLE;
    HAL_GPIO_TogglePin(LED_R_GPIO_Port,LED_R_Pin);
    HAL_GPIO_TogglePin(LED_G_GPIO_Port,LED_G_Pin);
    HAL_GPIO_TogglePin(LED_B_GPIO_Port,LED_B_Pin);
}

/*! \fn			void function(UNSIGNED32 u32Param1)
 *  \brief 		在systick中断中使用，每INTERVAL_TIME ms换一次led状态
 *  \param 		param1: Description of parameter
 *  \param 		param2: Description of parameter
 *  \exception (None non-reentrant code)
 *  \return 	TRUE: success FALSE: unsuccess
 */
void LedTimer(void)
{
    if(Led_Cnt++ == INTERVAL_TIME)
    {
        Led_Cnt = 0;
        LedFlash = ENABLE;
    }
}
//-------------------- private functions ------------------------------------
/*! \fn			void function(UNSIGNED32 u32Param1)
 *  \brief 		Description of this function
 *  \param 		param1: Description of parameter
 *  \param 		param2: Description of parameter
 *  \exception (None non-reentrant code)
 *  \return 	TRUE: success FALSE: unsuccess
 */


//-----------------------End of file------------------------------------------
/** @} */ /* End of group */
