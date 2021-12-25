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
 * @file system.h
 *
 */
#ifndef __SYSTEM_H
#define __SYSTEM_H

/*********************
*      INCLUDES
*********************/
#ifndef STCMCU_H
#include "stcmcu.h"
#endif

/*********************
 *      DEFINES
 *********************/


/**********************
*      TYPEDEFS
**********************/
struct system_operations {
	void ( *init ) ();
	void ( *reset ) ( uint8_t reset_type );
	void ( *wdt_init ) ();
	void ( *iomux ) ( uint8_t iomux_type );
};


/**********************
*      ENUMS
**********************/
typedef enum {
	SYSTEM_ISP_AREA = 0,
	USER_PROGRAM_AREA,
} software_reset_type;

typedef enum {
	ALL_AS_GPIO = 0,
	P32P33_I2C,
} iomux_config;

/**********************
* GLOBAL PROTOTYPES
**********************/
void register_system_operations ( struct system_operations *opr );
#endif
