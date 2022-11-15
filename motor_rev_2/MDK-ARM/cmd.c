#include "cmd.h"
#include <string.h>
#include "crc.h"
#include "weight.h"
#include "cmsis_os.h"

//定时器
extern osTimerId DoorTimer01Handle;
extern osTimerId DoorTimer02Handle;
extern osTimerId DoorTimer03Handle;
extern osTimerId DoorTimer04Handle;
extern osTimerId DoorTimer05Handle;
extern osTimerId DoorTimer06Handle;
//流程完成，关门标志
uint8_t close_finish_flag = 0;

void cmd_master_salve(uint8_t* package,uint8_t packlen)
{
  if(packlen==0x0D)
  {
    memcpy(&open_pack,package,packlen);
    if(open_pack.func==CMD_OPEN_DOOR)
    {
      moter_pack.addr=open_pack.addr;
      uint8_t a[8];
      memcpy(a,&moter_pack,sizeof(moter_pack)-2);
      int sum=CRC16(a,sizeof(moter_pack)-2);
      moter_pack.crc_low=sum&0xFF;
      moter_pack.crc_high=sum>>8;
      sendFlag485=CMD_OPEN_DOOR;
    }
  }
  else if(packlen==0x0C)
  {
    memcpy(&cali_search_pack,package,packlen);
    switch(cali_search_pack.func)
    {
      case CMD_CALIBRATE_0KG:
        {
          calib_pack.addr=cali_search_pack.addr+ADDRMATCH;
          calib_pack.data_low=DATA_0KG;
          memcpy(crc16_232,&calib_pack,sizeof(calib_pack)-2);
          crc_value_232=CRC16(crc16_232,sizeof(calib_pack)-2);
          memset(crc16_232,'\0',sizeof(crc16_232));
          calib_pack.crc_low=crc_value_232&0xFF;
          calib_pack.crc_high=crc_value_232>>8;
          crc_value_232=0x00;
          
          //更改485发送标志位
          sendFlag485=CMD_CALIBRATE_0KG;
        }
        break;
      case CMD_CALIBRATE_10KG:
        {
          calib_pack.addr=cali_search_pack.addr+ADDRMATCH;
          calib_pack.data_low=DATA_10KG;
          memcpy(crc16_232,&calib_pack,sizeof(calib_pack)-2);
          crc_value_232=CRC16(crc16_232,sizeof(calib_pack)-2);
          memset(crc16_232,'\0',sizeof(crc16_232));
          calib_pack.crc_low=crc_value_232&0xFF;
          calib_pack.crc_high=crc_value_232>>8;
          crc_value_232=0x00;
          
          //更改485发送标志位
          sendFlag485=CMD_CALIBRATE_10KG;
        }
        break;
      case CMD_CALIBRATE_SEARCH:
        {
          if(calib_pack.data_low==DATA_0KG)
          {
            if(memcmp(&calib_pack,&calib_pack_receive,sizeof(calib_pack))==0)
            {
              calib_reply_pack.addr=calib_pack_receive.addr-ADDRMATCH;
              calib_reply_pack.data=0x03;//0kg校准成功
            }
            else
            {
              calib_reply_pack.addr=calib_pack.addr-ADDRMATCH;
              calib_reply_pack.data=0x08;
            }
          }
          else
          {
            if(calib_pack.data_low==DATA_10KG)
            {
              if(memcmp(&calib_pack,&calib_pack_receive,sizeof(calib_pack))==0)
            {
              calib_reply_pack.addr=calib_pack_receive.addr-ADDRMATCH;
              calib_reply_pack.data=0x05;//10kg校准成功
            }
            else
            {
              calib_reply_pack.addr=calib_pack.addr-ADDRMATCH;
              calib_reply_pack.data=0x09;
            }
            }
          }
          sendFlag232=CMD_CALIBRATE_SEARCH;
        }
        break;
      case CMD_SEARCH:
        {
          
          read_motor_pack.addr=cali_search_pack.addr;
          memcpy(crc16_232,&read_motor_pack,sizeof(read_motor_pack)-2);
          crc_value_232=CRC16(crc16_232,sizeof(read_motor_pack)-2);
          memset(crc16_232,'\0',sizeof(crc16_232));
          read_motor_pack.crc_low=crc_value_232&0xFF;
          read_motor_pack.crc_high=crc_value_232>>8;
          crc_value_232=0x00;
          
          
          read_weight_pack.addr=cali_search_pack.addr+ADDRMATCH;
          memcpy(crc16_232,&read_weight_pack,sizeof(read_weight_pack)-2);
          crc_value_232=CRC16(crc16_232,sizeof(read_weight_pack)-2);
          memset(crc16_232,'\0',sizeof(crc16_232));
          read_weight_pack.crc_low=crc_value_232&0xFF;
          read_weight_pack.crc_high=crc_value_232>>8;
          crc_value_232=0x00;
          
          sendFlag485=CMD_GET_DOOR_STATE;//传输读取电机状态指令
          //sendFlag485=CMD_GET_WEIGHT;
        }
        break;
      default:
        break;
    }
  }
}

