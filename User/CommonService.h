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
void Delay(__IO u32 u32Count);

//-------------------- public definitions -----------------------------------
#define MAX_TIME_COUNT_U32 (0xffffffff - (0xffffffff % 100UL))
#define MAX_INTERVAL_TIME_OF_RECEIVING_DATA 5UL//ms             
//-------------------- public data ------------------------------------------
extern u32 g_u32SysTick;

//-------------------- public functions -------------------------------------


//-------------------- inline functions -------------------------------------

#endif /* COMMON_SERVICE_H_ */
//-----------------------End of file------------------------------------------
/** @}*/
