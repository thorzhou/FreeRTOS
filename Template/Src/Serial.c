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
//              ***  Confidential property of Company name ***
//                             Copyright(c) Company name, 2020
//------------------------------------------------------------------------------

//-------------------- pragmas ----------------------------------------------

//-------------------- include files ----------------------------------------
#include <stdio.h>
#include <string.h>
#include "Serial.h"
//-------------------- local definitions ------------------------------------
#define MAX_INTERVAL_TIME_OF_RECEIVING 2 //当前接收检测放在systick中，间隔2ms
//-------------------- private data -----------------------------------------

//-------------------- private functions declare ----------------------------

//-------------------- public data ------------------------------------------
UART_MSG Uart1_Msg;
//-------------------- public functions -------------------------------------
/*! \fn			void function(UNSIGNED32 u32Param1)
 *  \brief 		Description of this function
 *  \param 		param1: Description of parameter
 *  \param 		param2: Description of parameter
 *  \exception (None non-reentrant code)
 *  \return 	TRUE: success FALSE: unsuccess
 */
void ResetUartMsgStructure(void)
{
    Uart1_Msg.huart = &huart1;
    Uart1_Msg.hdma_usart_tx = &hdma_usart1_tx;
    Uart1_Msg.hdma_usart_rx = &hdma_usart1_rx;
    memset(&Uart1_Msg, 0, MAX_UART_TXRX_BUFFER_SIZE_BYTE);
    memset(Uart1_Msg.UartTxBuffer, 0, MAX_UART_TXRX_BUFFER_SIZE_BYTE);
    Uart1_Msg.u16RxMsgLength = 0;
    Uart1_Msg.u16TxMsgLength = 0;
    Uart1_Msg.Flag_Uart_Rx_Msg_Ready = RESET;
    Uart1_Msg.Flag_Uart_Tx_Msg_Ready = RESET;
}
/*! \fn			void function(UNSIGNED32 u32Param1)
 *  \brief 		Description of this function
 *  \param 		param1: Description of parameter
 *  \param 		param2: Description of parameter
 *  \exception (None non-reentrant code)
 *  \return 	TRUE: success FALSE: unsuccess
 */
void SetUartTxData(UART_MSG *Uart_Msg, uint8_t *data, uint16_t length)
{
    memset(Uart1_Msg.UartTxBuffer, 0, MAX_UART_TXRX_BUFFER_SIZE_BYTE);
    strcpy((char *)Uart1_Msg.UartTxBuffer, (char *)data);
    Uart1_Msg.u16TxMsgLength = length;
    Uart1_Msg.Flag_Uart_Tx_Msg_Ready = SET;
}

/*! \fn			void Uart_Tx_Processing(UART_MSG *Uart_Msg)
 *  \brief 		
 *  \param 		param1: Description of parameter
 *  \exception (None non-reentrant code)
 *  \return 	None
 */
void UartTxProcessing(UART_MSG *Uart_Msg)
{
    if (Uart_Msg->Flag_Uart_Tx_Msg_Ready == RESET)
    {
        return;
    }
    __HAL_DMA_DISABLE(&hdma_usart1_tx); //单次模式重新启动之前一定要关闭DMA传输
    // HAL_UART_DMAStop(&huart1);//这里发送不能使用stop来停止，会使得接收也停止，并且发送不了数据，原因未知。
    if (HAL_UART_Transmit_DMA(Uart_Msg->huart, Uart_Msg->UartTxBuffer, Uart_Msg->u16TxMsgLength) != HAL_OK)
    {
        Error_Handler();
    }
    else
    {
        Uart_Msg->Flag_Uart_Tx_Msg_Ready = RESET;
    }
}

/*! \fn			void function(UNSIGNED32 u32Param1)
 *  \brief 		运行在systick，或其他时间处理函数中
 *  \param 		param1: Description of parameter
 *  \param 		param2: Description of parameter
 *  \exception (None non-reentrant code)
 *  \return 	TRUE: success FALSE: unsuccess
 */
