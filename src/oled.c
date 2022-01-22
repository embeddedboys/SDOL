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

#include "oled.h"
#include "oledfont.h"
#include "i2c.h"

static uint8_t oled_buffer[1024]; /* oled display buffer */

/**
*@description
*@param
*@return
*/
void oled_write_cmd(oled_dc_t val)
{
	i2c_start();
	i2c_sendbyte(0x78); //slave address
	i2c_sndack();
	i2c_sendbyte(COMMAND);
	i2c_sndack();
	i2c_sendbyte(val);
	i2c_sndack();
	i2c_stop();
}

/**
*@description
*@param
*@return
*/
void oled_write_dat(oled_dc_t val)
{
	i2c_start();
	i2c_sendbyte(0x78);
	i2c_sndack();
	i2c_sendbyte(DATA);
	i2c_sndack();
	i2c_sendbyte(val);
	i2c_sndack();
	i2c_stop();
}

/**
*@description
*@param
*@return
*/
static void oled_set_addr_mode(int mode)
{
	oled_write_cmd(0x20);

	switch (mode)
	{
	case 0:
		oled_write_cmd(0x00);
		break; // Horizontal Addressing Mode

	case 1:
		oled_write_cmd(0x01);
		break; // Vertical Addressing Mode

	case 2:
		oled_write_cmd(0x02);
		break; // Page Addressing Mode

	case 3:
		oled_write_cmd(0x03);
		break; // Invalid

	default:
		oled_write_cmd(0x02);
		break; // Page Addressing Mode
	}
}

/**
*@description
*@param
*@return
*/
void oled_set_pos(uint8_t page, uint8_t col)
{
	oled_write_cmd(0xb0 + page);

	oled_write_cmd(0x00 | (col & 0x0f));
	oled_write_cmd(0x10 | (col >> 4));
}

/**
*@description
*@param
*@return
*/
void oled_flush()
{
	uint8_t page, col;

	for (page = 0; page < 8; page++)
		for (col = 0; col < 128; col++)
		// if (oled_buffer[OFFSET(page, col)] != 0x00)
		{
			oled_set_pos(page, col);
			oled_write_dat(oled_buffer[OFFSET(page, col)]);
		}
}

/**
*@description
*@param
*@return
*/
void oled_clear()
{
	uint8_t page, col;

	for (page = 0; page < 8; page++)
		for (col = 0; col < 128; col++)
			if (oled_buffer[OFFSET(page, col)] > 0x00)
			{
				oled_set_pos(page, col);
				oled_write_dat(0);
			}
	// memset(oled_buffer, 0x0, 1024);
	// oled_flush();
}

/**
*@description
*@param
*@return
*/
void oled_init(void)
{
	oled_write_cmd(0xAE); /*display off*/
	oled_write_cmd(0x00); /*set lower column address*/
	oled_write_cmd(0x10); /*set higher column address*/
	oled_write_cmd(0x40); /*set display start line*/
	oled_write_cmd(0xB0); /*set page address*/
	oled_write_cmd(0x81); /*contract control*/
	oled_write_cmd(0x66); /*128*/
	oled_write_cmd(0xA1); /*set segment remap*/
	oled_write_cmd(0xA6); /*normal / reverse*/
	oled_write_cmd(0xA8); /*multiplex ratio*/
	oled_write_cmd(0x3F); /*duty = 1/64*/
	oled_write_cmd(0xC8); /*Com scan direction*/
	oled_write_cmd(0xD3); /*set display offset*/
	oled_write_cmd(0x00);
	oled_write_cmd(0xD5); /*set osc division*/
	oled_write_cmd(0x80);
	oled_write_cmd(0xD9); /*set pre-charge period*/
	oled_write_cmd(0x1f);
	oled_write_cmd(0xDA); /*set COM pins*/
	oled_write_cmd(0x12);
	oled_write_cmd(0xdb); /*set vcomh*/
	oled_write_cmd(0x30);
	oled_write_cmd(0x8d); /*set charge pump enable*/
	oled_write_cmd(0x14);
	oled_write_cmd(0xAF); /*display ON*/

	oled_set_addr_mode(2);
	oled_clear();
}

