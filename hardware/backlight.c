/*
 * backlight.c
 *
 *  Created on: 12 февр. 2018 г.
 *      Author: ru
 */

#include "backlight.h"

#include <util/delay.h>
#include <avr/io.h>

void configureBacklight(void)
{
	DDRD |= (1 << DDD2);

}

void switchBacklight(uint8_t bl)
{
	if (bl) PORTD |= (1 << PORTD2); else PORTD &= ~(1 << PORTD2);
}

void blinkBacklight(void)
{
	switchBacklight(BACKLIGHT_ON);
	_delay_ms(100);
	switchBacklight(BACKLIGHT_OFF);
}
