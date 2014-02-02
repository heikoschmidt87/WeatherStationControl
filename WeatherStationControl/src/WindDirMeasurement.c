/*
 * WindDirMeasurement.c
 *
 *  Created on: 02.02.2014
 *      Author: heiko
 */

#include "../inc/WindDirMeasurement.h"

static void GetAvgValues(int *nNorth, int *nSouthWest, int *nSouthEast, int nMeasureCount, const int nMeasureTimeInMs) {
	*nNorth = 0;
	*nSouthWest = 0;
	*nSouthEast = 0;

	// dummy readout
	ADCSRA |= (1 << ADSC);
	while(ADSC & (1 << ADSC));
	(void) ADCH;				// lesen, damit neue Wandlung freigegeben wird


	for(int i = 0; i < nMeasureCount; i++)
	{
		// get north
		ADMUX = (ADMUX & ~(0x1F)) | (2 & 0x1F);		// channel löschen und 2 setzen --> N, 0°

		ADCSRA |= (1 << ADSC);
		while(ADSC & (1 << ADSC));

		if(i > 0)
			*nNorth = (*nNorth + (ADCH >> 2)) / 2;
		else
			*nNorth = (ADCH >> 2);

		// get south-west
		ADMUX = (ADMUX & ~(0x1F)) | (3 & 0x1F);		// channel löschen und 3 setzen --> SW, 120°

		ADCSRA |= (1 << ADSC);
		while(ADSC & (1 << ADSC));

		if(i > 0)
			*nSouthWest = (*nSouthWest + (ADCH >> 2) + CORR_SW) / 2;
		else
			*nSouthWest = (ADCH >> 2) + CORR_SW;


		ADMUX = (ADMUX & ~(0x1F)) | (4 & 0x1F);		// channel löschen und 4 setzen --> SO, 240°

		ADCSRA |= (1 << ADSC);
		while(ADSC & (1 << ADSC));

		if(i > 0)
			*nSouthEast = (*nSouthEast + (ADCH >> 2) + CORR_SE) / 2;
		else
			*nSouthEast = (ADCH >> 2) + CORR_SE;

		_delay_ms(nMeasureTimeInMs);
	}

}

int GetWindDirection(void) {

}
