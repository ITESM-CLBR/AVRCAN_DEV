/****************************************************************** 
* cpu.h
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
 
#ifndef IMPLEMENTATION_INCLUDE_CPU_H_
#define IMPLEMENTATION_INCLUDE_CPU_H_

#ifndef cpu_C_
#define cpu_EXTERN extern
#else
#define cpu_EXTERN
#endif /* cpu_C_ */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/iocan128.h>
#include <board_configs.h>
#define	__AVR_AT90CAN128__	1

/** AT90CAN BOARD XTAL  */
#define OSCSPEED						16000000		/* in Hz */


#endif /* IMPLEMENTATION_INCLUDE_CPU_H_ */
