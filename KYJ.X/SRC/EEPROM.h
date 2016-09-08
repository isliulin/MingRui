/* 
 * File:   EEPROM.h
 * Author: tlan
 *
 * Created on 2015年12月18日, 上午9:45
 */

#ifndef EEPROM_H
#define	EEPROM_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#define EEPROM_FLAG_ADDR 0x10  //EEPROM存储是否已经初始化标志的地址
#define EEPROM_PARAM_ADDR 0x12 //EEPROM存储设置参数的地址
#define PARAM_STORE_BYTES 0x01B8-0x0128+2 //EEPROM保存的参数字节数
#define EEPROM_COUNTER_ADDR EEPROM_PARAM_ADDR+PARAM_STORE_BYTES+2  //EEPROM保存各计数值的地址
    
void EEPROM_Write(unsigned char nAddr, unsigned char nData);
unsigned char EEPROM_Read(unsigned char nAddr);
void EEPROM_Save_Param(unsigned char nBytes);
void EEPROM_Load_Param(unsigned char nBytes);
void EEPROM_Save_Counter(void);  //保存各计数值
void EEPROM_Load_Counter(void); //读取各计数值


#ifdef	__cplusplus
}
#endif

#endif	/* EEPROM_H */

