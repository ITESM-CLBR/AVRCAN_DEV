/****************************************************************** 
* usart.c The Universal Synchronous and Asynchronous serial Receiver
* 		 and Transmitter (USART)
* Created on: Jul 9, 2015
* This program is free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* as published by the Free Software Foundation; either version 2
* of the License, or (at your option) any later version.
* 
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
*© 2015
*****************************************************************/ 
#ifndef usart_C_
 #define usart_C_
#endif
/**
 * \addtogroup usart_module
 * @{
 */

/******************************************************************/
/*    I N C L U D E   F I L E S                                   */
/******************************************************************/
#include <usart.h>
#include <cpu.h>

/*******************************************************************************************/
/*    M A C R O S                                                                          */
/*******************************************************************************************/
#define GPIO_TX_USART0	(1<<1)
#define BAUDREG  ((OSCSPEED / (16 * 9600)) - 1)
#define cbi(port, bit) (port) &= ~(1 << (bit))
#define sbi(port, bit) (port) |= (1 << (bit))

/*******************************************************************************************/
/*    F U N C T I O N   P R O T O T Y P E S                                                */
/*******************************************************************************************/



/**********************************************************************************//**
 *  \param[in] param Description of the  parameter of the function.
 *  \param[out] param Description of the  parameter of the function.
 *  \return 0
 *  \brief Module Description
 *  \see See more information Here !!
 *  \note First Implementation 5:34:44 PM Jul 9, 2015
 *  \warning Warning.
 *  \author Author
 ****************************************************************************************/
void usart_init(uint32_t BaudRate)
{
	uint32_t BaudRate = OSCSPEED / (16 * Baud) - 1;	//calculate BaudRate

	//GPIO ENABLE
	DDRE  += GPIO_TX_USART0;		//Led set as output (Bit4 = 1), TX set as output (Bit1 = 1)

	//set BaudRate into registers
	UBRR0H = (unsigned char) (BaudRate>>8);
	UBRR0L = (unsigned char) BaudRate;

	// Bit 7 – RXCIEn: RX Complete Interrupt Enable
	// Bit 6 – TXCIEn: TX Complete Interrupt Enable
	// Bit 5 – UDRIEn: USARTn Data Register Empty Interrupt Enable
	// Bit 4 – RXENn: Receiver Enable
	// Bit 3 – TXENn: Transmitter Enable
	// Bit 1 – RXB8n: Receive Data Bit 8
	// Bit 0 – TXB8n: Transmit Data Bit 8
	UCSR0B= (1<<RXEN0) | (1<<TXEN0);

	UCSR0C =(1<<UCSZ01) | (1<<UCSZ00);
    //UCSR0C = 0b00000110;		//set frame format (8 bits, 1 stop bit)

	/* Interrups on USART */
	#if USART_INTERRUPT_RX_SUPPORT == 1
	 sbi(UCSR0B,RXCIE0);
	#endif

	sei();

}

/**
 * @}
 */
