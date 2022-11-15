#include "rs485.h"
#include "cmd.h"
#include "rs232.h"


void enReceive485()
{
  HAL_GPIO_WritePin(DE,DE_PIN,GPIO_PIN_RESET);
  HAL_GPIO_WritePin(RE,RE_PIN,GPIO_PIN_RESET);
}

void enSend485()
{
  HAL_GPIO_WritePin(DE,DE_PIN,GPIO_PIN_SET);
  HAL_GPIO_WritePin(RE,RE_PIN,GPIO_PIN_SET);
}

//485��ʼ��
void InitRs485()
{
  //Ĭ�Ͻ���
  enReceive485();
}

//485����
void Rs485_Send(uint8_t* pdata,uint8_t sendLen485)
{
  enSend485();
  HAL_Delay(5);
  HAL_UART_Transmit(&huart3,pdata,sendLen485,0xff);//��������
  enReceive485();
  HAL_Delay(5);
}

//485����
void Rs485_Rec()
{
  uint32_t temp;
  if(RESET!=__HAL_UART_GET_FLAG(&huart3,UART_FLAG_IDLE))
  {  
    __HAL_UART_CLEAR_IDLEFLAG(&huart3);//����жϱ�־
    HAL_UART_DMAStop(&huart3);//ֹͣDMA����
    temp  = __HAL_DMA_GET_COUNTER(&hdma_usart3_rx);//��ȡDMA��ǰ���ж���δ���
    Rx_len485 =  BUFFERSIZE - temp; //���㴮�ڽ��յ������ݸ���
     
    cmd_salve_master(ReceiveBuff485,Rx_len485);
        
    Rx_len485=0;//�������ݳ�������
  }

  cmd_salve_master(ReceiveBuff485,6);
}