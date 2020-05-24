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

#ifndef LED_H_
#define LED_H_
//-------------------- include files ----------------------------------------
#include "main.h"
#include "CommonService.h"

//-------------------- public definitions -----------------------------------
#define digitalHi(port,pin) {port->BSRR=pin;}
#define digitalLo(port,pin) {port->BSRR=(uint32_t)pin << 16;}
#define digitalToggle(port,pin) {port->ODR ^=pin;}

#define LED1_TOGGLE digitalToggle(LED_R_GPIO_Port,LED_R_Pin)
#define LED1_OFF  digitalHi(LED_R_GPIO_Port,LED_R_Pin)
#define LED1_ON digitalLo(LED_R_GPIO_Port,LED_R_Pin)
#define LED2_TOGGLE digitalToggle(LED_G_GPIO_Port,LED_G_Pin)
#define LED2_OFF digitalHi(LED_G_GPIO_Port,LED_G_Pin)
#define LED2_ON digitalLo(LED_G_GPIO_Port,LED_G_Pin)
#define LED3_TOGGLE digitalToggle(LED_B_GPIO_Port,LED_B_Pin)
#define LED3_OFF digitalHi(LED_B_GPIO_Port,LED_B_Pin)
#define LED3_ON digitalLo(LED_B_GPIO_Port,LED_B_Pin)
//MIX
#define LED_RED {LED1_ON;LED2_OFF;LED3_OFF;}
#define LED_GREEN {LED1_OFF;LED2_ON;LED3_OFF;}
#define LED_BLUE {LED1_OFF;LED2_OFF;LED3_ON;}
#define LED_YELLOW {LED1_ON;LED2_ON;LED3_OFF;}
#define LED_PURPLE {LED1_ON;LED2_OFF;LED3_ON;}
#define LED_CYAN {LED1_OFF;LED2_ON;LED3_ON;}
#define LED_WHITE {LED1_ON;LED2_ON;LED3_ON;}
#define LED_OFF {LED1_OFF;LED2_OFF;LED3_OFF;}

#define KEY_ON  1
#define KEY_OFF 0                                
//-------------------- public data ------------------------------------------


//-------------------- public functions -------------------------------------
void LedFlashing(uint32_t speed);
uint8_t Key_Scan(GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin);

//-------------------- inline functions -------------------------------------

#endif /* LED_H_ */
//-----------------------End of file------------------------------------------
/** @}*/
