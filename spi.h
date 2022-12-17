/*
=============================================================================================================
Author       : Mamoun
Module       : SPI
File Name    : spi.h
Date Created : Oct 10, 2022
Description  : Source file for the SPI driver.
=============================================================================================================
*/


#ifndef SPI_H_
#define SPI_H_

/*===========================================================================================================
                                               < Includes >
===========================================================================================================*/

#include "std_types.h"

/*===========================================================================================================
                                < Definitions and Static Configurations >
===========================================================================================================*/

#define SLAVE                         (0)
#define MASTER                        (1)
#define SPI_DEVICE_MODE               (MASTER)

#if ((SPI_DEVICE_MODE != MASTER) && (SPI_DEVICE_MODE != SLAVE))
#error "Invalid device mode, The SPI has only two modes: MASTER and SLAVE."
#endif

#define SPI_MESSAGE_TERMINATOR        ';'     /* Pre-agreed string terminator character. */
#define SPI_DUMMY_BYTE                (0XFF)  /* Used when the MASTER wants to receive a byte. */

/*===========================================================================================================
                                         < Functions Prototypes >
===========================================================================================================*/


#if (SPI_DEVICE_MODE == MASTER)
/*===========================================================================================================
 * [Function Name] : SPI_initMaster
 * [Description]   : Initialize the SPI in in Master mode.
 * [Arguments]     : The function takes no arguments.
 * [return]        : The function returns void.
 ==========================================================================================================*/
void SPI_initMaster(void);
#endif


#if (SPI_DEVICE_MODE == SLAVE)
/*===========================================================================================================
 * [Function Name] : SPI_initSlave
 * [Description]   : Initialize the SPI in in Master mode.
 * [Arguments]     : The function takes no arguments.
 * [return]        : The function returns void.
 ==========================================================================================================*/
void SPI_initSlave(void);
#endif


/*===========================================================================================================
 * [Function Name] : SPI_sendByte
 * [Description]   : Transmit a specific byte to the Slave.
 * [Arguments]     : <a_data>      -> Indicates to the required byte.
 * [return]        : The function returns void.
 ==========================================================================================================*/
void SPI_sendByte(const uint8 a_data);


/*===========================================================================================================
 * [Function Name] : SPI_receiveByte
 * [Description]   : Receive a byte from the Slave.
 * [Arguments]     : The function takes no arguments.
 * [return]        : The function returns the received byte.
 ==========================================================================================================*/
uint8 SPI_receiveByte(void);


/*===========================================================================================================
 * [Function Name] : SPI_sendString
 * [Description]   : Transmit a specific string to the Slave.
 * [Arguments]     : <a_ptr2data>      -> Pointer points to the required string.
 * [return]        : The function returns void.
 ==========================================================================================================*/
void SPI_sendString(const uint8* a_ptr2data);


/*===========================================================================================================
 * [Function Name] : SPI_sendString
 * [Description]   : Receive a string from the Slave.
 * [Arguments]     : <a_ptr2string>      -> Pointer points to an array to write the string in it.
 * [return]        : The function returns void.
 ==========================================================================================================*/
void SPI_receiveString(uint8* const a_ptr2data);

#endif /* SPI_H_ */
