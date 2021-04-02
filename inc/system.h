/**
 * @file system.h
 *
 */
#ifndef SYSTEM_H
#define SYSTEM_H

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
struct system_operations {
	void ( *init ) ();
	void ( *reset ) ( uint8_t reset_type );
	void ( *wdt_init ) ();
	void ( *iomux ) ( uint8_t iomux_type );
};


/**********************
*      ENUMS
**********************/
typedef enum {
	SYSTEM_ISP_AREA = 0,
	USER_PROGRAM_AREA,
} software_reset_type;

typedef enum {
	ALL_AS_GPIO = 0,
	P32P33_I2C,
} iomux_config;

/**********************
* GLOBAL PROTOTYPES
**********************/
void register_system_operations ( struct system_operations *opr );
#endif
