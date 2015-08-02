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
/**
 * \addtogroup can_driver_macros
 * @{
 */
/* Included Headers */
#include <stdint.h>
#include <can_types.h>

typedef enum{
	CAN_VERSION_2A=0,
	CAN_VERSION_2B
}CAN__STD_PROTOCOL;

typedef enum{
	MOB_DISABLED=0,
	MOB_TX_DATA_FRAME,
	MOB_TX_REMOTE_FRAME,
	MOB_RX_DATA_FRAME,
	MOB_RX_REMOTE_FRAME,
	MOB_RX_REMO_FRAME_THEN_TX_DATA_FRAME_REPLY,
	MOB_FRAME_BUFFER_MODE
}MOB_MODES;

typedef enum{
	MAIL_BOX_DISABLE=0,
	MAIL_BOX_ENABLE_TX,
	MAIL_BOX_ENABLE_RX,
	MAIL_BOX_FRAME_BUFFER_RECEPTION
}MOB_SIMPLE_MODE;

//can_driver_EXTERN	
#define CAN_VERSION_SUPPORTED CAN_VERSION_2A


can_driver_EXTERN CAN_ID_type Get_CAN_ID(void);
can_driver_EXTERN CAN_ID_type Get_Mask_ID(void);
can_driver_EXTERN void Can_Set_MSG_ID(CAN_ID_type input_id);
can_driver_EXTERN void Can_Set_IDMask(CAN_ID_type mask_id);

// INTERRUPTS SECTION
#define ENABLE_ALL_INTERRUPTS()						CANGIE |= (1<<ENIT)
#define ENABLE_BUS_OFF_INTERRUPT()					CANGIE |= (1<<ENBOFF)
#define ENABLE_CAN_RECEIVE_INTERRUPT()				CANGIE |= (1<<ENRX)
#define ENABLE_CAN_TX_INTERRUPT()					CANGIE |= (1<<ENTX)
#define ENABLE_MOB_ERRORS_INTERRUPT()				CANGIE |= (1<<ENERR)
#define ENABLE_FRAME_BUFFER_INTERRUPT()				CANGIE |= (1<<ENBX)
#define ENABLE_GENERAL_ERRORS_INTERRUPT()			CANGIE |= (1<<ENERG)
#define ENABLE_CAN_TIMER_OVERRUN_INTERRUPT()		CANGIE |= (1<<ENOVRT)

#define DISABLE_ALL_INTERRUPTS()					CANGIE = (CANGIE & (~(1<<ENIT)   )
#define DISABLE_BUS_OFF_INTERRUPT()					CANGIE = (CANGIE & (~(1<<ENBOFF) )
#define DISABLE_CAN_RECEIVE_INTERRUPT()				CANGIE = (CANGIE & (~(1<<ENRX)   )
#define DISABLE_CAN_TX_INTERRUPT()					CANGIE = (CANGIE & (~(1<<ENTX)   )
#define DISABLE_MOB_ERRORS_INTERRUPT()				CANGIE = (CANGIE & (~(1<<ENERR)  )
#define DISABLE_FRAME_BUFFER_INTERRUPT()			CANGIE = (CANGIE & (~(1<<ENBX)   )
#define DISABLE_GENERAL_ERRORS_INTERRUPT()			CANGIE = (CANGIE & (~(1<<ENERG)  )
#define DISABLE_CAN_TIMER_OVERRUN_INTERRUPT()		CANGIE = (CANGIE & (~(1<<ENOVRT) )



/** This auto resettable bit only resets the CAN controller. */
#define Reset_Can_Controller()			CANGCON |= (1 << SWRES)
#define Enable_Can_Controller()			CANGCON |= (1 << ENASTB)

/**********************************************************************************//**
 *  \param[in] param Description of the  parameter of the function.
 *  \param[out] param Description of the  parameter of the function.
 *  \return 0
 *  \brief Module Description
 *  \see See more information Here !!
 *  \note First Implementation 6:05:51 PM Jul 30, 2015
 *  \warning Warning.
 *  \author Author
 ****************************************************************************************/
#define DLC_MSK     ((1<<DLC3)|(1<<DLC2)|(1<<DLC1)|(1<<DLC0))            //! MaSK for Data Length Coding
 
#define Standby_Can_Controller()		 CANGCON = ( CANGCON & (~(1 << ENASTB)) )
#define Can_Get_FifoPosition()	   		(CANPAGE & 0x07)
#define Get_MailBox()			   		((CANPAGE >> 4) & 0x0F)
#define Set_MailBox(mbox)				(CANPAGE=(mbox << 4))

//Mail Box Operation
#define Can_Mob_ClrStatus_Flags()			(CANSTMOB=0x00)
#define Can_Mob_get_DLCW()					(CANSTMOB & (1<<DLCW))
#define Can_Mob_TX_OK()						(CANSTMOB & (1<<TX_OK))
#define Can_Mob_RX_OK()						(CANSTMOB & (1<<RX_OK))
#define Can_Mob_BitError()					(CANSTMOB & (1<<BERR))
#define Can_Mob_Disable()					(CANCDMOB=0x00)
#define can_config_mail_box_mode(mode)		(CANCDMOB |= (mode<<CONMOB0))
#define Can_set_dlc(dlc)  					(CANCDMOB |= (dlc))
#define Can_get_dlc()      					((CANCDMOB &  DLC_MSK)     >> DLC0   )
//#define Can_config_rx() 		CANCDMOB |= (MAIL_BOX_ENABLE_RX << CONMOB_OFFSET);
/**
 * @}
 */

#endif /* AVRCAN_DEV_IMPLEMENTATION_INCLUDE_CAN_DRIVER_H_ */
