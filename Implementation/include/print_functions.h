/****************************************************************** 
* print_functions.h
* Created on: Jul 30, 2015
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
 
#ifndef AVRCAN_DEV_IMPLEMENTATION_INCLUDE_PRINT_FUNCTIONS_H_
#define AVRCAN_DEV_IMPLEMENTATION_INCLUDE_PRINT_FUNCTIONS_H_

#ifndef print_functions_C_
#define print_functions_EXTERN extern
#else
#define print_functions_EXTERN
#endif /* print_functions_C_ */

/* Included Headers */
#include <usart.h>

#define PUT_CHAR_STDOUT UART_Transmit
print_functions_EXTERN void Print_Buffer(unsigned char * data);
print_functions_EXTERN void Print_BufferHEX(unsigned char * data,uint8_t ico);

//print_functions_EXTERN	




#endif /* AVRCAN_DEV_IMPLEMENTATION_INCLUDE_PRINT_FUNCTIONS_H_ */
