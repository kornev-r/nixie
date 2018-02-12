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
#include "hardware/backlight.h"

#include "appconfig.h"

volatile DisplayState DISPLAY_STATE = dsPost;

volatile uint16_t TIMER_TICKS = 0;
volatile uint8_t TEMP_STATE = 0;

uint8_t DO_SYNC = 1;

void post(void)
{
	uint8_t d[2];
	uint8_t* pd = &d[0];
	for (uint8_t i = 0; i < 10; i++) {
		d[0] = d[1] = (i | i << 4);
		beep();
		setDisplayData(pd, DIG_ALL_SHOW, POINT_ALL_SHOW);
		blinkBacklight();
		_delay_ms(200);

	}
}

uint8_t isSetupState(void)
{
	return DISPLAY_STATE == dsSetMinLo
			|| DISPLAY_STATE == dsSetMinHi
			|| DISPLAY_STATE == dsSetHourLo
			|| DISPLAY_STATE == dsSetHourHi
			|| DISPLAY_STATE == dsSetDayLo
			|| DISPLAY_STATE == dsSetDayHi
			|| DISPLAY_STATE == dsSetMonLo
			|| DISPLAY_STATE == dsSetMonHi
			|| DISPLAY_STATE == dsSetYearLo
			|| DISPLAY_STATE == dsSetYearHi;

}

void rtcSync(void)
{
	ds1307_getdatebcd(P_RTC_D_YEAR, P_RTC_D_MONTH, P_RTC_D_DAY, P_RTC_D_HOUR, P_RTC_D_MINUTE, P_RTC_D_SECOND);
}

void rtcSave(void)
{
	ds1307_setdatebcd(*P_RTC_D_YEAR, *P_RTC_D_MONTH, *P_RTC_D_DAY, *P_RTC_D_HOUR, *P_RTC_D_MINUTE, *P_RTC_D_SECOND);
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
		case dsSetMinLo :
			setDisplayData(P_RTC_DS_TIME, DIG_H_SHOW | DIG_2_SHOW | DIG_1_BLINK, POINT_ALL_SHOW);
			break;
		case dsSetMinHi :
			setDisplayData(P_RTC_DS_TIME, DIG_H_SHOW | DIG_2_BLINK | DIG_1_SHOW, POINT_ALL_SHOW);
			break;
		case dsSetHourLo :
			setDisplayData(P_RTC_DS_TIME, DIG_L_SHOW | DIG_3_BLINK | DIG_4_SHOW, POINT_ALL_SHOW);
			break;
		case dsSetHourHi :
			setDisplayData(P_RTC_DS_TIME, DIG_L_SHOW | DIG_3_SHOW | DIG_4_BLINK, POINT_ALL_SHOW);
			break;

		default:
			break;
	}
	TIMER_TICKS = 0;
}

