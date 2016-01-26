#include<pic.h>
#include<pic16f1939.h>
#include "delay.h"
#include "LCD_LIXIAN.h"
#include "EEPROM.h"
#include "KYJDEF.h"
#include "adc.h"
#include "key.h"

//__CONFIG (FOSC_INTOSC&WDTE_OFF &PWRTE_ON  & MCLRE_OFF& CLKOUTEN_OFF); 
__CONFIG (FOSC_INTOSC&WDTE_OFF &PWRTE_OFF  & MCLRE_ON& CLKOUTEN_OFF& BOREN_ON); 
__CONFIG(LVP_OFF&PLLEN_OFF);

unsigned int nTemp;
char bTimer1Flag;
char nTimer1Count;
void IO_Config(void);
//主函数
void main()
{
	Uchar i;
	int contrast;			//对比度=48(根据我们常用的外部电阻参数来的)


	OSCCON = 0x7A; //配置CPU时钟频率为16MHz

	//定时器1配置，10ms，源Fosc/4，再分频1:2，10ms一次中断
	TMR1ON = 0;
	TMR1GE = 0;
	TMR1CS1 = 0;
	TMR1CS0 = 0;
	T1CKPS1 = 1;
	T1CKPS0 = 0;
	//TMR1H = 0xD8;   //10ms
	//TMR1L = 0xEF;
    TMR1H = 0x3C;  //50ms
    TMR1L = 0xAF;
	PEIE = 1;
	GIE = 1;
	TMR1IE = 1;
	TMR1ON = 1;
    //定时器1配置结束并启用
    
    //定时器2配置，1ms
    TMR4ON=0;
    TMR4IE=0;
    T4CON=0b00001010;
    PR4=125;
    TMR4IE=1;
    TMR4ON=1;

//	nCount = 0;
	bTimer1Flag = 0;
    nTimer1Count = 0;
    IO_Config();  //初始化所有端口
    
    //初始化参数，如果已经保存到EEPROM，则读取，否则默认值初始化并保存
    KYJ_Param_Default();
    if(EEPROM_Read(0x10) == 100)
    {
        EEPROM_Load_Param(PARAM_STORE_BYTES);
    }
    else
    {
        EEPROM_Save_Param(PARAM_STORE_BYTES);
        EEPROM_Write(0x10,100);
    }
    LcmInit();
    DelayMs(100);
    LcmInit();
    LED_ON;
    DelayMs(100);
    KYJ_Init();
    adc_init();
    //dac_init();
    contrast = -20;
    LED_RUN_ON;
    LED_ERROR_ON;
    BEEP_ON;
    //显示欢迎界面
    LcmSetSongBuff(1,2,3,4,0,0,0,0);
    LcmPutSongStr(1,30,BuffCharDot,4,0);

    LcmSetSongBuff(5,6,7,8,9,0,0,0);
    LcmPutSongStr(4,20,BuffCharDot,5,0);
    DelayS(2);
    LcmClear(0x00);
    LED_RUN_OFF;
    LED_ERROR_OFF;
    BEEP_OFF;
    
    //sKYJ.nStatusTimeElapse = sKYJ.sUserParam.nRestartDelayTime;
    //sKYJ.sFactoryParam.nLowTempProtect = -10;
    while(1)
	{
        //检查状态
        if(KYJ_CheckStatus(STATUS_POWERSTOP)) KYJ_SwitchToStatus(STATUS_POWERSTOP);
		if(KYJ_CheckStatus(STATUS_KEYSTOP)) KYJ_SwitchToStatus(STATUS_KEYSTOP);
		if(KYJ_CheckStatus(STATUS_DELAYSTOP)) KYJ_SwitchToStatus(STATUS_DELAYSTOP);
		if(KYJ_CheckStatus(STATUS_FAULTSTOP)) KYJ_SwitchToStatus(STATUS_FAULTSTOP);
		if(KYJ_CheckStatus(STATUS_STARTUP)) KYJ_SwitchToStatus(STATUS_STARTUP);
		if(KYJ_CheckStatus(STATUS_LOAD)) KYJ_SwitchToStatus(STATUS_LOAD);
		if(KYJ_CheckStatus(STATUS_UNLOAD)) KYJ_SwitchToStatus(STATUS_UNLOAD);
		if(KYJ_CheckStatus(STATUS_MANUAL)) KYJ_SwitchToStatus(STATUS_MANUAL);
		KYJ_ExcecuteStatus();

        //检查界面
        if(KYJ_CheckInterface(INTERFACE_MAIN)) KYJ_SwitchToInterface(INTERFACE_MAIN);
		if(KYJ_CheckInterface(INTERFACE_MENU)) KYJ_SwitchToInterface(INTERFACE_MENU);
		if(KYJ_CheckInterface(INTERFACE_RUNPARAM)) KYJ_SwitchToInterface(INTERFACE_RUNPARAM);
		if(KYJ_CheckInterface(INTERFACE_USERPARAM)) KYJ_SwitchToInterface(INTERFACE_USERPARAM);
		if(KYJ_CheckInterface(INTERFACE_FACTORYPARAM)) KYJ_SwitchToInterface(INTERFACE_FACTORYPARAM);
		if(KYJ_CheckInterface(INTERFACE_REGPARAM)) KYJ_SwitchToInterface(INTERFACE_REGPARAM);
		if(KYJ_CheckInterface(INTERFACE_PASSWORD)) KYJ_SwitchToInterface(INTERFACE_PASSWORD);
		if(KYJ_CheckInterface(INTERFACE_PARAM)) KYJ_SwitchToInterface(INTERFACE_PARAM);
		KYJ_ExecuteInterface();
        
		if(bTimer1Flag == 1)
		{
            KYJ_UpdateData();
            nTimer1Count++;
            if(nTimer1Count>20)
            {
                sKYJ.nStatusTimeElapse++;
                if(sKYJ.nStatusTimeElapse>9999) sKYJ.nStatusTimeElapse = 9999;
                sKYJ.nInterfaceTimeElapse++;
                nTimer1Count = 0;
            }
			bTimer1Flag = 0;
		}
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
			TMR1H = 0x3C;  //50ms
			TMR1L = 0xAF;
			bTimer1Flag = 1;
        }
         // Timer 2 Interrupt
         if (TMR4IF == 1 && TMR4IE == 1) 
         {
             TMR4IF = 0;
             KYJ_SampleCurrent();
//             nTemp++;
//             if(nTemp<1000)
//             {
//                 LED_ERROR_ON;
//             }
//             else if(nTemp<2000)
//             {
//                 LED_ERROR_OFF;
//             }
//             else
//             {
//                 nTemp=0;
//             }
                 
         }
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

void IO_Config(void)
{
/*
    //LCD背景灯光
	ANSELE = 0x00;
	TRISE0 = 0;
    RE0=1;
    //LCD端口配置
    ANSELD &= 0b11111000;
    TRISC3 = 0;
    TRISC4 = 0;
    TRISC5 = 0;
    TRISD0 = 0;
    TRISD1 = 0;
    TRISD2 = 0;
    
    //开关输入，RE2远程开关，RB0停止开关
    ANSELE &= 0b11111011;
    TRISE2 = 1;
    ANSELB &=0b11111110;
    TRISB0 = 1;
 */   
    //端口A设置；RA7 RA7 继电器开关输出；RA5压力输入；RA4相序输入；RA3RA1RA0三相电流输入；RA6蜂鸣器；RA2温度测量基础电压DA输出
    ANSELA = 0b00101111;
    TRISA = 0b00111011;
    
    //端口B设置；RB4 温度输入；RB0 停止开关输入；RB1，RB2，RB3 按键输入 5、6、7，RB5 RUN LED，RB6 ERROR LED
    ANSELB = 0b00010000;
    TRISB = 0b00011111;
    WPUB = 0b00001111;  //使能RB0~RB3的弱上拉
    OPTION_REG &= 0b01111111; //使能弱上拉功能
    
    //端口C设置：RC5 DAT输出；RC3 CLK输出；RC2 继电器开关输出
    TRISC = 0b11010011;
    
    //端口D设置：RD0：ADR输出；	RD1：RES输出；	RD2：CS 输出； RD4-7 键盘输入1、2、3、4
    ANSELD = 0b00000000;
    TRISD = 0b11111000;
    
    //端口E设置：RE0 LCD背光输出；RE2 远程开关输入
    ANSELE = 0b00000000;
    TRISE = 0b11111110;
}