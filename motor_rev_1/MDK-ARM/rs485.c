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

//485初始化
void InitRs485()
{
  //默认接收
  enReceive485();
}

//485发送
void Rs485_Send(uint8_t* pdata,uint8_t sendLen485)
{
  enSend485();
  HAL_Delay(5);
  HAL_UART_Transmit(&huart3,pdata,sendLen485,0xff);//发送数据
  enReceive485();
  HAL_Delay(5);
}

//485接收
void Rs485_Rec()
{
  uint32_t temp;
  if(RESET!=__HAL_UART_GET_FLAG(&huart3,UART_FLAG_IDLE))
  {  
    __HAL_UART_CLEAR_IDLEFLAG(&huart3);//清除中断标志
    HAL_UART_DMAStop(&huart3);//停止DMA接收
    temp  = __HAL_DMA_GET_COUNTER(&hdma_usart3_rx);//获取DMA当前还有多少未填充
    Rx_len485 =  BUFFERSIZE - temp; //计算串口接收到的数据个数
     
    cmd_salve_master(ReceiveBuff485,Rx_len485);
        
    Rx_len485=0;//接收数据长度清零
  }

  cmd_salve_master(ReceiveBuff485,6);
}