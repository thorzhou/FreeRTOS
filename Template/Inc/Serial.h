/** @file */ /* DoxyGen file declaration */
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

#ifndef SERIAL_H_
#define SERIAL_H_
//-------------------- include files ----------------------------------------
#include "main.h"
#include "usart.h"

//-------------------- public definitions -----------------------------------
#define MAX_UART_TXRX_BUFFER_SIZE_BYTE  256
typedef struct
{
    uint8_t UartRxBuffer[MAX_UART_TXRX_BUFFER_SIZE_BYTE];
    uint8_t UartTxBuffer[MAX_UART_TXRX_BUFFER_SIZE_BYTE];
    uint16_t u16RxMsgLength;
    uint16_t u16TxMsgLength;
    FlagStatus Flag_Uart_Rx_Msg_Ready;
    FlagStatus Flag_Uart_Tx_Msg_Ready;
    UART_HandleTypeDef *huart;
    DMA_HandleTypeDef *hdma_usart_tx;
    DMA_HandleTypeDef *hdma_usart_rx;
} UART_MSG;

//-------------------- public data ------------------------------------------
extern UART_MSG Uart1_Msg;

//-------------------- public functions -------------------------------------
void ResetUartMsgStructure(void);
void SetUartTxData(UART_MSG *Uart_Msg,uint8_t *data,uint16_t length);
void UartTxProcessing(UART_MSG *Uart_Msg);
void Uart_Rx_Complete_Detecter(UART_MSG *Uart_Msg);
void UartRxProcessing(UART_MSG *Uart_Msg);
//-------------------- inline functions -------------------------------------

#endif /* SERIAL_H_ */
//-----------------------End of file------------------------------------------
/** @}*/
