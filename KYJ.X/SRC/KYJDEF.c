#include "KYJDEF.h"
#include "LCD_LIXIAN.h"
#include "key.h"
#include "adc.h"
#include "EEPROM.h"

volatile unsigned int nADVref=5000;  //AD参考电压，单位：mV
struct KYJ_s sKYJ;
bit bRefreshInterface;
unsigned char nMenuIndex;  //当前菜单序号  1-运行参数；2-用户参数；3-厂家参数；4-注册参数；5-用户密码
unsigned char nParamIndex;   //当前参数序号
unsigned char nDigitIndex; //当前数位
int nParamValue;

unsigned int nCurrent;  //电流采样累加值
unsigned char nCurrentSampleCount;  //电流采样次数，1ms采样一次，每20ms（对应50Hz）计算平均值
unsigned long nLongTemp; //32位临时变量
bit nRet;
int nValue;
void KYJ_Init(void)
{
    nCurrent=0;
    nCurrentSampleCount=0;
    
    sKYJ.nStatus = STATUS_POWERSTOP;
    sKYJ.nFaultFlag = 0;
    sKYJ.nStatusTimeElapse = 0;
    sKYJ.nInterface = 0; //设成0后会自动切换到main界面
    sKYJ.nInterfaceTimeElapse = 0;
    FAN_SW_OFF;
    MOTOR_SW_OFF;
    LOAD_SW_OFF;
}

void KYJ_Param_Default(void)
{
    sKYJ.nPressure = 0;
    sKYJ.nTemperature = 0;
    sKYJ.nVoltage = 0;
    
    sKYJ.sUserParam.nLoadPress = 70;//加载压力
    sKYJ.sUserParam.nUnLoadPress = 90;//卸载压力
    sKYJ.sUserParam.nFanStartTemp = 80; //风机启温度
    sKYJ.sUserParam.nFanStopTemp = 70;//风机停温度
    sKYJ.sUserParam.nMCUDelayTime = 8; //主机延时时间，单位：秒
    sKYJ.sUserParam.nSADelayTime = 6; //星角延时时间，单位：秒
    sKYJ.sUserParam.nLoadDelayTime = 2; //加载延时时间，单位：秒
    sKYJ.sUserParam.nNoLoadDelayTime = 600; //空载延时时间
    sKYJ.sUserParam.nStopDelayTime =10; //停机延时时间
    sKYJ.sUserParam.nRestartDelayTime = 100; //重启延时时间
    sKYJ.sUserParam.nStartStopMode = 0; //启停方式
    sKYJ.sUserParam.nLoadMode = 1; //加载方式
    sKYJ.sUserParam.nCommMode = 0 ; //通讯方式
    sKYJ.sUserParam.nCommCode = 16; //通讯编码
    sKYJ.sUserParam.nSlaveMode = 0; //联动状态
    sKYJ.sUserParam.nInTurnTime = 99; //轮换时间，单位：小时
    sKYJ.sUserParam.nSlaveCount = 0; //联动机数
    sKYJ.sUserParam.nSlaveLoadPress = 70;//联动加载压力
    sKYJ.sUserParam.nSlaveUnLoadPress = 90;//联动卸载压力
    sKYJ.sUserParam.nSlaveDelayTime = 50;//联动延时时间
    sKYJ.sUserParam.nOilFilterTime = 0;//油滤器时间复位
    sKYJ.sUserParam.nOilDeployTime = 0;//油分器时间复位
    sKYJ.sUserParam.nAirFilterTime = 0; //空滤器时间复位
    sKYJ.sUserParam.nOil2Time = 0; //润滑油时间复位
    sKYJ.sUserParam.nOil3Time = 0; //润滑脂时间复位
    sKYJ.sUserParam.nBeltTime = 0; //皮带时间复位
    sKYJ.sUserParam.nOilFilterPresetTime = 0; //油滤器时间预置
    sKYJ.sUserParam.nOilDeployPresetTime = 0; //油分器时间预置
    sKYJ.sUserParam.nAirFilterPresetTime = 0; //空滤器时间预置
    sKYJ.sUserParam.nOil2PresetTime = 0; //润滑油时间预置
    sKYJ.sUserParam.nOil3PresetTime = 0; //润滑脂时间预置
    sKYJ.sUserParam.nBeltPresetTime = 0; //皮带时间预置
    sKYJ.sUserParam.nLanguage = 1;//中文/英文
    sKYJ.sUserParam.nPassword = 0000;//修改用户密码
    
    
    sKYJ.sFactoryParam.nMainMotorNormalCurrent = 100;  //主机额定电流
    sKYJ.sFactoryParam.nWarningTemp = 105; //排温预警温度
    sKYJ.sFactoryParam.nStopTemp = 110;//排温停机温度
    sKYJ.sFactoryParam.nStopPress = 100; //供气停机压力
    sKYJ.sFactoryParam.nUnloadPressLimit= 80; //卸载压力高限
    sKYJ.sFactoryParam.nTotalRunTime = 0; //运行总时间
    sKYJ.sFactoryParam.nTotalLoadTime = 0; //负载总时间
    sKYJ.sFactoryParam.nHistoryFaultRest = 0; //历史故障复位
    sKYJ.sFactoryParam.nCurrentNotBalance = 6; //电流不平衡度
    sKYJ.sFactoryParam.nNoPhaseProtectTime = 2; //断相保护时间
    sKYJ.sFactoryParam.nProductDate = 160101; //出厂日期
    sKYJ.sFactoryParam.nProductSN = 0;//出厂编号
    sKYJ.sFactoryParam.nPhaseProtect = 1; //相序保护
    sKYJ.sFactoryParam.nFreqSelect = 0; //频率选择
    sKYJ.sFactoryParam.nCooperationMode = 0; //联动方式
    sKYJ.sFactoryParam.nLowTempProtect = 5; //低温保护
    sKYJ.sFactoryParam.nTimeLimit = 0;//时限
    sKYJ.sFactoryParam.nWarningOverTime = 10;//预警过久停机
    sKYJ.sFactoryParam.nCommParam = 0;//通信预置参数
    //sKYJ.sFactoryParam.nParam1 = 0;//参数1
     sKYJ.sFactoryParam.nStartType = 0;  //默认直接启动   
    
    sKYJ.sRegParam.nStandCurrentA = 0;//标准电流
    sKYJ.sRegParam.nStandCurrentAFactor = 1000;//系数
    sKYJ.sRegParam.nCurrentA = 0;//现行电流
    sKYJ.sRegParam.nStandCurrentB = 0;//标准电流
    sKYJ.sRegParam.nStandCurrentBFactor = 1000;//系数
    sKYJ.sRegParam.nCurrentB = 0;//现行电流
    sKYJ.sRegParam.nStandCurrentC = 0; //标准电流
    sKYJ.sRegParam.nStandCurrentCFactor = 1000;//系数
    sKYJ.sRegParam.nCurrentC = 0;//现行电流
    sKYJ.sRegParam.nStandTemp = 25;//标准温度
    sKYJ.sRegParam.nStandTempFactor = 1000;//系数
    sKYJ.sRegParam.nZeroBias = 0;//零点
    sKYJ.sRegParam.nTemp = 0;//现行温度
    sKYJ.sRegParam.nStandVoltage = 220; //标准电压
    sKYJ.sRegParam.nVoltage = 0; //现行电压
    sKYJ.sRegParam.nStandVoltageFactor = 1000; //电压系数,0.001
    sKYJ.sRegParam.nCurrMode = 0;//CURR MODE

    sKYJ.sPassword.nOpPass = 0000; //操作密码
    sKYJ.sPassword.nUserPass = 1111; //用户密码
    sKYJ.sPassword.nSalePass = 2222; //销售密码
    sKYJ.sPassword.nFactoryPass = 3333; //厂家密码
    sKYJ.sPassword.nRegPass = 4444;//校准密码
    sKYJ.sPassword.nSuperPass = 5555;//厂家超级密码
}

