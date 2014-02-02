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
#define COS_0		100000l
#define SIN_0		0l

#define COS_120		-50000l
#define SIN_120		86603l

#define COS_240		50000l
#define SIN_240		-86603l

#define CORR_SW		0
#define CORR_SE		-1

/* wind direction return values */
#define N			1
#define NE			2
#define E			3
#define SE			4
#define S			5
#define SW			6
#define W			7
#define NW			8

/* includes */
#include "system.h"

/* functions */
static void GetAvgValues(int *nNorth, int *nSouthWest, int *nSouthEast, int nMeasureCount, int nMeasureTimeInMs);
int GetWindDirection(void);

#endif /* WINDDIRMEASUREMENT_H_ */
