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
//  Company    : Suzhou Naxin New Energy Technology, Co., Ltd.
//
//  Project    : P1001
//
//  Filename   :
//
//  Programmer : ZYQ
//
//  Description   : 将一些调试功能，不受平台影响的代码记录在此
//
//              ***  Confidential property of Company name ***
//                             Copyright(c) Company name, 2020
//------------------------------------------------------------------------------

//-------------------- pragmas ----------------------------------------------

//-------------------- include files ----------------------------------------
#include "UartService.h"
//-------------------- local definitions ------------------------------------

//-------------------- private data -----------------------------------------

//-------------------- private functions declare ----------------------------

//-------------------- public data ------------------------------------------

//-------------------- public functions -------------------------------------
/*! \fn			void Delay(__IO u32 u32Count)
 *  \brief 		随缘延迟，时间靠试
 *  \param 		u32Count delay time
 *  \exception (None non-reentrant code)
 *  \return 	NONE
 */
void Delay(__IO uint32_t u32Count)
{
    for (; u32Count != 0; u32Count--);
}

/*! \fn			void function(UNSIGNED32 u32Param1)
 *  \brief 		Description of this function
 *  \param 		param1: Description of parameter
 *  \param 		param2: Description of parameter
 *  \exception (None non-reentrant code)
 *  \return 	TRUE: success FALSE: unsuccess
 */
//-------------------- private functions ------------------------------------
#if (USE_STM32CUBEMX == 1)
/*! \fn			void function(UNSIGNED32 u32Param1)
 *  \brief 		printf, 使用cubeMX的版本， 需要usart.h
 *  \param 		param1: Description of parameter
 *  \param 		param2: Description of parameter
 *  \exception (None non-reentrant code)
 *  \return 	TRUE: success FALSE: unsuccess
 */
int fputc(int ch, FILE *f)
{
    //1.25.0版
    HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, 0xffff);
    return ch;
}
int fgetc(FILE *f)
{
    int ch;
    while (__HAL_UART_GET_FLAG(&huart1, UART_FLAG_RXNE) == RESET);
    HAL_UART_Receive(&huart1, (uint8_t *)&ch, 1, 0xffff);
    return (ch);
}
#else
/*! \fn			void function(UNSIGNED32 u32Param1)
 *  \brief 		printf, 不使用cubeMX的版本， 需要usart.h
 *  \param 		param1: Description of parameter
 *  \param 		param2: Description of parameter
 *  \exception (None non-reentrant code)
 *  \return 	TRUE: success FALSE: unsuccess
 */
int fputc(int ch, FILE *f)
{
	USART_SendData(USART1,(uint8_t) ch);
	while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
	return (ch);
}
int fgetc(FILE *f)
{
	while(USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET);
	return (int)USART_ReceiveData(USART1);
}
#endif
//-----------------------End of file------------------------------------------
/** @} */ /* End of group */