bit KYJ_CheckStatus(unsigned char nStatus)
{
    int nCurrentMax,nCurrentMin;
    nRet = 0;
    switch(nStatus)
    {
        case STATUS_POWERSTOP:
            break;
        case STATUS_KEYSTOP:
            if(sKYJ.nStatus != STATUS_KEYSTOP && Key_Press(KEY_STOP)) nRet=1;
            if(sKYJ.nStatus == STATUS_FAULTSTOP && sKYJ.nFaultFlag == 0) nRet = 1;
            break;
        case STATUS_DELAYSTOP:
            if(sKYJ.nStatus == STATUS_UNLOAD && sKYJ.nStatusTimeElapse > sKYJ.sUserParam.nNoLoadDelayTime) nRet = 1;
            break;
        case STATUS_FAULTSTOP:
            
            //if(sKYJ.nStatus !=STATUS_FAULTSTOP)
            //相序检测

            if(!(sKYJ.nFaultFlag&0x01) && !PORTAbits.RA4) {sKYJ.nFaultFlag |= 0x01;nRet=0;}
            else if(PORTAbits.RA4) sKYJ.nFaultFlag &= 0xFE;

            //电流不平衡检测，是否需要在主机延时时间以后才检测？
            nCurrentMax = max(sKYJ.nCurrentA,sKYJ.nCurrentB);
            nCurrentMax = max(nCurrentMax,sKYJ.nCurrentC);
            nCurrentMin = min(sKYJ.nCurrentA,sKYJ.nCurrentB);
            nCurrentMin = min(nCurrentMin,sKYJ.nCurrentC); 
                
            if(sKYJ.sFactoryParam.nCurrentNotBalance < 15 &&   //不平衡度设置值大于等于15，则不检测电流不平衡
                    sKYJ.nStatusTimeElapse>2 &&   //躲过启动瞬间
                    !(sKYJ.nFaultFlag&0x02)
                    )
            {
               

                if(nCurrentMax > (nCurrentMin*(10+sKYJ.sFactoryParam.nCurrentNotBalance)/10))
                {
                    sKYJ.nFaultFlag |= 0x02;
                    nRet=1;
                }

            }

            //超压检测
            if(!(sKYJ.nFaultFlag&0x08) && sKYJ.nPressure > sKYJ.sFactoryParam.nStopPress)
            {
                sKYJ.nFaultFlag | =0x08;
                nRet=1;
            }

            //低温保护
            if(!(sKYJ.nFaultFlag&0x10) && sKYJ.nTemperature < (- sKYJ.sFactoryParam.nLowTempProtect)) 
            {
                sKYJ.nFaultFlag |=0x10;
                nRet=1;
            }

            //过载保护，在主机延时时间以后才检测
            if(!(sKYJ.nFaultFlag&0x20) && 
                    sKYJ.nStatusTimeElapse>sKYJ.sUserParam.nMCUDelayTime && 
                    nCurrentMax > (sKYJ.sFactoryParam.nMainMotorNormalCurrent * 12 /10))   //大于额定电流1.2倍
            {
                sKYJ.nFaultFlag |=0x20;
                nRet=1;
            }

            //电源电压保护
            if(!(sKYJ.nFaultFlag&0x40) && (sKYJ.nVoltage<180 || sKYJ.nVoltage> 240))
            {
                sKYJ.nFaultFlag|=0x40;
                nRet = 1;
            }

            //压力传感器故障，如果检测到的电流<4mA，则测量值为0
            if(!(sKYJ.nFaultFlag&0x80) && (sKYJ.nPressure <1))
            {
                sKYJ.nFaultFlag |= 0x80;
                nRet = 1;
            }

            //温度传感器故障，如果检测到的温度值大于1000，则很有可能温度传感器没接
            if(!(sKYJ.nFaultFlag&0x100) && (sKYJ.nTemperature >= 1000))
            {
                sKYJ.nFaultFlag |= 0x100;
                nRet = 1;
            }
            else if(!(sKYJ.nFaultFlag&0x04) && sKYJ.nTemperature > (int)sKYJ.sFactoryParam.nStopTemp) //不超过1000，则进行过热检测
            {
                sKYJ.nFaultFlag |= 0x04; 
                nRet=1;
            }
    
        
            break;
        case STATUS_STARTUP:
            if(sKYJ.nFaultFlag == 0)  //有错误时，不能直接启动，必须按OK键先清除错误；没错误时，可以启动
            {
                if(Key_Release(KEY_START) && sKYJ.nStatusTimeElapse>sKYJ.sUserParam.nRestartDelayTime) nRet = 1;
                if(sKYJ.nStatus == STATUS_DELAYSTOP && sKYJ.nPressure < sKYJ.sUserParam.nLoadPress) nRet=1;
            }
            break;
        case STATUS_LOAD:
            if(sKYJ.sUserParam.nLoadMode == 0) //如果是手动方式
            {
                if((sKYJ.nStatus & (STATUS_STARTUP | STATUS_UNLOAD)) && sKYJ.nStatusTimeElapse > sKYJ.sUserParam.nLoadDelayTime)
                {
                    if(sKYJ.nInterface == INTERFACE_MAIN && sKYJ.nPressure < sKYJ.sUserParam.nUnLoadPress && Key_Release(KEY_OK)) nRet = 1;
                }
            }
            else  //自动方式
            {
                if(sKYJ.nStatus & (STATUS_STARTUP | STATUS_UNLOAD))
                {
                    if((sKYJ.nStatusTimeElapse > sKYJ.sUserParam.nLoadDelayTime) && (sKYJ.nPressure < sKYJ.sUserParam.nLoadPress)) nRet = 1;
                    //位于主界面时，如果压力低于卸载压力，按下确认键，可以手动加载
                    if(sKYJ.nInterface == INTERFACE_MAIN && sKYJ.nPressure < sKYJ.sUserParam.nUnLoadPress && Key_Release(KEY_OK)) nRet = 1;
                }
            }
            break;
        case STATUS_UNLOAD:
            if(sKYJ.sUserParam.nLoadMode == 0) //如果是手动方式
            {
                if(sKYJ.nInterface == INTERFACE_MAIN && sKYJ.nPressure > sKYJ.sUserParam.nLoadPress && Key_Release(KEY_OK)) nRet = 1;
            }
            else //自动方式
            {
                if(sKYJ.nStatus == STATUS_LOAD && sKYJ.nPressure > sKYJ.sUserParam.nUnLoadPress) nRet = 1;
                if(sKYJ.nStatus == STATUS_STARTUP)
                {
                    if((sKYJ.nStatusTimeElapse > sKYJ.sUserParam.nLoadDelayTime) && (sKYJ.nPressure >= sKYJ.sUserParam.nLoadPress)) nRet = 1;           
                }
                //位于主界面时，如果压力高于加载压力，按下确认键，可以手动卸载
                if(sKYJ.nInterface == INTERFACE_MAIN && 
                        sKYJ.nStatus == STATUS_LOAD &&
                        sKYJ.nPressure > sKYJ.sUserParam.nLoadPress && 
                        Key_Release(KEY_OK)) 
                    nRet = 1;
            }
            break;
        case STATUS_MANUAL:
            break;
        default:
            break;
    }
    return nRet;    
}

void KYJ_SwitchToStatus(unsigned char nStatus)
{
    switch(nStatus)
    {
        case STATUS_FAULTSTOP:
            LED_ERROR_ON;
            LED_ERROR_ON; //给两次就能点亮？
            
            //是否需要立即关闭主机和风扇？
            LOAD_SW_OFF;
            FAN_SW_OFF;
            MOTOR_SW_OFF;
            //break;
        case STATUS_POWERSTOP:
            LED_RUN_OFF;
            //break;
        case STATUS_KEYSTOP:
            LED_RUN_OFF;
            //break;
        case STATUS_DELAYSTOP:
            LOAD_SW_OFF;
            //MOTOR_SW_OFF;
            break;
        case STATUS_STARTUP:
            LED_RUN_ON;
            
            if(sKYJ.sFactoryParam.nStartType == 1) //星角启动
            {
                MOTOR_SW_ON;  
            }
            else
            {
                MOTOR_SW_ON;  //直接启动
            }
           
            
            //sKYJ.nFaultFlag=0;  //错误标志清零
            LED_ERROR_OFF;
            break;
        case STATUS_LOAD:
            LOAD_SW_ON;
            break;
        case STATUS_UNLOAD:
            LOAD_SW_OFF;
            break;
        case STATUS_MANUAL:
            break;
        default:
            break;
    }
    sKYJ.nStatus = nStatus;
    sKYJ.nStatusTimeElapse = 0;
    return;      
}

void KYJ_ExcecuteStatus(void)
{
    switch(sKYJ.nStatus)
    {
        case STATUS_POWERSTOP:
            //break;
        case STATUS_KEYSTOP:
            //break;
        case STATUS_DELAYSTOP:
            //break;
        case STATUS_FAULTSTOP:
            if(sKYJ.nStatusTimeElapse > sKYJ.sUserParam.nStopDelayTime) {MOTOR_SW_OFF;FAN_SW_OFF;}
            if(Key_Press(KEY_OK)) sKYJ.nFaultFlag=0;  //按下OK键，则错误标志清零。
            break;
        case STATUS_STARTUP:
            if(sKYJ.sFactoryParam.nStartType == 1) //星角启动
            {
                if(sKYJ.nStatusTimeElapse < sKYJ.sUserParam.nSADelayTime)
                {
                    MOTOR_SW_ON;
                    FAN_SW_ON;
                }
                else
                {
                    FAN_SW_OFF;
                }
            }
            else
            {
                MOTOR_SW_ON;  //直接启动
            }
            break;
        case STATUS_LOAD:
            //break;
        case STATUS_UNLOAD:
            //需要确认下，风扇是否在加载/卸载运行过程中自动启停。在主机启动后是否需要启停？会否影响星角启动？
            if(sKYJ.nTemperature > (int)sKYJ.sUserParam.nFanStartTemp) 
                FAN_SW_ON;
            else if(sKYJ.nTemperature < (int)sKYJ.sUserParam.nFanStopTemp) 
                FAN_SW_OFF;
            break;
        case STATUS_MANUAL:
            break;
        default:
            break;
    }
    return;      
}

