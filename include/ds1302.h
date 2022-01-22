/**
 * @file ds1302.h
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

#ifndef __DS1302_H
#define __DS1302_H

/*********************
* Documents for ds1302
*********************/
/**
    3-wire synchronous serial communication
    Vcc1 and Vcc2 dual power supply

    7   6      5   4   3   2   1   0
    1 RAM/CK#  A4  A3  A2  A1  A0  RD/WR#

    CLK
    DAT
    RST
*/

/*********************
*      INCLUDES
*********************/
#ifndef STCMCU_H
    #include "stcmcu.h"
#endif

/*********************
 *      DEFINES
 *********************/
sbit DS1302_CLK = P1 ^ 5;
sbit DS1302_DAT = P1 ^ 3;
sbit DS1302_RST = P1 ^ 2;


/**********************
*      TYPEDEFS
**********************/
typedef struct {

    float temperature;
    float humidity;
    uint8_t checksum;

    //ds1302_state_enum state;
    //ds1302_lock_enum lock;

} ds1302_handle_t;

typedef struct {
    uint8_t year;
    uint8_t month;
    uint8_t day;
    uint8_t hour;
    uint8_t minute;
    uint8_t second;

    uint8_t format_hour;

} ds1302_config_t;

struct ds1302_operations {
    void ( *init )();
    void ( *deinit )();
    uint8_t ( *read_register )( uint8_t command );
    void ( *write_register )( uint8_t command, uint8_t byte );

    /* getter and setters for each value*/
    uint8_t ( *get_year )();
    uint8_t ( *get_month )();
    uint8_t ( *get_day )();
    uint8_t ( *get_hour )();
    uint8_t ( *get_minute )();
    uint8_t ( *get_second )();
    void ( *set_year )( uint8_t year );
    void ( *set_month )( uint8_t month );
    void ( *set_day )( uint8_t day );
    void ( *set_hour )( uint8_t hour );
    void ( *set_minute )( uint8_t minute );
    void ( *set_second )( uint8_t second );

    /* getter  and setter for config */
    //ds1302_config_t (*get_configs)();
    //uint8_t (*set_configs)(ds1302_config_t config);

    uint8_t ( *set_trickle_charge )( uint8_t function );
};

/**********************
*      ENUMS
**********************/
typedef enum {
    DS1302_TRICKLE_CHARGE_DISABLED = 0,
    DS1302_TRICKLE_CHARGE_1_DIODE_2K,
    DS1302_TRICKLE_CHARGE_1_DIODE_4K,
    DS1302_TRICKLE_CHARGE_1_DIODE_8K,
    DS1302_TRICKLE_CHARGE_2_DIODE_2K,
    DS1302_TRICKLE_CHARGE_2_DIODE_4K,
    DS1302_TRICKLE_CHARGE_2_DIODE_8K,
    DS1302_TRICKLE_CHARGE_INITIAL_POWER_ON_STATE,
} ds1032_trickle_charge_mode;

/**********************
* GLOBAL PROTOTYPES
**********************/
void register_ds1302_operations( struct ds1302_operations *opr );
#endif
