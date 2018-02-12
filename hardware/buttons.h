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

#define BUTTON_LP_MENU 0x40

volatile uint8_t BUTTONS;
volatile uint8_t B_FLAGS;

#define IS_B_MENU_PRESSED (BUTTONS & BUTTON_MENU)
#define IS_B_UP_PRESSED (BUTTONS & BUTTON_UP)
#define IS_B_DN_PRESSED (BUTTONS & BUTTON_DN)
#define IS_B_MENU_LONG_PRESSED (BUTTONS & BUTTON_LP_MENU)

#define SET_B_MENU_FLAG B_FLAGS |= BUTTON_MENU
#define SET_B_UP_FLAG B_FLAGS |= BUTTON_UP
#define SET_B_DN_FLAG B_FLAGS |= BUTTON_DN
#define SET_B_MENU_LP_FLAG B_FLAGS |= BUTTON_LP_MENU

#define UNSET_B_MENU_FLAG B_FLAGS &= ~BUTTON_MENU
#define UNSET_B_UP_FLAG B_FLAGS &= ~BUTTON_UP
#define UNSET_B_DN_FLAG B_FLAGS &= ~BUTTON_DN
#define UNSET_B_MENU_LP_FLAG B_FLAGS &= ~BUTTON_LP_MENU

#define IS_B_MENU_FLAG_SET (B_FLAGS & BUTTON_MENU)
#define IS_B_UP_FLAG_SET (B_FLAGS & BUTTON_UP)
#define IS_B_DN_FLAG_SET (B_FLAGS & BUTTON_DN)
#define IS_B_MENU_LP_FLAG_SET (B_FLAGS & BUTTON_LP_MENU)

void configureButtons(void);

void readButtons(void);

uint8_t isMenuPressed(void);
uint8_t isUpPressed(void);
uint8_t isDnPressed(void);

uint8_t isMenuLongPressed(void);

#endif /* HARDWARE_BUTTONS_H_ */
