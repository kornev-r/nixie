/*
 * dstemp.c
 *
 *  Created on: 10 февр. 2018 г.
 *      Author: ru
 */

#include "dstemp.h"

#include <avr/io.h>

#include "../3rdparty/ds18b20/ds18b20.h"

#define TEMP_CORR -4

void configureTempSensor(void)
{
	ds18b20wsp(&PORTD, &DDRD, &PIND, (1 << PORTD3), 0, 0, 0, DS18B20_RES09);
}

void startMeasure(void)
{
	ds18b20convert(&PORTD, &DDRD, &PIND, (1 << PORTD3), 0);
}

uint8_t readMeasure(void)
{
	int16_t rt;
	ds18b20read(&PORTD, &DDRD, &PIND, (1 << PORTD3), 0, &rt);
	return (uint8_t) (rt >> 3) * 0.5 + TEMP_CORR;
}
