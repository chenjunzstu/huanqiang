#ifndef _RS232_H
#define _RS232_H
#include <usart.h>
#include <gpio.h>

//232´®¿Ú
extern UART_HandleTypeDef huart1;
#define COM232 huart1


void InitRs232();
void Rs232_Send(uint8_t* pdata,uint8_t sendLen232);
void Rs232_Rec();

#endif