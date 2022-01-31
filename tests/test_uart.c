/**
 * @file test_ds1302_capability.c
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
#include "tm1650.h"
#include "uart.h"

static struct uart_operations nMyUartOpr;
static uint16_t nCount = 0;
static uint16_t nInterruptCount = 0;

char wptr = 0;
char rptr = 0;
bit busy = 0;
char recv_buf[16];

void Timer2Init( void )     //10毫秒@23.894MMHz
{
    AUXR &= 0xFB;       //定时器时钟12T模式
    T2L = 0x38;     //设置定时初始值
    T2H = 0xB2;     //设置定时初始值
    AUXR |= 0x10;       //定时器2开始计时
    IE2 = 0x04;
    EA = 1;
}

void SystemInit()
{
    P0M0 = 0x00;
    P0M1 = 0x00;
    P1M0 = 0x00;
    P1M1 = 0x00;
    P2M0 = 0x00;
    P2M1 = 0x00;
    P3M0 = 0x00;
    P3M1 = 0x00;
    P4M0 = 0x00;
    P4M1 = 0x00;
    P5M0 = 0x00;
    P5M1 = 0x00;
    
    register_uart_operations( &nMyUartOpr );
    // nMyUartOpr.fast_init();
    nMyUartOpr.init(UART_1);

    ES=1;
    EA=1;
}

void Timer2_Isr() interrupt 12
{
    if( nInterruptCount++ == 100 ) {
        nCount++;
        nInterruptCount = 0;
    }
}

void Delay1000ms()      //@24.000MHz
{
    unsigned char i, j, k;
    
    _nop_();
    _nop_();
    i = 122;
    j = 193;
    k = 128;
    
    do
    {
        do
        {
            while( --k );
        }
        while( --j );
    }
    while( --i );
}

void Uart1_Isr() interrupt 4
{
    if( TI ) {
        TI = 0;
        busy = 0;
    }
    
    if( RI ) {
        RI = 0;
        recv_buf[wptr++] = SBUF;
        wptr &= 0x0f;
    }
}

void UartSend( char dat )
{
    while( busy );
    
    busy = 1;
    SBUF = dat;
}

void UartSendStr( char *str )
{
    while( *str ) {
        UartSend(*str++);
    }
}

void main( void )
{
    uint8_t loop = 1;
    
    SystemInit();
    UartSendStr("Uart Test!\r\n");
    UartSendStr("Starting...!\r\n");

    while( loop ) {
        if(rptr != wptr)
        {
            UartSend(recv_buf[rptr++]);
            rptr &= 0x0f;
        }
    }
}