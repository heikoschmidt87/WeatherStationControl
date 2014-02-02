/*
 * uart.c
 *
 *  Created on: 02.02.2014
 *      Author: heiko
 *
 *  Based on mikrocontroller.net UART description - Thanks!
 *  Link: https://www.mikrocontroller.net/articles/AVR-GCC-Tutorial/Der_UART
 */

#include "../inc/uart.h"

/* UART initializing */
void uart_init(void) {
	UBRRH = UBRRH_VALUE;
	UBRRL = UBRRL_VALUE;

#if USE_2X
	UCSRA |= (1 << U2X);
#else
	UCSRA &= ~(1 << U2X);
#endif

	UCSRB |= (1 << TXEN);									/* UART TX on */
	UCSRC = (1 << URSEL) | (1 << UCSZ1) | (1 << UCSZ0);		/* Async, 8N1 */
}

/* UART char send */
int uart_putc(unsigned char c) {

	/* wait for send buffer to be clear */
	while(!(UCSRA & (1 << UDRE)));				/* TODO: check for timing security/deadlock! */

	UDR = c;

	return 0;
}

/* UART string send */
void uart_puts(char *s) {

	while(*s) {
		/* send characters till *s != "\0" */
		uart_putc(*s);
		s++;
	}
}
