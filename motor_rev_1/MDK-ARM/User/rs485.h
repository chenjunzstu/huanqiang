/*
 * rs485.h
 *
 *  Created on: Oct 21, 2021
 *      Author: Administrator
 */

#ifndef RS485_RS485_H_
#define RS485_RS485_H_

#include "stm32f1xx_hal.h" //HAL库文件声明
#include <string.h>//用于字符串处理的库
#include <stdarg.h>
#include <stdlib.h>
#include "stdio.h"

extern UART_HandleTypeDef huart2;//声明USART2的HAL库结构体
void RS485_printf (char *fmt, ...);  //RS485发送

#endif /* RS485_RS485_H_ */
