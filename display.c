/*
 * display.c
 *
 *  Created on: 1 февр. 2018 г.
 *      Author: ru
 */

#include "display.h"

#include <avr/io.h>
#include <math.h>

//Порт управления анодными ключами
#define D_AN_PORT PORTB
//Порт управления дешифратором
#define D_DC_PORT PORTD

typedef enum {
	cp1 = 0,
	cp2,
	cp3,
	cp4
} CurPos;

volatile CurPos CUR_POS = cp1;

uint8_t DISP_BUF[4];

void shiftPos(void)
{
	if (++CUR_POS > cp4) CUR_POS = cp1;
}

uint16_t ipow(uint16_t a, uint16_t e)
{
	uint16_t r = a;
	for (uint16_t i = 0; i < e; i++) r *= a;
	return r;
}

void getDigits(uint16_t d)
{
	uint16_t dd = d;
	uint8_t i = 0;
	while (dd) {
		DISP_BUF[i++] = dd % 10;
		dd /= 10;
	}
}

void indicate(uint16_t d, uint8_t df, uint8_t pf)
{

}
