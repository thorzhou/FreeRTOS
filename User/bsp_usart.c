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
#include "bsp_usart.h"
//-------------------- local definitions ------------------------------------

//-------------------- private data -----------------------------------------

//-------------------- private functions declare ----------------------------
// static void NVIC_Configuration(void);
//-------------------- public data ------------------------------------------

//-------------------- public functions -------------------------------------
/*! \fn			void function(UNSIGNED32 u32Param1)
 *  \brief 		Description of this function
 *  \param 		param1: Description of parameter
 *  \param 		param2: Description of parameter
 *  \exception (None non-reentrant code)
 *  \return 	TRUE: success FALSE: unsuccess
 */
void DEBUG_USART_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;

    /* init clock */
    RCC_AHB1PeriphClockCmd(DEBUG_USART_RX_GPIO_CLK | DEBUG_USART_TX_GPIO_CLK, ENABLE);
    DEBUG_USART_CLK_CMD(DEBUG_USART_CLK, ENABLE);
    /* remap */
    GPIO_PinAFConfig(DEBUG_USART_RX_GPIO_PORT, DEBUG_USART_RX_SOURCE, DEBUG_USART_RX_AF);
    GPIO_PinAFConfig(DEBUG_USART_TX_GPIO_PORT, DEBUG_USART_TX_SOURCE, DEBUG_USART_TX_AF);

    /* GPIO INIT */
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Pin = DEBUG_USART_TX_PIN;
    GPIO_Init(DEBUG_USART_TX_GPIO_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Pin = DEBUG_USART_RX_PIN;
    GPIO_Init(DEBUG_USART_RX_GPIO_PORT, &GPIO_InitStructure);

    /*  set usart mode */
    USART_InitStructure.USART_BaudRate = DEBUG_USART_BAUDRATE;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(DEBUG_USART, &USART_InitStructure);

    // NVIC_Configuration();
    /* 使能串口接收中断 */
    // USART_ITConfig(DEBUG_USART, USART_IT_RXNE, ENABLE);
    /* 使能串口 */
    USART_Cmd(DEBUG_USART, ENABLE);
}
// /**
//   * @brief  USART Init Structure definition
//   */
// typedef struct
// {
//   uint32_t USART_BaudRate;            /*!< This member configures the USART communication baud rate.
//                                            The baud rate is computed using the following formula:
//                                             - IntegerDivider = ((PCLKx) / (8 * (OVR8+1) * (USART_InitStruct->USART_BaudRate)))
//                                             - FractionalDivider = ((IntegerDivider - ((u32) IntegerDivider)) * 8 * (OVR8+1)) + 0.5
//                                            Where OVR8 is the "oversampling by 8 mode" configuration bit in the CR1 register. */

//   uint16_t USART_WordLength;          /*!< Specifies the number of data bits transmitted or received in a frame.
//                                            This parameter can be a value of @ref USART_Word_Length */

//   uint16_t USART_StopBits;            /*!< Specifies the number of stop bits transmitted.
//                                            This parameter can be a value of @ref USART_Stop_Bits */

//   uint16_t USART_Parity;              /*!< Specifies the parity mode.
//                                            This parameter can be a value of @ref USART_Parity
//                                            @note When parity is enabled, the computed parity is inserted
//                                                  at the MSB position of the transmitted data (9th bit when
//                                                  the word length is set to 9 data bits; 8th bit when the
//                                                  word length is set to 8 data bits). */

//   uint16_t USART_Mode;                /*!< Specifies whether the Receive or Transmit mode is enabled or disabled.
//                                            This parameter can be a value of @ref USART_Mode */

//   uint16_t USART_HardwareFlowControl; /*!< Specifies wether the hardware flow control mode is enabled
//                                            or disabled.
//                                            This parameter can be a value of @ref USART_Hardware_Flow_Control */
// } USART_InitTypeDef;

/*! \fn			void Usart_SendByte(USART_TypeDef *pUSARTx, uint8_t ch)
 *  \brief 		send a byte of data though usartx
 *  \param 		param1: usartx
 *  \param 		param2: data
 *  \exception (None non-reentrant code)
 *  \return 	NONE
 */
void Usart_SendByte(USART_TypeDef *pUSARTx, uint8_t ch)
{
    /* send a byte */
    USART_SendData(pUSARTx, ch);
    /* waitfor TXE */
    while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET)
        ;
}

