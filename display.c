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

#define D_DC_MASK 0xF0u

#define D_AN_DIG_MASK 0x0Fu

#define D_AN_POINT_MASK 0x30u

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

void setDisplayData16(uint16_t d)
{
	DISPLAY.data = d;
	DISPLAY.dDigits = getDigits(d);
}

void setDisplayData(uint8_t h, uint8_t l)
{
	setDisplayData16(h * 100 + l);
}

void point(uint8_t on)
{
	if (on) PORTB |= (1 << PORTB4) | (1 << PORTB5);
	else PORTB &= ~((1 << PORTB4) | (1 << PORTB5));

}

void indicate()
{
	//Устанавливаем цифру на дешифраторе
	uint8_t pd = PIND & (~D_DC_MASK);
	PORTD = (DISPLAY.dDigits.d[CUR_POS] << 4) | pd;
	//Включаем отображение
	uint8_t pb = PINB & (~D_AN_DIG_MASK);
	PORTB = (1 << CUR_POS) | pb;
	//Сдвигаем позицию
	shiftPos();
}

