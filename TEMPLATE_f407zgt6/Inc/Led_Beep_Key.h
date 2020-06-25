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

#ifndef LED_BEEP_KEY_H_
#define LED_BEEP_KEY_H_
//-------------------- include files ----------------------------------------
#include "main.h"

//-------------------- public definitions -----------------------------------
#define KEY_SCAN_MODE_CONTINUED 1
#define KEY_SCAN_MODE_SINGLE    0

#define KEY_UP_PRESSED  1
#define KEY_2_PRESSED   2
#define KEY_1_PRESSED   3
#define KEY_0_PRESSED   4

#define KEYSCAN_KEYUP   HAL_GPIO_ReadPin(KEY_UP_GPIO_Port,KEY_UP_Pin)
#define KEYSCAN_KEY2    HAL_GPIO_ReadPin(KEY2_GPIO_Port,KEY2_Pin)
#define KEYSCAN_KEY1    HAL_GPIO_ReadPin(KEY1_GPIO_Port,KEY1_Pin)
#define KEYSCAN_KEY0    HAL_GPIO_ReadPin(KEY0_GPIO_Port,KEY0_Pin)
                                  
//-------------------- public data ------------------------------------------


//-------------------- public functions -------------------------------------
void Led_Beep_Processing(void);
uint8_t KeyScan(uint8_t mode);


//-------------------- inline functions -------------------------------------

#endif /* LED_BEEP_KEY_H_ */
//-----------------------End of file------------------------------------------
/** @}*/
