/****************************************************************** 
 * can_midleware.c
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
#ifndef can_midleware_C_
#define can_midleware_C_
#endif
/**
 * \addtogroup can_midleware_module
 * @{
 */

/******************************************************************/
/*    I N C L U D E   F I L E S                                   */
/******************************************************************/
#include <can_midleware.h>
#include <can_driver.h>
#include <cpu.h>
volatile can_Ir_lock mutex_reg;
volatile can_event	event_can;
volatile can_event	event_can_dummy;
volatile MBox_type mail_box_no;
volatile CanMW_MBox test_01;

#define Event_Set_ISR()			event_can=1

#define Set_Event_to_ISRAPP()		event_can_dummy=1
#define Clr_Event_to_ISRAPP()		event_can_dummy=0
#define Get_Event_to_ISRAPP()		(event_can_dummy)

#define CAN_MIDLEWARE_RX_MESSAGES_FILL_ON_INT	1
/*******************************************************************************************/
/*    M A C R O S                                                                          */
/*******************************************************************************************/
void CanMw_MailBox_Rx_Handler(MBox_type mail_box_no){
		can_dlc_type dlcw_reg=0;
		can_dlc_type j=0;
		uint8_t place=0;
		can_message_data candata=0;

		dlcw_reg=can_get_dlc();
		test_01.msg->dlc=dlcw_reg;
		test_01.msg->message_id=Get_CAN_ID();
		for(j=0; j<dlcw_reg; j++){
			place=Can_Get_FifoPosition();
			candata=CANMSG;
			test_01.msg->data[place]=candata;
		}
}
void CanMW_ReceivedRxHandle(void){
	mail_box_no=can_highest_priority_mob();

	#if CAN_MIDLEWARE_RX_MESSAGES_FILL_ON_INT == 1
	  CanMw_MailBox_Rx_Handler(mail_box_no);
	  Event_Set_ISR();
	#else
	  Set_Event_to_ISRAPP();
	#endif
}

void CanMw_Update_App(void){
   #if CAN_MIDLEWARE_RX_MESSAGES_FILL_ON_INT == 1

   #else
   if(Get_Event_to_ISRAPP()){
    CanMw_MailBox_Rx_Handler(mail_box_no);
    Event_Set_ISR();
   }
   #endif
}

void CanMW_APP_Init(void){
	event_can=0;
	event_can_dummy=0;
}
void CAN_Lib_Get_Errors(void){

}
void CanMW_InitMail_Box(MBox_type mailbox_num, CAN_Mode_type operation_mode,CanMw_Message	*msg_ptr){
	test_01.msg=msg_ptr;
}
void CanMW_set_mutex(can_Ir_lock state){
	mutex_reg=state;
}
can_Ir_lock CanMW_get_mutex(void){
	return mutex_reg;
}

can_event CanMW_Event_Get(void){
	return event_can;
}
void CanMW_Event_Clean(void){
	event_can=0;
}
/*******************************************************************************************/
/*    F U N C T I O N   P R O T O T Y P E S                                                */
/*******************************************************************************************/

/**
 * @}
 */
