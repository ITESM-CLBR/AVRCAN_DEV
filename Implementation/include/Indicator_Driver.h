/****************************************************************** 
* Indicator_Driver.h
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
 
#ifndef IMPLEMENTATION_INCLUDE_INDICATOR_DRIVER_H_
#define IMPLEMENTATION_INCLUDE_INDICATOR_DRIVER_H_

#ifndef Indicator_Driver_C_
#define Indicator_Driver_EXTERN extern
#else
#define Indicator_Driver_EXTERN
#endif /* Indicator_Driver_C_ */

#include <cpu.h>
/* Included Headers */
typedef enum{
	LED_INDICATOR_ON=0,
	LED_INDICATOR_OFF
}Ind_states;



//Indicator_Driver_EXTERN	
Indicator_Driver_EXTERN void Led_Indicators_Init(void);
Indicator_Driver_EXTERN void Led_Tx(uint8_t state);
Indicator_Driver_EXTERN void Led_Rx(uint8_t state);
Indicator_Driver_EXTERN void Led_Err(uint8_t state);

#endif /* IMPLEMENTATION_INCLUDE_INDICATOR_DRIVER_H_ */
