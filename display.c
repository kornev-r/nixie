/*
 * display.c
 *
 *  Created on: 1 февр. 2018 г.
 *      Author: ru
 */

#include "display.h"

#include <avr/io.h>
#include <math.h>

#include "datastruct/datetimedata.h"

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

volatile DisplayData DISPLAY;

void configureDisplay()
{
	//Настраиваем порт для работы с анодными ключами
	DDRB |= (1 << DDB0) | (1 << DDB1) | (1 << DDB2) | (1 << DDB3) | (1 << DDB4) | (1 << DDB5);
	//Настраиваем порт D для работы с дешифратором
	DDRD |= (1 << DDD4) | (1 << DDD5) | (1 << DDD6) | (1 << DDD7);
}

void shiftPos(void)
{
	if (++CUR_POS > cp4) CUR_POS = cp1;
}

void setDisplayData(uint16_t d)
{
	DISPLAY.data = d;
	DISPLAY.dDigits = getDigits(d);
}

void indicate()
{
	//Пишем цифру в дешифратор
	PORTD |= DISPLAY.dDigits.d[CUR_POS];
	//Включаем нужный ключ
	PORTB |= (1 << CUR_POS);
	//Сдвигаем позицию
	shiftPos();
}