/**
 * @brief 
 * 
 */
void oled_device_init(void)
{
	int count = 0;
	oled_init();

	for (; count < 1024; count++)
	{
		oled_buffer[count] = 0x00;
	}
}

/**
 * @brief 
 * 
 * @param x 
 * @param y 
 * @param color 
 */
void oled_set_pixel(oled_coord_t x, oled_coord_t y, oled_color_t color)
{
	uint8_t page, page_left;
	uint8_t *pen = oled_buffer;

#ifdef OLED_COORD_CHECK
	if ((x >= 0 && x < OLED_HOR_RES_MAX) && (y >= 0 && y < OLED_VER_RES_MAX))
	{
#endif
		page = y / 8;
		page_left = y % 8 == 0 ? 0 : y % 8;

		if (color)
		{
			pen[OFFSET(page, x)] |= (1 << page_left);
		}
		else
		{
			pen[OFFSET(page, x)] &= ~(1 << page_left);
		}

#ifdef OLED_CHECK_VAILD
	}
#endif

	/*oled_set_pos(page, x);
	oled_write_dat(oled_buffer[offset]);*/
}

/**
 * @brief 
 * 
 * @param area 
 * @param color 
 */
void oled_clear_area(oled_area_t *area, oled_color_t color)
{
	int32_t x, y;
	for (y = area->y1; y <= area->y2; y++)
	{
		for (x = area->x1; x <= area->x2; x++)
		{
			oled_set_pixel(x, y, color);
		}
	}
}

/**
 * @brief put a char to give area.
 * TODO: remember to clear the area before write.
 * @param page 
 * @param col 
 * @param cha 
 */
void oled_putchar(uint8_t page, uint8_t col, uint8_t cha)
{
	int i;
	/* get the cha in oledfont */
	const uint8_t *dots = oled_asc2_8x16[cha - ' '];
	uint8_t *pen = oled_buffer;

	for (i = 0; i < 8; i++)
	{
		pen[OFFSET(page, col + i)] = 0x00;
		pen[OFFSET(page + 1, col + i)] = 0x00;
	}

	for (i = 0; i < 8; i++)
	{
		pen[OFFSET(page, col + i)] = dots[i];
	}

	for (i = 0; i < 8; i++)
	{
		pen[OFFSET(page + 1, col + i)] = dots[i + 8];
	}
}

/**
 * @brief 
 * 
 * @param page 
 * @param col 
 * @param str 
 */
void oled_putstring(uint8_t page, uint8_t col, uint8_t *str)
{
	while (*str != '\0')
	{
		oled_putchar(page, col, *str++);
		col += 8;
	}
}

/**
 * @brief 
 * 
 * @param x 
 * @param y 
 * @param c 
 */
void oled_put_ascii(oled_coord_t x, oled_coord_t y, uint32_t c)
{
	int row, column;
	uint8_t byte;
	const uint8_t *dots = (uint8_t *)&fontdata_8x16[c * 16];
	uint8_t *pen = oled_buffer;

	// oled_area_t clear_area;
	// clear_area.x1 = x;
	// clear_area.y1 = y;
	// clear_area.x2 = x + 8;
	// clear_area.y2 = y + 16;

	// oled_clear_area(&clear_area, 0);

	for (row = 0; row < 16; row++)
	{
		byte = dots[row];
		for (column = 7; column >= 0; column--)
		{
			if (byte & (1 << column))
			{
				oled_set_pixel(x + 7 - column, y + row, 1);
			}
			else
			{
				oled_set_pixel(x + 7 - column, y + row, 0);
			}
		}
	}
}

/**
 * @brief 
 * 
 * @param x 
 * @param y 
 * @param str 
 */
void oled_putascii_string(oled_coord_t x, oled_coord_t y, uint8_t *str)
{
	while (*str != '\0')
	{
		oled_put_ascii(x, y, *str++);
		x += 8;
		if (x == 128)
			y += 5;
	}
}

/**
 * @brief 
 * 
 * @param x1 
 * @param y1 
 * @param x2 
 * @param y2 
 */