bit KYJ_CheckInterface(unsigned char nInterface)
{
    nRet = 0;
    switch(nInterface)
    {
        case INTERFACE_MAIN:
            if(sKYJ.nInterface == 0 ||
                    (sKYJ.nInterface!=INTERFACE_MAIN && sKYJ.nInterfaceTimeElapse > 10) || 
                    (sKYJ.nInterface == INTERFACE_MENU && Key_Release(KEY_RESET))
                    ) nRet = 1;
            break;
        case INTERFACE_MENU:
            if(sKYJ.nInterface == INTERFACE_MAIN && Key_Release(KEY_DOWN)) nRet = 1;
            if((sKYJ.nInterface == INTERFACE_RUNPARAM || 
                    sKYJ.nInterface==INTERFACE_USERPARAM || 
                    sKYJ.nInterface==INTERFACE_FACTORYPARAM|| 
                    sKYJ.nInterface==INTERFACE_REGPARAM|| 
                    sKYJ.nInterface==INTERFACE_PASSWORD) && 
                    Key_Release(KEY_RESET)) nRet = 1;
            break;
        case INTERFACE_RUNPARAM:
            if(sKYJ.nInterface == INTERFACE_MENU && nMenuIndex == 1 && Key_Release(KEY_MOVE)) nRet = 1;
            if(sKYJ.nInterface == INTERFACE_PARAM && nMenuIndex == 1 && Key_Release(KEY_RESET)) nRet = 1;
            break;
        case INTERFACE_USERPARAM:
            if(sKYJ.nInterface == INTERFACE_MENU && nMenuIndex == 2 && Key_Release(KEY_MOVE)) nRet = 1;
            if(sKYJ.nInterface == INTERFACE_PARAM && nMenuIndex == 2 && Key_Release(KEY_RESET)) nRet = 1;
            break;
        case INTERFACE_FACTORYPARAM:
            if(sKYJ.nInterface == INTERFACE_MENU && nMenuIndex == 3 && Key_Release(KEY_MOVE)) nRet = 1;
            if(sKYJ.nInterface == INTERFACE_PARAM && nMenuIndex == 3 && Key_Release(KEY_RESET)) nRet = 1;
            break;
        case INTERFACE_REGPARAM:
            if(sKYJ.nInterface == INTERFACE_MENU && nMenuIndex == 4 && Key_Release(KEY_MOVE)) nRet = 1;
            if(sKYJ.nInterface == INTERFACE_PARAM && nMenuIndex == 4 && Key_Release(KEY_RESET)) nRet = 1;
            break;
        case INTERFACE_PASSWORD:
            if(sKYJ.nInterface == INTERFACE_MENU && nMenuIndex == 5 && Key_Release(KEY_MOVE)) nRet = 1;
            if(sKYJ.nInterface == INTERFACE_PARAM && nMenuIndex == 5 && Key_Release(KEY_RESET)) nRet = 1;
            break;
        case INTERFACE_PARAM:
            if((sKYJ.nInterface == INTERFACE_USERPARAM || sKYJ.nInterface == INTERFACE_FACTORYPARAM || sKYJ.nInterface == INTERFACE_REGPARAM)
                    && Key_Release(KEY_MOVE)
                    ) nRet = 1;
            break;
        default:
            break;
    }
    return nRet;    
}

void KYJ_SwitchToInterface(unsigned char nInterface)
{
    if(nInterface != INTERFACE_PARAM) LcmClear(0x00);
    switch(nInterface)
    {
        case INTERFACE_MAIN:
                
                //LcmSetSongBuff(10,11,0,0,0,0,0,0); //温度
                //LcmPutSongStr(1,0,BuffCharDot,2,0);
                
                LcmSetSongBuff(12,0,0,0,0,0,0,0); //℃
                LcmPutSongStr(1,32,BuffCharDot,1,0);
                
                LcmPutStr(104,1,(unsigned char *)"MPa");
                
//                LcmSetSongBuff(13,14,15,17,18,0,0,0);//设备已停止
//                LcmPutSongStr(4,0,BuffCharDot,5,0);

                LcmSetSongBuff(19,0,0,0,0,0,0,0); //秒
                LcmPutSongStr(4,112,BuffCharDot,1,0);

            break;
        case INTERFACE_MENU:
            nMenuIndex = 1;
            nParamIndex = 0;
            
            break;
        case INTERFACE_RUNPARAM:
//            if(nParamIndex==0)nParamIndex = 1;
//            break;
        case INTERFACE_USERPARAM:
//            if(nParamIndex==0)nParamIndex = 1;
//            break;
        case INTERFACE_FACTORYPARAM:
//            if(nParamIndex==0)nParamIndex = 1;
//            break;
        case INTERFACE_REGPARAM:
//            if(nParamIndex==0)nParamIndex = 1;
//            break;
        case INTERFACE_PASSWORD:
            if(nParamIndex==0)nParamIndex = 1;
            break;
        case INTERFACE_PARAM:
            //nParamIndex = 1;
            nDigitIndex = 1;
            break;
        default:
            break;
    }
    sKYJ.nInterface = nInterface;
    sKYJ.nInterfaceTimeElapse = 0;
    bRefreshInterface = 1;

    return;      
}

