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
/* cost 416ns in STC8G 24MHz IRC */
#define delay() do { \
        _nop_();         \
        _nop_();         \
        _nop_();         \
        _nop_();         \
        _nop_();         \
        _nop_();         \
        _nop_();         \
        _nop_();         \
        _nop_();         \
        _nop_();         \
    }while(0);

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

typedef union
{
    /* Address : 0x8e */
    struct {
        uint8_t S1ST2     : 1;
        uint8_t EXTRAM    : 1;
        uint8_t T2x12     : 1;
        uint8_t T2_C_T    : 1;
        uint8_t T2R       : 1;
        uint8_t UART_M0x6 : 1;
        uint8_t T1x12     : 1;
        uint8_t T0x12     : 1;
    } reg;
    
    uint8_t full;
} stcmcu_register_AUXR_t;

typedef union
{
    /* Address : 0x89 */
    struct {
        uint8_t T0_M0     : 1;
        uint8_t T0_M1    : 1;
        uint8_t T0_C_T     : 1;
        uint8_t T0_GATE    : 1;
        uint8_t T1_M0       : 1;
        uint8_t T1_M1 : 1;
        uint8_t T1_C_T     : 1;
        uint8_t T1_GATE     : 1;
    }reg;

    uint8_t full;
}stcmcu_register_TMOD_t;

/**********************
* GLOBAL PROTOTYPES
**********************/

typedef union {
    /* Address :  */
    struct {
        uint8_t WDT_PS  : 3;
        uint8_t idl_wdt : 1;
        uint8_t clr_wdt : 1;
        uint8_t en_wdt  : 1;
        uint8_t unused  : 1;
        uint8_t wdt_flag: 1;
    } reg;

    uint8_t full;
} stcmcu_register_WDT_CONTR_t;



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
