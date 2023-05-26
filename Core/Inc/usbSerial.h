/*
 * usbSerial.h
 *
 *  Created on: 11 mai 2022
 *      Author: Administrator
 */

#ifndef INC_USBSERIAL_H_
#define INC_USBSERIAL_H_



#endif /* INC_USBSERIAL_H_ */




void Usb_Serial_Command_Buffer_Reset(void);
void Usb_Serial_Read(void);
void Usb_Serial_Uart_Receive(void);
void Usb_Serial_Lpuart_Receive(void);
void Usb_Serial_Send_Data(char* usbSerialTx_buffer);
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);
void Serial_Receive_Init(void);

bool Is_Transmmit (void);


