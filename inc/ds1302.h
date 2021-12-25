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

/**
 * @file ds1302.h
 *
 */
#ifndef __DS1302_H
#define __DS1302_H

/*********************
* Documents for ds1302
*********************/
/**
	3-wire synchronous serial communication
	Vcc1 and Vcc2 dual power supply
	
	7   6      5   4   3   2   1   0
	1 RAM/CK#  A4  A3  A2  A1  A0  RD/WR#
	
	CLK
	DAT
	RST
*/

/*********************
*      INCLUDES
*********************/
#ifndef STCMCU_H
#include "stcmcu.h"
#endif

/*********************
 *      DEFINES
 *********************/
sbit DS1302_CLK = P2 ^ 0;
sbit DS1302_DAT = P2 ^ 1;
sbit DS1302_RST = P2 ^ 2;
#define nop() {_nop_();_nop_();_nop_();_nop_();}

/**********************
*      TYPEDEFS
**********************/
typedef struct
{

	float temperature;
	float humidity;
	uint8_t checksum;

	//ds1302_state_enum state;
	//ds1302_lock_enum lock;

} ds1302_handle_t;

struct ds1302_operations
{
	void (*init)();
	void (*deinit)();
	uint8_t (*read_register)(uint8_t command);
	void (*write_register)(uint8_t command, uint8_t byte);
};

/**********************
*      ENUMS
**********************/

/**********************
* GLOBAL PROTOTYPES
**********************/
void register_ds1302_operations(struct ds1302_operations *opr);
#endif
