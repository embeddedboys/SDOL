/**
 * @file gpio_i2c.c
 * @author Zheng Hua (writeforever@foxmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-01-22
 * 
 * MIT License
 * 
 * Copyright 2022 Zheng Hua(writeforever@foxmail.com)
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 * 
 */

#include "gpio_i2c.h"

static void __gpio_i2c_set_scl( uint8_t val )
{
    if( val ) {
        GPIO_I2C_SCL = 1;
    }
    else {
        GPIO_I2C_SCL = 0;
    }
}

static void __gpio_i2c_set_sda( uint8_t val )
{
    if( val ) {
        GPIO_I2C_SDA = 1;
    }
    else {
        GPIO_I2C_SDA = 0;
    }
}

static uint8_t __gpio_i2c_get_sda()
{
    return GPIO_I2C_SDA;
}

void gpio_i2c_init()
{
    /* set config */
    __gpio_i2c_set_scl( 0 );
    __gpio_i2c_set_sda( 1 );
}

void gpio_i2c_start()
{
    __gpio_i2c_set_scl( 1 );

    delay();
    __gpio_i2c_set_sda( 1 );
    __gpio_i2c_set_sda( 0 );
    delay();

    __gpio_i2c_set_scl( 0 );
}

void gpio_i2c_stop()
{
    __gpio_i2c_set_scl( 1 );

    __gpio_i2c_set_sda( 0 );
    __gpio_i2c_set_sda( 1 );
    delay();

    __gpio_i2c_set_scl( 0 );
}

uint8_t gpio_i2c_revack()
{
    __gpio_i2c_set_scl( 1 );
    delay();
    __gpio_i2c_set_scl( 0 );
    return __gpio_i2c_get_sda();
}

void gpio_i2c_sndack()
{
    __gpio_i2c_set_sda( 0 );
    __gpio_i2c_set_scl( 1 );
    __gpio_i2c_set_scl( 0 );
    __gpio_i2c_set_sda( 1 );
}

void gpio_i2c_sndnack()
{
}

uint8_t gpio_i2c_readbyte()
{
    int i;
    uint8_t byte_read = 0;

    for( i = 0; i < 8; i++ ) {
        byte_read |= __gpio_i2c_get_sda();
        __gpio_i2c_set_scl( 1 );
        __gpio_i2c_set_scl( 0 );
        byte_read <<= 1;
    }

    return byte_read;
}

void gpio_i2c_sendbyte( uint8_t byte_in )
{
    int i;

    for( i = 0; i < 8; i++ ) {
        __gpio_i2c_set_sda( ( byte_in & 0x80 ) ? 1 : 0 );
        delay();
        __gpio_i2c_set_scl( 1 );
        delay();
        __gpio_i2c_set_scl( 0 );
        byte_in <<= 1;
    }
    __gpio_i2c_set_sda( 0 );
}