#ifndef _CMD_H
#define _CMD_H
#include "protocol.h"
#include "rs485.h"
#include "rs232.h"

#define CMD_READ 0x03
#define CMD_WRITE 0x10
#define CMD_OPEN 0x11
#define CMD_CLOSE 0x22
#define CMD_CALIBRATE_0KG 0x01
#define CMD_CALIBRATE_10KG 0x02
#define CMD_CALIBRATE_SEARCH 0x03
#define CMD_CLOSE_DOOR 0x04
#define CMD_OPEN_DOOR 0x05
#define CMD_SEARCH 0x06
#define CMD_GET_DOOR_STATE 0x07
#define CMD_GET_WEIGHT 0x08
#define DATA_0KG 0x01
#define DATA_10KG 0x02
#define MAXWEIGHT 200000
#define OVERWEIGHT 0x01
#define NOVERWEIGHT 0x00
#define DOOR_STATE_STOP 0x00
#define DOOR_STATE_OPEN 0x01
#define DOOR_STATE_CLOSE 0x02
#define OPEN_TIME 20000

//crc变量
static uint8_t crc16_232[256]={'\0'};
static int crc_value_232=0x00;
static uint8_t crc16_485[256]={'\0'};
static int crc_value_485=0x00;

//指令包
extern OpenDoor_Package open_pack;
extern WriteMotor_Package moter_pack;
extern ReadMotor_Package read_motor_pack;
extern OpenDoor_Reply_Package open_reply_pack;
extern ReplyMotor_Package replymotor_pack;
extern WriteMotor_Reply_Package writemotor_reply_pack;
extern Calib_Search_Package cali_search_pack;
extern Calib_Package calib_pack;
extern Calib_Reply_Package calib_reply_pack;
extern Calib_Package calib_pack_receive;
extern Calib_Search_Reply_Package cs_reply_pack;
extern ReadMotor_Package read_motor_pack;
extern ReadWeight_Package read_weight_pack;
extern SearchReply_Package searchreply_pack;
extern ReplyWeight_Package reply_weight_pack;
extern WriteMotor_Package close_pack;


void cmd_master_salve(uint8_t* package,uint8_t packlen);
void cmd_salve_master(uint8_t* package,uint8_t packlen);
void cmd_select();
void cmd_send_close();
//发送标志位
extern uint8_t sendFlag232;
extern uint8_t sendFlag485;
extern uint8_t closeFlag1;
extern uint8_t closeFlag2;
extern uint8_t closeFlag3;
extern uint8_t closeFlag4;
extern uint8_t closeFlag5;
extern uint8_t closeFlag6;
#endif