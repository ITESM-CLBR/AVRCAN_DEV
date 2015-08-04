/****************************************************************** 
 * main.c
 * Created on: Jul 14, 2015
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
#ifndef main_C_
#define main_C_
#endif
/**
 * \addtogroup main_module
 * @{
 */

/******************************************************************/
/*    I N C L U D E   F I L E S                                   */
/******************************************************************/
#include <cpu.h>
#include <usart.h>
#include <watchdog.h>
#include <hardware_init.h>
#include <can_driver.h>
#include <can_midleware.h>
#include <avr/interrupt.h> 
/*******************************************************************************************/
/*    M A C R O S                                                                          */
/*******************************************************************************************/
volatile uint8_t dlcw=0;
volatile uint8_t j=0;
volatile uint8_t place=0;
volatile uint8_t datacan[10];
volatile uint8_t candata;
volatile CAN_ID_type my_id=0;

volatile CanMw_Message Message_A;
volatile CanMw_Message Message_B;

#pragma vector=SIG_CAN_INTERRUPT1
ISR(SIG_CAN_INTERRUPT1)
{
	CanMW_set_mutex(MUTEX_LOCK_CHANNEL);
	CanMW_ReceivedRxHandle();
	CanMW_set_mutex(MUTEX_RELEASE_CHANNEL);
}

/*******************************************************************************************/
/*    F U N C T I O N   P R O T O T Y P E S                                                */
/*******************************************************************************************/
int  main(void){
	char printer[20];
	uint8_t icdlc=0;
	CAN_Main_Board_Init();
	usart_init((uint8_t)BAUD_RATE_115_2k);
	Print_Buffer("Test 1  \r\n");

	memset(&Message_A,0,sizeof(Message_A));
	Can_Driver_Init();
	CanMW_APP_Init();

	CanMW_InitMail_Box(1,0,&Message_A);
	CanMW_InitMail_Box(0,0,&Message_B);

	Can_Configure_MailBox(1,MAIL_BOX_ENABLE_RX,6,(CAN_ID_type)0x188,(CAN_ID_type)0x07FF,1);
	Can_Configure_MailBox(0,MAIL_BOX_ENABLE_RX,8,(CAN_ID_type)0x294,(CAN_ID_type)0x07FF,1);

	ENABLE_CAN_RECEIVE_INTERRUPT();
	ENABLE_ALL_INTERRUPTS();
	sei();

	while(1){
		watchdog_reset();

		CanMw_Update_App();

		if(CanMW_Event_Get()){
			watchdog_reset();

			if(Message_A.data[3] == 0x08){
				Led_Tx(0);
			}else{
				Led_Tx(1);
			}

			if(Message_B.data[0] == 0x20){
				Led_Rx(0);
			}else{
				Led_Rx(1);
			}
			
			/*
					if(datacan[3]==0x08 &&  my_id == 0x188){
						Led_Tx(0);
					}else{
						Led_Tx(1);
					}
					if(datacan[0]==0x04 &&  my_id == 0x164){
						Led_Err(0);
					}else{
						Led_Err(1);
					}
			 */
			Can_Configure_MailBox(1,MAIL_BOX_ENABLE_RX,6,(CAN_ID_type)0x188,(CAN_ID_type)0x07FF,1);
			Can_Configure_MailBox(0,MAIL_BOX_ENABLE_RX,8,(CAN_ID_type)0x294,(CAN_ID_type)0x07FF,1);

			CanMW_Event_Clean();
			ENABLE_CAN_RECEIVE_INTERRUPT();
			ENABLE_ALL_INTERRUPTS();
			sei();
		}

	}

	return 0;
}
/**
 * @}
 */
