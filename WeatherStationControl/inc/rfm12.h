/*
 * rfm12.h
 *
 *  Created on: 02.02.2014
 *      Author: heiko
 */

#ifndef RFM12_H_
#define RFM12_H_

/* includes */
#include "system.h"

/* port/pin definitions for software SPI */
#define RFM12_SEL_port	PORTB
#define RFM12_SEL_pin	PINB
#define RFM12_SEL_dir	DDRB
#define RFM12_SEL_bit	4
#define RFM12_SEL_on()	RST_BIT(RFM12_SEL_port,	RFM12_SEL_bit)
#define RFM12_SEL_off()	SET_BIT(RFM12_SEL_port,	RFM12_SEL_bit)

#define RFM12_SCK_port	PORTB
#define RFM12_SCK_pin	PINB
#define RFM12_SCK_dir	DDRB
#define RFM12_SCK_bit	7
#define RFM12_SCK_on()	SET_BIT(RFM12_SCK_port,	RFM12_SCK_bit)
#define RFM12_SCK_off()	RST_BIT(RFM12_SCK_port,	RFM12_SCK_bit)

#define RFM12_SDI_port	PORTB
#define RFM12_SDI_pin	PINB
#define RFM12_SDI_dir	DDRB
#define RFM12_SDI_bit	5
#define RFM12_SDI_on()	SET_BIT(RFM12_SDI_port,	RFM12_SDI_bit)
#define RFM12_SDI_off()	RST_BIT(RFM12_SDI_port,	RFM12_SDI_bit)

#define RFM12_SDO_port	PORTB
#define RFM12_SDO_pin	PINB
#define RFM12_SDO_dir	DDRB
#define RFM12_SDO_bit	6

#define	RFM12_IRQ_port	PORTD
#define	RFM12_IRQ_pin	PIND
#define	RFM12_IRQ_dir	DDRD
#define	RFM12_IRQ_bit	2

/* command definitions */
#define RFM12_command_CONF	0b1000000000000000	//	Configuration Setting Command
#define RFM12_command_PWR	0b1000001000000000	//	Power Management Command
#define RFM12_command_FREQ	0b1010000000000000	//	Frequency Setting Command
#define RFM12_command_DTRT	0b1100011000000000	//	Data Rate Command
#define RFM12_command_RXCT	0b1001000000000000	//	Receiver Control Command
#define RFM12_command_DFLT	0b1100001000000000	//	Data Filter Command
#define RFM12_command_FFRM	0b1100101000000000	//	FIFO Reset Mode Command
#define RFM12_command_RXFR	0b1011000000000000	//	Receiver FIFO Read Command
#define RFM12_command_AFC	0b1100010000000000	//	AFC Command
#define RFM12_command_TXCC	0b1001100000000000	//	TX Configuration Control Command
#define RFM12_command_TXRW	0b1011100000000000	//	Transmitter Register Write Command
#define RFM12_command_WAKE	0b1110000000000000	//	Wake-Up Timer Command
#define RFM12_command_LDC	0b1100100000000000	//	Low Duty-Cycle Command
#define RFM12_command_BDCD	0b1100000000000000	//	Low Battery Detector / Clock Divider Command
#define RFM12_command_STAT	0b0000000000000000	//	Status Read Command

#define RFM12_PWR_off	RFM12_command (RFM12_command_PWR	|	0b00000001);
#define RFM12_TX_on		RFM12_command (RFM12_command_PWR	|	0b00111001);
#define RFM12_TX_off	RFM12_command (RFM12_command_PWR	|	0b00000001);
#define RFM12_RX_on		RFM12_command (RFM12_command_PWR	|	0b11011001);
#define RFM12_RX_off	RFM12_command (RFM12_command_PWR	|	0b00011001);
#define RFM12_FIFO_on	RFM12_command (RFM12_command_FFRM	|	0b10000011);
#define RFM12_FIFO_off	RFM12_command (RFM12_command_FFRM	|	0b10000001);
#define RFM12_AFC_on	RFM12_command (RFM12_command_AFC	|	0b01000011);
#define RFM12_AFC_off	RFM12_command (RFM12_command_AFC	|	0b01000010);

/* functions */
void RFM12_init ();
unsigned int RFM12_command (unsigned int cmd);
void RFM12_send (unsigned char byte);
unsigned char RFM12_receive ();


#endif /* RFM12_H_ */
