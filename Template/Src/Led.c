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
#include "Led.h"
//-------------------- local definitions ------------------------------------

//-------------------- private data -----------------------------------------

//-------------------- private functions declare ----------------------------

//-------------------- public data ------------------------------------------

//-------------------- public functions -------------------------------------
/*! \fn			void function(UNSIGNED32 u32Param1)
 *  \brief 		Description of this function
 *  \param 		param1: Description of parameter
 *  \param 		param2: Description of parameter
 *  \exception (None non-reentrant code)
 *  \return 	TRUE: success FALSE: unsuccess
 */
void LedFlashing(uint32_t speed)
{
    Delay(speed);
    LED_RED;
    Delay(speed);
    LED_GREEN;
    Delay(speed);
    LED_BLUE;
    Delay(speed);
    LED_YELLOW;
    Delay(speed);
    LED_PURPLE;
    Delay(speed);
    LED_CYAN;
    Delay(speed);
    LED_WHITE;
    Delay(speed);
    LED_OFF;
}

/*! \fn			uint8_t Key_Scan(GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin)
 *  \brief 		检测是否有按键按下
 *  \param 		param1: port
 *  \param 		param2: pin
 *  \exception (None non-reentrant code)
 *  \return 	KEY_ON, KEY_OFF
 */
uint8_t Key_Scan(GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin)
{
    if(HAL_GPIO_ReadPin(GPIOx,GPIO_Pin) == KEY_ON)
    {
        /* 等待按键释放 */
        while (HAL_GPIO_ReadPin(GPIOx,GPIO_Pin) == KEY_ON){};
        return KEY_ON;
    }
    else
    {
        return KEY_OFF;
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
