/*
 * WindDirMeasurement.h
 *
 *  Created on: 02.02.2014
 *      Author: heiko
 */

#ifndef WINDDIRMEASUREMENT_H_
#define WINDDIRMEASUREMENT_H_

/* defines */

/* multiplication for sin/cos at angles, fixed point 10^5 */
#define COS_0		100000
#define SIN_0		0

#define COS_120		-50000
#define SIN_120		86603

#define COS_240		50000
#define SIN_240		-86603

#define CORR_SW		0
#define CORR_SE		-1

#define PI_1e5		314159

/* wind direction return values */
#define DIR_NONE	0
#define DIR_N		1
#define DIR_NE		2
#define DIR_E		3
#define DIR_SE		4
#define DIR_S		5
#define DIR_SW		6
#define DIR_W		7
#define DIR_NW		8

/* ADC channels */
#define CH_DIR_0	2
#define CH_DIR_120	3
#define CH_DIR_240	4

/* sum vector length at which air flow is present */
#define MIN_SUM_VECT_LENGTH		10					/* TODO: evaluate this */

/* includes */
#include "system.h"

/* functions */
static void GetAvgValues(long *nNorth, long *nSouthWest, long *nSouthEast, int nMeasureCount, int nMeasureDelayTimeInMs);
int GetWindDirection(void);

#endif /* WINDDIRMEASUREMENT_H_ */
