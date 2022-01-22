/**
 * @file i2c.h
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

#ifndef __I2C_H
#define __I2C_H

/*********************
*      INCLUDES
*********************/
#ifndef STCMCU_H
    #include "stcmcu.h"
#endif

/*********************
 *      DEFINES
 *********************/
#define I2CCFG   (*(unsigned char volatile xdata *)0xfe80)
#define I2CMSCR  (*(unsigned char volatile xdata *)0xfe81)
#define I2CMSST  (*(unsigned char volatile xdata *)0xfe82)
#define I2CSLCR  (*(unsigned char volatile xdata *)0xfe83)
#define I2CSLST  (*(unsigned char volatile xdata *)0xfe84)
#define I2CSLADR (*(unsigned char volatile xdata *)0xfe85)
#define I2CTXD   (*(unsigned char volatile xdata *)0xfe86)
#define I2CRXD   (*(unsigned char volatile xdata *)0xfe87)
#define I2CMSAUX (*(unsigned char volatile xdata *)0xfe88)

/**********************
*      TYPEDEFS
**********************/
typedef struct
{
    uint8_t dat;
}i2c_handle_t;

typedef struct{
    uint8_t config;
}i2c_config_t;

/**********************
*      STRUCT
**********************/


/**********************
* GLOBAL PROTOTYPES
**********************/
void i2c_init();
void i2c_start();
void i2c_revack();
void i2c_sndack();
void i2c_sndnack();
void i2c_stop();
uint8_t i2c_readbyte();
void i2c_sendbyte( uint8_t byte );

/**********************
*      MACROS
**********************/

#endif /* I2C_H */
