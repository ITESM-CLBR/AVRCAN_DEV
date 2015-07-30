/****************************************************************** 
* can_driver.h
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
 
#ifndef AVRCAN_DEV_IMPLEMENTATION_INCLUDE_CAN_DRIVER_H_
#define AVRCAN_DEV_IMPLEMENTATION_INCLUDE_CAN_DRIVER_H_

#ifndef can_driver_C_
#define can_driver_EXTERN extern
#else
#define can_driver_EXTERN
#endif /* can_driver_C_ */

/* Included Headers */
#include <stdint.h>
#include <can_types.h>

typedef enum{
	CAN_VERSION_2A=0,
	CAN_VERSION_2B
};
//can_driver_EXTERN	
#define CAN_VERSION_SUPPORTED CAN_VERSION_2A



#endif /* AVRCAN_DEV_IMPLEMENTATION_INCLUDE_CAN_DRIVER_H_ */
