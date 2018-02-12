/*
 * buzzer.c
 *
 *  Created on: 10 февр. 2018 г.
 *      Author: ru
 */

#include "buzzer.h"

#include <avr/io.h>
#include <util/delay.h>

void configureBuzzer(void)
{
	DDRC |= (1 << DDC0);
}

void beep(void)
{
	PORTC |= (1 << PORTC0);
	_delay_ms(50);
	PORTC &= ~(1 << PORTC0);
}
