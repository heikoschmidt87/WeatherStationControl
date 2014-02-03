/*
 * system.c
 *
 *  Created on: 02.02.2014
 *      Author: heiko
 */

#include "../inc/system.h"

int check_bit(unsigned int Port_Pin, unsigned int Port_Bit) {

	if(Port_Pin & (1 << Port_Bit))
		return 1;
	else
		return 0;
}

unsigned long isqrt(unsigned long nVal) {
	/* TODO: implement this */
	return 0;
}
