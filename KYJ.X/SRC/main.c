#include <xc.h>
#include "delay.h"
#include "LCD_LIXIAN.h"
#include "EEPROM.h"
#include "KYJDEF.h"
#include "adc.h"
#include "key.h"

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

// CONFIG1H
#pragma config FOSC = INTIO67   // Oscillator Selection bits (Internal oscillator block, port function on RA6 and RA7)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)
#pragma config IESO = OFF       // Internal/External Oscillator Switchover bit (Oscillator Switchover mode disabled)

// CONFIG2L
#pragma config PWRT = OFF       // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = SBORDIS  // Brown-out Reset Enable bits (Brown-out Reset enabled in hardware only (SBOREN is disabled))
#pragma config BORV = 18        // Brown Out Reset Voltage bits (VBOR set to 1.8 V nominal)

// CONFIG2H
#pragma config WDTEN = OFF      // Watchdog Timer Enable bit (WDT is controlled by SWDTEN bit of the WDTCON register)
#pragma config WDTPS = 32768    // Watchdog Timer Postscale Select bits (1:32768)

// CONFIG3H
#pragma config CCP2MX = PORTC   // CCP2 MUX bit (CCP2 input/output is multiplexed with RC1)
#pragma config PBADEN = ON      // PORTB A/D Enable bit (PORTB<4:0> pins are configured as analog input channels on Reset)
#pragma config LPT1OSC = OFF    // Low-Power Timer1 Oscillator Enable bit (Timer1 configured for higher power operation)
#pragma config HFOFST = ON      // HFINTOSC Fast Start-up (HFINTOSC starts clocking the CPU without waiting for the oscillator to stablize.)
#pragma config MCLRE = ON       // MCLR Pin Enable bit (MCLR pin enabled; RE3 input pin disabled)

// CONFIG4L
#pragma config STVREN = ON      // Stack Full/Underflow Reset Enable bit (Stack full/underflow will cause Reset)
#pragma config LVP = OFF        // Single-Supply ICSP Enable bit (Single-Supply ICSP disabled)
#pragma config XINST = OFF      // Extended Instruction Set Enable bit (Instruction set extension and Indexed Addressing mode disabled (Legacy mode))

// CONFIG5L
#pragma config CP0 = OFF        // Code Protection Block 0 (Block 0 (000800-003FFFh) not code-protected)
#pragma config CP1 = OFF        // Code Protection Block 1 (Block 1 (004000-007FFFh) not code-protected)
#pragma config CP2 = OFF        // Code Protection Block 2 (Block 2 (008000-00BFFFh) not code-protected)
#pragma config CP3 = OFF        // Code Protection Block 3 (Block 3 (00C000-00FFFFh) not code-protected)

// CONFIG5H
#pragma config CPB = OFF        // Boot Block Code Protection bit (Boot block (000000-0007FFh) not code-protected)
#pragma config CPD = OFF        // Data EEPROM Code Protection bit (Data EEPROM not code-protected)

// CONFIG6L
#pragma config WRT0 = OFF       // Write Protection Block 0 (Block 0 (000800-003FFFh) not write-protected)
#pragma config WRT1 = OFF       // Write Protection Block 1 (Block 1 (004000-007FFFh) not write-protected)
#pragma config WRT2 = OFF       // Write Protection Block 2 (Block 2 (008000-00BFFFh) not write-protected)
#pragma config WRT3 = OFF       // Write Protection Block 3 (Block 3 (00C000h-00FFFFh) not write-protected)

// CONFIG6H
#pragma config WRTC = OFF       // Configuration Register Write Protection bit (Configuration registers (300000-3000FFh) not write-protected)
#pragma config WRTB = OFF       // Boot Block Write Protection bit (Boot Block (000000-0007FFh) not write-protected)
#pragma config WRTD = OFF       // Data EEPROM Write Protection bit (Data EEPROM not write-protected)

// CONFIG7L
#pragma config EBTR0 = OFF      // Table Read Protection Block 0 (Block 0 (000800-003FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR1 = OFF      // Table Read Protection Block 1 (Block 1 (004000-007FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR2 = OFF      // Table Read Protection Block 2 (Block 2 (008000-00BFFFh) not protected from table reads executed in other blocks)
#pragma config EBTR3 = OFF      // Table Read Protection Block 3 (Block 3 (00C000-00FFFFh) not protected from table reads executed in other blocks)

// CONFIG7H
#pragma config EBTRB = OFF      // Boot Block Table Read Protection bit (Boot Block (000000-0007FFh) not protected from table reads executed in other blocks)

bit b50MsFlag;
bit b1SecFlag;
char nTimer1Count;
//int nTemp;
void IO_Config(void);

