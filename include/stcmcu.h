/**
 * @file stcmcu.h
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

#ifndef __STCMCU_H
#define __STCMCU_H

/*********************
*      INCLUDES
*********************/
#include "stc8_keil.h"


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <intrins.h>

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