void cmd_salve_master(uint8_t* package,uint8_t packlen)
{
  if(packlen>0x09)
  {
    return;
  }
  if(package[0]<ADDR_LOW&&package[0]>0x00)//电机地址
  {
    if(packlen==0x08)
    {
      memcpy(&writemotor_reply_pack,package,packlen);
      open_reply_pack.addr=writemotor_reply_pack.addr;
      
      if(memcmp(&writemotor_reply_pack,&moter_pack,sizeof(moter_pack))==0&&writemotor_reply_pack.data_high==0x03&&writemotor_reply_pack.data_low==0xE8)
      {
        sendFlag232=CMD_OPEN_DOOR;
      }
    }
    
    else if(packlen==0x09)//电机状态查询
    {
      
      memcpy(&replymotor_pack,package,sizeof(replymotor_pack));
      /*
      if(replymotor_pack.crc_low+(replymotor_pack.crc_high<<8)==CRC16(package,packlen-2))
      {
        if(((replymotor_pack.crc_high<<8)+replymotor_pack.crc_low)==CRC16(package,sizeof(replymotor_pack)-2))
        {
          if(replymotor_pack.sq1_low==1&&replymotor_pack.sq2_low==0)
          {
            searchreply_pack.DOOR_STATE=DOOR_STATE_OPEN;
          }
          else if(replymotor_pack.sq1_low==1&&replymotor_pack.sq2_low==1)
          {
            searchreply_pack.DOOR_STATE=DOOR_STATE_STOP;
          }
          else if(replymotor_pack.sq1_low==0&&replymotor_pack.sq2_low==1)
          {
            searchreply_pack.DOOR_STATE=DOOR_STATE_CLOSE;
          }
        }
        
      }
      */
      sendFlag485=CMD_GET_WEIGHT;//传输获取重量指令
    }
    
  }
  else
  {
    if(packlen==0x08)//校准指令返回
    {
      memcpy(&calib_pack_receive,package,sizeof(calib_pack_receive));
      cs_reply_pack.addr=calib_pack.addr-ADDRMATCH;
      cs_reply_pack.func=calib_pack.data_low;
      switch(cs_reply_pack.func)
      {
        case CMD_CALIBRATE_0KG:
          {
            sendFlag232=CMD_CALIBRATE_0KG;
          }
          break;
        case CMD_CALIBRATE_10KG:
          {
            sendFlag232=CMD_CALIBRATE_10KG;
          }
          break;
      }
    }
    else//重量返回
    {
      memcpy(&reply_weight_pack,package,sizeof(reply_weight_pack));
      searchreply_pack.addr=reply_weight_pack.addr-ADDRMATCH;
      //门状态
      switch(searchreply_pack.addr)
      {
        case 0x01:
          {
            searchreply_pack.DOOR_STATE=door1_state;
          }
          break;
        case 0x02:
          {
            searchreply_pack.DOOR_STATE=door2_state;
          }
          break;
        case 0x03:
          {
            searchreply_pack.DOOR_STATE=door3_state;
          }
          break;
        case 0x04:
          {
            searchreply_pack.DOOR_STATE=door4_state;
          }
          break;
        case 0x05:
          {
            searchreply_pack.DOOR_STATE=door5_state;
          }
          break;
        case 0x06:
          {
            searchreply_pack.DOOR_STATE=door6_state;
          }
          break;
        default:
          break;
      }
      
      if(reply_weight_pack.data[0]==0xFF)
      {
        searchreply_pack.WEIGHT_high=0x00;
        searchreply_pack.WEIGHT_low=0x00;
      }
      else
      {
        searchreply_pack.WEIGHT_high=reply_weight_pack.data[0];
        searchreply_pack.WEIGHT_low=reply_weight_pack.data[1];
      }
      int weight=(searchreply_pack.WEIGHT_high<<8)+searchreply_pack.WEIGHT_low;
      if(weight>MAXWEIGHT)
      {
        searchreply_pack.OVER_WEIGHT=OVERWEIGHT;
      }
      else
      {
        searchreply_pack.OVER_WEIGHT=NOVERWEIGHT;
      }
      if(reply_weight_pack.func==0x03&&reply_weight_pack.addr==replymotor_pack.addr+ADDRMATCH)
      {
        sendFlag232=CMD_SEARCH;
      }
    }
  }
}