int main(void)
{
    OSCCON = 0xF2; //配置CPU时钟频率为16MHz
    
	//定时器1配置，10ms，源Fosc/4，再分频1:2，10ms一次中断
	TMR1ON = 0;
	TMR1CS = 0; //内部时钟Fosc/4
	T1CKPS1 = 1; //1：4预分频比
	T1CKPS0 = 0;
	//TMR1H = 0xD8;   //10ms
	//TMR1L = 0xEF;
    TMR1H = 0x3C;  //50ms
    TMR1L = 0xAF;

	TMR1IE = 1;
	TMR1ON = 1;
    //定时器1配置结束并启用
    
    //定时器2配置，1ms
    TMR2ON=0;
    TMR2IE=0;
    T2CON=0b00000010;
    PR2=125;
    TMR2IE=1;
    TMR2ON=1;
    //定时器2配置结束
    
    //开启全局中断
   	PEIE = 1;
	GIE = 1;

	b50MsFlag = 0;
    b1SecFlag=0;
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
    
    //初始化
    LcmInit();
    DelayMs(100);
    LcmInit();  //防止LCD一次初始化失败，再次初始化
    LED_ON;
//    DelayMs(100);
    KYJ_Init();
    adc_init();
    LED_RUN_ON;
    LED_ERROR_ON;
    BEEP_ON;
    //显示欢迎界面
    LcmSetSongBuff(1,2,3,4,0,0,0,0);
    LcmPutSongStr(1,30,BuffCharDot,4,0);

    LcmSetSongBuff(5,6,7,8,9,0,0,0);
    LcmPutSongStr(4,20,BuffCharDot,5,0);
    asm("CLRWDT");
    DelayS(1);
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
        
		if(b50MsFlag)
		{
            //更新压力和温度数据
//            KYJ_UpdateData();  //不能放在这里，会被1ms的中断打断，导致采样不准
            b50MsFlag = 0;
        }
        if(b1SecFlag)
        {
            asm("CLRWDT");
            sKYJ.nStatusTimeElapse++;
            //如果时间超过9999秒，则定格在9999秒，否则无法显示
            if(sKYJ.nStatusTimeElapse>9999) sKYJ.nStatusTimeElapse = 9999;
            sKYJ.nInterfaceTimeElapse++;
            //重新初始化下端口
//            IO_Config();
            b1SecFlag=0;
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
			b50MsFlag = 1;
            nTimer1Count++;
            if(nTimer1Count>20)
            {
                b1SecFlag=1;
                nTimer1Count=0;
            }
        }
         // Timer 2 Interrupt
         if (TMR2IF == 1 && TMR2IE == 1) 
         {
            TMR2IF = 0;
            KYJ_SampleCurrent();  //采样一次电流值
//             RD2=!RD2;
//             nTemp++;
//             if(nTemp<1000)
//             {
//                 //LED_ERROR_ON;
//                 RE0=0;
//             }
//             else if(nTemp<2000)
//             {
//                 //LED_ERROR_OFF;
//                 RE0=1;
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

void IO_Config(void)
{
    //端口A设置；RA7 RA7 继电器开关输出；RA5压力输入；RA4相序输入；RA3RA1RA0三相电流输入；RA6蜂鸣器；RA2温度测量基础电压DA输出
    ANSEL = 0b00011111; //ANS0-ANS4，对应RA0,RA1,RA2,RA3,RA5
    TRISA = 0b00111011;
    
    //端口B设置；RB4 温度输入；RB0 停止开关输入；RB1，RB2，RB3 按键输入 5、6、7，RB5 RUN LED，RB6 ERROR LED
    //RUN LED 从 RB5改为RB6；ERR LED从RB6改为RB7。但是RB6，RB7为调试口，暂时先不用，RB5改为输入电压模拟量输入
    //46K20，RB5改成down按键输入，RB3改成电源电压模拟输入
    ANSELH = 0b00001010; //ANS11，对应RB4端口；ANS9，对应RB3端口
    TRISB = 0b00111111;
    WPUB = 0b00100111;  //使能RB0~RB3的弱上拉
    RBPU = 0;  //使能弱上拉功能
    
    //端口C设置：RC5 DAT输出；RC3 CLK输出；RC2 继电器开关输出
    TRISC = 0b11010011;
    
    //端口D设置：RD0：ADR输出；	RD1：RES输出；	RD2：CS 输出； RD4-7 键盘输入1、2、3、4
    TRISD = 0b11111000;
    //46K20 Port D 没有弱上拉功能
    
    //端口E设置：RE0 LCD背光输出；RE2 远程开关输入，RE1 蜂鸣器输出
    //TRISE的D4位跟PortD有关，设成0
    TRISE = 0b11101100;
}