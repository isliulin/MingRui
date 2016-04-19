#include "adc.h"
#include "delay.h"
void adc_init()
{
    ADCON0 = 0b00000000; 
    ADCON1 = 0b00000000;  //D5负参考电压=0采用Vss，D4正参考电压=0采用Vdd
    ADCON2 = 0b10010010; //10位右对齐，A/D 采集时间4Tad，A/D 转换时钟FOSC/32

    //参考电压输出
    CVRCON=0b11100101;  //使RA2（CVref）引脚输出电压=5/24*5=1.04V，供热电阻用
    CVRCON2=0b10000000; //使能固定参考电压FVR=1.2V，D6位=1表示稳定，=0表示不稳定。
}

int adc_Get_Value(unsigned char nChannel)
{
    //int nRes;
    //ADON = 0;
    ADCON0 = nChannel<<2 | 0b00000001;
    //DelayUs(10);
    //ADON = 1;
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