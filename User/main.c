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
#include "bsp_led.h"
//-------------------- local definitions ------------------------------------

//-------------------- private data -----------------------------------------

//-------------------- private functions declare ----------------------------
void Delay(__IO u32 nCount); 

//-------------------- public data ------------------------------------------

//-------------------- public functions -------------------------------------
/*! \fn			void function(UNSIGNED32 u32Param1)
 *  \brief 		Description of this function
 *  \param 		param1: Description of parameter
 *  \param 		param2: Description of parameter
 *  \exception (None non-reentrant code)
 *  \return 	TRUE: success FALSE: unsuccess
 */
void Delay(__IO uint32_t nCount)	 //简单的延时函数
{
	for(; nCount != 0; nCount--);
}
//-------------------- private functions ------------------------------------
/*! \fn			void function(UNSIGNED32 u32Param1)
 *  \brief 		Description of this function
 *  \param 		param1: Description of parameter
 *  \param 		param2: Description of parameter
 *  \exception (None non-reentrant code)
 *  \return 	TRUE: success FALSE: unsuccess
 */

//-------------------- private functions ------------------------------------
/*! \fn			int main(void)
 *  \brief 		main entry
 *  \param 		none
 *  \exception  (None non-reentrant code)
 *  \return 	TRUE: success FALSE: unsuccess
 */
int main(void)
{
	/* LED 端口初始化 */
	LED_GPIO_Config();

	/* 控制LED灯 */
	while (1)
	{
		LED1( ON );			 // 亮 
		Delay(0xFFFFFF);
		LED1( OFF );		  // 灭

		LED2( ON );			// 亮 
		Delay(0xFFFFFF);
		LED2( OFF );		  // 灭

		LED3( ON );			 // 亮 
		Delay(0xFFFFFF);
		LED3( OFF );		  // 灭	

		/*轮流显示 红绿蓝黄紫青白 颜色*/
		LED_RED;
		Delay(0xFFFFFF);
		
		LED_GREEN;
		Delay(0xFFFFFF);
		
		LED_BLUE;
		Delay(0xFFFFFF);
		
		LED_YELLOW;
		Delay(0xFFFFFF);
		
		LED_PURPLE;
		Delay(0xFFFFFF);
				
		LED_CYAN;
		Delay(0xFFFFFF);
		
		LED_WHITE;
		Delay(0xFFFFFF);
		
		LED_RGBOFF;
		Delay(0xFFFFFF);
	}

    return 0;
}
//-----------------------End of file------------------------------------------
/** @} */ /* End of group */
