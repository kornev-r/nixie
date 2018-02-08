/*
 * display.h
 *
 *  Created on: 1 февр. 2018 г.
 *      Author: ru
 *
 *  Для дисплея используются пины 0-5 порта B для анодных ключей. 0-3 отвечают за цифры, 4, 5 - за точки.
 *  Пины 4-7 порта D используются для управления дешифратором
 */

#ifndef DISPLAY_H_
#define DISPLAY_H_

#include <stdint.h>

//Видимость цифр
#define DIG_1_SHOW 0x01u
#define DIG_2_SHOW 0x02u
#define DIG_3_SHOW 0x04u
#define DIG_4_SHOW 0x08u

#define DIG_L_SHOW DIG_1_SHOW | DIG_2_SHOW
#define DIG_H_SHOW DIG_3_SHOW | DIG_4_SHOW
#define DIG_ALL_SHOW DIG_L_SHOW | DIG_H_SHOW

//Флаги мигания цифр
#define DIG_1_BLINK 0x10u
#define DIG_2_BLINK 0x20u
#define DIG_3_BLINK 0x40u
#define DIG_4_BLINK 0x80u

#define DIG_L_BLINK DIG_1_BLINK | DIG_2_BLINK
#define DIG_H_BLINK DIG_3_BLINK | DIG_4_BLINK
#define DIG_ALL_BLINK DIG_L_BLINK | DIG_H_BLINK

//Видимость точки
#define POINT_U_SHOW 0x01u
#define POINT_D_SHOW 0x02u

//Флаги мигания точки
#define POINT_U_BLINK 0x10u
#define POINT_D_BLINK 0x20u

#define POINT_ALL_SHOW POINT_U_SHOW | POINT_D_SHOW
#define POINT_ALL_BLINK POINT_U_BLINK | POINT_D_BLINK

//Сдвиг позиции для дин. индикации
void shiftPos(void);

void configureDisplay();

void setDisplayData(uint8_t* pd, uint8_t flags, uint8_t pFlags);
//Индикация
void indicate();
void blink();
void point(uint8_t on)

#endif /* DISPLAY_H_ */
;
