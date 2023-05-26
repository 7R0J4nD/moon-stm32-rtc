/*
 * rtc.c
 *
 *  Created on: May 18, 2022
 *      Author: Administrator
 */


#include "main.h"
#include "rtc.h"
#include "serialCommand.h"




char dateGet[15];
char timeGet[15];




uint32_t RTC_Get_Time(void)
{
	RTC_DateTypeDef gDate;
	RTC_TimeTypeDef gTime;
	struct tm test;
	uint32_t timestampGet;

	HAL_RTC_GetTime(&hrtc, &gTime, RTC_FORMAT_BIN);
	HAL_RTC_GetDate(&hrtc, &gDate, RTC_FORMAT_BIN);

	//Display time Format: hh:mm:ss and Display date Format: yy-mm-dd
	sprintf((char*)timeGet,"%02d:%02d:%02d",gTime.Hours, gTime.Minutes, gTime.Seconds);
	sprintf((char*)dateGet,"%2d-%02d-%02d",(gDate.Year + 1900), gDate.Month, gDate.Date);
	//HAL_RTCEx_GetTimeStamp(&hrtc, &tTime, &tDate, RTC_FORMAT_BIN);

	test.tm_year = gDate.Year;  // + 100;  // In fact: 2000 + 18 - 1900
	test.tm_mday = gDate.Date;
	test.tm_mon  = (gDate.Month - 1);   // - 1;

	test.tm_hour = gTime.Hours;
	test.tm_min  = gTime.Minutes;
	test.tm_sec  = gTime.Seconds;

	timestampGet = mktime(&test);
	return timestampGet;

}


void Time_Init(void)
{

	/** Initialize RTC and set the Time and Date */
	RTC_TimeTypeDef sTime = {0};
	RTC_DateTypeDef sDate = {0};

	/** Initialize RTC and set the Time and Date */
	sTime.Hours = 10;
	sTime.Minutes = 0;
	sTime.Seconds = 0;
	sTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
	sTime.StoreOperation = RTC_STOREOPERATION_RESET;
	if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN) != HAL_OK)
	{
		Error_Handler();
	}
	sDate.WeekDay = RTC_WEEKDAY_MONDAY;
	sDate.Month = RTC_MONTH_JANUARY;
	sDate.Date = 1;
	sDate.Year = 99;

	if (HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BIN) != HAL_OK)
	{
		Error_Handler();
	}

}


void Set_Time_To_Timestamp(struct tm ts)
{

	RTC_TimeTypeDef sTime = {0};
	RTC_DateTypeDef sDate = {0};

	sTime.Hours = ts.tm_hour;
	sTime.Minutes = ts.tm_min;
	sTime.Seconds = ts.tm_sec;
	sTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
	sTime.StoreOperation = RTC_STOREOPERATION_RESET;
	if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN) != HAL_OK)
	{
		Error_Handler();
	}
	sDate.WeekDay = (ts.tm_wday + 1);
	sDate.Month = (ts.tm_mon + 1);
	sDate.Date = ts.tm_mday;
	sDate.Year = ts.tm_year;  // TODO --> à revoir :: doit prendre de 0 à 99, hors tm_year return 122
	if (HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BIN) != HAL_OK)
	{
		Error_Handler();
	}

}


void Convert_Timestamp_To_Time(time_t rawtime)
{

  struct tm  ts;

  /* Format time, "ddd yyyy-mm-dd hh:mm:ss zzz" */
  ts = *localtime(&rawtime);
  Set_Time_To_Timestamp(ts);

}
