/*
 * datetimedata.h
 *
 *  Created on: 3 февр. 2018 г.
 *      Author: ru
 */

#ifndef DATASTRUCT_DATETIMEDATA_H_
#define DATASTRUCT_DATETIMEDATA_H_

#include <stdint.h>

typedef struct Digits{
	uint8_t* pd;
} Digits;

typedef struct DisplayData {
	uint8_t* pData;
	uint8_t flags;
	uint8_t pointFlags;
} DisplayData;

typedef struct RtcDataItem {
	uint8_t year;
	uint8_t month;
	uint8_t day;
	uint8_t hour;
	uint8_t minute;
	uint8_t second;
} RtcDataItem;

typedef struct DateTimeData {
	/* Полные данные о дате, времени, годе */
	uint16_t fDate;
	uint16_t fTime;
	uint16_t fYear;

	/* Раскладка даты по цифрам */
	Digits dDate;

	/* Раскладка времени по цифрам */
	Digits dTime;
	/* Раскладка года по цифрам */
	Digits dYear;

} DateTimeData;

//uint8_t isEqual(DateTimeData left, DateTimeData right);
//
////Целочисленное возведение в степень
//uint16_t ipow(uint16_t a, uint16_t e);
//
////Получить текущую отображаемую цифруs
//Digits getDigits(uint16_t dt);
//
//void fillDateTimeData(DateTimeData* dt);

//RtcDataItem RTC_DATA;
uint8_t RTC_DATA[6];

uint8_t* P_RTC_D_SECOND;
uint8_t* P_RTC_D_MINUTE;
uint8_t* P_RTC_D_HOUR;
uint8_t* P_RTC_D_DAY;
uint8_t* P_RTC_D_MONTH;
uint8_t* P_RTC_D_YEAR;

uint8_t* P_RTC_DS_TIME;
uint8_t* P_RTC_DS_DATE;

volatile DisplayData DISPLAY;

#endif /* DATASTRUCT_DATETIMEDATA_H_ */
