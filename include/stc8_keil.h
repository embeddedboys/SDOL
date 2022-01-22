/**
 * @file stc8_keil.h
 * @author Zheng Hua (writeforever@foxmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-01-22
 * 
 * MIT License
 * 
 * Copyright 2022 Zheng Hua(writeforever@foxmail.com)
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 * 
 */

#ifndef __STC8_KEIL_H
#define __STC8_KEIL_H

#include <STC8G.h>

/*********************
 *      DEFINES
 *********************/
/* ((void(code *)(void))0x00)(); */
#define GROUP(g)(g>>4)
#define PIN(p)(p&0x0f)
#define GROUP_PIN(g,p)( (g<<4) | p)

#if 0
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
#endif

#endif