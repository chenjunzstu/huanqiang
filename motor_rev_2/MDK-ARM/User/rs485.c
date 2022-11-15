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
RS485����ͨ�ţ�ʹ��UART8������RS485ר�õ�printf����
���÷�����RS485_printf("123"); //��UART8�����ַ�123
*/
void RS485_printf (char *fmt, ...)
{
    char buff[USART2_REC_LEN+1];  //���ڴ��ת��������� [����]
    uint16_t i=0;
    va_list arg_ptr;
    HAL_GPIO_WritePin(RS485_RE_GPIO_Port,RS485_RE_Pin, GPIO_PIN_SET);//RS485�շ�ѡ����REΪ�ߵ�ƽ�����ͣ�
    va_start(arg_ptr,fmt);
    vsnprintf(buff, USART2_REC_LEN+1,fmt,arg_ptr);//����ת��
    i=strlen(buff);//�ó����ݳ���
    if(strlen(buff)>USART2_REC_LEN)i=USART2_REC_LEN;//������ȴ������ֵ���򳤶ȵ������ֵ��������ֺ��ԣ�
    HAL_UART_Transmit(&huart2,(uint8_t *)buff,i,0xffff);//���ڷ��ͺ��������ںţ����ݣ����������ʱ�䣩
    va_end(arg_ptr);
    HAL_GPIO_WritePin(RS485_RE_GPIO_Port,RS485_RE_Pin, GPIO_PIN_RESET);//RS485�շ�ѡ����REΪ�͵�ƽ�����գ�
}
//����USART���ڵ��жϻص�����HAL_UART_RxCpltCallback��ͳһ����ڡ�USART1.C���ļ��С�
