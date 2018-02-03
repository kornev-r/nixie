/*
 * statemachine.h
 *
 *  Created on: 1 февр. 2018 г.
 *      Author: ru
 */

#ifndef STATEMACHINE_H_
#define STATEMACHINE_H_

/*
 * Состояния конечного автомата
 */
typedef enum {
	dsIndTime,
	dsIndDate,
	dsIndTemp,
	dsSetMin,
	dsSetHour,
	dsSetDay,
	dsSetMon,
	dsSetYear,
	dsSetOptBacklight,
	dsSetOptSound
} DisplayState;

void stateMachine(void);

void init(void);

void run(void);

#endif /* STATEMACHINE_H_ */
