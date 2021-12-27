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

#include "ds1302.h"
#include "oled.h"
#include <string.h>
/**
 * @brief set DS1302 pin CLK state
 * 
 * @param val pin state to set
 */
void __ds1302_set_clk(uint8_t val)
{
    if (val)
    {
        DS1302_CLK = 1;
    }
    else
    {
        DS1302_CLK = 0;
    }
}

/**
 * @brief set pin DAT state
 * 
 * @param val pin state to set
 */
void __ds1302_set_dat(uint8_t val)
{
    if (val)
    {
        DS1302_DAT = 1;
    }
    else
    {
        DS1302_DAT = 0;
    }
}

/**
 * @brief return the state of pin CLK
 * 
 * @return uint8_t 
 */
uint8_t __ds1302_get_dat()
{
    return DS1302_DAT;
}

/**
 * @brief set the pin RST state
 * 
 * @param val pin state to set
 */
void __ds1302_set_rst(uint8_t val)
{
    if (val)
    {
        DS1302_RST = 1;
    }
    else
    {
        DS1302_RST = 0;
    }
}

/**
 * @brief write a byte to ds1302, LSB first out!
 * 
 * @param byte_in 
 */
void __ds1302_writebyte(uint8_t byte_in)
{
    int i;
    for (i = 0; i < 8; i++)
    {
        __ds1302_set_clk(0);
        __ds1302_set_dat(byte_in & 0x1);
        byte_in >>= 1;
        __ds1302_set_clk(1);
    } 
}

/**
 * @brief read a byte from ds1302, LSB first out too!
 * 
 * @return uint8_t 
 */
uint8_t __ds1302_readebyte()
{
    uint8_t i;
    uint8_t res = 0;

    for (i = 0; i < 8; i++)
    {
        __ds1302_set_clk(0);
        res |= __ds1302_get_dat() << i;
        __ds1302_set_clk(1);
    }

    return res;
}

uint8_t ds1302_read_register(uint8_t command)
{
    uint8_t res = 0;

    __ds1302_set_rst(1);

    __ds1302_writebyte(command);
    res = __ds1302_readebyte();

    __ds1302_set_rst(0);
    return res;
}

void ds1302_write_register(uint8_t command, uint8_t byte_in)
{
    __ds1302_set_rst(1);

    __ds1302_writebyte(command);
    __ds1302_writebyte(byte_in);

    __ds1302_set_rst(0);
}

void ds1302_init()
{
    P2PU &= ~(0x07 << 0);
    P2PU |= (0x07 << 0);

    __ds1302_set_rst(0);
    __ds1302_set_clk(0);
    __ds1302_set_dat(0);

    // ds1302_write_register(0x80, 0x00);
    ds1302_write_register(0x8e, 0x00);
}

void ds1302_deinit()
{
}

void register_ds1302_operations(struct ds1302_operations *opr)
{
    opr->init = ds1302_init;
    opr->read_register = ds1302_read_register;
    opr->write_register = ds1302_write_register;
}
