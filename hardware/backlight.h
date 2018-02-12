/*
 * backlight.h
 *
 *  Created on: 12 февр. 2018 г.
 *      Author: ru
 */

#ifndef HARDWARE_BACKLIGHT_H_
#define HARDWARE_BACKLIGHT_H_

#include <stdint.h>

#define BACKLIGHT_ON 1
#define BACKLIGHT_OFF 0

void configureBacklight(void);

void switchBacklight(uint8_t bl);

void blinkBacklight(void);


#endif /* HARDWARE_BACKLIGHT_H_ */