void KYJ_ExecuteInterface(void)
{
    //float fFactor;
    char tempValue[4];
    //如果有按键按下，则界面流逝归零
    if(!KEY_RESET_PIN || !KEY_OK_PIN || !KEY_UP_PIN|| !KEY_DOWN_PIN||!KEY_MOVE_PIN)
        sKYJ.nInterfaceTimeElapse = 0;
    switch(sKYJ.nInterface)
    {
        case INTERFACE_MAIN:
            switch(sKYJ.nStatus)
            {
                case STATUS_POWERSTOP:
//                    LcmSetSongBuff(13,14,15,17,18,0,0,0);//设备已停止
//                    break;
                case STATUS_KEYSTOP:
//                    LcmSetSongBuff(13,14,15,17,18,0,0,0);//设备已停止
//                    break;
                case STATUS_DELAYSTOP:
                    LcmSetSongBuff(13,14,15,17,18,0,0,0);//设备停止
                    //显示停机延时剩余时间
                    nValue = (sKYJ.nStatusTimeElapse > sKYJ.sUserParam.nStopDelayTime)? 0 : (sKYJ.sUserParam.nStopDelayTime - sKYJ.nStatusTimeElapse);
                    LcmPutFixDigit(4,79,nValue,4,0);
                    LcmSetSongBuff(19,0,0,0,0,0,0,0); //秒
                    LcmPutSongStr(4,112,BuffCharDot,1,0);
                    break;
                case STATUS_FAULTSTOP:
                    if(sKYJ.nFaultFlag & 0x0100) //温度故障
                    {
                        LcmSetSongBuff(10,11,91,92,30,0,0,0);
                    }
                    else if(sKYJ.nFaultFlag & 0x80)  //压力故障
                    {
                        LcmSetSongBuff(7,56,91,92,30,0,0,0);
                    }
                    else if(sKYJ.nFaultFlag & 0x40) //电压保护
                    {
                        LcmSetSongBuff(79,7,98,99,30,0,0,0);
                    }
                    else if(sKYJ.nFaultFlag & 0x20) //过载保护
                    {
                        LcmSetSongBuff(110,36,98,99,30,0,0,0);
                    }
                    else if(sKYJ.nFaultFlag & 0x10) //低温保护
                    {
                        LcmSetSongBuff(109,10,98,99,30,0,0,0);
                    }
                    else if(sKYJ.nFaultFlag & 0x08) //过压保护
                    {
                        LcmSetSongBuff(110,7,98,99,30,0,0,0);
                    }
                    else if(sKYJ.nFaultFlag & 0x04) //过热保护
                    {
                        LcmSetSongBuff(110,10,98,99,30,0,0,0);
                    }
                    else if(sKYJ.nFaultFlag & 0x02) //电流不平衡
                    {
                        LcmSetSongBuff(79,80,93,94,95,0,0,0);
                    }
                    else if(sKYJ.nFaultFlag & 0x01) //相序保护
                    {
                        LcmSetSongBuff(97,108,98,99,30,0,0,0);
                    }
                    else
                    {
                        //LcmSetSongBuff(13,14,15,17,18,0,0,0);//设备已停止
                        ;
                    }
                    //显示故障代码
                    LcmPutFixDigit(4,79,sKYJ.nFaultFlag,4,0);
                    break;
                case STATUS_STARTUP:
                    LcmSetSongBuff(13,14,15,31,32,0,0,0);//设备已启动
                    //显示加载延时剩余时间
                    nValue = (sKYJ.nStatusTimeElapse > sKYJ.sUserParam.nLoadDelayTime)? 0 : (sKYJ.sUserParam.nLoadDelayTime - sKYJ.nStatusTimeElapse);
                    LcmPutFixDigit(4,79,nValue,4,0);
                    LcmSetSongBuff(19,0,0,0,0,0,0,0); //秒
                    LcmPutSongStr(4,112,BuffCharDot,1,0);                    
                    break;
                case STATUS_LOAD:
                    LcmSetSongBuff(13,14,15,35,36,0,0,0);//设备已加载
                    //显示0剩余时间
                    LcmPutFixDigit(4,79,0,4,0);
                    LcmSetSongBuff(19,0,0,0,0,0,0,0); //秒
                    LcmPutSongStr(4,112,BuffCharDot,1,0);                    
                    break;
                case STATUS_UNLOAD:
                    LcmSetSongBuff(13,14,15,57,36,0,0,0);//设备已卸载
                    //显示空车延时剩余时间
                    nValue = (sKYJ.nStatusTimeElapse > sKYJ.sUserParam.nNoLoadDelayTime)? 0 : (sKYJ.sUserParam.nNoLoadDelayTime - sKYJ.nStatusTimeElapse);
                    LcmPutFixDigit(4,79,nValue,4,0);
                    LcmSetSongBuff(19,0,0,0,0,0,0,0); //秒
                    LcmPutSongStr(4,112,BuffCharDot,1,0);                    
                    break;
                case STATUS_MANUAL:
                    break;
                default:
                    break;
            
            }
            LcmPutSongStr(4,0,BuffCharDot,5,0);
            
            //显示温度
            if(sKYJ.nTemperature<0)
                LcmPutFixDigit(1,0,sKYJ.nTemperature,2,0);
            else
                LcmPutFixDigit(1,0,sKYJ.nTemperature,3,0);

            //显示压力
            //LcmPutFixDigit(1,79,sKYJ.sRunParam.fPressure,4,0);
            LcmPutFloatDigit(1,64,sKYJ.nPressure,4,0,2);
            
            //显示调试信息
            LcmPutFixDigit(6,30,sKYJ.nStatus,4,0);
            break;
        case INTERFACE_MENU:
            if(Key_Release(KEY_DOWN))
            {
                nMenuIndex++;
                if(nMenuIndex> 5) nMenuIndex = 1;
                bRefreshInterface = 1;
            }
            else if(Key_Release(KEY_UP))
            {
                nMenuIndex--;
                if(nMenuIndex<1) nMenuIndex = 5;
                bRefreshInterface = 1;
            }
            if(bRefreshInterface)
            {
                if(nMenuIndex < 5)  //显示第1-4项
                {
                    LcmSetSongBuff(20,21,22,23,0,0,0,0); //运行参数
                    if(nMenuIndex == 1)LcmPutSongStr(0,0,BuffCharDot,4,1); else  LcmPutSongStr(0,0,BuffCharDot,4,0);     
                    
                    LcmSetSongBuff(4,24,22,23,0,0,0,0); //用户参数
                    if(nMenuIndex == 2)LcmPutSongStr(2,0,BuffCharDot,4,1); else  LcmPutSongStr(2,0,BuffCharDot,4,0);    
                    
                    LcmSetSongBuff(25,26,22,23,0,0,0,0); //厂家参数
                    if(nMenuIndex == 3)LcmPutSongStr(4,0,BuffCharDot,4,1); else  LcmPutSongStr(4,0,BuffCharDot,4,0);    
                    
                    LcmSetSongBuff(27,28,22,23,0,0,0,0); //调整参数
                    if(nMenuIndex == 4)LcmPutSongStr(6,0,BuffCharDot,4,1); else  LcmPutSongStr(6,0,BuffCharDot,4,0);    
                }
                else  //显示第5项
                {
                    LcmClear(0x00);
                    LcmSetSongBuff(40,41,13,70,0,0,0,0); //密码设置
                    LcmPutSongStr(0,0,BuffCharDot,4,1);
                }
            }
            break;
        case INTERFACE_RUNPARAM:
            if(Key_Release(KEY_DOWN))
            {
                nParamIndex++;
                if(nParamIndex> 5) nParamIndex = 1;
                bRefreshInterface = 1;
            }
            else if(Key_Release(KEY_UP))
            {
                nParamIndex--;
                if(nParamIndex<1) nParamIndex = 5;
                bRefreshInterface = 1;
            }
            if(bRefreshInterface)
            {
                LcmClear(0x00);
                switch(nParamIndex)
                {
                    case 1:
                        LcmSetSongBuff(29,9,79,80,0,0,0,0); //主机电流
                        LcmPutSongStr(0,0,BuffCharDot,4,0);
                        LcmPutStr(0,2,(unsigned char *)"(A):");
                        LcmPutStr(0,4,(unsigned char *)"(B):");
                        LcmPutStr(0,6,(unsigned char *)"(C):");
                        break;
                    case 2:
                        LcmSetSongBuff(7,56,0,0,0,0,0,0); //压力
                        LcmPutSongStr(1,0,BuffCharDot,2,0);
                        LcmPutStr(96,4,(unsigned char *)"MPa");
                        
                        break;
                    case 3:
                        LcmSetSongBuff(20,21,87,33,34,0,0,0); //运行总时间
                        LcmPutSongStr(1,0,BuffCharDot,5,0);
                        
                        LcmSetSongBuff(119,33,0,0,0,0,0,0); //小时
                        LcmPutSongStr(4,96,BuffCharDot,2,0);
                        
                        break;

                    case 4:
                        
                        LcmSetSongBuff(88,36,87,33,34,0,0,0); //负载总时间
                        LcmPutSongStr(1,0,BuffCharDot,5,0);
                        
                        LcmSetSongBuff(119,33,0,0,0,0,0,0); //小时
                        LcmPutSongStr(4,96,BuffCharDot,2,0);                        
                        break;
                    case 5:
                        
                        LcmSetSongBuff(83,79,79,7,0,0,0,0); //供电电压
                        LcmPutSongStr(1,0,BuffCharDot,4,0);
                        
                        LcmPutStr(96,4,(unsigned char *) "V");                        
                        break;
                    default:
                        break;
                }
            }
                switch(nParamIndex)
                {
                    case 1:
//                        LcmSetSongBuff(29,9,79,80,0,0,0,0); //主机电流
//                        LcmPutSongStr(0,0,BuffCharDot,4,0);
//                        LcmPutStr(0,2,"(A):");
//                        LcmPutStr(0,4,"(B):");
//                        LcmPutStr(0,6,"(C):");
                        //nLongTemp = (unsigned long)sKYJ.sRunParam.nCurrentA * sKYJ.sRegParam.nStandCurrentAFactor;
                        LcmPutFloatDigit(2,32,sKYJ.nCurrentA,4,0,1);
                        LcmPutChar(80,2,'A');
                        //nLongTemp = (unsigned long)sKYJ.sRunParam.nCurrentB*sKYJ.sRegParam.nStandCurrentBFactor;
                        LcmPutFloatDigit(4,32,sKYJ.nCurrentB,4,0,1);
                        LcmPutChar(80,4,'A');
                        //nLongTemp = (unsigned long)sKYJ.sRunParam.nCurrentC*sKYJ.sRegParam.nStandCurrentCFactor;
                        LcmPutFloatDigit(6,32,sKYJ.nCurrentC,4,0,1);
                        LcmPutChar(80,6,'A');
                        break;
                    case 2:
//                        LcmSetSongBuff(7,56,0,0,0,0,0,0); //压力
//                        LcmPutSongStr(1,0,BuffCharDot,2,0);
//                        LcmPutStr(96,4,"MPa");
                        LcmPutFloatDigit(4,40,sKYJ.nPressure,4,0,2);
                        
                        break;
                    case 3:
//                        LcmSetSongBuff(20,21,87,33,34,0,0,0); //运行总时间
//                        LcmPutSongStr(1,0,BuffCharDot,5,0);
//                        
//                        LcmSetSongBuff(119,33,0,0,0,0,0,0); //小时
//                        LcmPutSongStr(4,96,BuffCharDot,2,0);
                        LcmPutFixDigit(4,8,sKYJ.sRunParam.nTotalTime/10000,4,0);
                        LcmPutFixDigit(4,40,sKYJ.sRunParam.nTotalTime%10000,4,0);
                        break;

                    case 4:
                        
//                        LcmSetSongBuff(88,36,87,33,34,0,0,0); //负载总时间
//                        LcmPutSongStr(1,0,BuffCharDot,5,0);
//                        
//                        LcmSetSongBuff(119,33,0,0,0,0,0,0); //小时
//                        LcmPutSongStr(4,96,BuffCharDot,2,0);        
                        LcmPutFixDigit(4,8,sKYJ.sRunParam.nLoadTime/10000,4,0);
                        LcmPutFixDigit(4,40,sKYJ.sRunParam.nLoadTime%10000,4,0);
                        break;
                    case 5:
                        LcmPutFixDigit(4,40,sKYJ.nVoltage,4,0);
                        break;
                    default:
                        break;
                }
            break;
        case INTERFACE_USERPARAM:  //用户参数
            if(Key_Release(KEY_DOWN))
            {
                nParamIndex++;
                if(nParamIndex> 11) nParamIndex = 1;
                bRefreshInterface = 1;
            }
            else if(Key_Release(KEY_UP))
            {
                nParamIndex--;
                if(nParamIndex<1) nParamIndex = 11;
                bRefreshInterface = 1;
            }
            if(bRefreshInterface)
            {
                LcmClear(0x00);
                KYJ_ShowUserParam(nParamIndex);
            }             
            break;
        case INTERFACE_FACTORYPARAM:
            if(Key_Release(KEY_DOWN))
            {
                nParamIndex++;
                if(nParamIndex> 9) nParamIndex = 1;
                bRefreshInterface = 1;
            }
            else if(Key_Release(KEY_UP))
            {
                nParamIndex--;
                if(nParamIndex<1) nParamIndex = 9;
                bRefreshInterface = 1;
            }
            if(bRefreshInterface)
            {
                LcmClear(0x00);
                KYJ_ShowFactoryParam(nParamIndex);
            }              
            break;
        case INTERFACE_REGPARAM:
            if(Key_Release(KEY_DOWN))
            {
                nParamIndex++;
                if(nParamIndex> 6) nParamIndex = 1;
                bRefreshInterface = 1;
            }
            else if(Key_Release(KEY_UP))
            {
                nParamIndex--;
                if(nParamIndex<1) nParamIndex = 6;
                bRefreshInterface = 1;
            }
            if(bRefreshInterface)
            {
                LcmClear(0x00);
                KYJ_ShowRegParam(nParamIndex);
            }            
            break;
        case INTERFACE_PASSWORD:
            break;
        case INTERFACE_PARAM:
            tempValue[3] = nParamValue/1000;
            tempValue[2] = (nParamValue - tempValue[3]*1000)/100;
            tempValue[1] = (nParamValue - tempValue[3]*1000-tempValue[2]*100)/10;
            tempValue[0] = nParamValue%10;
            
            if(Key_Release(KEY_DOWN))
            {
                
                if(tempValue[nDigitIndex-1]==0) 
                    tempValue[nDigitIndex-1]=10;
                tempValue[nDigitIndex-1]--;
            }
            else if(Key_Release(KEY_UP))
            {
                tempValue[nDigitIndex-1]++;
                if(tempValue[nDigitIndex-1]>9)tempValue[nDigitIndex-1]=0;
            }
            else if(Key_Release(KEY_MOVE))
            {
                nDigitIndex++;
                if(nDigitIndex>4)nDigitIndex = 1;
            }
//            else if(Key_Release(KEY_OK))
//            {
//                KYJ_EnterParamValue(nMenuIndex,nParamIndex,nParamValue);
//            }
            nParamValue = tempValue[3]*1000 + tempValue[2]*100 + tempValue[1]*10 + tempValue[0];
            if(nMenuIndex == 2 && (nParamIndex==8 || nParamIndex == 9))
                LcmPutFloatDigit(4,40,nParamValue,4,nDigitIndex,2);
            else if(nMenuIndex == 2 && nParamIndex == 10) //启动方式
            {
                nDigitIndex = 1;
                if(nParamValue>0)nParamValue = 1;
                LcmPutFixDigit(4,40,nParamValue,1,nDigitIndex);
                if(nParamValue == 0)
                    LcmSetSongBuff(120,121,31,32,0,0,0,0); //星角启动
                else
                    LcmSetSongBuff(122,123,31,32,0,0,0,0); //直接启动
                LcmPutSongStr(4,60,BuffCharDot,4,0);                
            }
            else if(nMenuIndex == 3 && (nParamIndex==1 || nParamIndex==9))
                LcmPutFloatDigit(4,40,nParamValue,4,nDigitIndex,1);
            else if(nMenuIndex == 3 && (nParamIndex == 4 || nParamIndex == 5))
                LcmPutFloatDigit(4,40,nParamValue,4,nDigitIndex,2);
            else if(nMenuIndex == 4 && (nParamIndex == 1 || nParamIndex == 2|| nParamIndex ==3))
                LcmPutFloatDigit(0,87,nParamValue,4,nDigitIndex,1);
            else if(nMenuIndex == 4 && nParamIndex==4)
                LcmPutFixDigit(3,87,nParamValue,4,nDigitIndex);
            else if(nMenuIndex == 4 && nParamIndex==5)
                LcmPutFixDigit(0,87,nParamValue,4,nDigitIndex);
            else if(nMenuIndex == 4 && nParamIndex==6)
                LcmPutFixDigit(0,87,nParamValue,4,nDigitIndex);
            else
                LcmPutFixDigit(4,40,nParamValue,4,nDigitIndex);
            if(Key_Release(KEY_OK))
            {
                KYJ_EnterParamValue(nMenuIndex,nParamIndex,nParamValue);
            }
            
            break;
        default:
            break;
    }
    
    bRefreshInterface = 0;
    return;      
}

