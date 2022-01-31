/**
 * @file uart.c
 * @author Zheng Hua (writeforever@foxmail.com)
 * @brief uart driver
 * @version 0.1
 * @date 2022-01-28
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

#include "uart.h"

static bit busy;
static char ringbuffer[16];
static uint8_t rd_index;
static uint8_t wr_index;

static void uart_init( uint8_t which )
{
    uart_register_scon_t scon = {0};
    uart_register_pcon_t pcon = {0};
    stcmcu_register_AUXR_t auxr = {0};
    stcmcu_register_TMOD_t tmod = {0};
    
    switch( which ) {
    case UART_1:
    
        /* SCON 串口1控制寄存器 配置 */
        scon.full = SCON;
        scon.reg.SM0_or_FE = 0;  /* 设置串口1工作模式为模式1 */
        scon.reg.SM1 = 1;        /* 可变波特率8位数据方式 */
        scon.reg.SM2 = 0;        /* 禁用模式2或模式3多机通信 */
        scon.reg.REN = 1;        /* 允许串口接收数据 */
        SCON = scon.full;
        
        /* PCON 电源管理寄存器 配置 */
        pcon.full = PCON;
        pcon.reg.SMOD0 = 0; /* 关闭帧错误检测功能 */
        pcon.reg.SMOD = 0;  /* 串口1各模式波特率不加倍 */
        PCON = pcon.full;
        
        auxr.full = AUXR;
        auxr.reg.T1x12 = 1;
        auxr.reg.S1ST2 = 0;
        AUXR = auxr.full;
        
        /* TMOD 定时器0/1模式寄存器 配置*/
        tmod.full = TMOD;
        tmod.reg.T1_GATE = 0;   /* 无条件启动定时器1 */
        tmod.reg.T1_C_T = 0;    /* 清0用作定时器 */
        tmod.reg.T1_M1 = 0;     /* 配置定时器1工作模式 */
        tmod.reg.T1_M0 = 0;     /* 16位自动重载模式 */
        TMOD = tmod.full;
        
        /* 设置定时器初值 此处对应波特率115200 */
        TL1 = 0xCC;
        TH1 = 0xFF;
        ET1 = 0;    /* 进制定时器1中断 */
        TR1 = 1;    /* 启动定时器1 */
        
        break;
        
    case UART_2:
        break;
        
    case UART_3:
        break;
        
    case UART_4:
        break;
        
    default:
        break;
    }
    
    // init_failed:
    
}

static void uart_fast_init()
{
    SCON  = 0x50;        //8位数据,可变波特率
    AUXR |= 0x40;       //定时器时钟1T模式
    AUXR &= 0xFE;       //串口1选择定时器1为波特率发生器
    TMOD &= 0x0F;       //设置定时器模式
    TL1   = 0xCC;     //设置定时初始值
    TH1   = 0xFF;     //设置定时初始值
    ET1   = 0;        //禁止定时器1中断
    TR1   = 1;        //定时器1开始计时
}

static void uart_deinit( uint8_t which )
{
    (void *)which;
}

static void uart_set_baud_rate(uart_handle_t *handle, uint32_t baud_rate)
{
    
}

static void set_data_length(uart_handle_t *handle, uint8_t length)
{

}

static void set_parity(uart_handle_t *handle, uint8_t enable)
{

}

static void set_hardware_flow_control(uart_handle_t *handle, uint8_t enable)
{

}



void register_uart_operations( struct uart_operations *opr )
{
    opr->init = uart_init;
    opr->fast_init = uart_fast_init;
    opr->deinit = uart_deinit;
}
