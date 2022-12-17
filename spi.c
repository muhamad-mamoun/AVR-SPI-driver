/*
=============================================================================================================
Author       : Mamoun
Module       : SPI
File Name    : spi.c
Date Created : Oct 10, 2022
Description  : Source file for the SPI driver.
=============================================================================================================
*/


/*===========================================================================================================
                                               < Includes >
===========================================================================================================*/

#include "spi.h"
#include "gpio.h"
#include <avr/io.h>
#include "common_macros.h"

/*===========================================================================================================
                                          < Functions Definitions >
===========================================================================================================*/

#if (SPI_DEVICE_MODE == MASTER)
/*===========================================================================================================
 * [Function Name] : SPI_initMaster
 * [Description]   : Initialize the SPI in in Master mode.
 * [Arguments]     : The function takes no arguments.
 * [return]        : The function returns void.
 ==========================================================================================================*/
void SPI_initMaster(void)
{
	GPIO_setupPinDirection(PORTB_ID,PIN4_ID,OUTPUT_PIN);       /* Set-up SS pin as Output pin.   */
	GPIO_setupPinDirection(PORTB_ID,PIN5_ID,OUTPUT_PIN);       /* Set-up MOSI pin as Output pin. */
	GPIO_setupPinDirection(PORTB_ID,PIN6_ID,INPUT_PIN);        /* Set-up MISO pin as Input pin.  */
	GPIO_setupPinDirection(PORTB_ID,PIN7_ID,OUTPUT_PIN);       /* Set-up SCK pin as Output pin.  */
	SPCR |= (1<<SPE)|(1<<MSTR);                                /* Enable SPI in Master Mode.     */
}
#endif

#if (SPI_DEVICE_MODE == SLAVE)
/*===========================================================================================================
 * [Function Name] : SPI_initSlave
 * [Description]   : Initialize the SPI in in Master mode.
 * [Arguments]     : The function takes no arguments.
 * [return]        : The function returns void.
 ==========================================================================================================*/
void SPI_initSlave(void)
{
	GPIO_setupPinDirection(PORTB_ID,PIN4_ID,INPUT_PIN);        /* Set-up SS pin as Input pin.    */
	GPIO_setupPinDirection(PORTB_ID,PIN5_ID,INPUT_PIN);        /* Set-up MOSI pin as Input pin.  */
	GPIO_setupPinDirection(PORTB_ID,PIN6_ID,OUTPUT_PIN);       /* Set-up MISO pin as Output pin. */
	GPIO_setupPinDirection(PORTB_ID,PIN7_ID,INPUT_PIN);        /* Set-up SCK pin as Input pin.   */
	SPCR |= (1<<SPE);                                          /* Enable SPI in Slave Mode.      */
}
#endif

/*===========================================================================================================
 * [Function Name] : SPI_sendByte
 * [Description]   : Transmit a specific byte to the Slave.
 * [Arguments]     : <a_data>      -> Indicates to the required byte.
 * [return]        : The function returns void.
 ==========================================================================================================*/
void SPI_sendByte(const uint8 a_data)
{
	SPDR = a_data;                         /* Write the data in the SPDR register to be transmitted. */
	while(BIT_IS_CLEAR(SPSR,SPIF));        /* Wait until SPI interrupt flag SPIF = 1.                */
}

/*===========================================================================================================
 * [Function Name] : SPI_receiveByte
 * [Description]   : Receive a byte from the Slave.
 * [Arguments]     : The function takes no arguments.
 * [return]        : The function returns the received byte.
 ==========================================================================================================*/
uint8 SPI_receiveByte(void)
{
	SPDR = SPI_DUMMY_BYTE;             /* Write a Dummy Byte in the SPDR register to be transmitted. */
	while(BIT_IS_CLEAR(SPSR,SPIF));    /* Wait until SPI interrupt flag SPIF = 1.                    */
	return SPDR;                       /* Read the received byte and return it.                      */
}

/*===========================================================================================================
 * [Function Name] : SPI_sendString
 * [Description]   : Transmit a specific string to the Slave.
 * [Arguments]     : <a_ptr2data>      -> Pointer points to the required string.
 * [return]        : The function returns void.
 ==========================================================================================================*/
void SPI_sendString(const uint8* a_ptr2data)
{
	/* Loop on the string characters until the NULL character */
	for(uint8 counter = 0; *(a_ptr2data+counter) != '\0'; counter++)
	{
		/* Send every character to the UART_sendByte to be transmitted. */
		SPI_sendByte(*(a_ptr2data+counter));
	}
}

/*===========================================================================================================
 * [Function Name] : SPI_sendString
 * [Description]   : Receive a string from the Slave.
 * [Arguments]     : <a_ptr2string>      -> Pointer points to an array to write the string in it.
 * [return]        : The function returns void.
 ==========================================================================================================*/
void SPI_receiveString(uint8* const a_ptr2data)
{
	uint8 counter = 0;

	/* Read the received character and store it in the array */
	*(a_ptr2data + counter) = SPI_receiveByte();

	/* Check if the received character is the pre-agreed terminator character. */
	while(*(a_ptr2data + counter) != SPI_MESSAGE_TERMINATOR)
	{
		counter++;
		/* Read the next character and store it in the array. */
		*(a_ptr2data + counter) = SPI_receiveByte();
	}

	/* Replace the pre-agreed terminator character with a NULL character */
	*(a_ptr2data + counter) = '\0';
}