void KYJ_ShowUserParam(unsigned char nParamIndex)
{
                switch(nParamIndex)
                {
                    case 1:
                        LcmSetSongBuff(42,9,31,32,10,11,0,0); //风机启动温度
                        LcmPutSongStr(1,0,BuffCharDot,6,0);
                        nParamValue = sKYJ.sUserParam.nFanStartTemp;
                        LcmPutFixDigit(4,40,nParamValue,4,0);
                        LcmSetSongBuff(12,0,0,0,0,0,0,0); //℃
                        LcmPutSongStr(4,96,BuffCharDot,1,0);
                        break;
                    case 2:
                        LcmSetSongBuff(42,9,17,18,10,11,0,0); //风机停止温度
                        LcmPutSongStr(1,0,BuffCharDot,6,0);
                        nParamValue = sKYJ.sUserParam.nFanStopTemp;
                        LcmPutFixDigit(4,40,nParamValue,4,0);
                        LcmSetSongBuff(12,0,0,0,0,0,0,0); //℃
                        LcmPutSongStr(4,96,BuffCharDot,1,0);
                        
                        break;
                    case 3:
                        LcmSetSongBuff(29,9,37,33,33,34,0,0); //主机延时时间
                        LcmPutSongStr(1,0,BuffCharDot,6,0);
                        nParamValue = sKYJ.sUserParam.nMCUDelayTime;
                        LcmPutFixDigit(4,40,nParamValue,4,0);
                        LcmSetSongBuff(19,0,0,0,0,0,0,0); //秒
                        LcmPutSongStr(4,96,BuffCharDot,1,0);
                        
                        break;

                    case 4:
                        LcmSetSongBuff(35,36,37,33,33,34,0,0); //加载延时时间
                        LcmPutSongStr(1,0,BuffCharDot,6,0);
                        nParamValue = sKYJ.sUserParam.nLoadDelayTime;
                        LcmPutFixDigit(4,40,nParamValue,4,0);
                        LcmSetSongBuff(19,0,0,0,0,0,0,0); //秒
                        LcmPutSongStr(4,96,BuffCharDot,1,0);                        
                        break;
                    case 5:
                        LcmSetSongBuff(43,36,37,33,33,34,0,0); //空载延时时间
                        LcmPutSongStr(1,0,BuffCharDot,6,0);
                        nParamValue = sKYJ.sUserParam.nNoLoadDelayTime;
                        LcmPutFixDigit(4,40,nParamValue,4,0);
                        LcmSetSongBuff(19,0,0,0,0,0,0,0); //秒
                        LcmPutSongStr(4,96,BuffCharDot,1,0);                        
                        break;
                    case 6:
                        LcmSetSongBuff(17,9,37,33,33,34,0,0); //停机延时时间
                        LcmPutSongStr(1,0,BuffCharDot,6,0);
                        nParamValue = sKYJ.sUserParam.nStopDelayTime;
                        LcmPutFixDigit(4,40,nParamValue,4,0);
                        LcmSetSongBuff(19,0,0,0,0,0,0,0); //秒
                        LcmPutSongStr(4,96,BuffCharDot,1,0);                        
                        break;
                    case 7:
                        LcmSetSongBuff(44,31,37,33,33,34,0,0); //重启延时时间
                        LcmPutSongStr(1,0,BuffCharDot,6,0);
                        nParamValue = sKYJ.sUserParam.nRestartDelayTime;
                        LcmPutFixDigit(4,40,nParamValue,4,0);
                        LcmSetSongBuff(19,0,0,0,0,0,0,0); //秒
                        LcmPutSongStr(4,96,BuffCharDot,1,0);                        
                        break;
                    case 8:
                        LcmSetSongBuff(35,36,7,56,0,0,0,0); //加载压力
                        LcmPutSongStr(1,0,BuffCharDot,4,0);
                        nParamValue = sKYJ.sUserParam.nLoadPress;
                        //LcmPutFixDigit(4,40,nParamValue,4,0);
                        LcmPutFloatDigit(4,40,nParamValue,4,0,2);
                        //LcmSetSongBuff(19,0,0,0,0,0,0,0); //秒
                        //LcmPutSongStr(4,96,BuffCharDot,1,0); 
                        LcmPutStr(96,4,(unsigned char *)"MPa");
                        break;
                    case 9:
                         LcmSetSongBuff(57,36,7,56,0,0,0,0); //卸载压力
                        LcmPutSongStr(1,0,BuffCharDot,4,0);
                        nParamValue = sKYJ.sUserParam.nUnLoadPress;
                        //LcmPutFixDigit(4,40,nParamValue,4,0);
                        LcmPutFloatDigit(4,40,nParamValue,4,0,2);
                        //LcmSetSongBuff(19,0,0,0,0,0,0,0); //秒
                        //LcmPutSongStr(4,96,BuffCharDot,1,0);
                        LcmPutStr(96,4,(unsigned char *)"MPa");
                        break;
                    case 10:
                        LcmSetSongBuff(31,32,45,46,0,0,0,0);//启动方式
                        LcmPutSongStr(1,0,BuffCharDot,4,0);
                        nParamValue = sKYJ.sFactoryParam.nStartType;
                        LcmPutFixDigit(4,40,nParamValue,1,0);
                        if(nParamValue == 0)
                            LcmSetSongBuff(122,123,31,32,0,0,0,0); //星角启动
                        else
                            LcmSetSongBuff(120,121,31,32,0,0,0,0); //直接启动
                        LcmPutSongStr(4,60,BuffCharDot,4,0);
                        break;
                    case 11:
                        LcmSetSongBuff(120,121,37,33,33,34,0,0);//星角延时时间
                        LcmPutSongStr(1,0,BuffCharDot,6,0);
                        nParamValue = sKYJ.sUserParam.nSADelayTime;
                        LcmPutFixDigit(4,40,nParamValue,4,0);
                        LcmSetSongBuff(19,0,0,0,0,0,0,0); //秒
                        LcmPutSongStr(4,96,BuffCharDot,1,0);
                        break;
                    default:
                        break;
                }    
}

