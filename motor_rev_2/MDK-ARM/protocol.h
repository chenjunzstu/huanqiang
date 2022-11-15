#ifndef _PROTOCOL_H
#define _PROTOCOL_H
#include <stdint.h>

#define LEADLEN 4
#define HEADLEN 2
#define LEAD 0xFF
#define ADDRMATCH 9
#define REGISTERLEN 4

//��ȡ���״ָ̬���
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

//��ȡ���״̬����ָ���
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

//��д���״ָ̬���
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
//��д���״̬�ظ�ָ���
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
//����ָ���
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

//���Żظ�ָ���
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

//У���ѯָ���
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

//У���ѯ�ظ�ָ���
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

//��ѯУ׼�ظ�ָ���
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

//��ѯ״̬�ظ�ָ���
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

//��̨У׼ָ���
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

//��ȡ����ָ���
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

//�����ظ���
typedef struct
{
  uint8_t addr;
  uint8_t func;
  uint8_t len;
  uint8_t data[REGISTERLEN];
  uint8_t crc_low;
  uint8_t crc_high;
}ReplyWeight_Package;

//�����Ĵ���д������ָ���
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

