/**
 * @file system.h
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

#ifndef __SYSTEM_H
#define __SYSTEM_H

/*********************
*      INCLUDES
*********************/
#ifndef STCMCU_H
    #include "stcmcu.h"
#endif

/*********************
 *      DEFINES
 *********************/

/**********************
*      TYPEDEFS
**********************/

/**
 * @brief here redfine because 0x01 and 0x02 
 *        all present use external clock input
 */
typedef enum {

    INTERNAL_HIGH_PRECISION_IRC      = 0x00,
    EXTERNAL_CRYSTAL_OR_CLOCK        = 0x01,
    EXTERNAL_CRYSTAL_OR_CLOCK_TOO    = 0x02,    
    INTERNAL_32KHz_LOW_SPEED_IRC     = 0x03,

} system_clock_t;
typedef enum {

    SYSTEM_ISP_AREA = 0,
    USER_PROGRAM_AREA,

} software_reset_type;

typedef enum {

    ALL_AS_GPIO = 0,
    P32P33_I2C,

} iomux_config;
typedef struct {

    system_clock_t clock_use;

} system_config_t;

struct system_operations {

    void ( *init )();
    void ( *reset )( uint8_t reset_type );
    void ( *wdt_init )();
    void ( *iomux )( uint8_t iomux_type );

};

/**********************
*      ENUMS
**********************/


/**********************
* GLOBAL PROTOTYPES
**********************/
void register_system_operations( struct system_operations *opr );
#endif
