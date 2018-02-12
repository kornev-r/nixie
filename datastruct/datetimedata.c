/*
 * datetimedata.c
 *
 *  Created on: 3 февр. 2018 г.
 *      Author: ru
 */

#include "datetimedata.h"

uint8_t RTC_DATA[6] = {0};
uint8_t TEMP_DATA[2] = {0};

uint8_t* P_RTC_D_SECOND = &RTC_DATA[0];
uint8_t* P_RTC_D_MINUTE = &RTC_DATA[1];
uint8_t* P_RTC_D_HOUR = &RTC_DATA[2];
uint8_t* P_RTC_D_DAY = &RTC_DATA[3];
uint8_t* P_RTC_D_MONTH = &RTC_DATA[4];
uint8_t* P_RTC_D_YEAR = &RTC_DATA[5];

uint8_t* P_RTC_DS_TIME = &RTC_DATA[1];
uint8_t* P_RTC_DS_DATE = &RTC_DATA[3];

uint8_t* P_TEMP_DATA = &TEMP_DATA[1];
uint8_t* P_TEMP_DS_DATA = &TEMP_DATA[0];


