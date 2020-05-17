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

#ifndef BSP_USART1_H_
#define BSP_USART1_H_
//-------------------- include files ----------------------------------------
#include "stm32f4xx.h"
#include <stdio.h>

//-------------------- public definitions -----------------------------------
/* 8N1 */
#define DEBUG_USART                 USART1
#define DEBUG_USART_CLK             RCC_APB2Periph_USART1
#define DEBUG_USART_BAUDRATE        115200
#define DEBUG_USART_CLK_CMD         RCC_APB2PeriphClockCmd

#define DEBUG_USART_RX_GPIO_PORT    GPIOA
#define DEBUG_USART_RX_GPIO_CLK     RCC_AHB1Periph_GPIOA
#define DEBUG_USART_RX_PIN          GPIO_Pin_10
#define DEBUG_USART_RX_AF           GPIO_AF_USART1
#define DEBUG_USART_RX_SOURCE       GPIO_PinSource10

#define DEBUG_USART_TX_GPIO_PORT    GPIOA
#define DEBUG_USART_TX_GPIO_CLK     RCC_AHB1Periph_GPIOA
#define DEBUG_USART_TX_PIN          GPIO_Pin_9
#define DEBUG_USART_TX_AF           GPIO_AF_USART1
#define DEBUG_USART_TX_SOURCE       GPIO_PinSource9

#define DEBUG_USART_IRQHandler      USART1_IRQHandler
#define DEBUG_USART_IRQ             USART1_IRQn
                                  
//-------------------- public data ------------------------------------------


//-------------------- public functions -------------------------------------
void DEBUG_USART_Config(void);
void Usart_SendByte(USART_TypeDef *pUSARTx, uint8_t ch);
void Usart_SendString(USART_TypeDef *pUSARTx, char* str);

//-------------------- inline functions -------------------------------------

#endif /* BSP_USART1_H_ */
//-----------------------End of file------------------------------------------
/** @}*/
