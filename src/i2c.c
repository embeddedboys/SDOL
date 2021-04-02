#include "i2c.h"

#define I2CCFG (*(unsigned char volatile xdata *)0xfe80)
#define I2CMSCR (*(unsigned char volatile xdata *)0xfe81)
#define I2CMSST (*(unsigned char volatile xdata *)0xfe82)
#define I2CSLCR (*(unsigned char volatile xdata *)0xfe83)
#define I2CSLST (*(unsigned char volatile xdata *)0xfe84)
#define I2CSLADR (*(unsigned char volatile xdata *)0xfe85)
#define I2CTXD (*(unsigned char volatile xdata *)0xfe86)
#define I2CRXD (*(unsigned char volatile xdata *)0xfe87)

void i2c_init()
{
	I2CCFG = 0xe0;
	I2CMSST = 0x00;
}
void Wait()
{
	while ( ! ( I2CMSST & 0x40 ) );

	I2CMSST &= ~0x40;
}
void i2c_start()
{
	I2CMSCR = 0x01; //?? START ??
	Wait();
}

void i2c_stop()
{
	I2CMSCR = 0x06; //?? STOP ??
	Wait();
}

void i2c_revack()
{
	I2CMSCR = 0x03; //??? ACK ??
	Wait();
}

void i2c_sndack()
{
	I2CMSST = 0x00; //?? ACK ??
	I2CMSCR = 0x05; //?? ACK ??
	Wait();
}

void i2c_sndnack()
{
	I2CMSST = 0x01; //?? NAK ??
	I2CMSCR = 0x05; //?? ACK ??
	Wait();
}

uint8_t i2c_readbyte()
{
	I2CMSCR = 0x04; //?? RECV ??
	Wait();
	return I2CRXD;
}

void i2c_sendbyte ( uint8_t byte )
{
	I2CTXD = byte; //?????????
	I2CMSCR = 0x02; //?? SEND ??
	Wait();
}
