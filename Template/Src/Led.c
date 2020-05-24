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
static FunctionalState flag_led_on;

//-------------------- private functions declare ----------------------------
// void LedFlashing(uint32_t speed);
void LedFlashing(void);
//-------------------- public data ------------------------------------------

//-------------------- public functions -------------------------------------
/*! \fn			void function(UNSIGNED32 u32Param1)
 *  \brief 		Description of this function
 *  \param 		param1: Description of parameter
 *  \param 		param2: Description of parameter
 *  \exception (None non-reentrant code)
 *  \return 	TRUE: success FALSE: unsuccess
 */
void Led_Task(void)
{
    // if (Key_Scan(KEY1_GPIO_Port, KEY1_Pin) == KEY_ON)
    // {
    //     flag_led_on = ENABLE;
    // }
    // if (Key_Scan(KEY2_GPIO_Port, KEY2_Pin) == KEY_ON)
    // {
    //     flag_led_on = DISABLE;
    // }
    if (flag_led_on == ENABLE) //这样写的弊端是在这边的时间太久了，需要长时间按键才能关闭LED输出
    {
        LedFlashing();
    }
    else
    {
        LED_OFF;
    }
}
/*! \fn			void function(UNSIGNED32 u32Param1)
 *  \brief 		Description of this function
 *  \param 		param1: Description of parameter
 *  \param 		param2: Description of parameter
 *  \exception (None non-reentrant code)
 *  \return 	TRUE: success FALSE: unsuccess
 */
#if 0
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
#endif
void LedFlashing(void)
{
    Delay_ms(1000);
    LED_RED;
    Delay_ms(1000);
    LED_GREEN;
    Delay_ms(1000);
    LED_BLUE;
    Delay_ms(1000);
    LED_YELLOW;
    Delay_ms(1000);
    LED_PURPLE;
    Delay_ms(1000);
    LED_CYAN;
    Delay_ms(1000);
    LED_WHITE;
    Delay_ms(1000);
    LED_OFF;
}

/*! \fn			uint8_t Key_Scan(GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin)
 *  \brief 		检测是否有按键按下
 *  \param 		param1: port
 *  \param 		param2: pin
 *  \exception (None non-reentrant code)
 *  \return 	KEY_ON, KEY_OFF
 */
uint8_t Key_Scan(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
    if (HAL_GPIO_ReadPin(GPIOx, GPIO_Pin) == KEY_ON)
    {
        /* 等待按键释放 */
        while (HAL_GPIO_ReadPin(GPIOx, GPIO_Pin) == KEY_ON)
        {
        };
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
/**
  * @brief This function handles EXTI line0 interrupt.
  */
void EXTI0_IRQHandler(void)
{
    /* USER CODE BEGIN EXTI0_IRQn 0 */

    /* USER CODE END EXTI0_IRQn 0 */
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_0);
    /* USER CODE BEGIN EXTI0_IRQn 1 */
    flag_led_on = ENABLE;

    /* USER CODE END EXTI0_IRQn 1 */
}
/**
  * @brief This function handles EXTI line[15:10] interrupts.
  */
void EXTI15_10_IRQHandler(void)
{
    /* USER CODE BEGIN EXTI15_10_IRQn 0 */

    /* USER CODE END EXTI15_10_IRQn 0 */
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_13);
    /* USER CODE BEGIN EXTI15_10_IRQn 1 */
    flag_led_on = DISABLE;

    /* USER CODE END EXTI15_10_IRQn 1 */
}
//-----------------------End of file------------------------------------------
/** @} */ /* End of group */
