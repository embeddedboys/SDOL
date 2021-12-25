#include <stdio.h>
#include <stdint.h>
#include <stdarg.h>

#define OLED_DEBUG(fmt,...) do {   \
		uint8_t buf[16];					  \
		sprintf(buf,fmt,##__VA_ARGS__);	  \
		printf("%s\n",buf);		  \
}while(0);

int get_bit(int n)
{
	return (n % 2) >0?1:0;
}

int call_sprintf(const char *fmt, int num)
{
	uint8_t buf[16]={0};

	sprintf(buf, fmt, num);
	printf("%s\n", buf);

	return 0;
}

int
main(int argc, char **argv)
{
	int val = 0xA4;
	do{
		printf("bit: %d\n", val & 0x01);
	}while(val>>=1);

	int i, res;
	for(i=0;i<8;i++)
	{
		res |= get_bit(i) << i;
	}
	printf("res: %d\n", res);

	int val2 = 0x07;
	uint8_t buf[16];
	sprintf(buf, "%d", val2);
	printf("sprintf: %s\n", buf);
	
	call_sprintf("%d", 2);
	OLED_DEBUG("%s, %d", "regs:",2);

	return 0;
}
