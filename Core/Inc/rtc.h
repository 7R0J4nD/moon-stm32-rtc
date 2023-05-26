/*
 * rtc.h
 *
 *  Created on: May 18, 2022
 *      Author: Administrator
 */

#ifndef INC_RTC_H_
#define INC_RTC_H_



#endif /* INC_RTC_H_ */

extern char dateGet[15];
extern char timeGet[15];
extern bool timerState;


uint32_t RTC_Get_Time(void);
void Time_Init(void);
void Set_Time_To_Timestamp(struct tm ts);
void Convert_Timestamp_To_Time(time_t rawtime);
void Rtc_Save(void);


