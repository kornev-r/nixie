/*
 * dstemp.h
 *
 *  Created on: 10 февр. 2018 г.
 *      Author: ru
 */

#ifndef HARDWARE_DSTEMP_H_
#define HARDWARE_DSTEMP_H_

#include <stdint.h>

void configureTempSensor(void);

void startMeasure(void);

uint8_t readMeasure(void);

#endif /* HARDWARE_DSTEMP_H_ */
