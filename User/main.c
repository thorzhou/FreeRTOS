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
#include "stm32f4xx.h"
#include "config.h"
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
void Delay(__IO uint32_t nCount) //简单的延时函数
{
	for (; nCount != 0; nCount--)
		;
}

//-------------------- private functions ------------------------------------
/*! \fn			int main(void)
 *  \brief 		main entry
 *  \param 		none
 *  \exception  (None non-reentrant code)
 *  \return 	TRUE: success FALSE: unsuccess
 */
int main(void)
{
	uint32_t i;
	/* LED 端口初始化 */
	LED_GPIO_Config();

#if (USE_USART1 == 1)
	DEBUG_USART_Config();
	DEBUG_USART_DMA_Config();
	// Usart_SendString(DEBUG_USART, "This is a usart test.\n");
	printf("This is a test of printf.\n");
	printf("Welcome to far west.\n");
	for (i = 0; i < SENDBUFF_SIZE; i++)
	{
		SendBuff[i] = 'a';
	}
	USART_DMACmd(DEBUG_USART,USART_DMAReq_Tx,ENABLE);
	// while (1)
	// {
	// 	char ch = getchar();
	// 	if (ch == 's')
	// 	{
	// 		break;
	// 	}
	// }
#endif

	/* 控制LED灯 */
	while (1)
	{
		LED1(ON); // 亮
		Delay(0xFFFFF);
		LED1(OFF); // 灭

		LED2(ON); // 亮
		Delay(0xFFFFF);
		LED2(OFF); // 灭

		LED3(ON); // 亮
		Delay(0xFFFFF);
		LED3(OFF); // 灭

		/*轮流显示 红绿蓝黄紫青白 颜色*/
		LED_RED;
		Delay(0xFFFFF);

		LED_GREEN;
		Delay(0xFFFFF);

		LED_BLUE;
		Delay(0xFFFFF);

		LED_YELLOW;
		Delay(0xFFFFF);

		LED_PURPLE;
		Delay(0xFFFFF);

		LED_CYAN;
		Delay(0xFFFFF);

		LED_WHITE;
		Delay(0xFFFFF);

		LED_RGBOFF;
		Delay(0xFFFFF);
	}

	// return 0;
}
/*! \fn			void function(UNSIGNED32 u32Param1)
 *  \brief 		Description of this function
 *  \param 		param1: Description of parameter
 *  \param 		param2: Description of parameter
 *  \exception (None non-reentrant code)
 *  \return 	TRUE: success FALSE: unsuccess
 */
//-----------------------End of file------------------------------------------
/** @} */ /* End of group */
