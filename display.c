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

#define BCD_LO(x) x & 0x0F
#define BCD_HI(x) x  >> 4

typedef enum {
	cp1 = 0,
	cp2,
	cp3,
	cp4
} CurPos;

volatile CurPos CUR_POS;

volatile uint8_t BLINK_STATE = 0;

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

void setDisplayData(uint8_t* pData, uint8_t flags, uint8_t pFlags)
{
	DISPLAY.pData = pData;
	DISPLAY.flags = flags;
	DISPLAY.pointFlags = pFlags;
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
	uint8_t pdd = 0;
	switch (CUR_POS) {
	case cp1 : pdd = BCD_LO(*(DISPLAY.pData)); break;
	case cp2 : pdd = BCD_HI(*(DISPLAY.pData)); break;
	case cp3 : pdd = BCD_LO(*(DISPLAY.pData + 1)); break;
	case cp4 : pdd = BCD_HI(*(DISPLAY.pData + 1)); break;
	}
	PORTD = (pdd << 4) | pd;
	//Включаем отображение
	uint8_t pb = PINB & ~(D_AN_DIG_MASK | D_AN_POINT_MASK);
	uint8_t df = DISPLAY.flags & 0x0F;
	uint8_t bf = (DISPLAY.flags >> 4) & (BLINK_STATE ? 0x0F : 0x00);
	uint8_t upf = ((DISPLAY.pointFlags & POINT_U_SHOW) > 0) || (((DISPLAY.pointFlags & POINT_U_BLINK) > 0) && BLINK_STATE);
	uint8_t dpf = ((DISPLAY.pointFlags & POINT_D_SHOW) > 0) || (((DISPLAY.pointFlags & POINT_D_BLINK) > 0) && BLINK_STATE);
	PORTB = ((1 << CUR_POS) & (df | bf)) | (upf << PORTB4) | (dpf << PORTB5) | pb;
	//Сдвигаем позицию
	shiftPos();
}

void blink(void)
{
	BLINK_STATE = !BLINK_STATE;
}
