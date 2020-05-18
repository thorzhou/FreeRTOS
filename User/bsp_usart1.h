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
#include "CommonService.h"
//-------------------- public definitions -----------------------------------
#define USE_USART1_IRQ 0
//timer2 1ms中断
#define INTERVAL_TIME_OF_USART1_BY_DMA  100UL
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

#define DEBUG_USART_DR_BASE               (USART1_BASE+0x04)		
#define SENDBUFF_SIZE                     100			
#define DEBUG_USART_DMA_CLK               RCC_AHB1Periph_DMA2	
#define DEBUG_USART_DMA_CHANNEL           DMA_Channel_4
#define DEBUG_USART_DMA_STREAM            DMA2_Stream7
                                  
//-------------------- public data ------------------------------------------
extern uint8_t SendBuff[SENDBUFF_SIZE];


//-------------------- public functions -------------------------------------
void DEBUG_USART_Config(void);
void Usart_SendByte(USART_TypeDef *pUSARTx, uint8_t ch);
void Usart_SendString(USART_TypeDef *pUSARTx, char* str);
void DEBUG_USART_DMA_Config(void);
//-------------------- inline functions -------------------------------------

#endif /* BSP_USART1_H_ */
//-----------------------End of file------------------------------------------
/** @}*/