/*! \fn			void Usart_SendString(USART_TypeDef *pUSARTx, char* str)
 *  \brief 		send a byte of data though usartx
 *  \param 		param1: usartx
 *  \param 		param2: data
 *  \exception (None non-reentrant code)
 *  \return 	NONE
 */
void Usart_SendString(USART_TypeDef *pUSARTx, char *str)
{
    uint32_t cnt = 0;
    do
    {
        Usart_SendByte(pUSARTx, *(str + cnt));
        cnt++;
    } while (*(str + cnt) != '\0');

    /* waitfor TXE */
    while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TC) == RESET)
        ;
}

//-------------------- private functions ------------------------------------
/*! \fn			void function(UNSIGNED32 u32Param1)
 *  \brief 		Description of this function
 *  \param 		param1: Description of parameter
 *  \param 		param2: Description of parameter
 *  \exception (None non-reentrant code)
 *  \return 	TRUE: success FALSE: unsuccess
 */
// static void NVIC_Configuration(void)
// {
//     NVIC_InitTypeDef NVIC_InitStructure;
//     /* 嵌套向量中断控制器组选择 */
//     NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); /*!< 2 bits for pre-emption priority*/
//     NVIC_InitStructure.NVIC_IRQChannel = DEBUG_USART_IRQ;
//     NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
//     NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
//     NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//     NVIC_Init(&NVIC_InitStructure);
// }
// /**
//   * @brief  NVIC Init Structure definition
//   */

// typedef struct
// {
//   uint8_t NVIC_IRQChannel;                    /*!< Specifies the IRQ channel to be enabled or disabled.
//                                                    This parameter can be an enumerator of @ref IRQn_Type
//                                                    enumeration (For the complete STM32 Devices IRQ Channels
//                                                    list, please refer to stm32f4xx.h file) */

//   uint8_t NVIC_IRQChannelPreemptionPriority;  /*!< Specifies the pre-emption priority for the IRQ channel
//                                                    specified in NVIC_IRQChannel. This parameter can be a value
//                                                    between 0 and 15 as described in the table @ref MISC_NVIC_Priority_Table
//                                                    A lower priority value indicates a higher priority */

//   uint8_t NVIC_IRQChannelSubPriority;         /*!< Specifies the subpriority level for the IRQ channel specified
//                                                    in NVIC_IRQChannel. This parameter can be a value
//                                                    between 0 and 15 as described in the table @ref MISC_NVIC_Priority_Table
//                                                    A lower priority value indicates a higher priority */

//   FunctionalState NVIC_IRQChannelCmd;         /*!< Specifies whether the IRQ channel defined in NVIC_IRQChannel
//                                                    will be enabled or disabled.
//                                                    This parameter can be set either to ENABLE or DISABLE */
// } NVIC_InitTypeDef;

/*! \fn			void function(UNSIGNED32 u32Param1)
 *  \brief 		Description of this function
 *  \param 		param1: Description of parameter
 *  \param 		param2: Description of parameter
 *  \exception (None non-reentrant code)
 *  \return 	TRUE: success FALSE: unsuccess
 */
int fputc(int ch, FILE *f)
{
    USART_SendData(DEBUG_USART, (uint8_t)ch);
    while (USART_GetFlagStatus(DEBUG_USART, USART_FLAG_TXE) == RESET)
        ;
    return (ch);
}

/*! \fn			void function(UNSIGNED32 u32Param1)
 *  \brief 		Description of this function
 *  \param 		param1: Description of parameter
 *  \param 		param2: Description of parameter
 *  \exception (None non-reentrant code)
 *  \return 	TRUE: success FALSE: unsuccess
 */
int fgetc(FILE *f)
{
    while (USART_GetFlagStatus(DEBUG_USART, USART_FLAG_RXNE) == RESET)
        ;
    return (int)USART_ReceiveData(DEBUG_USART);
}

void DEBUG_USART_IRQHandler(void)
{
    uint8_t ucTemp;
    if (USART_GetFlagStatus(DEBUG_USART, USART_IT_RXNE) != RESET)
    {
        ucTemp = USART_ReceiveData(DEBUG_USART);
        USART_SendData(DEBUG_USART, ucTemp);
    }
}
//-----------------------End of file------------------------------------------
/** @} */ /* End of group */