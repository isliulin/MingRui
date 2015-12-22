#include<pic16f1939.h>
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