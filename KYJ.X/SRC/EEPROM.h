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

void EEPROM_Write(unsigned char nAddr, unsigned char nData);
unsigned char EEPROM_Read(unsigned char nAddr);


#ifdef	__cplusplus
}
#endif

#endif	/* EEPROM_H */

