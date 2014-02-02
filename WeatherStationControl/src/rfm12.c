/*
 * rfm12.c
 *
 *  Created on: 02.02.2014
 *      Author: heiko
 */

#include "../inc/rfm12.h"

void RFM12_init () {
	RFM12_SEL_off ();
	RFM12_SDI_on ();
	RFM12_SCK_off ();

	SET_BIT (RFM12_SEL_dir, RFM12_SEL_bit);		//	SEL = Output
	SET_BIT (RFM12_SDI_dir, RFM12_SDI_bit);		//	SDI = Output
	RST_BIT (RFM12_SDO_dir, RFM12_SDO_bit);	//	SDO = Input
	SET_BIT (RFM12_SCK_dir, RFM12_SCK_bit);		//	SCK = Output

	RST_BIT (RFM12_IRQ_dir, RFM12_IRQ_bit);	//	IRQ = Input

	RFM12_PWR_off;
	RFM12_command (RFM12_command_FREQ	|	1600);			//	Frequenz
	RFM12_command (RFM12_command_DTRT	|	36);			//	Datenrate 9600 kbps

	RFM12_command (RFM12_command_CONF	|	0b11100111);	//	Enable
	RFM12_command (RFM12_command_RXCT	|	0b10010100000);	//	Receiver Control Command
	RFM12_command (RFM12_command_DFLT	|	0b10101100);	//	Data Filter
	RFM12_command (RFM12_command_TXCC	|	0b001010000);	//	TX Config

	RFM12_command (RFM12_command_PWR	|	0b11111000);

	RFM12_FIFO_on;
	RFM12_AFC_on;
	RFM12_command (RFM12_command_STAT);
}

unsigned int RFM12_command (unsigned int command)
{
	unsigned int serial_data = 0;

	RFM12_SEL_on ();

	for (unsigned char i = 0; i < 16; i++)
	{

		if (command & 0x8000) RFM12_SDI_on (); else RFM12_SDI_off ();
		command <<= 1;

		RFM12_SCK_on ();

		serial_data <<= 1;
		if (check_bit(RFM12_SDO_pin, RFM12_SDO_bit)) serial_data |= 0x0001;
		_delay_us(1);
		RFM12_SCK_off ();
	}

	RFM12_SEL_off ();

	return serial_data;
}

void RFM12_send (unsigned char senden)
{
	loop_until_bit_is_clear (RFM12_IRQ_pin, RFM12_IRQ_bit);	//wait for previously TX over	/* TODO: check for timing security/deadlock! */
	RFM12_command (RFM12_command_TXRW | senden);
}

unsigned char RFM12_recv ()
{
	loop_until_bit_is_clear (RFM12_IRQ_pin, RFM12_IRQ_bit);	//wait for data					/* TODO: check for timing security/deadlock! */
	RFM12_command (RFM12_command_STAT);
	return RFM12_command (RFM12_command_RXFR) & 0x00FF;
}
