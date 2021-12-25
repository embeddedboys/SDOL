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

#ifndef __UTILS_H
#define __UTILS_H

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
*      ENUMS
**********************/

/**********************
* GLOBAL PROTOTYPES
**********************/
int32_t simple_atoi(char s[]);

uint8_t simple_lower(uint8_t c);
uint8_t simple_isdigit(uint8_t c);

#endif