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
 * @file tm1650.h
 *
 */
#ifndef __TM1650_H
#define __TM1650_H

/*********************
*      INCLUDES
*********************/
#ifndef STCMCU_H
#include "stcmcu.h"
#endif
#include "gpio_i2c.h"

/*********************
 *      DEFINES
 *********************/
#define TM1650_DISPLAY_REG 0x48

/*********************
 *  GLOBAL VARIABLE
 *********************/
// const unsigned char code tm1650_segment_value[2] = {
// 	0xfe, /* 0 */
// 	0x60, /* 1 */

// };

/**********************
*      TYPEDEFS
**********************/
typedef struct
{

	float temperature;
	float humidity;
	uint8_t checksum;

} tm1650_handle_t;

typedef union
{
	struct
	{
		uint8_t power : 3;
		uint8_t segment_format : 1;
		uint8_t brightness : 4;
	} display_register;
	uint8_t full;

} tm1650_config_t;

/**********************
*      ENUMS
**********************/
typedef enum
{
	TM1650_BRIGHTNESS_LEVEL_8 = 0,
	TM1650_BRIGHTNESS_LEVEL_1 = 1,
	TM1650_BRIGHTNESS_LEVEL_2 = 2,
	TM1650_BRIGHTNESS_LEVEL_3 = 3,
	TM1650_BRIGHTNESS_LEVEL_4 = 4,
	TM1650_BRIGHTNESS_LEVEL_5 = 5,
	TM1650_BRIGHTNESS_LEVEL_6 = 6,
	TM1650_BRIGHTNESS_LEVEL_7 = 7,
} tm1650_brightness_level_t;
typedef enum
{
	TM1650_DISPLAY_POWER_OFF = 0,
	TM1650_DISPLAY_POWER_ON = 1,
} tm1650_display_power_t;

typedef enum
{
	TM1650_SEGMENT_FORMAT_8 = 0,
	TM1650_SEGMENT_FORMAT_7 = 1,
} tm1650_segment_format_t;

typedef enum
{
	TM1650_BIT_1 = 0x68,
	TM1650_BIT_2 = 0x6a,
	TM1650_BIT_3 = 0x6c,
	TM1650_BIT_4 = 0x6e,
} tm1650_bit_selection_t;

typedef enum
{
	TM1650_SEGMENT_VALUE_0 = 0x3f, /* `0` */
	TM1650_SEGMENT_VALUE_1 = 0x06, /* `1` */
	TM1650_SEGMENT_VALUE_2 = 0x5b, /* `2` */
	TM1650_SEGMENT_VALUE_3 = 0x4f, /* `3` */
	TM1650_SEGMENT_VALUE_4 = 0x66, /* `4` */
	TM1650_SEGMENT_VALUE_5 = 0x6d, /* `5` */
	TM1650_SEGMENT_VALUE_6 = 0x7d, /* `6` */
	TM1650_SEGMENT_VALUE_7 = 0x07, /* `7` */
	TM1650_SEGMENT_VALUE_8 = 0x7f, /* `8` */
	TM1650_SEGMENT_VALUE_9 = 0x6f, /* `9` */

} tm1650_segment_value_t;
/**********************
*      STRUCT
**********************/
struct tm1650_operations
{
	void (*init)();
	void (*deinit)();

	void (*write_register)(uint8_t addr, uint8_t dat);

	void (*set_brightness)(tm1650_brightness_level_t level);
	void (*set_display)(tm1650_display_power_t state);
	void (*set_segment_format)(tm1650_segment_format_t format);

	void (*show_bit)(tm1650_bit_selection_t which, tm1650_segment_value_t value);
};

/**********************
* GLOBAL PROTOTYPES
**********************/
void register_tm1650_operations(struct tm1650_operations *opr);
#endif
