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
 * @file oled.h
 *
 */

#ifndef __OLED_H
#define __OLED_H

/*********************
*      INCLUDES
*********************/
#ifndef STCMCU_H
#include "stcmcu.h"
#endif

/*********************
 *      DEFINES
 *********************/

#define OLED_HOR_RES_MAX 128
#define OLED_VER_RES_MAX 64
#define OLED_COLOR_DEPTH 1

#define OFFSET(p, c) ((p)*128 + (c)-1)
#define GET_PAGE_FROM_BUFFER(i) (i / 128)
#define GET_COL_FROM_BUFFER(i) (i % 128)

#define GET_PAGE(pc) (pc >> 16)
#define GET_COL(pc) (pc & 0xFFFF)
#define PAGE_COL(page, col) ((page << 16) | col)
#define PAGE_COL_GET_X(pc) (GET_COL(pc))
#define PAGE_COL_GET_Y(pc) (GET_PAGE(pc) * 8)

#define COMMAND 0x00
#define DATA 0x40

/**********************
 *      TYPEDEFS
 **********************/
#if ((OLED_HOR_RES_MAX <= 255) && (OLED_VER_RES_MAX <= 255))
typedef uint8_t oled_coord_t;
#elif
typedef uint16_t oled_coord_t;
#endif

typedef struct
{
	oled_coord_t x;
	oled_coord_t y;
} oled_point_t;

typedef struct
{
	oled_coord_t x1;
	oled_coord_t y1;
	oled_coord_t x2;
	oled_coord_t y2;
} oled_area_t;

typedef union
{
	struct
	{
		uint8_t blue : 2;
		uint8_t green : 3;
		uint8_t red : 3;
	} chnnel;
	uint8_t full;
} oled_color8_t;

#if (OLED_COLOR_DEPTH == 1)
typedef uint8_t oled_color_t;
#elif
typedef oled_color8_t oled_color_t;
#endif

typedef uint8_t oled_dc_t;
typedef uint8_t oled_size_t;

typedef struct
{
	uint8_t i2c_state;
	uint8_t lock;
}oled_handle_t;
/**********************
 * GLOBAL PROTOTYPES
 **********************/

struct oled_operations
{
	void (*init)();

	/* basic function */
	void (*write_cmd)(oled_dc_t val);
	void (*write_dat)(oled_dc_t val);
	void (*set_pos)(uint8_t page, uint8_t col);
	void (*clear)();
	void (*set_pixel)(uint16_t x, uint16_t y, uint16_t color);
	void (*flush)();
	void (*putchar)(uint8_t page, uint8_t col, uint8_t cha);
	void (*putstring)(uint8_t page, uint8_t col, uint8_t *str);
	void (*putascii)(oled_coord_t x, oled_coord_t y, uint32_t c);
	void (*putascii_string)(oled_coord_t x, oled_coord_t y, uint32_t *str);
	
};
void register_oled_operations(struct oled_operations *opr);

void Glib_Line(int x1, int y1, int x2, int y2);
void Glib_Rectangle(int x1, int y1, int x2, int y2);
#endif /*OLED_H*/