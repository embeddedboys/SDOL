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
#include "tm1650.h"

static tm1650_config_t __mTM1650_config = {0};

void tm1650_write_register(uint8_t addr, uint8_t dat)
{
    gpio_i2c_start();

    gpio_i2c_sendbyte(addr); //slave address
    gpio_i2c_revack();
    gpio_i2c_sendbyte(dat);
    gpio_i2c_revack();

    gpio_i2c_stop();
}

void tm1650_set_brightness(tm1650_brightness_level_t level)
{
    __mTM1650_config.display_register.brightness = level;
    tm1650_write_register(TM1650_DISPLAY_REG, __mTM1650_config.full);
}

void tm1650_set_display(tm1650_display_power_t state)
{
    __mTM1650_config.display_register.power = state;
    tm1650_write_register(TM1650_DISPLAY_REG, __mTM1650_config.full);
}

void tm1650_set_segment_format(tm1650_segment_format_t format)
{
    __mTM1650_config.display_register.segment_format = format;
    tm1650_write_register(TM1650_DISPLAY_REG, __mTM1650_config.full);
}

void tm1650_show_bit(tm1650_bit_selection_t which, tm1650_segment_value_t value)
{
    tm1650_write_register(which, value);
}

void tm1650_init()
{
    /* enable pin internal pull up res */
    // P3PU &= ~(0x03 << 6);
    // P3PU |= (0x03 << 6);
    /**
     * default mode:
     * power: ON
     * brightness: level 1
     * segment format: 8 bit
     */
    __mTM1650_config.display_register.power = TM1650_DISPLAY_POWER_ON;
    __mTM1650_config.display_register.brightness = TM1650_BRIGHTNESS_LEVEL_1;
    __mTM1650_config.display_register.segment_format = TM1650_SEGMENT_FORMAT_8;
    tm1650_write_register(0x48, __mTM1650_config.full);
}

void tm1650_deinit()
{
}

void register_tm1650_operations(struct tm1650_operations *opr)
{
    opr->init = tm1650_init;
    opr->write_register = tm1650_write_register;
    opr->set_brightness = tm1650_set_brightness;
    opr->set_display = tm1650_set_display;
    opr->set_segment_format = tm1650_set_segment_format;
    opr->show_bit = tm1650_show_bit;
}