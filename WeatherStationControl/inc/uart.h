/*
 * uart.h
 *
 *  Created on: 02.02.2014
 *      Author: heiko
 *
 *  Based on mikrocontroller.net UART description - Thanks!
 *  Link: https://www.mikrocontroller.net/articles/AVR-GCC-Tutorial/Der_UART
 */

#ifndef UART_H_
#define UART_H_

/* defined */
#define BAUD	9600

/* includes */
#include "system.h"
#include <util/setbaud.h>

/* functions */
void uart_init(void);
int uart_putc(unsigned char c);
void uart_puts(char *s);


#endif /* UART_H_ */
