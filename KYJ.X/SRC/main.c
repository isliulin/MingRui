#include<pic.h>
#include<pic16f1939.h>
#include "delay.h"
#include "LCD_LIXIAN.h"

//__CONFIG (FOSC_INTOSC&WDTE_OFF &PWRTE_ON  & MCLRE_OFF& CLKOUTEN_OFF); 
__CONFIG (FOSC_INTOSC&WDTE_OFF &PWRTE_ON  & MCLRE_ON& CLKOUTEN_OFF); 

	char bTimer1Flag;
//主函数
void main()
{
	Uchar i;
	Uchar contrast=48;			//对比度=48(根据我们常用的外部电阻参数来的)


	OSCCON = 0x7A; //配置CPU时钟频率为16MHz

	//定时器1配置，10ms，源Fosc/4，再分频1:2，10ms一次中断
	TMR1ON = 0;
	TMR1GE = 0;
	TMR1CS1 = 0;
	TMR1CS0 = 0;
	T1CKPS1 = 1;
	T1CKPS0 = 0;
	TMR1H = 0xD8;
	TMR1L = 0xEF;
	PEIE = 1;
	GIE = 1;
	TMR1IE = 1;
	TMR1ON = 1;

//	nCount = 0;
	bTimer1Flag = 0;

	ANSELE = 0x00;
	TRISE0 = 0;
    RE0=1;

ANSELD &= 0b11111000;
//ANSELD = 0x00;
TRISC3 = 0;
TRISC4 = 0;
TRISC5 = 0;
TRISD0 = 0;
TRISD1 = 0;
TRISD2 = 0;
DelayMs(100);
LcmInit();
DelayMs(100);

    while(1)
	{
/*
		if(bTimer1Flag == 1)
		{
			nCount++;
			if(nCount > 99)
			{ nCount = 0;
			RE0=!RE0;
			}
			bTimer1Flag = 0;
		}
*/
		DelayS(1);
//		RD0=!RD0;

  //    LcmPutBmp(bmp1);
		LcmClear(0x00);
		for(i=(contrast-5);i<(contrast+5);i++)
		{
			WriteCommand(0x81);	//Sets V0
			WriteCommand(0x3F&i);	//内部电位器调节对比度
			LcmPutNum(10,2,i);
			DelayS(1);
		}
		
		WriteCommand(0x81);		//Sets V0
		WriteCommand(contrast);	//恢复对比度
		LcmPutNum(10,2,contrast);
		
		//LcmClear(0xff);
		DelayS(1);
		
		LcmClear(0);
		LcmPutStr(0,0,"CA12864I2 Program");
		LcmPutStr(0,2,"SunSon ELEC-TECH");
		LcmPutStr(0,4,"TEL:755-29970110");
		LcmPutStr(0,6,"By LJ 2009.04.08");
		DelayS(1);

	}
}


//中断处理程序
void interrupt isr(void) 
{
        // Timer 0 Interrupt
        //if (TMR0IF == 1 && TMR0IE == 1) 
        //{
		//		//bitset(MT_STATUS_H,2);
		//		TMR0IF = 0;
		//		TMR0IE = 0;   
		//}
        // Timer 1 Interrupt
        if (TMR1IF == 1 && TMR1IE == 1) 
        {
			TMR1IF = 0;
			//TMR1IE = 0;
			TMR1H = 0xD8;
			TMR1L = 0xEF;
			bTimer1Flag = 1;
        }
         // Timer 2 Interrupt
         //if (TMR2IF == 1 && TMR2IE == 1) 
         //{           }
         // AD Interrupt
         //if (ADIF == 1 && ADIE == 1) 
         //{           }
		
		//串口中断
}

void LCD_Init()
{
//RC3: CLK
//RD0: ADR
//RD1: RES
//RD2: CS
//RC4: DAT
SSPEN = 0; //禁止SPI
ANSELD &= 0b11111000;
TRISC3 = 0;
TRISC4 = 0;
TRISD0 = 0;
TRISD1 = 0;
TRISD2 = 0;

CKP= 1;
SSPM0 = 0;
SSPM1 = 0;
SSPM2 = 0;
SSPM3 = 0;

SSPEN = 1; //使能SPI


}