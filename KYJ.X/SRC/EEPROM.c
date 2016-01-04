#include<pic16f1939.h>
#include"KYJDEF.h"
void EEPROM_Write(unsigned char nAddr, unsigned char nData)
{
    EEADRL = nAddr;
    EEDATL = nData;
    CFGS = 0;
    EEPGD = 0;
    WREN = 1;
    GIE = 0;
    EECON2 = 0x55;
    EECON2 = 0xAA;
    WR = 1;
    GIE = 1;
    WREN = 0;
    while (WR==1){;}
}

unsigned char EEPROM_Read(unsigned char nAddr)
{
    EEADRL = nAddr;
    CFGS = 0;
    EEPGD = 0;
    RD = 1;
    return EEDATA;
}

void EEPROM_Save_Param(unsigned char nBytes)
{
    unsigned char * nAddr;
    unsigned char i;
    nAddr = &sKYJ.sUserParam;
    for(i=0;i<nBytes;i++)
    {
        EEPROM_Write(i+0x11,*nAddr++);
    }
}

void EEPROM_Load_Param(unsigned char nBytes)
{
    unsigned char * nAddr;
    unsigned char i;
    nAddr = &sKYJ.sUserParam;
    for(i=0;i<nBytes;i++)
    {
        *nAddr++=EEPROM_Read(i+0x11);
    }
}