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
#include "bsp_i2c_ee.h"
//-------------------- local definitions ------------------------------------

//-------------------- private data -----------------------------------------

//-------------------- private functions declare ----------------------------

//-------------------- public data ------------------------------------------
uint8_t EE_WriteBuffer[256];
uint8_t EE_ReadBuffer[256];
//-------------------- public functions -------------------------------------
#if 0
/*! \fn			void function(UNSIGNED32 u32Param1)
 *  \brief 		向EEPROM的指定内存地址写入一个字节数据
 *  \param 		param1: 写入缓冲区
 *  \param 		param2: 写到EEPROM的内存地址
 *  \exception (None non-reentrant code)
 *  \return 	TRUE: HAL_OK FALSE: OTHERS
 */
HAL_StatusTypeDef I2C_EE_WriteByte(uint8_t *pBuffer, uint16_t Addr)
{
    HAL_StatusTypeDef status;
    status = HAL_I2C_Mem_Write(&hi2c1, EEPROM_ADDRESS, Addr, I2C_MEMADD_SIZE_8BIT, pBuffer, 1, 100);
    if (status != HAL_OK)
    {
        /* execute user timeout callback */
        //I2Cx_Error(Addr);
        DEBUG("I2C page write eeprom error.WriteAddr:%d.", Addr);
        return status;
    }
    while (HAL_I2C_GetState(&hi2c1) != HAL_I2C_STATE_READY)
        ;
    while (HAL_I2C_IsDeviceReady(&hi2c1, EEPROM_ADDRESS, 3, 100) == HAL_TIMEOUT)
        ;
    while (HAL_I2C_GetState(&hi2c1) != HAL_I2C_STATE_READY)
        ;
    return status;
}

/*! \fn			void function(UNSIGNED32 u32Param1)
 *  \brief 		向EEPROM的指定内存地址写入一个页数据
 *  \param 		param1: 写入缓冲区
 *  \param 		param2: 写到EEPROM的内存地址
 *  \param 		param3: 写入长度，应为页大小
 *  \exception (None non-reentrant code)
 *  \return 	TRUE: HAL_OK FALSE: OTHERS
 */
HAL_StatusTypeDef I2C_EE_WritePage(uint8_t *pBuffer, uint16_t WriteAddr, uint16_t NumByteToWrite)
{
    HAL_StatusTypeDef status = HAL_OK;
    status = HAL_I2C_Mem_Write(&hi2c1, EEPROM_ADDRESS, WriteAddr, I2C_MEMADD_SIZE_8BIT, pBuffer, NumByteToWrite, 1000);
    if (status != HAL_OK)
    {
        /* execute user timeout callback */
        //I2Cx_Error(Addr);
        DEBUG("I2C page write eeprom error.WriteAddr:%d.", WriteAddr);
        return status;
    }
    while (HAL_I2C_GetState(&hi2c1) != HAL_I2C_STATE_READY)
        ;
    while (HAL_I2C_IsDeviceReady(&hi2c1, EEPROM_ADDRESS, 10, 100) == HAL_TIMEOUT)
        ;
    while (HAL_I2C_GetState(&hi2c1) != HAL_I2C_STATE_READY)
        ;
    return status;
}
#endif

/*! \fn			void function(UNSIGNED32 u32Param1)
 *  \brief 		向EEPROM的指定内存地址写入任意字节数据
 *  \param 		param1: 写入缓冲区
 *  \param 		param2: 写到EEPROM的内存地址
 *  \param 		param3: 写入长度，应为页大小
 *  \exception (None non-reentrant code)
 *  \return 	TRUE: HAL_OK FALSE: OTHERS
 */
HAL_StatusTypeDef I2C_EE_WriteBuffer(uint8_t *pBuffer, uint16_t WriteAddr, uint16_t NumByteToWrite)
{
    HAL_StatusTypeDef status = HAL_OK;
    /* 对输入数据分页，判断从什么位置开始，要写多少页，多少内容需要单独写byte */
    uint16_t AddrOffset, NumOfPage, NumOfRemain, cnt;
    AddrOffset = WriteAddr % EEPROM_PAGE_SIZE;                      //在使用页写入前需要先单个byte写入的数量
    NumOfPage = (NumByteToWrite - EEPROM_PAGE_SIZE + AddrOffset) / EEPROM_PAGE_SIZE;   //中间段，使用页写入的数据量
    NumOfRemain = NumByteToWrite - (EEPROM_PAGE_SIZE - AddrOffset) - NumOfPage * EEPROM_PAGE_SIZE; //最后小于一页的内容

    if (AddrOffset != 0)
    {
        status = HAL_I2C_Mem_Write(&hi2c1, EEPROM_ADDRESS, WriteAddr, I2C_MEMADD_SIZE_8BIT, pBuffer, EEPROM_PAGE_SIZE - AddrOffset, 100);
        if (status != HAL_OK)
        {
            DEBUG("i2c write error.Error code:%d.", (uint8_t)status);
            return status;
        }
        pBuffer += EEPROM_PAGE_SIZE - AddrOffset;
        WriteAddr += EEPROM_PAGE_SIZE - AddrOffset;
        HAL_Delay(5);
    }
    while (NumOfPage > 0)
    {
        status = HAL_I2C_Mem_Write(&hi2c1, EEPROM_ADDRESS, WriteAddr, I2C_MEMADD_SIZE_8BIT, pBuffer, EEPROM_PAGE_SIZE, 100);
        pBuffer += EEPROM_PAGE_SIZE;
        WriteAddr += EEPROM_PAGE_SIZE;
        if (status != HAL_OK)
        {
            DEBUG("i2c write error.Error code:%d.", (uint8_t)status);
            return status;
        }
        NumOfPage--;
        HAL_Delay(5);
    }
    if (NumOfRemain != 0)
    {
        status = HAL_I2C_Mem_Write(&hi2c1, EEPROM_ADDRESS, WriteAddr, I2C_MEMADD_SIZE_8BIT, pBuffer, NumOfRemain, 100);
        if (status != HAL_OK)
        {
            DEBUG("i2c write error.Error code:%d.", (uint8_t)status);
            return status;
        }
    }
    return status;
}

/*! \fn			void function(UNSIGNED32 u32Param1)
 *  \brief 		读取EEPROM指定内存地址数据,保存到指定缓冲区
 *  \param 		param1: 读取缓冲区
 *  \param 		param2: 被读取EEPROM的内存地址
 *  \param 		param3: 读取长度
 *  \exception (None non-reentrant code)
 *  \return 	TRUE: HAL_OK FALSE: OTHERS
 */
HAL_StatusTypeDef I2C_EE_ReadData(uint8_t *pReadBuffer, uint16_t ReadAddr, uint16_t NumByteToRead)
{
    HAL_StatusTypeDef status;
    status = HAL_I2C_Mem_Read(&hi2c1, EEPROM_ADDRESS, ReadAddr, I2C_MEMADD_SIZE_8BIT, pReadBuffer, NumByteToRead, 100);
    return status;
}

//-------------------- private functions ------------------------------------
/*! \fn			void function(UNSIGNED32 u32Param1)
 *  \brief 		Description of this function
 *  \param 		param1: Description of parameter
 *  \param 		param2: Description of parameter
 *  \exception (None non-reentrant code)
 *  \return 	TRUE: success FALSE: unsuccess
 */

//-----------------------End of file------------------------------------------
/** @} */ /* End of group */
