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
sbit GPIO_I2C_SCL = P3 ^ 6;
sbit GPIO_I2C_SDA = P3 ^ 7;

/**********************
*      TYPEDEFS
**********************/
typedef struct
{
    uint8_t lock;
} gpio_i2c_handle_t;

typedef struct
{
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
void gpio_i2c_sendbyte(uint8_t byte_in);

/**********************
*      MACROS
**********************/

#endif