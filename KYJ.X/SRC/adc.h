/* 
 * File:   adc.h
 * Author: tlan
 *
 * Created on 2015年12月30日, 下午12:54
 */

#ifndef ADC_H
#define	ADC_H

#define Pressure_adc_pin RA5  //AN4
#define Temperature_adc_pin RB4 //AN11
#define CurrentA_adc_pin RA0  //AN0
#define CurrentB_adc_pin RA1  //AN1
#define CurrentC_adc_pin RA3  //AN3

#define CH_Pressure 4  //AN4
#define CH_Temperature 11 //AN11
#define CH_CurrentA 0  //AN0
#define CH_CurrentB 1  //AN1
#define CH_CurrentC 3  //AN3

void adc_init(void);
int adc_Get_Value(unsigned char nChannel);
//void dac_init(void);

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* ADC_H */

