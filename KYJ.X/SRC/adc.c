#include<pic16f1939.h>
#include "adc.h"
#include "delay.h"
void adc_init()
{
    FVRCON = 0b10101111;  //参考电压4X，0-4.096V
    ADCON1 = 0b10100011;
//    TRISA0 = 1;
//    ANSELA |= 0b00000001;
    ADCON0 = 0b00000000; 
    
    //配置DAC输出
    DACCON0=0b10101000;
    DACCON1=0b00001000;//输出1.024V
}

int adc_Get_Value(unsigned char nChannel)
{
    //int nRes;
    ADCON0 = nChannel<<2 | 0b00000001;
    DelayUs(10);
    ADGO = 1;
    //ADCON0 |= 0b00000010;
    //while(ADCON0 & 0b00000010){;}
    while(ADGO){;}
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