void KYJ_ShowFactoryParam(unsigned char nParamIndex)  //显示厂家参数
{
                switch(nParamIndex)
                {
                    case 1:
                        LcmSetSongBuff(29,9,77,78,79,80,0,0); //主机额定电流
                        LcmPutSongStr(1,0,BuffCharDot,6,0);
                        nParamValue = sKYJ.sFactoryParam.nMainMotorNormalCurrent;
                        //LcmPutFixDigit(4,40,nParamValue,4,0);
                        LcmPutFloatDigit(4,40,nParamValue,4,0,1);
//                        LcmSetSongBuff(12,0,0,0,0,0,0,0); //℃
//                        LcmPutSongStr(4,96,BuffCharDot,1,0);
                        LcmPutChar(96,4,'A');
                        break;
                    case 2:
                        LcmSetSongBuff(81,10,69,82,10,11,0,0); //排温预警温度
                        LcmPutSongStr(1,0,BuffCharDot,6,0);
                        nParamValue = sKYJ.sFactoryParam.nWarningTemp;
                        LcmPutFixDigit(4,40,nParamValue,4,0);
                        LcmSetSongBuff(12,0,0,0,0,0,0,0); //℃
                        LcmPutSongStr(4,96,BuffCharDot,1,0);
                        
                        break;
                    case 3:
                        LcmSetSongBuff(81,10,17,9,10,11,0,0); //排温停机温度
                        LcmPutSongStr(1,0,BuffCharDot,6,0);
                        nParamValue = sKYJ.sFactoryParam.nStopTemp;
                        LcmPutFixDigit(4,40,nParamValue,4,0);
                        LcmSetSongBuff(12,0,0,0,0,0,0,0); //℃
                        LcmPutSongStr(4,96,BuffCharDot,1,0);
                        
                        break;

                    case 4:
                        LcmSetSongBuff(83,84,17,9,7,56,0,0); //供气停机压力
                        LcmPutSongStr(1,0,BuffCharDot,6,0);
                        nParamValue = sKYJ.sFactoryParam.nStopPress;
                        //LcmPutFixDigit(4,40,nParamValue,4,0);
                        LcmPutFloatDigit(4,40,nParamValue,4,0,2);
//                        LcmSetSongBuff(12,0,0,0,0,0,0,0); //℃
//                        LcmPutSongStr(4,96,BuffCharDot,1,0);      
                        LcmPutStr(96,4,(unsigned char *)"MPa");
                        break;
                    case 5:
                        LcmSetSongBuff(57,36,7,56,85,86,0,0); //卸载压力高限
                        LcmPutSongStr(1,0,BuffCharDot,6,0);
                        nParamValue = sKYJ.sFactoryParam.nUnloadPressLimit;
                        //LcmPutFixDigit(4,40,nParamValue,4,0);
                        LcmPutFloatDigit(4,40,nParamValue,4,0,2);
//                        LcmSetSongBuff(12,0,0,0,0,0,0,0); //℃
//                        LcmPutSongStr(4,96,BuffCharDot,1,0);      
                        LcmPutStr(96,4,(unsigned char *)"MPa");                        
                        break;
                    case 6:
                        LcmSetSongBuff(20,21,87,33,34,0,0,0); //运行总时间
                        LcmPutSongStr(1,0,BuffCharDot,5,0);
                        nParamValue = sKYJ.sFactoryParam.nTotalRunTime;
                        LcmPutFixDigit(4,40,nParamValue,4,0);
                        LcmSetSongBuff(119,33,0,0,0,0,0,0); //秒
                        LcmPutSongStr(4,96,BuffCharDot,2,0);                       
                        break;
                    case 7:
                        LcmSetSongBuff(88,36,87,33,34,0,0,0); //负载总时间
                        LcmPutSongStr(1,0,BuffCharDot,5,0);
                        nParamValue = sKYJ.sFactoryParam.nTotalLoadTime;
                        LcmPutFixDigit(4,40,nParamValue,4,0);
                        LcmSetSongBuff(119,33,0,0,0,0,0,0); //秒
                        LcmPutSongStr(4,96,BuffCharDot,2,0);                         
                        break;
                    case 8:
                        LcmSetSongBuff(109,10,98,99,0,0,0,0); //低温保护
                        LcmPutSongStr(1,0,BuffCharDot,4,0);
                        nParamValue = sKYJ.sFactoryParam.nLowTempProtect;
                        LcmPutChar(32,4,'-');
                        LcmPutFixDigit(4,40,nParamValue,4,0);
                        LcmSetSongBuff(12,0,0,0,0,0,0,0); //℃
                        LcmPutSongStr(4,96,BuffCharDot,1,0); 
                        break;
                    case 9:
//                        LcmSetSongBuff(33,86,0,0,0,0,0,0); //时限
//                        LcmPutSongStr(1,0,BuffCharDot,2,0);
//                        nParamValue = sKYJ.sFactoryParam.nTimeLimit;
//                        LcmPutFixDigit(4,40,nParamValue,4,0);
//                        LcmSetSongBuff(119,33,0,0,0,0,0,0); //时
//                        LcmPutSongStr(4,96,BuffCharDot,2,0);
                        LcmSetSongBuff(79,80,93,94,95,11,0,0); //电流不平衡度
                        LcmPutSongStr(1,0,BuffCharDot,6,0);
                        nParamValue = sKYJ.sFactoryParam.nCurrentNotBalance;
                        LcmPutFloatDigit(4,40,nParamValue,4,0,1);
                        break;                        
                    default:
                        break;
                }    
}
void KYJ_ShowRegParam(unsigned char nParamIndex)
{
                switch(nParamIndex)
                {
                    case 1:
                        LcmSetSongBuff(113,114,79,80,0,0,0,0); //标准电流
                        LcmPutSongStr(0,0,BuffCharDot,4,0);
                        LcmPutStr(64,0,(unsigned char *)"A");
                        nParamValue = sKYJ.sRegParam.nStandCurrentA;
                        LcmPutFloatDigit(0,87,nParamValue,4,0,1);
                        
                        LcmSetSongBuff(115,23,0,0,0,0,0,0); //系数
                        LcmPutSongStr(3,0,BuffCharDot,2,0);
                        LcmPutStr(32,3,(unsigned char *)"A");
                        LcmPutFloatDigit(3,87,sKYJ.sRegParam.nStandCurrentAFactor,4,0,3);
                        
                        LcmSetSongBuff(116,21,79,80,0,0,0,0); //现行电流
                        LcmPutSongStr(6,0,BuffCharDot,4,0);
                        LcmPutStr(64,6,(unsigned char *)"A");
                        //nLongTemp = (unsigned long)sKYJ.sRunParam.nCurrentA*sKYJ.sRegParam.nStandCurrentAFactor;
                        //sKYJ.sRegParam.nCurrentA = nLongTemp/1000;
                        sKYJ.sRegParam.nCurrentA = sKYJ.nCurrentA;
                        LcmPutFloatDigit(6,87,sKYJ.sRegParam.nCurrentA,4,0,1);
                        
                        break;
                    case 2:
                        LcmSetSongBuff(113,114,79,80,0,0,0,0); //标准电流
                        LcmPutSongStr(0,0,BuffCharDot,4,0);
                        LcmPutStr(64,0,(unsigned char *)"B");
                        nParamValue = sKYJ.sRegParam.nStandCurrentB;
                        LcmPutFloatDigit(0,87,nParamValue,4,0,1);
                        
                        LcmSetSongBuff(115,23,0,0,0,0,0,0); //系数
                        LcmPutSongStr(3,0,BuffCharDot,2,0);
                        LcmPutStr(32,3,(unsigned char *)"B");
                        LcmPutFloatDigit(3,87,sKYJ.sRegParam.nStandCurrentBFactor,4,0,3);
                        
                        LcmSetSongBuff(116,21,79,80,0,0,0,0); //现行电流
                        LcmPutSongStr(6,0,BuffCharDot,4,0);
                        LcmPutStr(64,6,(unsigned char *)"B");
                        //nLongTemp = (unsigned long)sKYJ.sRunParam.nCurrentB*sKYJ.sRegParam.nStandCurrentBFactor;
                        //sKYJ.sRegParam.nCurrentB = nLongTemp/1000;
                        sKYJ.sRegParam.nCurrentB = sKYJ.nCurrentB;
                        LcmPutFloatDigit(6,87,sKYJ.sRegParam.nCurrentB,4,0,1);
                        
                        break;
                    case 3:  
                        LcmSetSongBuff(113,114,79,80,0,0,0,0); //标准电流
                        LcmPutSongStr(0,0,BuffCharDot,4,0);
                        LcmPutStr(64,0,(unsigned char *)"C");
                        nParamValue = sKYJ.sRegParam.nStandCurrentC;
                        LcmPutFloatDigit(0,87,nParamValue,4,0,1);
                        
                        LcmSetSongBuff(115,23,0,0,0,0,0,0); //系数
                        LcmPutSongStr(3,0,BuffCharDot,2,0);
                        LcmPutStr(32,3,(unsigned char *)"C");
                        LcmPutFloatDigit(3,87,sKYJ.sRegParam.nStandCurrentCFactor,4,0,3);
                        
                        LcmSetSongBuff(116,21,79,80,0,0,0,0); //现行电流
                        LcmPutSongStr(6,0,BuffCharDot,4,0);
                        LcmPutStr(64,6,(unsigned char *)"C");
                        //nLongTemp = (unsigned long)sKYJ.sRunParam.nCurrentC*sKYJ.sRegParam.nStandCurrentCFactor;
                        //sKYJ.sRegParam.nCurrentC = nLongTemp/1000;
                        sKYJ.sRegParam.nCurrentC = sKYJ.nCurrentC;
                        LcmPutFloatDigit(6,87,sKYJ.sRegParam.nCurrentC,4,0,1);
                        break;

                    case 4: //调整零点
                        LcmSetSongBuff(113,114,10,11,0,0,0,0); //标准温度
                        LcmPutSongStr(0,0,BuffCharDot,4,0);
                        //LcmPutFixDigit(0,87,sKYJ.nTemperature,4,0);
                        LcmPutFixDigit(0,87,0,4,0);
                        
                        LcmSetSongBuff(117,118,0,0,0,0,0,0); //零点
                        LcmPutSongStr(3,0,BuffCharDot,2,0);
                        nParamValue = sKYJ.sRegParam.nZeroBias;
                        LcmPutFixDigit(3,87,sKYJ.sRegParam.nZeroBias,4,0);
                        
                        LcmSetSongBuff(116,21,10,11,0,0,0,0); //现行温度
                        LcmPutSongStr(6,0,BuffCharDot,4,0);
                        //sKYJ.sRegParam.nTemp = sKYJ.sRunParam.nTemperature;// - sKYJ.sRegParam.nZeroBias;
                        sKYJ.sRegParam.nTemp = sKYJ.nTemperature;
                        LcmPutFixDigit(6,87,sKYJ.sRegParam.nTemp,4,0);
                                            
                        break;
                    case 5: //调整温度系数
                        LcmSetSongBuff(113,114,10,11,0,0,0,0); //标准温度
                        LcmPutSongStr(0,0,BuffCharDot,4,0);
                        nParamValue = sKYJ.sRegParam.nStandTemp;
                        LcmPutFixDigit(0,87,nParamValue,4,0);
                        
                        LcmSetSongBuff(115,23,0,0,0,0,0,0); //系数
                        LcmPutSongStr(3,0,BuffCharDot,2,0);
                        LcmPutFloatDigit(3,87,sKYJ.sRegParam.nStandTempFactor,4,0,3);
                        
                        LcmSetSongBuff(116,21,10,11,0,0,0,0); //现行温度
                        LcmPutSongStr(6,0,BuffCharDot,4,0);
//                        nLongTemp = sKYJ.sRunParam.nTemperature - sKYJ.sRegParam.nZeroBias;
//                        nLongTemp = nLongTemp * sKYJ.sRegParam.nStandTempFactor/1000;
                        sKYJ.sRegParam.nTemp = sKYJ.nTemperature;
                        LcmPutFixDigit(6,87,sKYJ.sRegParam.nTemp,4,0);
                                            
                        break;
                    case 6: //调整电压系数
                        LcmSetSongBuff(113,114,79,7,0,0,0,0); //标准电压
                        LcmPutSongStr(0,0,BuffCharDot,4,0);
                        nParamValue = sKYJ.sRegParam.nStandVoltage;
                        LcmPutFixDigit(0,87,nParamValue,4,0);
                        
                        LcmSetSongBuff(115,23,0,0,0,0,0,0); //系数
                        LcmPutSongStr(3,0,BuffCharDot,2,0);
                        LcmPutFloatDigit(3,87,sKYJ.sRegParam.nStandVoltageFactor,4,0,3);
                        
                        LcmSetSongBuff(116,21,79,7,0,0,0,0); //现行电压
                        LcmPutSongStr(6,0,BuffCharDot,4,0);
                        sKYJ.sRegParam.nVoltage = sKYJ.nVoltage;
                        LcmPutFixDigit(6,87,sKYJ.sRegParam.nVoltage,4,0);
                                            
                        break;
                    default:
                        break;
                }    
}
void KYJ_EnterParamValue(unsigned char nMI,unsigned char nPI, int nValue)
{
    
    if(nMI == 2)//用户参数
    {
        switch(nPI)
        {
            case 1:
               sKYJ.sUserParam.nFanStartTemp = nValue;
                break;
            case 2:
                sKYJ.sUserParam.nFanStopTemp  = nValue;
                break;
            case 3:
                sKYJ.sUserParam.nMCUDelayTime = nValue;
                break;
            case 4:
                sKYJ.sUserParam.nLoadDelayTime = nValue;
                break;
            case 5:
                sKYJ.sUserParam.nNoLoadDelayTime = nValue;
                break;
            case 6:
                sKYJ.sUserParam.nStopDelayTime  = nValue;
                break;
            case 7:
                sKYJ.sUserParam.nRestartDelayTime = nValue;
                break;
            case 8:
                sKYJ.sUserParam.nLoadPress = nValue;
                break;
            case 9:
                sKYJ.sUserParam.nUnLoadPress = nValue;
                break;
            case 10: //保存启动方式，0直接启动，非0则为星角启动
                (nValue == 0) ? sKYJ.sFactoryParam.nStartType = 0 : sKYJ.sFactoryParam.nStartType=1;
                break;
            case 11:
                sKYJ.sUserParam.nSADelayTime = nValue;
                break;
            default:
                break;            
        }
        KYJ_SwitchToInterface(INTERFACE_USERPARAM);
        KYJ_ShowUserParam(nPI);
    }
    else if(nMI == 3) //厂家参数
    {
                switch(nPI)
                {
                    case 1:
                        sKYJ.sFactoryParam.nMainMotorNormalCurrent = nValue;
                        break;
                    case 2:
                        sKYJ.sFactoryParam.nWarningTemp=nValue;
                        break;
                    case 3:
                        sKYJ.sFactoryParam.nStopTemp = nValue;
                        break;

                    case 4:
                        sKYJ.sFactoryParam.nStopPress = nValue;
                        break;
                    case 5:
                        sKYJ.sFactoryParam.nUnloadPressLimit=nValue;
                        break;
                    case 6:
                        sKYJ.sFactoryParam.nTotalRunTime = nValue;
                        break;
                    case 7:
                        sKYJ.sFactoryParam.nTotalLoadTime = nValue;
                        break;
                    case 8:
                        sKYJ.sFactoryParam.nLowTempProtect = nValue;
                        break;
                    case 9:
                        //sKYJ.sFactoryParam.nTimeLimit = nValue;
                        sKYJ.sFactoryParam.nCurrentNotBalance = nValue;
                        break;                        
                    default:
                        break;
                }        
        KYJ_SwitchToInterface(INTERFACE_FACTORYPARAM);
        KYJ_ShowFactoryParam(nPI);
    }
    else if(nMI == 4) //调整参数
    {
        switch(nPI)
        {
            case 1:
                sKYJ.sRegParam.nStandCurrentA = nParamValue;
                nLongTemp = (unsigned long)sKYJ.sRegParam.nStandCurrentA * 1000;
                sKYJ.sRegParam.nStandCurrentAFactor = nLongTemp/sKYJ.sRunParam.nCurrentA;
                
                break;
            case 2:
                sKYJ.sRegParam.nStandCurrentB = nParamValue;
                nLongTemp = (unsigned long)sKYJ.sRegParam.nStandCurrentB * 1000;
                sKYJ.sRegParam.nStandCurrentBFactor = nLongTemp/sKYJ.sRunParam.nCurrentB;
                break;
            case 3:
                sKYJ.sRegParam.nStandCurrentC = nParamValue;
                nLongTemp = (unsigned long)sKYJ.sRegParam.nStandCurrentC * 1000;
                sKYJ.sRegParam.nStandCurrentCFactor = nLongTemp/sKYJ.sRunParam.nCurrentC;
                break;
            case 4:
                sKYJ.sRegParam.nZeroBias = nParamValue;
                break;
            case 5:
                sKYJ.sRegParam.nStandTemp = nParamValue;
                sKYJ.sRegParam.nStandTempFactor = (long)nParamValue *1000/(sKYJ.sRunParam.nTemperature - sKYJ.sRegParam.nZeroBias) ;
            case 6:
                sKYJ.sRegParam.nStandVoltage = nParamValue;
                sKYJ.sRegParam.nStandVoltageFactor = (long)nParamValue * 1000/sKYJ.sRunParam.nVoltage;
            default:
               ;
        }
        KYJ_SwitchToInterface(INTERFACE_REGPARAM);
        KYJ_ShowRegParam(nParamIndex);
    }
    else if(nMI == 5) //密码设置
    {
        KYJ_SwitchToInterface(INTERFACE_PASSWORD);
    }
    EEPROM_Save_Param(PARAM_STORE_BYTES);
}

