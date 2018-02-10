/*
 * datetimedata.h
 *
 *  Created on: 3 февр. 2018 г.
 *      Author: ru
 */

#ifndef DATASTRUCT_DATETIMEDATA_H_
#define DATASTRUCT_DATETIMEDATA_H_

#include <stdint.h>

typedef struct DisplayData {
	uint8_t* pData;
	uint8_t flags;
	uint8_t pointFlags;
} DisplayData;

uint8_t RTC_DATA[6];
uint8_t TEMP_DATA[2];

uint8_t* P_RTC_D_SECOND;
uint8_t* P_RTC_D_MINUTE;
uint8_t* P_RTC_D_HOUR;
uint8_t* P_RTC_D_DAY;
uint8_t* P_RTC_D_MONTH;
uint8_t* P_RTC_D_YEAR;

uint8_t* P_RTC_DS_TIME;
uint8_t* P_RTC_DS_DATE;

uint8_t* P_TEMP_DATA;
uint8_t* P_TEMP_DS_DATA;

volatile DisplayData DISPLAY;

#endif /* DATASTRUCT_DATETIMEDATA_H_ */
