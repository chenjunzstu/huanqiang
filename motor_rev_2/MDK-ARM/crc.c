#include "crc.h"

unsigned short CRC16 ( uint8_t *puchMsg, uint8_t usDataLen )
{ 
  uint8_t uchCRCHi = 0xFF ;  /* ���ֽڳ�ʼ��ֵ   */ 
  uint8_t uchCRCLo = 0xFF ;  /* ���ֽڳ�ʼ��ֵ   */
	unsigned uIndex ;  
	 
	while (usDataLen--) 
	{ 
		uIndex = uchCRCLo ^ *puchMsg++ ;   
		uchCRCLo = uchCRCHi ^ auchCRCHi[uIndex] ; 
		uchCRCHi = auchCRCLo[uIndex] ; 
	}
  return (uchCRCHi << 8 | uchCRCLo) ; 
}

unsigned short SUM_CALIBRATE(uint8_t *puchMsg, uint8_t usDataLen)
{
  uint16_t sum=0;
  for(uint8_t i=0;i<usDataLen;i++)
  {
    sum+=puchMsg[i];
  }
  
  return sum;
}