/**
 * @file spi_gpio.c
 * @author Zheng Hua (writeforever@foxmail.com)
 * @brief
 * @version 0.1
 * @date 2022-01-31
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

#ifndef __SPI_GPIO_H
#define __SPI_GPIO_H

#ifndef STCMCU_H
    #include "stcmcu.h"
#endif

sbit nSS = P1 ^ 2;
sbit MOSI = P1 ^ 3;
sbit MISO = P1 ^ 4;
sbit SCLK = P1 ^ 5;

typedef struct
{
    char *name;
    uint32_t speed;
    
    uint8_t cs_polarity;
    uint8_t clock_polarity;
    uint8_t clock_phase;
    uint8_t bit_order;
    uint8_t word_size;
} spi_gpio_handle_t;

void spi_init();
void spi_sendbyte();
void spi_readbyte();



#endif