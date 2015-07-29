/****************************************************************** 
* Indicator_Driver.c
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
*� 2015
*****************************************************************/ 
#ifndef Indicator_Driver_C_
 #define Indicator_Driver_C_
#endif
/**
 * \addtogroup Indicator_Driver_module
 * @{
 */

/******************************************************************/
/*    I N C L U D E   F I L E S                                   */
/******************************************************************/
#include <Indicator_Driver.h>


/*******************************************************************************************/
/*    M A C R O S                                                                          */
/*******************************************************************************************/


/*******************************************************************************************/
/*    F U N C T I O N   P R O T O T Y P E S                                                */
/*******************************************************************************************/
typedef struct{
	uint8_t can_tx_led_indicator;
	uint8_t can_rx_led_indicator;
	uint8_t can_err_led_indicator;
}LED_Indicators_struct;

volatile LED_Indicators_struct Ind_led;

void Led_Indicators_Init(void){
	memset(&Ind_led,0,sizeof(Ind_led));
}

void Led_Tx(uint8_t state){
	Ind_led.can_tx_led_indicator=state;
	if(1){

	}else{

	}
}

void Led_Rx(uint8_t state){
	Ind_led.can_rx_led_indicator=state;
	if(1){

	}else{

	}
}

void Led_Bussy(uint8_t state){
	Ind_led.can_err_led_indicator=state;
	if(1){

	}else{

	}
}

/**
 * @}
 */
