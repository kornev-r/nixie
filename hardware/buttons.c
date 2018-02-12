/*
 * buttons.c
 *
 *  Created on: 10 февр. 2018 г.
 *      Author: ru
 */

#include "buttons.h"

#include <avr/io.h>

#define LONG_PRESS_CYCLES 2000

uint16_t lpCounter = 0;

void configureButtons(void)
{
	DDRC &= ~((1 << DDC1) | (1 << DDC2) | (1 << DDC3));
}

void readButtons(void)
{
	uint8_t bs = ~(PINC & ((1 << PC1) | (1 << PC2) | (1 << PC3)));
	BUTTONS = bs & 0x0E;

	if (IS_B_MENU_PRESSED && lpCounter < LONG_PRESS_CYCLES) {
		lpCounter++;
	} else if (IS_B_MENU_PRESSED && lpCounter >= LONG_PRESS_CYCLES) {
		BUTTONS |= BUTTON_LP_MENU;
	} else BUTTONS &= ~BUTTON_LP_MENU;
}

uint8_t isMenuPressed(void)
{
	if (IS_B_MENU_PRESSED && !IS_B_MENU_FLAG_SET) {
		SET_B_MENU_FLAG;
		return 1;
	} else if (!IS_B_MENU_PRESSED) UNSET_B_MENU_FLAG;
	return 0;
}
uint8_t isUpPressed(void)
{
	if (IS_B_UP_PRESSED && !IS_B_UP_FLAG_SET) {
		SET_B_UP_FLAG;
		return 1;
	} else if (!IS_B_UP_PRESSED) UNSET_B_UP_FLAG;
	return 0;
}
uint8_t isDnPressed(void)
{
	if (IS_B_DN_PRESSED && !IS_B_DN_FLAG_SET) {
		SET_B_DN_FLAG;
		return 1;
	} else if (!IS_B_DN_PRESSED) UNSET_B_DN_FLAG;
	return 0;
}

uint8_t isMenuLongPressed(void)
{
	if (IS_B_MENU_LONG_PRESSED && !IS_B_MENU_LP_FLAG_SET) {
		SET_B_MENU_LP_FLAG;
		lpCounter = 0;
		return 1;
	} else if (!IS_B_MENU_LONG_PRESSED) UNSET_B_MENU_LP_FLAG;
	return 0;
}

