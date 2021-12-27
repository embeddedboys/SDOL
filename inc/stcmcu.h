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
#include <reg51.h>
#include <stdlib.h>
#include <intrins.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

/*********************
 *      DEFINES
 *********************/
/* ((void(code *)(void))0x00)(); */

#define GROUP(g)(g>>4)
#define PIN(p)(p&0x0f)
#define GROUP_PIN(g,p)( (g<<4) | p)

#define CKSEL      (*(volatile unsigned char xdata *)0xfe00)
#define CLKDIV     (*(volatile unsigned char xdata *)0xfe01)
#define HIRCCR     (*(volatile unsigned char xdata *)0xfe02)
#define XOSCCR     (*(volatile unsigned char xdata *)0xfe03)
#define IRC32KCR   (*(volatile unsigned char xdata *)0xfe04)
#define MCLKOCR    (*(volatile unsigned char xdata *)0xfe05)

#define P3PU       (*(volatile unsigned char xdata *)0xfe14)
#define P3NCS      (*(volatile unsigned char xdata *)0xfe1b)
#define P3SR       (*(volatile unsigned char xdata *)0xfe23)
#define P3DR       (*(volatile unsigned char xdata *)0xfe2b)
#define P3IE       (*(volatile unsigned char xdata *)0xfe33)

#define P2PU       (*(volatile unsigned char xdata *)0xfe12)

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


/*********************
*      SFR
*********************/
/* pin state register list(Px) */

/* Control register_ of STC8G inside IRC clock. */
sfr IRCBAND  =  0x9d;   /*  */
sfr LIRTRIM  =  0x9e;
sfr IRTRIM   =  0x9f;

sfr P0M1 = 0x94;
sfr P0M0 = 0x95;
sfr P1M1 = 0x91;
sfr P1M0 = 0x92;
sfr P2M1 = 0x95;
sfr P2M0 = 0x96;
sfr P3M1 = 0xb1;
sfr P3M0 = 0xb2;
sfr P4M1 = 0xb3;
sfr P4M0 = 0xb4;
sfr P_SW2 = 0xba;
/*
* System Reset
*/
/* Hardware & software reset. */
sfr WDT_CONTR = 0xc1;   /* Watchdog timer. */
sfr IAP_CONTR = 0xc7;   /* IAP control register_. */
sfr RSTCFG    = 0xff;   /* Reset configuration register_.  */

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
