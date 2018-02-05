/*
 * statemachine.c
 *
 *  Created on: 1 февр. 2018 г.
 *      Author: ru
 */

#include "statemachine.h"

#include <util/delay.h>
#include <avr/interrupt.h>

#include "3rdparty/ds1307/ds1307.h"

#include "display.h"
#include "datastruct/datetimedata.h"


extern RtcDataItem RTC_DATA;

volatile DisplayState DISPLAY_STATE = dsIndTime;

volatile uint8_t blink = 0;

void stateMachine(void)
{
	switch (DISPLAY_STATE) {
	case dsIndTime : //Индикация времени
		break;
	case dsIndDate : //Индикация даты
		break;
	case dsIndTemp : //Индикация температуры
		break;
	default:
		break;
	}
}

void rtcSync(void)
{
	ds1307_getdate(&RTC_DATA.year, &RTC_DATA.month, &RTC_DATA.day, &RTC_DATA.hour, &RTC_DATA.minute, &RTC_DATA.second);
}

void configureTimer(void)
{
	TCCR1A = 0;
	TCCR1B = 0;
	TCNT1 = 0;
	//Сброс по совпадению
	TCCR1B |= (1 <<WGM12);
	//Устанавливаем разрешение прерывания по совпадению с OCR1A
	TIMSK1 |= (1 << OCIE1A);
	//Делитель 256
	TCCR1B |= (1 << CS12);
	//Период - полсекунды
	OCR1AH = 0x3D;
	OCR1AL = 0x09;
	//Разрешаем прерывания
	sei();
}

ISR(TIMER1_COMPA_vect)
{
	//Период - полсекунды
//	OCR1AH = 0x3D;
//	OCR1AL = 0x09;
	blink = 1;
}

uint8_t pt = 0;

void init(void)
{
	configureDisplay();
	point(1);
	configureTimer();
	ds1307_init();
	rtcSync();
	point(0);

}

void run(void)
{
	setDisplayData(RTC_DATA.hour, RTC_DATA.minute);
	while(1) {
		indicate();
		if (blink) {
			blink = 0;
			rtcSync();
			setDisplayData(RTC_DATA.hour, RTC_DATA.minute);
			point(pt);
			pt = !pt;

		}
		_delay_us(1500);
		//stateMachine();
	}
}
