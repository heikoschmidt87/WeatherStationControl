/*
 * system.h
 *
 *  Created on: 01.02.2014
 *      Author: heiko
 *
 *  (C) Heiko Schmidt
 *  License: CC BY-NC-SA 4.0
 */

#ifndef SYSTEM_H_
#define SYSTEM_H_

/* defines */

/* macros */
#define SET_BIT(var, bit)	(var |= (1 << bit))
#define RST_BIT(var, bit)	(var &= ~(1 << bit))

/* includes */
#include <avr/io.h>
#include <avr/sfr_defs.h>

#include <util/delay.h>

#include <stdlib.h>
#include <stdfix-gcc.h>

#include <math.h>


/* helper functions */
int check_bit(unsigned int Port_Pin, unsigned int Port_Bit);
unsigned long isqrt(unsigned long nVal);

#endif /* SYSTEM_H_ */
