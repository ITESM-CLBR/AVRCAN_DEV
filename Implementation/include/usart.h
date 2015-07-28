/****************************************************************** 
* usart.h
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
 
#ifndef IMPLEMENTATION_SRC_USART_H_
#define IMPLEMENTATION_SRC_USART_H_

#ifndef usart_C_
#define usart_EXTERN extern
#else
#define usart_EXTERN
#endif /* usart_C_ */

/* Included Headers */
#include <stdint.h>
#include <cpu.h>



#define UBRR_16MHZ_MATRIX

typedef enum{
  BAUD_RATE_2400=0,
  BAUD_RATE_4800,
  BAUD_RATE_9600,
  BAUD_RATE_14_4k,
  BAUD_RATE_19_2k,
  BAUD_RATE_28_8k,
  BAUD_RATE_38_4k,
  BAUD_RATE_57_6k,
  BAUD_RATE_76_8k,
  BAUD_RATE_115_2k,
  BAUD_RATE_230_4k,
  BAUD_RATE_250k,
  BAUD_RATE_500k,
  BAUD_RATE_1M,
  MAX_SUPPORTED_BAUDRATE=BAUD_RATE_1M+1
}BAUD_RATE_CONFIGS;

typedef enum{
	USART_Char_Size_5_bit=0,
	USART_Char_Size_6_bit,
	USART_Char_Size_7_bit,
	USART_Char_Size_8_bit,
	USART_Char_Size_Reserved_0,
	USART_Char_Size_Reserved_1,
	USART_Char_Size_Reserved_2,
	USART_Char_Size_9_bit
}USART_CharacterSize;




//usart_EXTERN	
usart_EXTERN void usart_init(BAUD_RATE_CONFIGS BaudRate);
usart_EXTERN void usart_enable_interrupts(void);
usart_EXTERN void usart_disable_interrupts(void);


#endif /* IMPLEMENTATION_SRC_USART_H_ */
