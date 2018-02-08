/*
 * statemachine.c
 *
 *  Created on: 1 февр. 2018 г.
 *      Author: ru
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
 */

#include "statemachine.h"

#include <util/delay.h>
#include <avr/interrupt.h>

#include "3rdparty/ds1307/ds1307.h"

#include "datastruct/datetimedata.h"
#include "display.h"
#include "appconfig.h"

volatile DisplayState DISPLAY_STATE = dsIndTime;

volatile uint8_t TIMER_SHOT = 0;
volatile uint16_t TIMER_TICKS = 0;

void stateMachine(void)
{
	switch (DISPLAY_STATE) {
	case dsIndTime : //Индикация времени
		setDisplayData(P_RTC_DS_TIME, DIG_ALL_SHOW, POINT_ALL_BLINK);
		if (TIMER_TICKS >= TIME_SHOW_PERIOD) {
			DISPLAY_STATE = dsIndDate;
			TIMER_TICKS = 0;
		}
		break;
	case dsIndDate : //Индикация даты
		setDisplayData(P_RTC_DS_DATE, DIG_ALL_SHOW, POINT_D_SHOW);
		if (TIMER_TICKS >= DATE_SHOW_PERIOD) {
			DISPLAY_STATE = dsIndTemp;
			TIMER_TICKS = 0;
		}

		break;
	case dsIndTemp : //Индикация температуры
		setDisplayData(P_RTC_DS_DATE, DIG_ALL_SHOW, POINT_U_SHOW);
		if (TIMER_TICKS >= TEMP_SHOW_PERIOD) {
			DISPLAY_STATE = dsIndTime;
			TIMER_TICKS = 0;
		}
		break;
	default:
		break;
	}
}

void rtcSync(void)
{
//	*P_RTC_D_SECOND = 0x92;
//	*P_RTC_D_MINUTE = 0x86;
//	*P_RTC_D_HOUR = 0x56;
//	*P_RTC_D_DAY = 0x78;
//	*P_RTC_D_MONTH= 0x12;
//	*P_RTC_D_YEAR = 0x34;

	ds1307_getdatebcd(P_RTC_D_YEAR, P_RTC_D_MONTH, P_RTC_D_DAY, P_RTC_D_HOUR, P_RTC_D_MINUTE, P_RTC_D_SECOND);
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
	TIMER_SHOT = 1;
	TIMER_TICKS++;
}

uint8_t pt = 0;

void init(void)
{
	configureDisplay();
	configureTimer();
	ds1307_init();
	rtcSync();
}

void timerShot()
{
	rtcSync();
//	setDisplayData(P_RTC_DS_TIME, DIG_ALL_SHOW, POINT_ALL_BLINK);
	blink();
	TIMER_SHOT = 0;
}

void run(void)
{
	setDisplayData(P_RTC_DS_TIME, DIG_ALL_SHOW, POINT_ALL_BLINK);
	while(1) {
		stateMachine();
		indicate();
		if (TIMER_SHOT) timerShot();
		_delay_us(1500);
	}
}
