#include <intrins.h>
#include "system.h"
#include "oled.h"
#include "disp_manager.h"

static struct system_operations my_sys_opr;
static struct oled_operations my_oled_opr;

void SystemInit()
{
	register_system_operations ( &my_sys_opr );
	my_sys_opr.iomux ( P32P33_I2C );

	register_oled_operations ( &my_oled_opr );
	my_oled_opr.init();
}

void main()
{
	int x, y;
	int offset=1;
	int page,col;
	uint8_t *str = "Hello World!";
	
	SystemInit();

	/*for ( y = 0, x = 0; x < 64; y++, x++ ) {
		my_oled_opr.set_pixel ( x, y, 1 );
	}*/
	
	/*my_oled_opr.putchar(0,0,'A');
	my_oled_opr.putchar(0,8,'b');
	my_oled_opr.putchar(0,16,'c');
	
	my_oled_opr.putstring(4,0,str);*/
	for(y=0;y<6;y++)
		for(x=0;x<12;x++)
			Glib_Rectangle(x*10+offset,y*10,x*10+offset+10,y*10+10);
	
	my_oled_opr.flush();

	while ( 1 );
}

