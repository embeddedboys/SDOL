/**
 * @file gpio_i2c.h
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

#ifndef __GPIO_I2C_H
#define __GPIO_I2C_H

/*********************
*      INCLUDES
*********************/
#ifndef STCMCU_H
    #include "stcmcu.h"
#endif

/*********************
 *      DEFINES
 *********************/
sbit GPIO_I2C_SCL = P3 ^ 2;
sbit GPIO_I2C_SDA = P3 ^ 3;


/**********************
*      TYPEDEFS
**********************/
typedef struct {
    uint8_t lock;
} gpio_i2c_handle_t;

typedef struct {
    uint32_t speed;
} gpio_i2c_config_t;

/**********************
*      STRUCT
**********************/

/**********************
* GLOBAL PROTOTYPES
**********************/
void gpio_i2c_init();
void gpio_i2c_start();
uint8_t gpio_i2c_revack();
void gpio_i2c_sndack();
void gpio_i2c_sndnack();
void gpio_i2c_stop();
uint8_t gpio_i2c_readbyte();
void gpio_i2c_sendbyte( uint8_t byte_in );

/**********************
*      MACROS
**********************/

#endif
