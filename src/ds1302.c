/**
 * @file ds1302.c
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

#include "ds1302.h"
/**
 * @brief set DS1302 pin CLK state
 *
 * @param val pin state to set
 */
static void __ds1302_set_clk( uint8_t val )
{
    if( val ) {
        DS1302_CLK = 1;
    }
    else {
        DS1302_CLK = 0;
    }
}

/**
 * @brief set pin DAT state
 *
 * @param val pin state to set
 */
static void __ds1302_set_dat( uint8_t val )
{
    if( val ) {
        DS1302_DAT = 1;
    }
    else {
        DS1302_DAT = 0;
    }
}

/**
 * @brief return the state of pin CLK
 *
 * @return uint8_t
 */
static uint8_t __ds1302_get_dat()
{
    return DS1302_DAT;
}

/**
 * @brief set the pin RST state
 *
 * @param val pin state to set
 */
static void __ds1302_set_rst( uint8_t val )
{
    if( val ) {
        DS1302_RST = 1;
    }
    else {
        DS1302_RST = 0;
    }
}

/**
 * @brief write a byte to ds1302, LSB first out!
 *
 * @param byte_in
 */
static void __ds1302_writebyte( uint8_t byte_in )
{
    int i;

    for( i = 0; i < 8; i++ ) {
        __ds1302_set_clk( 0 );
        __ds1302_set_dat( byte_in & 0x1 );
        byte_in >>= 1;
        __ds1302_set_clk( 1 );
    }
}

/**
 * @brief read a byte from ds1302, LSB first out too!
 *
 * @return uint8_t
 */
static uint8_t __ds1302_readebyte()
{
    uint8_t i;
    uint8_t res = 0;

    for( i = 0; i < 8; i++ ) {
        __ds1302_set_clk( 0 );
        res |= __ds1302_get_dat() << i;
        __ds1302_set_clk( 1 );
    }

    return res;
}

uint8_t ds1302_read_register( uint8_t command )
{
    uint8_t res = 0;
    __ds1302_set_rst( 1 );
    __ds1302_writebyte( command );
    res = __ds1302_readebyte();
    __ds1302_set_rst( 0 );
    return res;
}

void ds1302_write_register( uint8_t command,
                            uint8_t byte_in )
{
    __ds1302_set_rst( 1 );
    __ds1302_writebyte( command );
    __ds1302_writebyte( byte_in );
    __ds1302_set_rst( 0 );
}

void ds1302_init()
{
    // P2PU &= ~(0x07 << 0);
    // P2PU |= (0x07 << 0);
    // P1PU &= ~(0x0f << 2);
    // P1PU |= (0x0f << 2);
    __ds1302_set_rst( 0 );
    __ds1302_set_clk( 0 );
    __ds1302_set_dat( 0 );
    ds1302_write_register( 0x80, 0x00 );
    ds1302_write_register( 0x8e, 0x00 );
}

void ds1302_deinit()
{
}

void register_ds1302_operations( struct ds1302_operations *opr )
{
    opr->init = ds1302_init;
    opr->read_register = ds1302_read_register;
    opr->write_register = ds1302_write_register;
}
