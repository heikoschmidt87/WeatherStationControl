/*
 * system.c
 *
 *  Created on: 02.02.2014
 *      Author: heiko
 *
 *  (C) Heiko Schmidt
 *  License: CC BY-NC-SA 4.0
 */

#include "../inc/system.h"

int check_bit(unsigned int Port_Pin, unsigned int Port_Bit) {

	if(Port_Pin & (1 << Port_Bit))
		return 1;
	else
		return 0;
}

unsigned long isqrt(unsigned long nVal) {

	unsigned long nSqu = 1;
	unsigned long nDiff = 3;

	while(nSqu <= nVal) {
		nSqu = nSqu + nDiff;
		nDiff = nDiff + 2;
	}

	return (nDiff / 2 - 1);
}
