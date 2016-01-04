#include<pic16f1939.h>
#include "adc.h"
#include "delay.h"
void adc_init()
{
    FVRCON = 0b10101111;
    ADCON1 = 0b10100011;
//    TRISA0 = 1;
//    ANSELA |= 0b00000001;
    ADCON0 = 0b00000000; 
}

int adc_Get_Value(unsigned char nChannel)
{
    int nRes;
    ADCON0 = nChannel<<2 | 0b00000001;
    DelayUs(10);
    ADGO = 1;
    //ADCON0 |= 0b00000010;
    //while(ADCON0 & 0b00000010){;}
    while(ADGO){;}
    //DelayUs(10);
    nRes = ADRESH << 8 | ADRESL;
    return nRes;
}