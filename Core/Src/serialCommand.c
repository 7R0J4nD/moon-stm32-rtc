/*
 * serialCommand.c
 *
 *  Created on: 12 mai 2022
 *      Author: Administrator
 */


#include "main.h"
#include "serialCommand.h"
#include "usbSerial.h"
#include "rtc.h"


#define  USB_SERIAL_COMMAND_DATA_TEST_MAX_LEN 1024


time_t lastRTC = 1661529600;





void Usb_Serial_Command_Get_Info()
{

	RTC_Get_Time();
	strcat(dateGet, " / ");
	char *response = strcat(dateGet, timeGet);
	strcat(response, "\n\n");
	Usb_Serial_Send_Data(response);

}


void Usb_Serial_Command_Set_Time(char *charTimestamp)
{
	char *response;
	time_t timestamp = atoi(charTimestamp);

	lastRTC = timestamp;
	Convert_Timestamp_To_Time(timestamp);
	response = "Time Set !\n";
	Usb_Serial_Send_Data(response);

}


void Usb_Serial_Command_Test_Data(char *size)
{
	int testDataSize = 0;
	char *response = "";
	char chaine[] = "s";

	testDataSize = (atoi(size) +2);

	if(testDataSize < USB_SERIAL_COMMAND_DATA_TEST_MAX_LEN)
	{

		for(int i = 0; i < (testDataSize - 2); i++)
		{
			strcat(response, chaine);
		}

		strcat(response, "\n");
		Usb_Serial_Send_Data(response);

	}
	else
	{
		response = "Error, size of data test is too big !\n";
		Usb_Serial_Send_Data(response);
	}
}

void Usb_Serial_Command_Handler(char *serialCommand, char *serialCommandArg)
{

	if(strcmp(serialCommand, "info") == 0)
	{
		Usb_Serial_Command_Get_Info();
	}
	else if(strcmp(serialCommand, "time") == 0)
	{
		Usb_Serial_Command_Set_Time(serialCommandArg);
	}
	else if(strcmp(serialCommand, "data") == 0)
	{
		Usb_Serial_Command_Test_Data(serialCommandArg);
	}
	else
	{
		char *response = "Error, invalid command or command len too big !\n";
		Usb_Serial_Send_Data(response);
	}
}


void Usb_Serial_Command_Splitter(char serialInput[64])
{

	const char split[2] = " ";
	char *cmd = NULL;
	char *arg = NULL;

	cmd = strtok(serialInput, split);
	arg = strtok(NULL, split);
	Usb_Serial_Command_Handler(cmd, arg);

}


