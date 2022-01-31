/**
 * @file system.c
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

#include "system.h"

/**
 * @brief 
 * 
 */
void system_init()
{
    CKSEL = 0x00;   /* Chosen inside high precision IRC */
    CLKDIV = 0x00;  /* Configure system clock div */
    HIRCCR |= ( 1 << 7 ); /* Enable inside high precision IRC */
    IRCBAND |= ( 1 << 0 ); /* 33MHz channle was chosen */
}

/**
 * @brief 
 * 
 * @param reset_type 
 */
void system_reset( uint8_t reset_type )
{
    iap_contr *con;
    con = 0xc7;

    switch( reset_type ) {
    case SYSTEM_ISP_AREA:
        con->ch.swbs = 1;
        con->ch.swrst = 1;
        break;

    case USER_PROGRAM_AREA:
        con->ch.swbs = 0;
        con->ch.swrst = 1;
        break;

    default:
        con->ch.swbs = 1;
        con->ch.swrst = 1;
        break;
    }
}

/**
 * @brief 
 * 
 */
void system_wdt_init()
{
    stcmcu_register_WDT_CONTR_t *con;
    con = 0xc1;
    con->reg.en_wdt = 1;     /* enable watchdog timer */
    /* clear the watchdog timer, hardware will do this automatically */
    con->reg.clr_wdt = 1;
    /*
    * watchdog timer clock frequency dividing
    * overflow time = 12*32768*2^(wdt_ps+1)/sysclk
    */
    con->reg.WDT_PS = ( 3 << 1 ); /* div:128;overflow time:1.44s when sysclk=35MHz */
}

/**
 * @brief 
 * 
 * @param gp 
 * @param mode 
 */
void __system_io_mode( grp_pin_t gp, uint8_t mode )
{
    uint8_t group, pin;
    group = GROUP( gp );
    pin   = PIN( gp );

    switch( group ) {
    case 0: /* Group P0 */
        P0M1 &= ~( ( mode & 0x02 ) << pin );
        P0M0 &= ~( ( mode & 0x01 ) << pin );
        break;

    case 1: /* Group P1 */
        P1M1 &= ~( ( mode & 0x02 ) << pin );
        P1M0 &= ~( ( mode & 0x01 ) << pin );
        break;

    case 2: /* Group P2 */
        P2M1 &= ~( ( mode & 0x02 ) << pin );
        P2M0 &= ~( ( mode & 0x01 ) << pin );
        break;

    case 3: /* Group P3 */
        P3M1 &= ~( ( mode & 0x02 ) << pin );
        P3M0 &= ~( ( mode & 0x01 ) << pin );
        break;

    default:
        break;
    }
}

/**
 * @brief 
 * 
 * @param iomux_type 
 */
void system_iomux( uint8_t iomux_type )
{
    switch( iomux_type ) {
    case P32P33_I2C:
        __system_io_mode( GROUP_PIN( 3, 2 ), STANDARD_IO );
        __system_io_mode( GROUP_PIN( 3, 3 ), STANDARD_IO );
        P_SW2 = ( 1 << 7 | 3 <<
                  4 );    /* enable XFR and set P3.2(SCL) P3.3(SDA) as I2C function */
        break;

    default:    /* As default. Configure P3.2 P3.3 pin as GPIO */
        __system_io_mode( GROUP_PIN( 3, 2 ), STANDARD_IO );
        __system_io_mode( GROUP_PIN( 3, 3 ), STANDARD_IO );
        break;
    }
}

/**
 * @brief 
 * 
 * @param opr 
 */
void register_system_operations( struct system_operations *opr )
{
    opr->init = system_init;
    opr->reset = system_reset;
    opr->wdt_init = system_wdt_init;
    opr->iomux = system_iomux;
}
