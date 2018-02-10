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
#include "datastruct/datetimedata.h"
#include "hardware/display.h"
#include "hardware/dstemp.h"
#include "hardware/buzzer.h"
#include "hardware/buttons.h"

#include "appconfig.h"

volatile DisplayState DISPLAY_STATE = dsPost;

volatile uint16_t TIMER_TICKS = 0;
volatile uint8_t TEMP_STATE = 0;

void post(void)
{
	uint8_t d[2];
	uint8_t* pd = &d[0];
	for (uint8_t i = 0; i < 10; i++) {
		d[0] = d[1] = (i | i << 4);
		beep();
		setDisplayData(pd, DIG_ALL_SHOW, POINT_ALL_SHOW);
		_delay_ms(300);
	}
}

void setDisplayState(DisplayState ds)
{
	DISPLAY_STATE = ds;
	switch (ds) {
		case dsIndTime :
			setDisplayData(P_RTC_DS_TIME, DIG_ALL_SHOW, POINT_ALL_BLINK);
			break;
		case dsIndDate :
			setDisplayData(P_RTC_DS_DATE, DIG_ALL_SHOW, POINT_D_SHOW);
			break;
		case dsIndTemp :
			setDisplayData(P_TEMP_DS_DATA, DIG_3_SHOW | DIG_4_SHOW, POINT_U_SHOW);
			break;
		default:
			break;
	}
	TIMER_TICKS = 0;
}

void stateMachine(void)
{
	if (DISPLAY_STATE == dsIndTime && TIMER_TICKS >= TIME_SHOW_PERIOD) {
		setDisplayState(dsIndDate);
	} else if (DISPLAY_STATE == dsIndDate && TIMER_TICKS >= DATE_SHOW_PERIOD) {
		setDisplayState(dsIndTemp);
	} else if (DISPLAY_STATE == dsIndTemp && TIMER_TICKS >= TEMP_SHOW_PERIOD) {
		setDisplayState(dsIndTime);
	} else if (DISPLAY_STATE == dsPost) {
		post();
		setDisplayState(dsIndTime);
	}
}

void rtcSync(void)
{
	ds1307_getdatebcd(P_RTC_D_YEAR, P_RTC_D_MONTH, P_RTC_D_DAY, P_RTC_D_HOUR, P_RTC_D_MINUTE, P_RTC_D_SECOND);
}

void tempSync(void)
{
	TEMP_STATE++;
	if (TEMP_STATE == 1) { //Запрос на измерение температуры
		startMeasure();
	} else if (TEMP_STATE == 2) {
		uint8_t t = readMeasure();
		*P_TEMP_DATA = (t + 6 * (t / 10));
		TEMP_STATE = 0;
	}
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
	OCR1AH = 0x00;
	OCR1AL = 0x1F;
	//Разрешаем прерывания
	sei();
}

ISR(TIMER1_COMPA_vect)
{
	indicate();
	readButtons();
}

uint8_t pt = 0;

void init(void)
{
	configureDisplay();
	configureTimer();
	configureTempSensor();
	configureBuzzer();
	configureButtons();
	ds1307_init();
	rtcSync();
}

void halfSecFuncs(void)
{
	rtcSync();
	tempSync();
	blink();
}

void fastFuncs(void)
{
	if (IS_B_MENU_PRESSED) beep();
}

uint16_t FAST_TICKS = 0;

void run(void)
{
	setDisplayData(P_RTC_DS_TIME, DIG_ALL_SHOW, POINT_ALL_BLINK);

	while(1) {

		FAST_TICKS++;
		if (FAST_TICKS > 50) {

			halfSecFuncs();
			stateMachine();

			TIMER_TICKS++;
			FAST_TICKS = 0;
		}

		fastFuncs();

		_delay_ms(10);

	}
}
