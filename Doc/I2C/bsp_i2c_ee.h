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

#ifndef BSP_I2C_EE_H_
#define BSP_I2C_EE_H_
//-------------------- include files ----------------------------------------
#include "main.h"
#include "i2c.h"

//-------------------- public definitions -----------------------------------
#define EEPROM_ADDRESS  0xA0
#define EEPROM_MEMORY_SIZE  256U
#define EEPROM_PAGE_SIZE 8U
//-------------------- public data ------------------------------------------
extern uint8_t EE_WriteBuffer[256];
extern uint8_t EE_ReadBuffer[256];

//-------------------- public functions -------------------------------------
// /* 向EEPROM中Addr地址写入pBuffer中内容 */
// HAL_StatusTypeDef I2C_EE_WriteByte(uint8_t *pBuffer, uint16_t Addr);
// /* 向EEPROM中Addr地址写入pBuffer中内容,长度应为一个页大小 */
// HAL_StatusTypeDef I2C_EE_WritePage(uint8_t *pBuffer, uint16_t WriteAddr, uint16_t NumByteToWrite);
HAL_StatusTypeDef I2C_EE_WriteBuffer(uint8_t *pBuffer, uint16_t WriteAddr, uint16_t NumByteToWrite);
/* 读取EEPROM中ReadAddr地址开始的NumByteToRead字节的数据，保存在pReadBuffer中 */
HAL_StatusTypeDef I2C_EE_ReadData(uint8_t *pReadBuffer, uint16_t ReadAddr, uint16_t NumByteToRead);


//-------------------- inline functions -------------------------------------

#endif /* BSP_I2C_EE_H_ */
//-----------------------End of file------------------------------------------
/** @}*/
