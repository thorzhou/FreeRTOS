/** @file */  /* DoxyGen file declaration */
/** @addtogroup <Module_Name> 
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
//              ***  Confidential property of company name ***
//                             Copyright(c) company name, 2020
//------------------------------------------------------------------------------

#ifndef BSP_LED_H_
#define BSP_LED_H_
//-------------------- include files ----------------------------------------
#include "main.h"
#include "stm32f4xx.h"
//-------------------- public definitions -----------------------------------

                                  
//-------------------- public data ------------------------------------------
extern FunctionalState LedFlash;


//-------------------- public functions -------------------------------------
/* 将led处理函数放在主循环中，每次LedFlash使能就翻转led状态 */
void Led_Processing(void);
/* 放在systick中断处理中，cubemx默认配置1ms中断一次，200ms使能一次LedFlash */
void LedTimer(void);


//-------------------- inline functions -------------------------------------

#endif /* BSP_LED_H_ */
//-----------------------End of file------------------------------------------
/** @}*/
