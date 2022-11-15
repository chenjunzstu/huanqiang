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
    __HAL_UART_CLEAR_IDLEFLAG(&huart1);//清除中断标志
    HAL_UART_DMAStop(&huart1);//停止DMA接收
    temp  = __HAL_DMA_GET_COUNTER(&hdma_usart1_rx);//获取DMA当前还有多少未填充
    Rx_len232 =  BUFFERSIZE - temp; //计算串口接收到的数据个数

    cmd_master_salve(ReceiveBuff232,Rx_len232);
        
    Rx_len232=0;//接收数据长度清零
    HAL_UART_Receive_DMA(&huart1,ReceiveBuff232,BUFFERSIZE);//开启下一次接收
  }
}