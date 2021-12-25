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
 * @file i2c.h
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

/**********************
*      TYPEDEFS
**********************/

/**********************
*      STRUCT
**********************/


/**********************
* GLOBAL PROTOTYPES
**********************/
void i2c_init();
void i2c_start();
void i2c_sndack();
void i2c_sndnack();
void i2c_stop();
uint8_t i2c_readbyte();
void i2c_sendbyte ( uint8_t byte );

/**********************
*      MACROS
**********************/

#endif /* I2C_H */