void KYJ_UpdateData(void)  //更新压力、温度、电流
{

    
    //更新压力
    //nValue = (int)(adc_Get_Value(CH_Pressure)*4*0.1*100/220.0-40);
    nValue = adc_Get_Value(CH_Pressure);
    nValue = adc_Get_Value(CH_Temperature);
    nLongTemp = (long) nValue * nADVref * 100;
    nValue = nLongTemp /(220*1024) - 40;  //压力计算公式：(sample/1024 * nADVref (mV) / 220 欧  - 4mA) * 0.1MPa/mA *100 倍数
    sKYJ.sRunParam.nPressure = nValue;  //压力=nValue * 0.01MPa，如果是负值，很可能是没有接压力传感器，连4mA的电流都没有。
//    if(nValue > 0)
//        sKYJ.nPressure = sKYJ.sRunParam.nPressure;  //压力显示值
    //更新温度
    nValue = adc_Get_Value(CH_Temperature);

    nLongTemp = (long)nValue*5000*100;
    nValue = nLongTemp/(21000-nValue);  //得到电阻值，单位：0.01欧
    nLongTemp = (long)(nValue - 10000) * 150 * 10 / 5700; 
    sKYJ.sRunParam.nTemperature = nLongTemp; //计算得到温度值，0.1度
    sKYJ.nTemperature = sKYJ.sRunParam.nTemperature/10;   //显示温度值

    //更新电源电压，RB3
    nValue = adc_Get_Value(CH_Power);
   
    nLongTemp = (long)nValue * nADVref * 6;  //采样电阻分压比5.5454：1，变压器变比11：1
    sKYJ.sRunParam.nVoltage = nLongTemp /102400; //假设电源电压到AD前的电压比是100：1
    
    KYJ_CalcRegValue();
}

