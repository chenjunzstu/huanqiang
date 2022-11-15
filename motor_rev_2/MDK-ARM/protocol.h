#ifndef _PROTOCOL_H
#define _PROTOCOL_H
#include <stdint.h>

#define LEADLEN 4
#define HEADLEN 2
#define LEAD 0xFF
#define ADDRMATCH 9
#define REGISTERLEN 4

//读取电机状态指令包
typedef struct
{
  uint8_t addr;
  uint8_t func;
  uint8_t start_high;
  uint8_t start_low;
  uint8_t num_high;
  uint8_t num_low;
  uint8_t crc_low;
  uint8_t crc_high;
}ReadMotor_Package;

//读取电机状态返回指令包
typedef struct
{
  uint8_t addr;
  uint8_t func;
  uint8_t num;
  uint8_t sq1_high;
  uint8_t sq1_low;
  uint8_t sq2_high;
  uint8_t sq2_low;
  uint8_t crc_low;
  uint8_t crc_high;
}ReplyMotor_Package;

//改写电机状态指令包
typedef struct
{
  uint8_t addr;
  uint8_t func;
  uint8_t reg_high;
  uint8_t reg_low;
  uint8_t data_high;
  uint8_t data_low;
  uint8_t crc_low;
  uint8_t crc_high;
}WriteMotor_Package;
//改写电机状态回复指令包
typedef struct
{
  uint8_t addr;
  uint8_t func;
  uint8_t reg_high;
  uint8_t reg_low;
  uint8_t data_high;
  uint8_t data_low;
  uint8_t crc_low;
  uint8_t crc_high;
}WriteMotor_Reply_Package;
//开门指令包
typedef struct
{
  uint8_t LeadCode[LEADLEN];
  uint8_t header[HEADLEN];
  uint8_t len;
  uint8_t addr;
  uint8_t control;
  uint8_t func;
  uint8_t data;
  uint8_t checkout;
  uint8_t tail; 
}OpenDoor_Package;

//开门回复指令包
typedef struct
{
  uint8_t LeadCode[LEADLEN];
  uint8_t header[HEADLEN];
  uint8_t len;
  uint8_t addr;
  uint8_t control;
  uint8_t func;
  uint8_t unused;
  uint8_t checkout;
  uint8_t tail; 
}OpenDoor_Reply_Package;

//校验查询指令包
typedef struct
{
  uint8_t LeadCode[LEADLEN];
  uint8_t header[HEADLEN];
  uint8_t len;
  uint8_t addr;
  uint8_t control;
  uint8_t func;
  uint8_t checkout;
  uint8_t tail; 
}Calib_Search_Package;

//校验查询回复指令包
typedef struct
{
  uint8_t LeadCode[LEADLEN];
  uint8_t header[HEADLEN];
  uint8_t len;
  uint8_t addr;
  uint8_t control;
  uint8_t func;
  uint8_t checkout;
  uint8_t tail; 
}Calib_Search_Reply_Package;

//查询校准回复指令包
typedef struct
{
  uint8_t LeadCode[LEADLEN];
  uint8_t header[HEADLEN];
  uint8_t len;
  uint8_t addr;
  uint8_t control;
  uint8_t func;
  uint8_t data;
  uint8_t checkout;
  uint8_t tail; 
}Calib_Reply_Package;

//查询状态回复指令包
typedef struct
{
  uint8_t LeadCode[LEADLEN];
  uint8_t header[HEADLEN];
  uint8_t len;
  uint8_t addr;
  uint8_t control;
  uint8_t func;
  uint8_t DOOR_STATE;
  uint8_t WEIGHT_high;
  uint8_t WEIGHT_low;
  uint8_t ERR;
  uint8_t DORP;
  uint8_t DOOR_OFF_TM;
  uint8_t OVER_WEIGHT;
  uint8_t RESP;
  uint8_t checkout;
  uint8_t tail; 
}SearchReply_Package;

//称台校准指令包
typedef struct
{
  uint8_t addr;
  uint8_t func;
  uint8_t start_high;
  uint8_t start_low;
  uint8_t data_high;
  uint8_t data_low;
  uint8_t crc_low;
  uint8_t crc_high;
}Calib_Package;

//读取重量指令包
typedef struct
{
  uint8_t addr;
  uint8_t func;
  uint8_t start_high;
  uint8_t start_low;
  uint8_t num_high;
  uint8_t num_low;
  uint8_t crc_low;
  uint8_t crc_high;
}ReadWeight_Package;

//重量回复包
typedef struct
{
  uint8_t addr;
  uint8_t func;
  uint8_t len;
  uint8_t data[REGISTERLEN];
  uint8_t crc_low;
  uint8_t crc_high;
}ReplyWeight_Package;

//重量寄存器写入重量指令包
typedef struct
{
  uint8_t addr;
  uint8_t func;
  uint8_t start_high;
  uint8_t start_low;
  uint8_t num_high;
  uint8_t num_low;
  uint8_t num;
  uint8_t data[REGISTERLEN];
  uint8_t crc_low;
  uint8_t crc_high;
}WriteWeight_Package;
#endif

