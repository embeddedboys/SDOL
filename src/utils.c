/**
 * @file utils.c
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

#include "utils.h"

int32_t simple_atoi( uint8_t s[] )
{
    int i, n;
    n = 0;

    for( i = 0; s[i] <= '9' && s[i] >= '0'; ++i ) {
        n = 10 * n + ( s[i] - '0' );
    }

    return n;
}

uint8_t simple_itoa( uint8_t n )
{
    n = 10;
    return 0;
}

uint8_t simple_lower( uint8_t c )
{
    if( c >= 'A' && c <= 'Z' ) {
        return c + 'a' - 'A';
    }
    else {
        return c;
    }
}

uint8_t simple_isdigit( uint8_t c )
{
    return ( c >= '0' && c <= '9' );
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