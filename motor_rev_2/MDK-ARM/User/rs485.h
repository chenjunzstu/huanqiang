/*
 * rs485.h
 *
 *  Created on: Oct 21, 2021
 *      Author: Administrator
 */

#ifndef RS485_RS485_H_
#define RS485_RS485_H_

#include "stm32f1xx_hal.h" //HAL���ļ�����
#include <string.h>//�����ַ�������Ŀ�
#include <stdarg.h>
#include <stdlib.h>
#include "stdio.h"

extern UART_HandleTypeDef huart2;//����USART2��HAL��ṹ��
void RS485_printf (char *fmt, ...);  //RS485����

#endif /* RS485_RS485_H_ */
