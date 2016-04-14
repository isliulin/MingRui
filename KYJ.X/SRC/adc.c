#include "adc.h"
#include "delay.h"
void adc_init()
{
    //FVRCON = 0b10101111;  //参考电压4X，0-4.096V
    ADCON1 = 0b00010000;  //ECCP1，内部4.096v，AVss，反相输入0
    ADCON2 = 0b10010110; //右对齐，4Tad，FOSC/32
//    TRISA0 = 1;
//    ANSELA |= 0b00000001;
    ADCON0 = 0b00000000; 
    
    //参考电压输出
    CVRCON=0b11100101;
    CVRCON2=0b10000000;
}

int adc_Get_Value(unsigned char nChannel)
{
    //int nRes;
    ADON = 0;
    ADCON0 = nChannel<<2 | 0b00000001;
    DelayUs(10);
    ADON = 1;
    ADCON0bits.GODONE = 1;
    //ADCON0 |= 0b00000010;
    //while(ADCON0 & 0b00000010){;}
    while(ADCON0bits.GODONE){;}
    //DelayUs(10);
    //nRes = ADRESH << 8 | ADRESL;
    return ADRESH << 8 | ADRESL;
    //return nRes;
}
/*
void dac_init(void)
{
    DACCON0=0b10101000;
    DACCON1=0b00010000;
}
*/