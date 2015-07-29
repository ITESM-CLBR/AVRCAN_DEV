/****************************************************************** 
* hardware_init.h
* Created on: Jul 29, 2015
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
 
#ifndef IMPLEMENTATION_INCLUDE_HARDWARE_INIT_H_
#define IMPLEMENTATION_INCLUDE_HARDWARE_INIT_H_

#ifndef hardware_init_C_
#define hardware_init_EXTERN extern
#else
#define hardware_init_EXTERN
#endif /* hardware_init_C_ */

/* Included Headers */


#include <board_configs.h>

#define pcbi(port, bit) 			(port) &= ~(1 << (bit))
#define psbi(port, bit) 			(port) |= (1 << (bit))

#define DDR_OUTPUT(PIN,DDR)			psbi(DDR,PIN)
#define DDR_INPUT(PIN,DDR)			pcbi(DDR,PIN)

//---------------------------------------------------------------------
//   LED Board COnfig Macros
//---------------------------------------------------------------------
#define Pin_Config_LED0() \
	DDR_OUTPUT(LED0_PIN,LED0_DDR_PORT); \
	psbi(LED0_PORT,LED0_PIN);
//---------------------------------------------------------------------
//  USART PIN CONFIG
//---------------------------------------------------------------------
#define Pin_Config_TX_RX_Usart()

#define Pin_Config_Tx() \
 DDR_OUTPUT(LED_TX_PIN,LED_TX_DDR_PORT); \
 psbi(LED_TX_PORT,LED_TX_PIN);

#define Pin_Config_Rx() \
 DDR_OUTPUT(LED_RX_PIN,LED_RX_DDR_PORT); \
 psbi(LED_RX_PORT,LED_RX_PIN);

#define Pin_Config_Err() \
 DDR_OUTPUT(LED_Err_PIN,LED_Err_DDR_PORT); \
 psbi(LED_Err_PORT,LED_Err_PIN);

#endif /* IMPLEMENTATION_INCLUDE_HARDWARE_INIT_H_ */
