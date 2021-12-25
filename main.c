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
#include "system.h" /*opreations of system*/
#include "oled.h"	/*oled lib*/
#include "ds1302.h"

/*

*/
static struct system_operations my_sys_opr;
static struct oled_operations my_oled_opr;
static struct ds1302_operations my_ds1302_opr;

/**
*@description All initial opr in system.
*@param
*@return
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
}

/**
*@description main thread of this project
*@param
*@return
*/
int main(void)
{
	int x, y;
	int offset = 1;
	int page, col;
	uint8_t res = 0;
	uint8_t *str = "Hello World!";
	uint8_t buf[16]={0};

	SystemInit();

	my_ds1302_opr.write_register(0x8A, 0x01);
	res = my_ds1302_opr.read_register(0x8B);
	my_oled_opr.putstring(0, 0, "read from reg:");
	sprintf(buf, "%d", res);
	my_oled_opr.putstring(2, 0, buf);

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

	/* flush pointdata to screen */
	my_oled_opr.flush();

	while (1)
		;
	return 0;
}
