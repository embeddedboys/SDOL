/**
 * Copyright (C) 2021 jensenhua(writeforever@foxmail.com)
 * 
 * This file is part of sdol.
 * 
 * sdol is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 * 
 * sdol is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with sdol.  If not, see <http://www.gnu.org/licenses/>.
 */


#include "system.h"

/**
* @description
*
* @param
* @return
*/
void system_init()
{

	CKSEL = 0x00;   /* Chosen inside high precision IRC */

	CLKDIV = 0x00;  /* Configure system clock div */

	HIRCCR |= ( 1 << 7 ); /* Enable inside high precision IRC */

	IRCBAND |= ( 1 << 0 ); /* 33MHz channle was chosen */


}

/**
* @description
*
* @param
* @return
*/
void system_reset ( uint8_t reset_type )
{
	iap_contr *con;
	con = 0xc7;

	switch ( reset_type ) {
		case SYSTEM_ISP_AREA:
			con->ch.swbs = 1;
			con->ch.swrst = 1;
			break;

		case USER_PROGRAM_AREA:
			con->ch.swbs = 0;
			con->ch.swrst = 1;
			break;

		default:
			con->ch.swbs = 1;
			con->ch.swrst = 1;
			break;
	}

}

/**
* @description
*
* @param
* @return
*/
void system_wdt_init()
{
	wdt_contr *con;
	con = 0xc1;

	con->ch.en_wdt = 1;     /* enable watchdog timer */
	con->ch.clr_wdt = 1;    /* clear the watchdog timer, hardware will do this automatically */
	/*
	* watchdog timer clock frequency dividing
	* overflow time = 12*32768*2^(wdt_ps+1)/sysclk
	*/
	con->ch.wdt_ps = ( 3 << 1 ); /* div:128;overflow time:1.44s when sysclk=35MHz */

}

/**
* @description
*
* @param
* @return
*/
void __system_io_mode ( grp_pin_t gp, uint8_t mode )
{
	uint8_t group, pin;

	group = GROUP ( gp );
	pin   = PIN ( gp );

	switch ( group ) {
		case 0: /* Group P0 */
			break;

		case 1: /* Group P1 */
			break;

		case 2: /* Group P2 */
			break;

		case 3: /* Group P3 */
			P3M1 &= ~ ( 1 << pin );
			P3M0 &= ~ ( 1 << pin );

			/*P3M1 |= ( ( mode >> 1 ) << pin );
			P3M0 |= ( mode & 0xfe );*/
			break;

		default:
			break;
	}
}

/**
* @description
*
* @param
* @return
*/
void system_iomux ( uint8_t iomux_type )
{


	switch ( iomux_type ) {
		case P32P33_I2C:
			__system_io_mode ( GROUP_PIN ( 3, 2 ), STANDARD_IO );
			__system_io_mode ( GROUP_PIN ( 3, 3 ), STANDARD_IO );
			P_SW2 = ( 1 << 7 | 3 << 4 );
			break;

		default:    /* As default. Configure P3.2 P3.3 pin as GPIO */
			__system_io_mode ( GROUP_PIN ( 3, 2 ), STANDARD_IO );
			__system_io_mode ( GROUP_PIN ( 3, 3 ), STANDARD_IO );
			break;
	}
}

/**
* @description
*
* @param
* @return
*/
void register_system_operations ( struct system_operations *opr )
{
	opr->init = system_init;
	opr->reset = system_reset;
	opr->wdt_init = system_wdt_init;
	opr->iomux = system_iomux;
}