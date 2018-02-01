/*
 * display.h
 *
 *  Created on: 1 февр. 2018 г.
 *      Author: ru
 */

#ifndef DISPLAY_H_
#define DISPLAY_H_

#include <stdint.h>

//Видимость цифр
#define DIG_1_SHOW 0x01u
#define DIG_2_SHOW 0x02u
#define DIG_3_SHOW 0x04u
#define DIG_4_SHOW 0x08u

//Флаги мигания цифр
#define DIG_1_BLINK 0x10u
#define DIG_2_BLINK 0x20u
#define DIG_3_BLINK 0x40u
#define DIG_4_BLINK 0x80u

//Видимость точки
#define POINT_U_SHOW 0x01u
#define POINT_D_SHOW 0x02u

//Флаги мигания точки
#define POINT_U_BLINK 0x10u
#define POINT_D_BLINK 0x20u

//Сдвиг позиции для дин. индикации
void shiftPos(void);

//Целочисленное возведение в степень
uint16_t ipow(uint16_t a, uint16_t e);

//Получить текущую отображаемую цифруs
uint8_t getDigit(uint16_t d);

//Индикация
void indicate(uint16_t d, uint8_t df, uint8_t pf);


#endif /* DISPLAY_H_ */
