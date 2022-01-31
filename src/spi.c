/**
 * @file spi.c
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

#include "spi.h"

/**
 * @brief 
 * 
 */
static void __spi_wait()
{
    while( !( SPSTAT & 0x40 ) );
    
    SPSTAT &= ~( 0x40 );
}

void spi_init()
{
    stcmcu_register_SPCTL_t spctl = {0};

    P_SW1 = 0x00;

    /* 配置SPI控制器 */
    spctl.full = SPCTL;
    spctl.reg.SSIG = 1;     /* 禁用SS引脚主从机确定功能 */
    spctl.reg.SPEN = 1;     /* 使能SPI */
    spctl.reg.DORD = 0;     /* 先发送/接收数据的高位(MSB) */
    spctl.reg.MSTR = 1;     /* 设置SPI为主机模式 */
    spctl.reg.CPOL = 1;     /* SCLK空闲时为高电平，SCLK前时钟沿为下降沿，
                               后时钟沿为上升沿 */
    spctl.reg.CPHA = 1;     /* 数据在SCLK的前时钟沿驱动，后时钟沿采样 */

    /* 配置SPI控制器速率 */
    spctl.reg.SPR = 0x01;   /* 01 SYSclk / 8 , 此处为 24MHz/8 = 3MHz */

    SPCTL = spctl.full;
}

void spi_sendbyte(uint8_t dat)
{
    SPDAT = dat;
    __spi_wait();
    SPSTAT = 0xc0;      /* 清除中断标志 */
}

uint8_t spi_readbyte()
{
    __spi_wait();
    SPSTAT = 0xC0;      /* 清除中断标志 */
    return SPDAT;
}