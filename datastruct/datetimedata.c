/*
 * datetimedata.c
 *
 *  Created on: 3 февр. 2018 г.
 *      Author: ru
 */

#include "datetimedata.h"

uint8_t isEqual(DateTimeData left, DateTimeData right)
{
	uint8_t res = 1;

	res &= left.fDate == right.fDate;
	res &= left.fTime == right.fTime;
	res &= left.fYear == right.fYear;

	return res;
}

uint16_t ipow(uint16_t a, uint16_t e)
{
	uint16_t r = a;
	for (uint16_t i = 0; i < e; i++) r *= a;
	return r;
}

Digits getDigits(uint16_t dt)
{
	Digits dd = {{0,0,0,0}};
	uint8_t i = 0;
	while (dt) {
		dd.d[i++] = dt % 10;
		dt /= 10;
	}
	return dd;
}

void fillDateTimeData(DateTimeData* dt)
{
	dt->dDate = getDigits(dt->fDate);
	dt->dTime = getDigits(dt->fTime);
	dt->dYear = getDigits(dt->fYear);
}

