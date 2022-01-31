/**
 * @file test_spi_controller_offical.c
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

#include "STC8G.H"
#include "intrins.h"
#include "uart.h"

sbit SS = P1^2;
#define ESPI 0x02;

char wptr = 0;
char rptr = 0;
bit busy = 0;
bit busy_spi = 0;
char recv_buf[16];
static struct uart_operations m_uart_opr;

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

void SPI_Isr() interrupt 9
{
    SPSTAT = 0xC0;
    SS = 1;
    busy_spi = 0; 
}

void main()
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

    register_uart_operations( & m_uart_opr);
    m_uart_opr.init(UART_1);

    busy=0;
    busy_spi=0;
    SS=1;
    P_SW1 = 0x00;

    SPCTL = 0x50;
    SPSTAT = 0xC0;

    ES=1;
    IE2 = ESPI;
    EA=1;

    while(1)
    {
        UartSendStr("Send Start!\r\n");
        
        
        while(busy_spi);
        busy_spi=1;
        SS=0;
        SPDAT = 0x5a;

        UartSendStr("Send Over!\r\n");
        Delay1000ms();
        
    }
}