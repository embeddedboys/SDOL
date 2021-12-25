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
#include "utils.h"

int32_t simple_atoi(uint8_t s[])
{
    int i, n;

    n = 0;
    for (i = 0; s[i] <= '9' && s[i] >= '0'; ++i)
    {
        n = 10 * n + (s[i] - '0');
    }
    return n;
}

uint8_t simple_itoa(uint8_t n)
{
}

uint8_t simple_lower(uint8_t c)
{
    if (c >= 'A' && c <= 'Z')
        return c + 'a' - 'A';
    else
        return c;
}

uint8_t simple_isdigit(uint8_t c)
{
    return (c >= '0' && c <= '9');
}

// void delay_us(uint32_t us)
// {
//     unsigned char i;

//     while (us--)
//     {
//         i = 6;
//         while (--i)
//             ;
//     }
// }