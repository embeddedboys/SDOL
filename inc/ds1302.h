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
// #define DS1302_CLK GROUP_PIN(2, 0)
// #define DS1302_DAT GROUP_PIN(2, 1)
// #define DS1302_RST GROUP_PIN(2, 2)
#define nop()    \
	{            \
		_nop_(); \
		_nop_(); \
		_nop_(); \
		_nop_(); \
	}

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

typedef struct
{
	uint8_t year;
	uint8_t month;
	uint8_t day;
	uint8_t hour;
	uint8_t minute;
	uint8_t second;

	uint8_t format_hour;

} ds1302_config_t;

struct ds1302_operations
{
	void (*init)();
	void (*deinit)();
	uint8_t (*read_register)(uint8_t command);
	void (*write_register)(uint8_t command, uint8_t byte);

	/* getter and setters for each value*/
	uint8_t (*get_year)();
	uint8_t (*get_month)();
	uint8_t (*get_day)();
	uint8_t (*get_hour)();
	uint8_t (*get_minute)();
	uint8_t (*get_second)();

	void (*set_year)(uint8_t year);
	void (*set_month)(uint8_t month);
	void (*set_day)(uint8_t day);
	void (*set_hour)(uint8_t hour);
	void (*set_minute)(uint8_t minute);
	void (*set_second)(uint8_t second);

	/* getter  and setter for config */
	ds1302_config_t (*get_configs)();
	uint8_t (*set_configs)(ds1302_config_t config);

	uint8_t (*set_trickle_charge)(uint8_t function);
};

/**********************
*      ENUMS
**********************/
typedef enum
{
	DS1302_TRICKLE_CHARGE_DISABLED = 0,
	DS1302_TRICKLE_CHARGE_1_DIODE_2K,
	DS1302_TRICKLE_CHARGE_1_DIODE_4K,
	DS1302_TRICKLE_CHARGE_1_DIODE_8K,
	DS1302_TRICKLE_CHARGE_2_DIODE_2K,
	DS1302_TRICKLE_CHARGE_2_DIODE_4K,
	DS1302_TRICKLE_CHARGE_2_DIODE_8K,
	DS1302_TRICKLE_CHARGE_INITIAL_POWER_ON_STATE,
} ds1032_trickle_charge_mode;

/**********************
* GLOBAL PROTOTYPES
**********************/
void register_ds1302_operations(struct ds1302_operations *opr);
#endif
