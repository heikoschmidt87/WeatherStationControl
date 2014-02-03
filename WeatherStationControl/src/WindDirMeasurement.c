/*
 * WindDirMeasurement.c
 *
 *  Created on: 02.02.2014
 *      Author: heiko
 *
 *  (C) Heiko Schmidt
 *  License: CC BY-NC-SA 4.0
 */

#include "../inc/WindDirMeasurement.h"

static void GetAvgValues(long *nNorth, long *nSouthWest, long *nSouthEast, int nMeasureCount, const int nMeasureDelayTimeInMs) {

	*nNorth = 0;
	*nSouthWest = 0;
	*nSouthEast = 0;


	/* configure ADC */
	ADMUX = (1 << REFS0) | (1 << ADLAR);
	ADCSRA |= (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);

	/* dummy readout as advised by Atmel */
	ADCSRA |= (1 << ADSC);
	while(ADSC & (1 << ADSC));
	(void) ADCH;				/* readout ADCH to enable conversion */

	/* we use 8 bit adc (ADCH) and shift two times right to have 6 bit ADC, as this is enough accuracy and avoids too much deviation */

	for(int i = 0; i < nMeasureCount; i++)
	{
		/* get 0 deg */
		ADMUX = (ADMUX & ~(0x1F)) | (CH_DIR_0 & 0x1F);		/* clear and set channel */

		ADCSRA |= (1 << ADSC);
		while(ADSC & (1 << ADSC));							/* TODO: check timing/deadlocks */

		if(i > 0)
			*nNorth = (*nNorth + (ADCH >> 2)) / 2;
		else
			*nNorth = (ADCH >> 2);

		// get south-west
		ADMUX = (ADMUX & ~(0x1F)) | (CH_DIR_120 & 0x1F);	/* clear and set channel */

		ADCSRA |= (1 << ADSC);
		while(ADSC & (1 << ADSC));							/* TODO: check timing/deadlocks */

		if(i > 0)
			*nSouthWest = (*nSouthWest + (ADCH >> 2) + CORR_SW) / 2;
		else
			*nSouthWest = (ADCH >> 2) + CORR_SW;


		ADMUX = (ADMUX & ~(0x1F)) | (CH_DIR_240 & 0x1F);	/* clear and set channel */

		ADCSRA |= (1 << ADSC);
		while(ADSC & (1 << ADSC));							/* TODO: check timing/deadlocks */

		if(i > 0)
			*nSouthEast = (*nSouthEast + (ADCH >> 2) + CORR_SE) / 2;
		else
			*nSouthEast = (ADCH >> 2) + CORR_SE;

		_delay_ms(nMeasureDelayTimeInMs);
	}
}

int GetWindDirection(void) {

	long nNorth, nSouthWest, nSouthEast;

	GetAvgValues(&nNorth, &nSouthWest, &nSouthEast, 10, 100);

	/* get vector components and scale down by 10^5 - truncate fractional part */
	long nVecNorth_x = (COS_0 * nNorth) / 1e5;
	long nVecNorth_y = (SIN_0 * nNorth) / 1e5;

	long nVecSouthWest_x = (COS_120 * nSouthWest) / 1e5;
	long nVecSouthWest_y = (SIN_120 * nSouthWest) / 1e5;

	long nVecSouthEast_x = (COS_240 * nSouthEast) / 1e5;
	long nVecSouthEast_y = (SIN_240 * nSouthEast) / 1e5;

	/* calculate the sum vector - base for direction angle and to determine if no wind speed */
	long nVec_sum_x = nVecNorth_x + nVecSouthWest_x + nVecSouthEast_x;
	long nVec_sum_y = nVecNorth_y + nVecSouthWest_y + nVecSouthEast_y;

	/* calculate angle - take care for special cases */
	int nDeg = 400;
	unsigned int nQuadrant = 0;

	if((nVec_sum_x == 0) && (nVec_sum_y == 0))		// vergleich mit betrag von summenvektor --> windstille detektieren
		nDeg = -1;
	else if((nVec_sum_x > 0) && (nVec_sum_y == 0))
		nDeg = 0;
	else if((nVec_sum_x == 0) && (nVec_sum_y > 0))
		nDeg = 90;
	else if((nVec_sum_x < 0) && (nVec_sum_y == 0))
		nDeg = 180;
	else if((nVec_sum_x == 0) && (nVec_sum_y < 0))
		nDeg = 270;
	else
	{
		if((nVec_sum_x > 0) && (nVec_sum_y > 0))
			nQuadrant = 1;
		else if((nVec_sum_x < 0) && (nVec_sum_y > 0))
			nQuadrant = 2;
		else if((nVec_sum_x < 0) && (nVec_sum_y < 0))
			nQuadrant = 3;
		else
			nQuadrant = 4;

		int nPhi = ((360 * atan2(abs(nVec_sum_y), abs(nVec_sum_x))) / (2 * PI_1e5)) / 1e5;		/* scale down by 10^5 * 10^5 */

		switch(nQuadrant) {
			case 1: nDeg = nPhi; break;
			case 2: nDeg = 180 - nPhi; break;
			case 3: nDeg = 180 + nPhi; break;
			case 4: nDeg = 360 - nPhi; break;
		}
	}

	/* calculate sum vector length - indication for air flow strength */
	int nSumVectLength = isqrt(nVec_sum_x * nVec_sum_x + nVec_sum_y * nVec_sum_y);
	int nDir = DIR_NONE;

	if((nDeg == -1) || (nSumVectLength < MIN_SUM_VECT_LENGTH))
		nDir = DIR_NONE;
	else if((nDeg < 23) || (nDeg > 337))
		nDir = DIR_N;
	else if((nDeg >= 23) && (nDeg < 68))
		nDir = DIR_NW;
	else if((nDeg >= 68) && (nDeg < 113))
		nDir = DIR_W;
	else if((nDeg >= 113) && (nDeg < 158))
		nDir = DIR_SW;
	else if((nDeg >= 158) && (nDeg < 203))
		nDir = DIR_S;
	else if((nDeg >= 203) && (nDeg < 248))
		nDir = DIR_SE;
	else if((nDeg >= 248) && (nDeg < 293))
		nDir = DIR_E;
	else if((nDeg >= 293) && (nDeg < 338))
		nDir = DIR_NE;

	return nDir;
}
