/****************************************************************** 
* watchdog.h
* Created on: Jul 13, 2015
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
 
#ifndef IMPLEMENTATION_INCLUDE_WATCHDOG_H_
#define IMPLEMENTATION_INCLUDE_WATCHDOG_H_

#ifndef watchdog_C_
#define watchdog_EXTERN extern
#else
#define watchdog_EXTERN
#endif /* watchdog_C_ */

/* Included Headers */

#include <cpu.h>
#include <stdint.h>

//*********************************************************
//Watchdog Timer Prescale Select
//*********************************************************
// [WDP2] [WDP1] [WDP0]  [WDT Osc Cycles]     [3.0V]     [5.0V]
//     0      0      0    16K cycles 		  17.1 ms    16.3 ms
//     0      0      1    32K cycles 		  34.3 ms    32.5 ms
//     0      1      0    64K cycles 		  68.5 ms    65 ms
//     0      1      1    32/64K cycles 	  0.14 s     0.13 s
//     1      0      0    256K cycles 		  0.27 s     0.26 s
//     1      0      1    512K cycles 		  0.55 s     0.52 s
//     1      1      0    1,024K cycles 	  1.1 s      1.0 s
//     1      1      1    2,048K cycles       2.2 s      2.1  
//watchdog_EXTERN	


#if POWER_BOARD_LEVEL == CPU_POWER_5V ||  POWER_BOARD_LEVEL == CPU_POWER_3V3

#if POWER_BOARD_LEVEL == CPU_POWER_5V
 typedef enum{
   WDT_TIME_16_3MS=0,
   WDT_TIME_32_5MS,
   WDT_TIME_65MS,
   WDT_TIME_0_13S,
   WDT_TIME_0_26S,
   WDT_TIME_0_52S,
   WDT_TIME_1_0S,
   WDT_TIME_2_1S
 }WATCHDOG_COMMON_TIMES;
#endif

#if POWER_BOARD_LEVEL == CPU_POWER_3V3
 typedef enum{
   WDT_TIME_17_1MS=0,
   WDT_TIME_34_3MS,
   WDT_TIME_68_5MS,
   WDT_TIME_0_14S,
   WDT_TIME_0_27S,
   WDT_TIME_0_55S,
   WDT_TIME_1_1S,
   WDT_TIME_2_2S
 };
#endif

#else

#error "Please Define POWER_BOARD_LEVEL in Config CPU"

#endif


watchdog_EXTERN void watchdog_off(void);
watchdog_EXTERN void wdt_reset(void);

#endif/* IMPLEMENTATION_INCLUDE_WATCHDOG_H_ */
