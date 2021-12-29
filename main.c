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
#include <stdio.h>
#include <string.h>
#include "system.h"    /* opreations of system */
#include "oled.h"
#include "ds1302.h"
#include "tm1650.h"

static struct system_operations my_sys_opr;
static struct oled_operations my_oled_opr;
static struct ds1302_operations my_ds1302_opr;
static struct tm1650_operations my_tm1650_opr;
const unsigned char code tm1650_segment_value[10] = {
	0x3f, /* `0` */
	0x06, /* `1` */
	0x5b, /* `2` */
	0x4f, /* `3` */
	0x66, /* `4` */
	0x6d, /* `5` */
	0x7d, /* `6` */
	0x07, /* `7` */
	0x7f, /* `8` */
	0x6f, /* `9` */
};

/**
 * @biref all initialization operations for mcu and device.
 */
void SystemInit()
{
	/* register driver of system*/
	register_system_operations(&my_sys_opr);
	my_sys_opr.iomux(P32P33_I2C);

	/* register driver of oled */
	register_oled_operations(&my_oled_opr);
	my_oled_opr.init();

	/* register driver of ds1302 */
	register_ds1302_operations(&my_ds1302_opr);
	my_ds1302_opr.init();

	register_tm1650_operations(&my_tm1650_opr);
	my_tm1650_opr.init();
}

/**
*@description main thread of this project
*@param
*@return
*/
int main(void)
{
	// int x, y;
	// int offset = 1;
	// int page, col;
	uint32_t i;
	uint8_t res = 0;
	uint32_t ten;
	uint32_t biz;
	uint32_t seconds;
	uint8_t *str = "Hello World!";
	uint8_t buf[16] = {0};

	SystemInit();

	/*for ( y = 0, x = 0; x < 64; y++, x++ ) {
		my_oled_opr.set_pixel ( x, y, 1 );
	}*/

	/*my_oled_opr.putchar(0,0,'A');
	my_oled_opr.putchar(0,8,'b');
	my_oled_opr.putchar(0,16,'c');
	
	my_oled_opr.putstring(4,0,str);*/

	/* operations on GDRAM */
	/*for(y=0;y<6;y++)
		for(x=0;x<12;x++)
			Glib_Rectangle(x*10+offset,y*10,x*10+offset+10,y*10+10);*/
	// my_oled_opr.putstring(0, 0, "seconds:");
	/* flush pointdata to screen */
	// my_oled_opr.flush();
	// my_ds1302_opr.write_register(0x84, 0x2);
	// my_ds1302_opr.write_register(0x82, 0x36);
	// my_ds1302_opr.write_register(0x80, 0x0);
	// my_tm1650_opr.write_register(0x48, 0x11);
	my_tm1650_opr.set_brightness(TM1650_BRIGHTNESS_LEVEL_8);
	// my_tm1650_opr.write_register(0x68, tm1650_segment_value[4]);
	// my_tm1650_opr.write_register(0x6A, tm1650_segment_value[5]);
	// my_tm1650_opr.write_register(0x6C, tm1650_segment_value[9]);
	// my_tm1650_opr.write_register(0x6E, tm1650_segment_value[8]);

	my_oled_opr.putascii_string(0, 0, "read from reg do you know ?:");
	while (1)
	{
		// i=5000;
		// res = my_ds1302_opr.read_register(0x81);
		// tmp = ((res << 1) >> 4) * 10 + (res & 0x0f);
		// seconds = tmp;
		// sprintf(buf, "%d", seconds);
		// buf[2]='\0';
		// my_oled_opr.putstring(2, 0, buf);
		// my_oled_opr.flush();
		// memset(buf, 0x0, 2);
		// while(i--);
		// my_oled_opr.clear();
		res = my_ds1302_opr.read_register(0x85) & ~(1 << 7);
		ten = (res & 0x10) >> 4;
		biz = (res & 0x0f);
		my_oled_opr.putascii(0, 30, ten + '0');
		my_oled_opr.putascii(8, 30, biz + '0');
		my_oled_opr.putascii(16, 30, ':');
		my_tm1650_opr.show_bit(TM1650_BIT_1, tm1650_segment_value[ten]);
		my_tm1650_opr.show_bit(TM1650_BIT_2, tm1650_segment_value[biz] | 0x80);


		res = my_ds1302_opr.read_register(0x83) & ~(1 << 7);
		ten = (res & 0xf0) >> 4;
		biz = (res & 0x0f);
		my_oled_opr.putascii(24, 30, ten + '0');
		my_oled_opr.putascii(32, 30, biz + '0');
		my_oled_opr.putascii(40, 30, ':');
		my_tm1650_opr.show_bit(TM1650_BIT_3, tm1650_segment_value[ten]);
		my_tm1650_opr.show_bit(TM1650_BIT_4, tm1650_segment_value[biz]);

		res = my_ds1302_opr.read_register(0x81) & ~(1 << 7);
		ten = (res & 0xf0) >> 4;
		biz = (res & 0x0f);
		my_oled_opr.putascii(48, 30, ten + '0');
		my_oled_opr.putascii(56, 30, biz + '0');

		// sprintf(buf, "%d%d", ten, biz);
		// buf[15] = '\0';
		// my_oled_opr.putascii_string(0, 30, buf);
		my_oled_opr.flush();
		// memset(buf, 0x0, 16);
	}
	return 0;
}
