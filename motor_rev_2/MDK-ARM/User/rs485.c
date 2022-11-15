/*
 * rs485.c
 *
 *  Created on: Oct 21, 2021
 *      Author: Administrator
 */

#include "rs485.h"
#include "../usart/usart.h"
#include "main.h"
/*
RS485总线通信，使用UART8，这是RS485专用的printf函数
调用方法：RS485_printf("123"); //向UART8发送字符123
*/
void RS485_printf (char *fmt, ...)
{
    char buff[USART2_REC_LEN+1];  //用于存放转换后的数据 [长度]
    uint16_t i=0;
    va_list arg_ptr;
    HAL_GPIO_WritePin(RS485_RE_GPIO_Port,RS485_RE_Pin, GPIO_PIN_SET);//RS485收发选择线RE为高电平（发送）
    va_start(arg_ptr,fmt);
    vsnprintf(buff, USART2_REC_LEN+1,fmt,arg_ptr);//数据转换
    i=strlen(buff);//得出数据长度
    if(strlen(buff)>USART2_REC_LEN)i=USART2_REC_LEN;//如果长度大于最大值，则长度等于最大值（多出部分忽略）
    HAL_UART_Transmit(&huart2,(uint8_t *)buff,i,0xffff);//串口发送函数（串口号，内容，数量，溢出时间）
    va_end(arg_ptr);
    HAL_GPIO_WritePin(RS485_RE_GPIO_Port,RS485_RE_Pin, GPIO_PIN_RESET);//RS485收发选择线RE为低电平（接收）
}
//所有USART串口的中断回调函数HAL_UART_RxCpltCallback，统一存放在【USART1.C】文件中。
