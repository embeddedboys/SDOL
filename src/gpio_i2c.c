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

#include "gpio_i2c.h"

static void __gpio_i2c_set_scl(uint8_t val)
{
    if (val)
    {
        GPIO_I2C_SCL = 1;
    }
    else
    {
        GPIO_I2C_SCL = 0;
    }
}

static void __gpio_i2c_set_sda(uint8_t val)
{
    if (val)
    {
        GPIO_I2C_SDA = 1;
    }
    else
    {
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
    __gpio_i2c_set_scl(0);
    __gpio_i2c_set_sda(0);
}

void gpio_i2c_start()
{
    __gpio_i2c_set_sda(0);
    __gpio_i2c_set_scl(1);
    __gpio_i2c_set_scl(0);
}

void gpio_i2c_stop()
{
    __gpio_i2c_set_scl(1);
    __gpio_i2c_set_sda(0);
    __gpio_i2c_set_sda(1);
}

uint8_t gpio_i2c_revack()
{
    uint8_t val_ack = 1;
    __gpio_i2c_set_scl(1);
    __gpio_i2c_set_scl(0);
    val_ack = __gpio_i2c_get_sda();

    return val_ack;
}

void gpio_i2c_sndack()
{
    __gpio_i2c_set_sda(0);
    __gpio_i2c_set_scl(1);
    __gpio_i2c_set_scl(0);
    __gpio_i2c_set_sda(1);
}

void gpio_i2c_sndnack()
{
}

uint8_t gpio_i2c_readbyte()
{
    int i;
    uint8_t byte_read = 0;
    for (i = 0; i < 8; i++)
    {
        byte_read |= __gpio_i2c_get_sda();
        __gpio_i2c_set_scl(1);
        __gpio_i2c_set_scl(0);
        byte_read <<= 1;
    }

    return byte_read;
}

void gpio_i2c_sendbyte(uint8_t byte_in)
{
    int i;
    for (i = 0; i < 8; i++)
    {
        __gpio_i2c_set_sda((byte_in & 0x80) ? 1 : 0);
        __gpio_i2c_set_scl(1);
        __gpio_i2c_set_scl(0);
        byte_in <<= 1;
    }
}