void cmd_select()
{
  switch(sendFlag485)
    {
      case CMD_OPEN_DOOR:
        {
          memcpy(TransmitBuff485,&moter_pack,sizeof(moter_pack));
          Rs485_Send(TransmitBuff485,sizeof(moter_pack));
          sendFlag485=0x00;
          cmd_send_close();
          
          switch(moter_pack.addr)
          {
            case 0x01:
              {
                door1_state=DOOR_STATE_OPEN;
              }
              break;
            case 0x02:
              {
                door2_state=DOOR_STATE_OPEN;
              }
              break;
            case 0x03:
              {
                door3_state=DOOR_STATE_OPEN;
              }
              break;
            case 0x04:
              {
                door4_state=DOOR_STATE_OPEN;
              }
              break;
            case 0x05:
              {
                door5_state=DOOR_STATE_OPEN;
              }
              break;
            case 0x06:
              {
                door6_state=DOOR_STATE_OPEN;
              }
              break;
            default:
              break;
          }
          
        }
        break;
      case CMD_CALIBRATE_0KG:
      case CMD_CALIBRATE_10KG:
        {
          memcpy(TransmitBuff485,&calib_pack,sizeof(calib_pack));
          Rs485_Send(TransmitBuff485,sizeof(calib_pack));
          sendFlag485=0x00;
          HAL_Delay(50);
        }
        break;
      case CMD_GET_DOOR_STATE:
        {
          memcpy(TransmitBuff485,&read_motor_pack,sizeof(read_motor_pack));
          Rs485_Send(TransmitBuff485,sizeof(read_motor_pack));
          sendFlag485=0x00;
          HAL_Delay(50);
        }
        break;
      case CMD_GET_WEIGHT:
        {
          memcpy(TransmitBuff485,&read_weight_pack,sizeof(read_weight_pack));
          Rs485_Send(TransmitBuff485,sizeof(read_weight_pack));
          sendFlag485=0x00;
          HAL_Delay(50);
        }
        break;
      default:
        break;
    }
    switch(sendFlag232)
    {
      case CMD_OPEN_DOOR:
        {
          memcpy(TransmitBuff232,&open_reply_pack,sizeof(open_reply_pack));
          Rs232_Send(TransmitBuff232,sizeof(open_reply_pack));
          HAL_Delay(50);
          sendFlag232=0x00;
        }
        break;
      case CMD_CALIBRATE_0KG:
      case CMD_CALIBRATE_10KG:
        {
          memcpy(TransmitBuff232,&cs_reply_pack,sizeof(cs_reply_pack));
          Rs232_Send(TransmitBuff232,sizeof(cs_reply_pack));
          HAL_Delay(50);
          sendFlag232=0x00;
        }
        break;
      case CMD_CALIBRATE_SEARCH:
        {
          memcpy(TransmitBuff232,&calib_reply_pack,sizeof(calib_reply_pack));
          Rs232_Send(TransmitBuff232,sizeof(calib_reply_pack));
          HAL_Delay(50);
          sendFlag232=0x00;
        }
        break;
      case CMD_SEARCH:
        {
          memcpy(TransmitBuff232,&searchreply_pack,sizeof(searchreply_pack));
          Rs232_Send(TransmitBuff232,sizeof(searchreply_pack));
          sendFlag232=0x00;
          HAL_Delay(50);
        }
        break;
      default:
        break;
    }
    
    if(closeFlag1)
    {
      close_pack.addr=0x01;
      uint8_t a[8];
      memcpy(a,&close_pack,sizeof(close_pack)-2);
      uint16_t sum=CRC16(a,sizeof(close_pack)-2);
      close_pack.crc_low=sum&0xFF;
      close_pack.crc_high=sum>>8;
      memcpy(TransmitBuff485,&close_pack,sizeof(close_pack));
      Rs485_Send(TransmitBuff485,sizeof(close_pack));
      closeFlag1=0;
    }
    else if(closeFlag2)
    {
      close_pack.addr=0x02;
      uint8_t a[8];
      memcpy(a,&close_pack,sizeof(close_pack)-2);
      uint16_t sum=CRC16(a,sizeof(close_pack)-2);
      close_pack.crc_low=sum&0xFF;
      close_pack.crc_high=sum>>8;
      memcpy(TransmitBuff485,&close_pack,sizeof(close_pack));
      Rs485_Send(TransmitBuff485,sizeof(close_pack));
      closeFlag2=0;
    }
    else if(closeFlag3)
    {
      close_pack.addr=0x03;
      uint8_t a[8];
      memcpy(a,&close_pack,sizeof(close_pack)-2);
      uint16_t sum=CRC16(a,sizeof(close_pack)-2);
      close_pack.crc_low=sum&0xFF;
      close_pack.crc_high=sum>>8;
      memcpy(TransmitBuff485,&close_pack,sizeof(close_pack));
      Rs485_Send(TransmitBuff485,sizeof(close_pack));
      closeFlag3=0;
    }
    else if(closeFlag4)
    {
      close_pack.addr=0x04;
      uint8_t a[8];
      memcpy(a,&close_pack,sizeof(close_pack)-2);
      uint16_t sum=CRC16(a,sizeof(close_pack)-2);
      close_pack.crc_low=sum&0xFF;
      close_pack.crc_high=sum>>8;
      memcpy(TransmitBuff485,&close_pack,sizeof(close_pack));
      Rs485_Send(TransmitBuff485,sizeof(close_pack));
      closeFlag4=0;
    }
    else if(closeFlag5)
    {
      close_pack.addr=0x05;
      uint8_t a[8];
      memcpy(a,&close_pack,sizeof(close_pack)-2);
      uint16_t sum=CRC16(a,sizeof(close_pack)-2);
      close_pack.crc_low=sum&0xFF;
      close_pack.crc_high=sum>>8;
      memcpy(TransmitBuff485,&close_pack,sizeof(close_pack));
      Rs485_Send(TransmitBuff485,sizeof(close_pack));
      closeFlag5=0;
    }
    else if(closeFlag6)
    {
      close_pack.addr=0x06;
      uint8_t a[8];
      memcpy(a,&close_pack,sizeof(close_pack)-2);
      uint16_t sum=CRC16(a,sizeof(close_pack)-2);
      close_pack.crc_low=sum&0xFF;
      close_pack.crc_high=sum>>8;
      memcpy(TransmitBuff485,&close_pack,sizeof(close_pack));
      Rs485_Send(TransmitBuff485,sizeof(close_pack));
      closeFlag6=0;
    }
}

void cmd_send_close()
{
  switch(moter_pack.addr)
  {
    case 0x01:
      {
        osTimerStart(DoorTimer01Handle,OPEN_TIME);
      }
      break;
    case 0x02:
      {
        osTimerStart(DoorTimer02Handle,OPEN_TIME);
      }
      break;
    case 0x03:
      {
        osTimerStart(DoorTimer03Handle,OPEN_TIME);
      }
      break;
    case 0x04:
      {
        osTimerStart(DoorTimer04Handle,OPEN_TIME);
      }
      break;
    case 0x05:
      {
        osTimerStart(DoorTimer05Handle,OPEN_TIME);
      }
      break;
    case 0x06:
      {
        osTimerStart(DoorTimer06Handle,OPEN_TIME);
      }
      break;
    default:
      break;
  }
}