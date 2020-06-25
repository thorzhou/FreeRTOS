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
#include "Led_Beep_Key.h"
//-------------------- local definitions ------------------------------------

//-------------------- private data -----------------------------------------
static uint32_t tick;
//-------------------- private functions declare ----------------------------

//-------------------- public data ------------------------------------------

//-------------------- public functions -------------------------------------
/*! \fn			void function(UNSIGNED32 u32Param1)
 *  \brief 		放在systick中断处理函数中，每500ms转换一次状态
 *  \param 		param1: none
 *  \exception (None non-reentrant code)
 *  \return 	TRUE: success FALSE: unsuccess
 */
void Led_Beep_Processing(void)
{
    if (++tick == 500)
    {
        tick = 0;
        // HAL_GPIO_TogglePin(BEEP_GPIO_Port, BEEP_Pin);//太吵了关掉
        HAL_GPIO_TogglePin(LED0_GPIO_Port, LED0_Pin);
        HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
    }
}

// switch (KeyScan(KEY_SCAN_MODE_CONTINUED))
// {
// case KEY_UP_PRESSED:
//   HAL_GPIO_WritePin(LED0_GPIO_Port, LED0_Pin, GPIO_PIN_SET);
//   HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_SET);
//   HAL_GPIO_WritePin(BEEP_GPIO_Port, BEEP_Pin, GPIO_PIN_RESET);
//   break;
// case KEY_2_PRESSED:
//   HAL_GPIO_TogglePin(LED0_GPIO_Port,LED0_Pin);
//   break;
// case KEY_1_PRESSED:
//   HAL_GPIO_TogglePin(LED1_GPIO_Port,LED1_Pin);
//   break;
// case KEY_0_PRESSED:
//   HAL_GPIO_TogglePin(BEEP_GPIO_Port,BEEP_Pin);
//   break;
// default:
//   break;
// }

/*
 *  \brief 		扫描按键，返回按下哪个键，按键扫描有优先级，不支持同时扫描多个
 *  \param 		param1: 1:使能连按，0：仅支持单次按键处理
 *  \exception (None non-reentrant code)
 *  \return 	TRUE: success FALSE: unsuccess
 */
uint8_t KeyScan(uint8_t mode)
{
    static uint8_t previous_status = 1; //按键上一次的状态，如果上一次没有被按下，则为1
    if (mode == KEY_SCAN_MODE_CONTINUED)
        previous_status = 1; //如果使用连续扫描模式，第二次进入该函数时设上一次为没按下状态
    if (previous_status && (KEYSCAN_KEYUP == 1 || KEYSCAN_KEY2 == 0 || KEYSCAN_KEY1 == 0 || KEYSCAN_KEY0 == 0))
    {
        previous_status = 0;
        HAL_Delay(100);
        if (KEYSCAN_KEYUP == 1)
            return KEY_UP_PRESSED;
        else if (KEYSCAN_KEY2 == 0)
            return KEY_2_PRESSED;
        else if (KEYSCAN_KEY1 == 0)
            return KEY_1_PRESSED;
        else if (KEYSCAN_KEY0 == 0)
            return KEY_0_PRESSED;
    }
    else if (KEYSCAN_KEYUP == 0 && KEYSCAN_KEY2 == 1 && KEYSCAN_KEY1 == 1 && KEYSCAN_KEY0 == 1)
        previous_status = 1;
    return 0;
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
