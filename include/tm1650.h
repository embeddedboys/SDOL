/**
 * @file tm1650.h
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

#ifndef __TM1650_H
#define __TM1650_H

/*********************
*      INCLUDES
*********************/
#ifndef STCMCU_H
    #include "stcmcu.h"
#endif
#include "gpio_i2c.h"

/*********************
 *      DEFINES
 *********************/
#define TM1650_DISPLAY_REG 0x48
#define TM1650_COMMAND_READ_KEY 0x49

/*********************
 *  GLOBAL VARIABLE
 *********************/

/**********************
*      TYPEDEFS
**********************/

/**
 * @brief TM1650控制结构体
 */
typedef struct {

    float temperature;
    float humidity;
    uint8_t checksum;
    
} tm1650_handle_t;

/**
 * @brief TM1650配置结构体
 */
typedef union {
    struct {
        uint8_t power : 3;
        uint8_t segment_format : 1;
        uint8_t brightness : 4;
    } display_register;
    
    uint8_t full;
} tm1650_config_t;

/**********************
*      ENUMS
**********************/

/**
 * @brief TM1650辉度级别
 */
typedef enum {

    TM1650_BRIGHTNESS_LEVEL_8 = 0,
    TM1650_BRIGHTNESS_LEVEL_1 = 1,
    TM1650_BRIGHTNESS_LEVEL_2 = 2,
    TM1650_BRIGHTNESS_LEVEL_3 = 3,
    TM1650_BRIGHTNESS_LEVEL_4 = 4,
    TM1650_BRIGHTNESS_LEVEL_5 = 5,
    TM1650_BRIGHTNESS_LEVEL_6 = 6,
    TM1650_BRIGHTNESS_LEVEL_7 = 7,
    
} tm1650_brightness_level_t;

/**
 * @brief TM1650数码管显示状态
 */
typedef enum {

    TM1650_DISPLAY_POWER_OFF = 0,
    TM1650_DISPLAY_POWER_ON = 1,
    
} tm1650_display_power_t;

/**
 * @brief TM1650数码管段格式
 */
typedef enum {

    TM1650_SEGMENT_FORMAT_8 = 0,
    TM1650_SEGMENT_FORMAT_7 = 1,
    
} tm1650_segment_format_t;

/**
 * @brief TM1650数码管位号
 */
typedef enum {

    TM1650_BIT_1 = 0x68,
    TM1650_BIT_2 = 0x6a,
    TM1650_BIT_3 = 0x6c,
    TM1650_BIT_4 = 0x6e,
    
} tm1650_bit_selection_t;

/**
 * @brief TM1650段码值（共阴极数码管）
 */
typedef enum {

    TM1650_SEGMENT_VALUE_0 = 0x3f, /* `0` */
    TM1650_SEGMENT_VALUE_1 = 0x06, /* `1` */
    TM1650_SEGMENT_VALUE_2 = 0x5b, /* `2` */
    TM1650_SEGMENT_VALUE_3 = 0x4f, /* `3` */
    TM1650_SEGMENT_VALUE_4 = 0x66, /* `4` */
    TM1650_SEGMENT_VALUE_5 = 0x6d, /* `5` */
    TM1650_SEGMENT_VALUE_6 = 0x7d, /* `6` */
    TM1650_SEGMENT_VALUE_7 = 0x07, /* `7` */
    TM1650_SEGMENT_VALUE_8 = 0x7f, /* `8` */
    TM1650_SEGMENT_VALUE_9 = 0x6f, /* `9` */
    
} tm1650_segment_value_t;

/**********************
*      STRUCT
**********************/
struct tm1650_operations {

    void ( *init )();
    void ( *deinit )();
    
    void ( *write_register )( uint8_t command, uint8_t dat );
    
    void ( *set_brightness )( tm1650_brightness_level_t level );
    void ( *set_display )( tm1650_display_power_t state );
    void ( *set_segment_format )( tm1650_segment_format_t format );
    
    void ( *show_bit )( tm1650_bit_selection_t which,
                        tm1650_segment_value_t value );

    uint8_t ( *read_key )();
};

/**********************
* GLOBAL PROTOTYPES
**********************/
void register_tm1650_operations( struct tm1650_operations *opr );
#endif
