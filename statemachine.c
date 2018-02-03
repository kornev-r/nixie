/*
 * statemachine.c
 *
 *  Created on: 1 февр. 2018 г.
 *      Author: ru
 */

#include "statemachine.h"

#include "display.h"

volatile DisplayState DISPLAY_STATE = dsIndTime;

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

void init(void)
{
	configureDisplay();
}

void run(void)
{
	setDisplayData(1234);
	while(1) {
		indicate();
		//stateMachine();
	}
}
