/*
 * usb.c
 *
 *  Created on: Apr 28, 2022
 *      Author: Administrator
 */


#include "main.h"
#include "usb.h"


/*
void Enable_Usb_5v(void)
{
	HAL_GPIO_WritePin(USB_5v_GPIO_Port, USB_5v_Pin, 1);
}


void Disable_Usb_5v(void)
{
	HAL_GPIO_WritePin(USB_5v_GPIO_Port, USB_5v_Pin, 0);
}

*/
void Enable_Usb(void)
{
	HAL_GPIO_WritePin(USB_enable_GPIO_Port, USB_enable_Pin, 1);
}


void Disable_Usb(void)
{
	HAL_GPIO_WritePin(USB_enable_GPIO_Port, USB_enable_Pin, 0);
}
