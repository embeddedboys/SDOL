/**
 * @file i2c.h
 *
 */

#ifndef I2C_H
#define I2C_H

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

/**********************
*      STRUCT
**********************/


/**********************
* GLOBAL PROTOTYPES
**********************/
void i2c_init();
void i2c_start();
void i2c_sndack();
void i2c_sndnack();
void i2c_stop();
uint8_t i2c_readbyte();
void i2c_sendbyte ( uint8_t byte );

/**********************
*      MACROS
**********************/

#endif /* I2C_H */