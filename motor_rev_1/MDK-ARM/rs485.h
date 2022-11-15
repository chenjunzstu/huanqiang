#ifndef _RS485_H
#define _RS485_H
#include <usart.h>
#include <gpio.h>

//485ʹ������
#define DE GPIOB
#define DE_PIN GPIO_PIN_0
#define RE GPIOB
#define RE_PIN GPIO_PIN_1

//485����
extern UART_HandleTypeDef huart3;
#define COM485 huart3

#define BUFFERSIZE 255//���Խ��յ�����ַ�����
extern uint8_t ReceiveBuff485[BUFFERSIZE];
extern uint8_t ReceiveBuff232[BUFFERSIZE]; //���ջ�����
extern uint8_t TransmitBuff485[BUFFERSIZE];
extern uint8_t TransmitBuff232[BUFFERSIZE]; //���ͻ�����
extern uint8_t Rx_len485;//��������жϱ�־�����յ��ַ�����
extern uint8_t Rx_len232;//��������жϱ�־�����յ��ַ�����
extern DMA_HandleTypeDef hdma_usart1_rx;
extern DMA_HandleTypeDef hdma_usart1_tx;
extern DMA_HandleTypeDef hdma_usart3_rx;
extern DMA_HandleTypeDef hdma_usart3_tx;

void InitRs485();
void Rs485_Send(uint8_t* pdata,uint8_t sendLen485);
void Rs485_Rec();
void enSend485();
void enReceive485();
#endif
