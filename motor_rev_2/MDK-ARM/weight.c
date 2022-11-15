#include "rs232.h"
#include "cmd.h"
#include "rs485.h"
#include "weight.h"
#include "crc.h"
#include "protocol.h"
#include <string.h>

extern WriteWeight_Package write_10kg_pack;
void InitWeight()
{
  uint8_t WeighBuf[sizeof(write_10kg_pack)];
  uint8_t crcval;
  for(uint8_t i=ADDR_LOW;i<=ADDR_HIGH;i++)
  {
    write_10kg_pack.addr=i;
    memcpy(WeighBuf,&write_10kg_pack,sizeof(write_10kg_pack));
    crcval=CRC16(WeighBuf,sizeof(write_10kg_pack)-2);
    write_10kg_pack.crc_low=0xFF&crcval;
    write_10kg_pack.crc_high=crcval>>8;
    memcpy(WeighBuf,&write_10kg_pack,sizeof(write_10kg_pack));
    Rs485_Send(WeighBuf,sizeof(WeighBuf));
  }
}