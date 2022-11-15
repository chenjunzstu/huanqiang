#include "rs232.h"
#include "cmd.h"
#include "rs485.h"

void InitRs232()
{
  
}

void Rs232_Send(uint8_t* pdata,uint8_t sendLen232)
{
  HAL_UART_Transmit(&huart1,pdata,sendLen232,0xff);
}

void Rs232_Rec()
{
  uint32_t temp;
  
  if(RESET!=__HAL_UART_GET_FLAG(&huart1,UART_FLAG_IDLE))
  {  
    __HAL_UART_CLEAR_IDLEFLAG(&huart1);//����жϱ�־
    HAL_UART_DMAStop(&huart1);//ֹͣDMA����
    temp  = __HAL_DMA_GET_COUNTER(&hdma_usart1_rx);//��ȡDMA��ǰ���ж���δ���
    Rx_len232 =  BUFFERSIZE - temp; //���㴮�ڽ��յ������ݸ���

    cmd_master_salve(ReceiveBuff232,Rx_len232);
        
    Rx_len232=0;//�������ݳ�������
    HAL_UART_Receive_DMA(&huart1,ReceiveBuff232,BUFFERSIZE);//������һ�ν���
  }
}