void Uart_Rx_Complete_Detecter(UART_MSG *Uart_Msg)
{
    static uint16_t u16DMA_Count = MAX_UART_TXRX_BUFFER_SIZE_BYTE;
    static uint32_t u32Timer = 0;
    static uint32_t u32PreviousTime = 0;
    /* 开始接收到数据 */
    if ((DMA2_Stream2->NDTR < MAX_UART_TXRX_BUFFER_SIZE_BYTE) && (((hdma_usart1_rx.Instance->CR) & 0x00000001) > 0))
    // if(__HAL_UART_GET_FLAG(Uart_Msg->huart,UART_FLAG_RXNE)!=RESET)
    {
        // __HAL_UART_CLEAR_FLAG(Uart_Msg->huart,UART_FLAG_RXNE);
        u32Timer++; //计时
        /* 如果有新的数据传输记录已传输数据量 */
        if (u16DMA_Count != __HAL_DMA_GET_COUNTER(&hdma_usart1_rx))
        {
            u16DMA_Count = __HAL_DMA_GET_COUNTER(&hdma_usart1_rx);
            u32PreviousTime = u32Timer;
        }
        /* 没有新的数据传输到一定时间 */
        else if ((u32Timer - u32PreviousTime) > MAX_INTERVAL_TIME_OF_RECEIVING)
        {
            u32Timer = 0;
            u32PreviousTime = 0;
            u16DMA_Count = MAX_UART_TXRX_BUFFER_SIZE_BYTE;
            // __HAL_UART_CLEAR_FLAG(&huart1, UART_FLAG_RXNE);
            __HAL_DMA_DISABLE(&hdma_usart1_rx);
            Uart1_Msg.u16RxMsgLength = MAX_UART_TXRX_BUFFER_SIZE_BYTE - __HAL_DMA_GET_COUNTER(&hdma_usart1_rx);
            Uart1_Msg.Flag_Uart_Rx_Msg_Ready = SET;
        }
    }
}

void UartRxProcessing(UART_MSG *Uart_Msg)
{
    if (Uart_Msg->Flag_Uart_Rx_Msg_Ready == RESET)
    {
        return;
    }
    // __HAL_DMA_DISABLE(&hdma_usart1_rx);
    HAL_UART_DMAStop(&huart1);
    SetUartTxData(Uart_Msg,Uart_Msg->UartRxBuffer,Uart_Msg->u16RxMsgLength);
    if (HAL_UART_Receive_DMA(Uart_Msg->huart, Uart_Msg->UartRxBuffer, MAX_UART_TXRX_BUFFER_SIZE_BYTE) != HAL_OK)
    {
        Error_Handler();
    }
    else
    {
        Uart_Msg->Flag_Uart_Rx_Msg_Ready = RESET;
    }
}
//-------------------- private functions ------------------------------------
/*! \fn			void function(UNSIGNED32 u32Param1)
 *  \brief 		Description of this function
 *  \param 		param1: Description of parameter
 *  \param 		param2: Description of parameter
 *  \exception (None non-reentrant code)
 *  \return 	TRUE: success FALSE: unsuccess
 */
int fputc(int ch, FILE *f)
{
    // 1.8.0版HAL库
    // USART_SendData(USART1,(uint8_t)ch);
    // while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);

    //1.25.0版
    HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, 0xffff);
    return ch;
}
int fgetc(FILE *f)
{
    int ch;
    while (__HAL_UART_GET_FLAG(&huart1, UART_FLAG_RXNE) == RESET)
        ;
    HAL_UART_Receive(&huart1, (uint8_t *)&ch, 1, 0xffff);
    return (ch);
}

void USART1_IRQHandler(void)
{
    if (__HAL_UART_GET_FLAG(&huart1, UART_FLAG_IDLE) != RESET)
    {
        __HAL_UART_CLEAR_FLAG(&huart1, UART_FLAG_RXNE);
        __HAL_DMA_DISABLE(&hdma_usart1_rx);
        Uart1_Msg.u16RxMsgLength = MAX_UART_TXRX_BUFFER_SIZE_BYTE - __HAL_DMA_GET_COUNTER(&hdma_usart1_rx);
        Uart1_Msg.Flag_Uart_Rx_Msg_Ready = SET;
    }
    // HAL_UART_IRQHandler(&huart1);
}
//-----------------------End of file------------------------------------------
/** @} */ /* End of group */