void stateMachine(void)
{
	uint8_t mp = isMenuPressed();
	uint8_t up = isUpPressed();
	uint8_t dp = isDnPressed();
	uint8_t mlp = isMenuLongPressed();
	if (mp || mlp || dp || up) beep();
	if (mlp) {
		if (isSetupState()) {
			setDisplayState(dsIndTime);
			rtcSave();
		} else setDisplayState(dsSetMinLo);
		DO_SYNC = !isSetupState();

	}

	if (DISPLAY_STATE == dsIndTime && ((TIMER_TICKS >= TIME_SHOW_PERIOD) || mp)) {
		setDisplayState(dsIndDate);
	} else if (DISPLAY_STATE == dsIndDate && ((TIMER_TICKS >= DATE_SHOW_PERIOD) || mp)) {
		setDisplayState(dsIndTemp);
	} else if (DISPLAY_STATE == dsIndTemp && ((TIMER_TICKS >= TEMP_SHOW_PERIOD) || mp)) {
		setDisplayState(dsIndTime);
	} else if (DISPLAY_STATE == dsPost) {
		post();
		setDisplayState(dsIndTime);
		switchBacklight(BACKLIGHT_ON);
	}

	if (DISPLAY_STATE == dsSetMinLo) {
		if (up) {
			uint8_t dig = *P_RTC_D_MINUTE & 0x0F;
			if (dig == 9) dig = 0; else dig++;
			*P_RTC_D_MINUTE = (*P_RTC_D_MINUTE & 0xF0) + dig;
		}
		if (dp) {
			uint8_t dig = *P_RTC_D_MINUTE & 0x0F;
			if (dig == 0) dig = 9; else dig--;
			*P_RTC_D_MINUTE = (*P_RTC_D_MINUTE & 0xF0) + dig;
		}
		if (mp) setDisplayState(dsSetMinHi);
	} else if (DISPLAY_STATE == dsSetMinHi) {
		if (up) {
			uint8_t dig = (*P_RTC_D_MINUTE & 0xF0) >> 4;
			if (dig == 5) dig = 0; else dig++;
			*P_RTC_D_MINUTE = (*P_RTC_D_MINUTE & 0x0F) + (dig << 4);
		}
		if (dp) {
			uint8_t dig = (*P_RTC_D_MINUTE & 0xF0) >> 4;
			if (dig == 0) dig = 5; else dig--;
			*P_RTC_D_MINUTE = (*P_RTC_D_MINUTE & 0x0F) + (dig << 4);
		}

		if (mp) setDisplayState(dsSetHourLo);
	} else if (DISPLAY_STATE == dsSetHourLo) {
		if (up) {
			uint8_t dig = *P_RTC_D_HOUR & 0x0F;
			if (dig == 9) dig = 0; else dig++;
			*P_RTC_D_HOUR = (*P_RTC_D_HOUR & 0xF0) + dig;
		}
		if (dp) {
			uint8_t dig = *P_RTC_D_HOUR & 0x0F;
			if (dig == 0) dig = 9; else dig--;
			*P_RTC_D_HOUR = (*P_RTC_D_HOUR & 0xF0) + dig;
		}

		if (mp) setDisplayState(dsSetHourHi);
	} else if (DISPLAY_STATE == dsSetHourHi) {
		if (up) {
			uint8_t dig = (*P_RTC_D_HOUR & 0xF0) >> 4;
			if (dig == 2) dig = 0; else dig++;
			*P_RTC_D_HOUR = (*P_RTC_D_HOUR & 0x0F) + (dig << 4);
		}
		if (dp) {
			uint8_t dig = (*P_RTC_D_HOUR & 0xF0) >> 4;
			if (dig == 0) dig = 2; else dig--;
			*P_RTC_D_HOUR = (*P_RTC_D_HOUR & 0x0F) + (dig << 4);
		}
		if (mp) setDisplayState(dsSetMinLo);
	}

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
	configureBacklight();
	ds1307_init();
	rtcSync();
}

void halfSecFuncs(void)
{
	if (DO_SYNC) rtcSync();
	tempSync();
	blink();
}

uint8_t B_MENU_PRESSED_FLAG = 0;

void fastFuncs(void)
{
//	if (isMenuPressed()) {
//		beep();
//		DISPLAY_STATE++;
//		if (DISPLAY_STATE > dsIndTemp) DISPLAY_STATE = dsIndTime;
//		setDisplayState(DISPLAY_STATE);
//	}
//	if (isMenuLongPressed()) {
//		beep();
//		setDisplayState(dsSetMin);
//	}
}

uint16_t FAST_TICKS = 0;

void run(void)
{
	setDisplayData(P_RTC_DS_TIME, DIG_ALL_SHOW, POINT_ALL_BLINK);

	while(1) {

		FAST_TICKS++;
		if (FAST_TICKS > 50) {

			halfSecFuncs();

			TIMER_TICKS++;
			FAST_TICKS = 0;
		}
		stateMachine();

//		fastFuncs();

		_delay_ms(10);

	}
}