void Glib_Line(int x1, int y1, int x2, int y2)
{
	int dx, dy, e;
	dx = x2 - x1;
	dy = y2 - y1;

	if (dx >= 0)
	{
		if (dy >= 0)
		{ // dy>=0
			if (dx >= dy)
			{ // 1/8 octant
				e = dy - dx / 2;

				while (x1 <= x2)
				{
					oled_set_pixel(x1, y1, 1);

					if (e > 0)
					{
						y1 += 1;
						e -= dx;
					}

					x1 += 1;
					e += dy;
				}
			}
			else
			{ // 2/8 octant
				e = dx - dy / 2;

				while (y1 <= y2)
				{
					oled_set_pixel(x1, y1, 1);

					if (e > 0)
					{
						x1 += 1;
						e -= dy;
					}

					y1 += 1;
					e += dx;
				}
			}
		}
		else
		{			  // dy<0
			dy = -dy; // dy=abs(dy)

			if (dx >= dy)
			{ // 8/8 octant
				e = dy - dx / 2;

				while (x1 <= x2)
				{
					oled_set_pixel(x1, y1, 1);

					if (e > 0)
					{
						y1 -= 1;
						e -= dx;
					}

					x1 += 1;
					e += dy;
				}
			}
			else
			{ // 7/8 octant
				e = dx - dy / 2;

				while (y1 >= y2)
				{
					oled_set_pixel(x1, y1, 1);

					if (e > 0)
					{
						x1 += 1;
						e -= dy;
					}

					y1 -= 1;
					e += dx;
				}
			}
		}
	}
	else
	{			  //dx<0
		dx = -dx; //dx=abs(dx)

		if (dy >= 0)
		{ // dy>=0
			if (dx >= dy)
			{ // 4/8 octant
				e = dy - dx / 2;

				while (x1 >= x2)
				{
					oled_set_pixel(x1, y1, 1);

					if (e > 0)
					{
						y1 += 1;
						e -= dx;
					}

					x1 -= 1;
					e += dy;
				}
			}
			else
			{ // 3/8 octant
				e = dx - dy / 2;

				while (y1 <= y2)
				{
					oled_set_pixel(x1, y1, 1);

					if (e > 0)
					{
						x1 -= 1;
						e -= dy;
					}

					y1 += 1;
					e += dx;
				}
			}
		}
		else
		{			  // dy<0
			dy = -dy; // dy=abs(dy)

			if (dx >= dy)
			{ // 5/8 octant
				e = dy - dx / 2;

				while (x1 >= x2)
				{
					oled_set_pixel(x1, y1, 1);

					if (e > 0)
					{
						y1 -= 1;
						e -= dx;
					}

					x1 -= 1;
					e += dy;
				}
			}
			else
			{ // 6/8 octant
				e = dx - dy / 2;

				while (y1 >= y2)
				{
					oled_set_pixel(x1, y1, 1);

					if (e > 0)
					{
						x1 -= 1;
						e -= dy;
					}

					y1 -= 1;
					e += dx;
				}
			}
		}
	}
}

/**
 * @brief 
 * 
 * @param x1 
 * @param y1 
 * @param x2 
 * @param y2 
 */
void Glib_Rectangle(int x1, int y1, int x2, int y2)
{
	Glib_Line(x1, y1, x2, y1);
	Glib_Line(x2, y1, x2, y2);
	Glib_Line(x1, y2, x2, y2);
	Glib_Line(x1, y1, x1, y2);
}

/**
 * @brief 
 * 
 * @param opr 
 */
void register_oled_operations(struct oled_operations *opr)
{
	i2c_init();
	opr->init = oled_device_init;
	opr->write_cmd = oled_write_cmd;
	opr->write_dat = oled_write_dat;
	opr->set_pos = oled_set_pos;
	opr->clear = oled_clear;
	opr->set_pixel = oled_set_pixel;
	opr->flush = oled_flush;
	opr->putchar = oled_putchar;
	opr->putascii = oled_put_ascii;
	opr->putstring = oled_putstring;
	opr->putascii_string = oled_putascii_string;
}
