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
#include "bsp_spi_flash.h"
//-------------------- local definitions ------------------------------------

//-------------------- private data -----------------------------------------

//-------------------- private functions declare ----------------------------

//-------------------- public data ------------------------------------------

//-------------------- public functions -------------------------------------
/*! \fn			void function(UNSIGNED32 u32Param1)
 *  \brief 		Description of this function
 *  \param 		param1: Description of parameter
 *  \param 		param2: Description of parameter
 *  \exception (None non-reentrant code)
 *  \return 	TRUE: success FALSE: unsuccess
 */
uint8_t SPI_FLASH_SendByte(uint8_t byte)
{
    SPITimeout = SPIT_FLAG_TIMEOUT;
    
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