void KYJ_SampleCurrent(void)  //在定时中断中1ms调用一次
{
    nCurrentSampleCount++;
    if(nCurrentSampleCount<20)  //1-19次采样A相
    {
        nCurrent+=adc_Get_Value(CH_CurrentA);
        //nCurrent+=1000;
    }
    else if(nCurrentSampleCount == 20) //第20次采样后，计算A相平均采样值
    {
        nCurrent+=adc_Get_Value(CH_CurrentA);
        //nCurrent+=1000;
        nLongTemp = nCurrent * nADVref * CURRENT_TRANS_RATIO;
        sKYJ.sRunParam.nCurrentA = nLongTemp/(1024*100*CURRENT_SAMPLE_RES);   //计算A相的平均值，因为半波检流，所以除以20在乘以2；

         nCurrent=0;
    }
    else if(nCurrentSampleCount < 40) //第21-39次采样B相
    {
        nCurrent+=adc_Get_Value(CH_CurrentB);
    }
    else if(nCurrentSampleCount == 40) //第40次采样B相后，计算B相采样平均值
    {
        nCurrent+=adc_Get_Value(CH_CurrentB);
        nLongTemp = nCurrent * nADVref * CURRENT_TRANS_RATIO;
        sKYJ.sRunParam.nCurrentB = nLongTemp/(1024*100*CURRENT_SAMPLE_RES); 
        
        nCurrent=0;
    }
    else if(nCurrentSampleCount <60) //第41-59次采样C相
    {
        nCurrent+=adc_Get_Value(CH_CurrentC);
    }
    else if(nCurrentSampleCount == 60)  //第60次采样C相后，计算C相平均采样值
    {
        nCurrent+=adc_Get_Value(CH_CurrentC);
        nLongTemp = nCurrent * nADVref * CURRENT_TRANS_RATIO;
        sKYJ.sRunParam.nCurrentC = nLongTemp/(1024*100*CURRENT_SAMPLE_RES); 
        
        nCurrent=0;
        //nCurrentSampleCount = 0;
    }
//    else if(nCurrentSampleCount <70)
//    {
//    
//    }
    else if(nCurrentSampleCount == 70)
    {
        //更新压力

//        nValue = adc_Get_Value(CH_Pressure);
//        nLongTemp = (long) nValue * nADVref * 100;
        
        nValue = adc_Get_Value(CH_Temperature)*1.5;
        nLongTemp = (long) nValue * nADVref;
        
        nValue = nLongTemp /(220*1024) - 40;  //压力计算公式：(sample/1024 * nADVref (mV) / 220 欧  - 4mA) * 0.1MPa/mA *100 倍数
        sKYJ.sRunParam.nPressure = nValue;  //压力=nValue * 0.01MPa，如果是负值，很可能是没有接压力传感器，连4mA的电流都没有。    
    }
//    else if(nCurrentSampleCount <80)
//    {
//    
//    }
    else if(nCurrentSampleCount == 80)
    {
         //更新温度
        nValue = adc_Get_Value(CH_Temperature);

        nLongTemp = (long)nValue*5000*100;
        nValue = nLongTemp/(21000-nValue);  //得到电阻值，单位：0.01欧
        nLongTemp = (long)(nValue - 10000) * 150 * 10 / 5700; 
        sKYJ.sRunParam.nTemperature = nLongTemp; //计算得到温度值，0.1度
        sKYJ.nTemperature = sKYJ.sRunParam.nTemperature/10;   //显示温度值   
    }
//    else if(nCurrentSampleCount <90)
//    {
//    
//    }
    else if(nCurrentSampleCount == 90)
    {
        //更新电源电压，RB3
        nValue = adc_Get_Value(CH_Power);

        nLongTemp = (long)nValue * nADVref * 6;  //采样电阻分压比5.5454：1，变压器变比11：1
        sKYJ.sRunParam.nVoltage = nLongTemp /102400; //假设电源电压到AD前的电压比是100：1    
    }   
    
    if(nCurrentSampleCount > 100)
    {
            KYJ_CalcRegValue();
        nCurrentSampleCount = 0;
    }   
}

void KYJ_CalcRegValue(void)  //根据调整参数计算调整后的传感器数值
{
    //计算压力值
    if(sKYJ.sRunParam.nPressure>0)
        sKYJ.nPressure = sKYJ.sRunParam.nPressure;
//    sKYJ.nPressure = 50; //调试用
    //计算温度值
    sKYJ.nTemperature = ((long)sKYJ.sRunParam.nTemperature/10-sKYJ.sRegParam.nZeroBias)* sKYJ.sRegParam.nStandTempFactor/1000;

    //计算电源电压值
    sKYJ.nVoltage = (unsigned long)sKYJ.sRunParam.nVoltage * sKYJ.sRegParam.nStandVoltageFactor / 1000;

    //计算电流值
    sKYJ.nCurrentA = (unsigned long)sKYJ.sRegParam.nStandCurrentAFactor*sKYJ.sRunParam.nCurrentA/1000;
    sKYJ.nCurrentB = (unsigned long)sKYJ.sRegParam.nStandCurrentBFactor*sKYJ.sRunParam.nCurrentB/1000;
    sKYJ.nCurrentC = (unsigned long)sKYJ.sRegParam.nStandCurrentCFactor*sKYJ.sRunParam.nCurrentC/1000;
}