/*
 * statemachine.c
 *
 *  Created on: 1 февр. 2018 г.
 *      Author: ru
 */

#include "statemachine.h"

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

void run(void)
{
	while(1) {
		stateMachine();
	}
}
