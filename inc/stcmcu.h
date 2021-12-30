// Copyright (C) 2021 jensenhua(writeforever@foxmail.com)
// 
// This file is part of sdol.
// 
// sdol is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
// 
// sdol is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with sdol.  If not, see <http://www.gnu.org/licenses/>.


/**
 * @file stcmcu.h
 *
 */

#ifndef __STCMCU_H
#define __STCMCU_H

/*********************
*      INCLUDES
*********************/
#include "stc8_keil.h"


#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*********************
 *      DEFINES
 *********************/

/**********************
*      TYPEDEFS
**********************/
typedef char    int8_t;
typedef short   int16_t;
typedef int     int32_t;

typedef unsigned char   uint8_t;
typedef unsigned short  uint16_t;
typedef unsigned int    uint32_t;

typedef uint8_t grp_pin_t;

/**********************
* GLOBAL PROTOTYPES
**********************/

typedef union {
	struct {
		uint8_t wdt_ps  : 3;
		uint8_t idl_wdt : 1;
		uint8_t clr_wdt : 1;
		uint8_t en_wdt  : 1;
		uint8_t unused  : 1;
		uint8_t wdt_flag: 1;
	} ch;
	uint8_t full;
} wdt_contr;



typedef union {
	struct {
		uint8_t unused: 4;
		uint8_t cmd_fail: 1;
		uint8_t swrst: 1;
		uint8_t swbs: 1;
		uint8_t iapen: 1;
	} ch;
	uint8_t full;
} iap_contr;

typedef union {
	struct {
		uint8_t lvds: 2;
		uint8_t unused1: 2;
		uint8_t p54rst: 1;
		uint8_t unused2: 1;
		uint8_t enlvr: 1;
		uint8_t unused3: 1;
	} ch;
	uint8_t full;
} rstcfg; /* Address: 0XFF */

typedef union {
	struct {
		uint8_t unused: 2;
		uint8_t spi_s: 2;
		uint8_t ccp_s: 2;
		uint8_t s1_s: 2;
	} ch;
	uint8_t full;
} p_sw1; /* Address: 0xA2 */

typedef union {
	struct {
		uint8_t s2_s: 1;
		uint8_t s3_s: 1;
		uint8_t s4_s: 1;
		uint8_t cmpo_s: 1;
		uint8_t i2c_s: 2;
		uint8_t unused: 1;
		uint8_t eaxfr: 1;
	} ch;
	uint8_t full;
} p_sw2;

/*********************
*       ENUM
*********************/
typedef enum {
	STANDARD_IO = 0,
	PUSH_PULL_OUTPUT,
	HIGH_RESISTANCE_INPUT,
	OPEN_DRAIN,
} io_modes;

/*********************
*      PIN DEFINES
*********************/

#endif
