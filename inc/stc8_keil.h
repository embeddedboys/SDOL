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

#include <reg51.h>

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


/*********************
*      SFR
*********************/
/* pin state register list(Px) */

/* Control register_ of STC8G inside IRC clock. */
sfr IRCBAND  =  0x9d;
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
