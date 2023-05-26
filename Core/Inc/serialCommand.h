/*
 *
 *
 *  Created on: 12 mai 2022
 *      Author: Administrator
 */

#ifndef INC_SERIALCOMMAND_H_
#define INC_SERIALCOMMAND_H_



#endif /* INC_SERIALCOMMAND_H_ */

extern time_t lastRTC;

char *uitoa(char *d, unsigned int num, int radix, int length);

void Usb_Serial_Command_Get_Info(void);
void Usb_Serial_Command_Set_Time(char *charTimestamp);
void Usb_Serial_Command_Test_Data(char *size);
void Usb_Serial_Command_Handler(char *serialCommand, char *serialCommandArg);
void Usb_Serial_Command_Splitter(char serialInput[64]);



