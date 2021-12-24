/**
 * @file ds1302.h
 *
 */
#ifndef SYSTEM_H
#define SYSTEM_H

/*********************
* Documents for ds1302
*********************/
/**
	3-wire synchronous serial communication
	Vcc1 and Vcc2 dual power supply
	
	7   6      5   4   3   2   1   0
	1 RAM/CK#  A4  A3  A2  A1  A0  RD/WR#
	
	
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


/**********************
*      TYPEDEFS
**********************/
struct ds1302_operations {
	void ( *read ) ();
	void ( *write ) ();
	void ( *init ) ();
	void ( *deinit ) ();
};


/**********************
*      ENUMS
**********************/

/**********************
* GLOBAL PROTOTYPES
**********************/
void register_ds1302_operations ( struct ds1302_operations *opr );
#endif
