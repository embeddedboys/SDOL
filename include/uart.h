/**
 * @file uart.h
 * @author Zheng Hua (writeforever@foxmail.com)
 * @brief
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

#ifndef __UART_H
#define __UART_H

/*********************
* Documents for uart
*********************/
/**
 *
 */

/*********************
*      INCLUDES
*********************/
#include <stdarg.h>
#include <stdlib.h>

#ifndef STCMCU_H
    #include "stcmcu.h"
#endif

/*********************
 *    STRUCTURE
 *********************/
struct uart_operations
{
    void ( *init )( uint8_t which );
    void (*fast_init)();
    void ( *deinit )( uint8_t which );

    void (*open_port)(uint8_t port);
    void (*close_port)(uint8_t port);

    uint8_t (*read_port)(uint8_t fd, uint8_t *buf, uint32_t size);
	uint8_t (*write_port)(uint8_t fd, uint8_t *buf, uint32_t size);
	uint8_t (*set_port)(uint8_t fd, struct uart_config *conf);
	uint8_t (*set_baud_rate)(struct termios *options, const uint32_t baud_rate);
	uint8_t (*set_data_length)(struct termios *options, const uint8_t data_length);

    
    void ( *putchar )( int c );
    void (*puts)(const char *s);
    
    void ( *printf )( const char *format, ... );
};

/*********************
 *      DEFINES
 *********************/

/**********************
*      ENUMS
**********************/
typedef enum {
    UART_1 = 0x01,
    UART_2 = 0x02,
    UART_3 = 0x03,
    UART_4 = 0x04,
} uart_enum_t;

/**********************
*      TYPEDEFS
**********************/
typedef struct
{
    char *uart_name;
    uart_enum_t port;

    uint32_t baud_rate;
    uint8_t data_bit;
    uint8_t pairty;

    uint8_t busy;
    char msg_buf[16];
    uint16_t rd_index;
    uint16_t wr_index;
    uint32_t timeout;
    
}uart_handle_t;

typedef union
{
    /* Address : 0x98 */
    struct {
        uint8_t RI        : 1;
        uint8_t TI        : 1;
        uint8_t RB8       : 1;
        uint8_t TB8       : 1;
        uint8_t REN       : 1;
        uint8_t SM2       : 1;
        uint8_t SM1       : 1;
        uint8_t SM0_or_FE : 1;
    } reg;
    
    uint8_t full;
} uart_register_scon_t;

typedef union
{

    /* Address : 0x87 */
    struct {
        uint8_t IDL   : 1;
        uint8_t PD    : 1;
        uint8_t GF0   : 1;
        uint8_t GF1   : 1;
        uint8_t POF   : 1;
        uint8_t LVDF  : 1;
        uint8_t SMOD0 : 1;
        uint8_t SMOD  : 1;
    }reg;
    uint8_t full;
}uart_register_pcon_t;

/**********************
* GLOBAL PROTOTYPES
**********************/
void help(void);
void register_uart_operations( struct uart_operations *opr );

#endif