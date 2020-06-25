/** @file */  /* DoxyGen file declaration */
/** @addtogroup <Module_Name> 
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
//  Description   : "file description" 
//
//              ***  Confidential property of company name ***
//                             Copyright(c) company name, 2020
//------------------------------------------------------------------------------

#ifndef UART_SERVICE_H_
#define UART_SERVICE_H_
//-------------------- include files ----------------------------------------
// #include "stm32f4xx_hal.h"
#include "usart.h"
#include <stdio.h>
//-------------------- public definitions -----------------------------------
#define USE_STM32CUBEMX 1   //切换是否使用由stm32cubeMX生成的代码

/* 调试信息开关,宏定义多参数说明https://blog.csdn.net/cp1300/article/details/7773239
 * usage: DEBUG("%d%x",arg,hexadecimal);DEBUG("hello");...
 */
#define USART1_DEBUG_OUTPUT
#ifdef USART1_DEBUG_OUTPUT
#define DEBUG(fmt,...)    printf("FILE: "__FILE__",LINE: %d, "fmt"\r\n",__LINE__,##__VA_ARGS__)
#else
#define DEBUG(fmt,...)
#endif
//-------------------- public data ------------------------------------------


//-------------------- public functions -------------------------------------
void Delay(__IO uint32_t u32Count);

//-------------------- inline functions -------------------------------------

#endif /* UART_SERVICE_H_ */
//-----------------------End of file------------------------------------------
/** @}*/
