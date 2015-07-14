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


//usart_EXTERN	
usart_EXTERN void usart_init(uint32_t BaudRate);
usart_EXTERN void usart_enable_interrupts(void);
usart_EXTERN void usart_disable_interrupts(void);


#endif /* IMPLEMENTATION_SRC_USART_H_ */
