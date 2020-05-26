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

#ifndef COMMON_SERVICE_H_
#define COMMON_SERVICE_H_
//-------------------- include files ----------------------------------------
// #include "stm32f429xx.h"
#include "stm32f4xx_hal.h"
// #include "main.h"
//-------------------- public definitions -----------------------------------


//-------------------- public data ------------------------------------------


//-------------------- public functions -------------------------------------
void Delay(__IO unsigned long u32Count);
void Delay_ms(__IO uint32_t nTime);
void TimingDelay_Decrement(void);

//-------------------- inline functions -------------------------------------

#endif /* COMMON_SERVICE_H_ */
//-----------------------End of file------------------------------------------
/** @}*/
