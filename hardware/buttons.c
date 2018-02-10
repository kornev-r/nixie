/*
 * buttons.c
 *
 *  Created on: 10 февр. 2018 г.
 *      Author: ru
 */

#include "buttons.h"

#include <avr/io.h>

void configureButtons(void)
{
	DDRC &= ~((1 << DDC1) | (1 << DDC2) | (1 << DDC3));
}

void readButtons(void)
{
	uint8_t bs = ~(PINC & ((1 << PC1) | (1 << PC2) | (1 << PC3)));
	BUTTONS = bs & 0x0E;
}

