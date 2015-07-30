/****************************************************************** 
* can_driver.c
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
#ifndef can_driver_C_
 #define can_driver_C_
#endif
/**
 * \addtogroup can_driver_module
 * @{
 */

/******************************************************************/
/*    I N C L U D E   F I L E S                                   */
/******************************************************************/
#include <can_driver.h>
#include <cpu.h>

/*******************************************************************************************/
/*    M A C R O S                                                                          */
/*******************************************************************************************/

CAN_ID_type Get_CAN_ID(void){
	CAN_ID_type idcan=0;
	uint8_t REG_CANIDT1=0;
	uint8_t REG_CANIDT2=0;

	#if CAN_VERSION_SUPPORTED == CAN_VERSION_2A
	REG_CANIDT1=CANIDT1;
	REG_CANIDT2=CANIDT2;

	idcan=((CAN_ID_type)((REG_CANIDT1 << 3) & 0x7F8)) + ((CAN_ID_type)( 0x07 &(REG_CANIDT2 >> 5)));

	#else
		#error " CAN Identifier Tag Registers V2.0 part B is not supported"
	#endif

	return idcan;
}


void Can_IDMask(CAN_ID_type mask_id){
	uint8_t mask_reg=0;

	mask_reg= (0xFF & (mask_id >> 3));
	mask_reg= (0xE0 & (mask_id << 5));
}

/*******************************************************************************************/
/*    F U N C T I O N   P R O T O T Y P E S                                                */
/*******************************************************************************************/

/**
 * @}
 */
