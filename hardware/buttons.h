/*
 * buttons.h
 *
 *  Created on: 10 февр. 2018 г.
 *      Author: ru
 */

#include <stdint.h>

#ifndef HARDWARE_BUTTONS_H_
#define HARDWARE_BUTTONS_H_

#define BUTTON_UP 0x02
#define BUTTON_MENU 0x04
#define BUTTON_DN 0x08

volatile uint8_t BUTTONS;

#define IS_B_MENU_PRESSED BUTTONS & BUTTON_MENU
#define IS_B_UP_PRESSED BUTTONS & BUTTON_UP
#define IS_B_DN_PRESSED BUTTONS & BUTTON_DN

void configureButtons(void);

void readButtons(void);

#endif /* HARDWARE_BUTTONS_H_ */
