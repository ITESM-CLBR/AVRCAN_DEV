/****************************************************************** 
* can_midleware.h
* Created on: Aug 3, 2015
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
 
#ifndef AVRCAN_DEV_IMPLEMENTATION_INCLUDE_CAN_MIDLEWARE_H_
#define AVRCAN_DEV_IMPLEMENTATION_INCLUDE_CAN_MIDLEWARE_H_

#ifndef can_midleware_C_
#define can_midleware_EXTERN extern
#else
#define can_midleware_EXTERN
#endif /* can_midleware_C_ */

/* Included Headers */
#include <stdint.h>
#include <can_types.h>
#define CAN_MW_LEN	(8+1)
typedef enum{
	INTERRUPT_CAN_ML_OFF=0,
	INTERRUPT_CAN_ML_1,
	INTERRUPT_CAN_ML_2,
	INTERRUPT_CAN_ML_3,
	INTERRUPT_CAN_ML_4,
	INTERRUPT_CAN_ML_5,
	INTERRUPT_CAN_ML_6,
}CanMW_Interrupt_level;

typedef struct{
	     CAN_ID_type message_id;
	    can_dlc_type dlc;
	can_message_data data[CAN_MW_LEN];
          can_tstamp stamp;
          Can_timmer_type ttc_timmer;
}CanMw_Message;

typedef struct{
	MBox_type              mailbox;
	CAN_Mode_type             mode;
	CanMw_Message	*		   msg;
}CanMW_MBox;

//can_midleware_EXTERN	




#endif /* AVRCAN_DEV_IMPLEMENTATION_INCLUDE_CAN_MIDLEWARE_H_ */
