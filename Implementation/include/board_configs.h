/****************************************************************** 
* board_configs.h
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
 
#ifndef IMPLEMENTATION_INCLUDE_BOARD_CONFIGS_H_
#define IMPLEMENTATION_INCLUDE_BOARD_CONFIGS_H_

#ifndef board_configs_C_
#define board_configs_EXTERN extern
#else
#define board_configs_EXTERN
#endif /* board_configs_C_ */



/** \addtogroup board_configs
 *  @{
 */
#define CPU_POWER_5V				5
#define CPU_POWER_3V3				3

#define	__AVR_AT90CAN128__			1
#define BOARD_MAIN_CLOCK			16000000
#define POWER_BOARD_LEVEL			CPU_POWER_5V	/**< POWER_BOARD_LEVEL SUPPLY CONFIG */




#define USART_INTERRUPT_RX_SUPPORT 0  	/**< RX Interrup Support */
#define USART_INTERRUPT_TX_SUPPORT 0	/**< TX Interrup Support */

/** @}*/




#endif /* IMPLEMENTATION_INCLUDE_BOARD_CONFIGS_H_ */
