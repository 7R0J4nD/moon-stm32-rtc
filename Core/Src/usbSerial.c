/*
 * usbSerial.c
 *
 *
 *  Created on: 11 mai 2022
 *      Author: Administrator
 */


#include "main.h"
#include "usbSerial.h"
#include "serialCommand.h"


#define USB_SERIAL_COMMAND_MAX_LEN 64


int usbSerialCommandLen = 0;
uint8_t usbSerialUartRx_byte[1];
char usbSerialCommandBuffer[USB_SERIAL_COMMAND_MAX_LEN];





void Usb_Serial_Command_Buffer_Reset(void)
{
	for(int i = 0; i<USB_SERIAL_COMMAND_MAX_LEN; i++)
	{
		usbSerialCommandBuffer[i] = '\0';
	}
}


void Usb_Serial_Read(void)
{
	/* TODO  */
	/* usbSerialRead, return a specific error when command send is too big ! */

	if(usbSerialUartRx_byte[0] != '\0')
	{
		if(usbSerialUartRx_byte[0] != '\n')
		{
			if(usbSerialCommandLen < USB_SERIAL_COMMAND_MAX_LEN)
			{
				usbSerialCommandBuffer[usbSerialCommandLen] = usbSerialUartRx_byte[0];
				usbSerialCommandLen++;
			}else
			{
				Usb_Serial_Command_Buffer_Reset();
			}
		}else if (usbSerialUartRx_byte[0] == '\n')
		{
			Usb_Serial_Command_Splitter(usbSerialCommandBuffer);
			usbSerialCommandLen = 0;
			Usb_Serial_Command_Buffer_Reset();
		}
		usbSerialUartRx_byte[0] = '\0';
	}
}


void Usb_Serial_Uart_Receive(void)
{
	HAL_LockTypeDef *lock = &huart1.Lock;
	huart1.Lock = HAL_UNLOCKED;

	HAL_StatusTypeDef statusReceive = HAL_UART_Receive_IT(&huart1, usbSerialUartRx_byte, 1);
	if(statusReceive != HAL_OK)
	{
		Error_Handler();
	}
	huart1.Lock = *lock;
}


void Serial_Receive_Init(void)
{
	Usb_Serial_Uart_Receive();
}


void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{

	if (huart->Instance == USART1)
	{
		Usb_Serial_Read();
		Usb_Serial_Uart_Receive();
	}

}


void Usb_Serial_Send_Data(char* usbSerialTx_buffer)
{
	uint16_t usbSerialTx_size;
	usbSerialTx_size = strlen(usbSerialTx_buffer);
	HAL_StatusTypeDef statusTransmit;
	statusTransmit = HAL_UART_Transmit(&huart1, (uint8_t *)usbSerialTx_buffer, usbSerialTx_size, HAL_MAX_DELAY);
	if(statusTransmit != HAL_OK)
	{
		Error_Handler();
	}
}

