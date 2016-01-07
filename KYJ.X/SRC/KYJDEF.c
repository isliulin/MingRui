#include "KYJDEF.h"
#include "LCD_LIXIAN.h"
#include "key.h"
#include<pic16f1939.h>
#include "adc.h"
#include "EEPROM.h"

struct KYJ_s sKYJ;
unsigned char nRefreshInterface;
unsigned char nMenuIndex;  //当前菜单序号  1-运行参数；2-用户参数；3-厂家参数；4-注册参数；5-用户密码
unsigned char nParamIndex;   //当前参数序号
unsigned char nDigitIndex; //当前数位
int nParamValue;
void KYJ_Param_Default(void)
{
    sKYJ.sUserParam.nFanStartTemp = 80; //风机启温度
    sKYJ.sUserParam.nFanStopTemp = 70;//风机停温度
    sKYJ.sUserParam.nMCUDelayTime = 8; //主机延时时间，单位：秒
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
    sKYJ.sFactoryParam.nLowTempProtect = -5; //低温保护
    sKYJ.sFactoryParam.nTimeLimit = 0;//时限
    sKYJ.sFactoryParam.nWarningOverTime = 10;//预警过久停机
    sKYJ.sFactoryParam.nCommParam = 0;//通信预置参数
    sKYJ.sFactoryParam.nParam1 = 0;//参数1
    
    
    sKYJ.sRegParam.nStandCurrentA = 0;//标准电流
    sKYJ.sRegParam.nStandCurrentAFactor = 1;//系数
    sKYJ.sRegParam.nCurrentA = 0;//现行电流
    sKYJ.sRegParam.nStandCurrentB = 0;//标准电流
    sKYJ.sRegParam.nStandCurrentBFactor = 1;//系数
    sKYJ.sRegParam.nCurrentB = 0;//现行电流
    sKYJ.sRegParam.nStandCurrentC = 0; //标准电流
    sKYJ.sRegParam.nStandCurrentCFactor = 1;//系数
    sKYJ.sRegParam.nCurrentC = 0;//现行电流
    sKYJ.sRegParam.nStandTemp = 25;//标准温度
    sKYJ.sRegParam.nStandTempFactor = 0;//系数
    sKYJ.sRegParam.nZeroBias = 0;//零点
    sKYJ.sRegParam.nTemp = 0;//现行温度
    sKYJ.sRegParam.nCurrMode = 0;//CURR MODE

    sKYJ.sPassword.nOpPass = 0000; //操作密码
    sKYJ.sPassword.nUserPass = 1111; //用户密码
    sKYJ.sPassword.nSalePass = 2222; //销售密码
    sKYJ.sPassword.nFactoryPass = 3333; //厂家密码
    sKYJ.sPassword.nRegPass = 4444;//校准密码
    sKYJ.sPassword.nSuperPass = 5555;//厂家超级密码
}

unsigned char KYJ_CheckStatus(unsigned char nStatus)
{
    unsigned char nRet;
    nRet = 0;
    switch(nStatus)
    {
        case STATUS_POWERSTOP:
            break;
        case STATUS_KEYSTOP:
            if(sKYJ.nStatus != STATUS_KEYSTOP && Key_Press(KEY_STOP)) nRet=1;
            break;
        case STATUS_DELAYSTOP:
            if(sKYJ.nStatus == STATUS_UNLOAD && sKYJ.nStatusTimeElapse > sKYJ.sUserParam.nNoLoadDelayTime) nRet = 1;
            break;
        case STATUS_FAULTSTOP:
            break;
        case STATUS_STARTUP:
            if(Key_Release(KEY_START) && sKYJ.nStatusTimeElapse>sKYJ.sUserParam.nRestartDelayTime) nRet = 1;
            if(sKYJ.nStatus == STATUS_DELAYSTOP && sKYJ.sRunParam.fPressure < sKYJ.sUserParam.nSlaveLoadPress) nRet=1;
            break;
        case STATUS_LOAD:
            if(sKYJ.nStatus & (STATUS_STARTUP | STATUS_UNLOAD))
            {
                if((sKYJ.nStatusTimeElapse > sKYJ.sUserParam.nLoadDelayTime) && (sKYJ.sRunParam.fPressure < sKYJ.sUserParam.nSlaveLoadPress)) nRet = 1;           
            }
            break;
        case STATUS_UNLOAD:
            if(sKYJ.nStatus == STATUS_LOAD && sKYJ.sRunParam.fPressure > sKYJ.sUserParam.nSlaveUnLoadPress) nRet = 1;
            if(sKYJ.nStatus == STATUS_STARTUP)
            {
                if((sKYJ.nStatusTimeElapse > sKYJ.sUserParam.nLoadDelayTime) && (sKYJ.sRunParam.fPressure >= sKYJ.sUserParam.nSlaveLoadPress)) nRet = 1;           
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
        case STATUS_POWERSTOP:
            //break;
        case STATUS_KEYSTOP:
            //break;
        case STATUS_DELAYSTOP:
            //break;
        case STATUS_FAULTSTOP:
            LOAD_SW_OFF;
            //MOTOR_SW_OFF;
            break;
        case STATUS_STARTUP:
            MOTOR_SW_ON;
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
            if(sKYJ.nStatusTimeElapse > sKYJ.sUserParam.nStopDelayTime) MOTOR_SW_OFF;
            break;
        case STATUS_STARTUP:
            break;
        case STATUS_LOAD:
            break;
        case STATUS_UNLOAD:
            break;
        case STATUS_MANUAL:
            break;
        default:
            break;
    }
    return;      
}

unsigned char KYJ_CheckInterface(unsigned char nInterface)
{
    unsigned char nRet;
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
            if((sKYJ.nInterface == INTERFACE_RUNPARAM || sKYJ.nInterface==INTERFACE_USERPARAM || sKYJ.nInterface==INTERFACE_FACTORYPARAM|| sKYJ.nInterface==INTERFACE_REGPARAM|| sKYJ.nInterface==INTERFACE_PASSWORD) && Key_Release(KEY_RESET)) nRet = 1;
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
                
                LcmSetSongBuff(10,11,0,0,0,0,0,0); //温度
                LcmPutSongStr(1,0,BuffCharDot,2,0);
                
                LcmSetSongBuff(12,0,0,0,0,0,0,0); //℃
                LcmPutSongStr(1,72,BuffCharDot,1,0);
                
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
    nRefreshInterface = 1;

    return;      
}

void KYJ_ExecuteInterface(void)
{
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
//                    LcmSetSongBuff(13,14,15,17,18,0,0,0);//设备已停止
//                    break;
                case STATUS_FAULTSTOP:
                    LcmSetSongBuff(13,14,15,17,18,0,0,0);//设备已停止
                    break;
                case STATUS_STARTUP:
                    LcmSetSongBuff(13,14,15,31,32,0,0,0);//设备已启动
                    break;
                case STATUS_LOAD:
                    LcmSetSongBuff(13,14,15,35,36,0,0,0);//设备已加载
                    break;
                case STATUS_UNLOAD:
                    LcmSetSongBuff(13,14,15,57,36,0,0,0);//设备已卸载
                    break;
                case STATUS_MANUAL:
                    break;
                default:
                    break;
            
            }
            LcmPutSongStr(4,0,BuffCharDot,5,0);
            
            //显示流逝的时间
            LcmPutFixDigit(4,79,sKYJ.nStatusTimeElapse,4,0);
            //显示温度
            //LcmPutFixDigit(1,31,sKYJ.sRunParam.fTemperature,4,0);
            LcmPutFloatDigit(1,31,sKYJ.sRunParam.fTemperature,3,0,1);
            //显示压力
            //LcmPutFixDigit(1,79,sKYJ.sRunParam.fPressure,4,0);
            LcmPutFloatDigit(1,87,sKYJ.sRunParam.fPressure,4,0,2);
            break;
        case INTERFACE_MENU:
            if(Key_Release(KEY_DOWN))
            {
                nMenuIndex++;
                if(nMenuIndex> 5) nMenuIndex = 1;
                nRefreshInterface = 1;
            }
            else if(Key_Release(KEY_UP))
            {
                nMenuIndex--;
                if(nMenuIndex<1) nMenuIndex = 5;
                nRefreshInterface = 1;
            }
            if(nRefreshInterface)
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
                if(nParamIndex> 4) nParamIndex = 1;
                nRefreshInterface = 1;
            }
            else if(Key_Release(KEY_UP))
            {
                nParamIndex--;
                if(nParamIndex<1) nParamIndex = 4;
                nRefreshInterface = 1;
            }
            if(nRefreshInterface)
            {
                LcmClear(0x00);
                switch(nParamIndex)
                {
                    case 1:
                        LcmSetSongBuff(29,9,79,80,0,0,0,0); //主机电流
                        LcmPutSongStr(0,0,BuffCharDot,4,0);
                        LcmPutStr(0,2,"(A):");
                        LcmPutStr(0,4,"(B):");
                        LcmPutStr(0,6,"(C):");
                        break;
                    case 2:
                        LcmSetSongBuff(42,9,79,80,0,0,0,0); //风机电流
                        LcmPutSongStr(1,0,BuffCharDot,4,0);
                        LcmPutStr(96,4,"A");
                        
                        break;
                    case 3:
                        LcmSetSongBuff(20,21,87,33,34,0,0,0); //运行总时间
                        LcmPutSongStr(1,0,BuffCharDot,5,0);
                        
                        LcmSetSongBuff(19,0,0,0,0,0,0,0); //秒
                        LcmPutSongStr(4,96,BuffCharDot,1,0);
                        
                        break;

                    case 4:
                        
                        LcmSetSongBuff(88,36,87,33,34,0,0,0); //负载总时间
                        LcmPutSongStr(1,0,BuffCharDot,5,0);
                        
                        LcmSetSongBuff(19,0,0,0,0,0,0,0); //秒
                        LcmPutSongStr(4,96,BuffCharDot,1,0);                        
                        break;
                    default:
                        break;
                }
            }            
            break;
        case INTERFACE_USERPARAM:  //用户参数
            if(Key_Release(KEY_DOWN))
            {
                nParamIndex++;
                if(nParamIndex> 9) nParamIndex = 1;
                nRefreshInterface = 1;
            }
            else if(Key_Release(KEY_UP))
            {
                nParamIndex--;
                if(nParamIndex<1) nParamIndex = 9;
                nRefreshInterface = 1;
            }
            if(nRefreshInterface)
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
                nRefreshInterface = 1;
            }
            else if(Key_Release(KEY_UP))
            {
                nParamIndex--;
                if(nParamIndex<1) nParamIndex = 9;
                nRefreshInterface = 1;
            }
            if(nRefreshInterface)
            {
                LcmClear(0x00);
                KYJ_ShowFactoryParam(nParamIndex);
            }              
            break;
        case INTERFACE_REGPARAM:
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
            else if(Key_Release(KEY_OK))
            {
                KYJ_EnterParamValue(nMenuIndex,nParamIndex,nParamValue);
            }
            nParamValue = tempValue[3]*1000 + tempValue[2]*100 + tempValue[1]*10 + tempValue[0];
            LcmPutFixDigit(4,56,nParamValue,4,nDigitIndex);
            
            break;
        default:
            break;
    }
    
    nRefreshInterface = 0;
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
                        LcmPutFixDigit(4,56,nParamValue,4,0);
                        LcmSetSongBuff(12,0,0,0,0,0,0,0); //℃
                        LcmPutSongStr(4,96,BuffCharDot,1,0);
                        break;
                    case 2:
                        LcmSetSongBuff(42,9,17,18,10,11,0,0); //风机停止温度
                        LcmPutSongStr(1,0,BuffCharDot,6,0);
                        nParamValue = sKYJ.sUserParam.nFanStopTemp;
                        LcmPutFixDigit(4,56,nParamValue,4,0);
                        LcmSetSongBuff(12,0,0,0,0,0,0,0); //℃
                        LcmPutSongStr(4,96,BuffCharDot,1,0);
                        
                        break;
                    case 3:
                        LcmSetSongBuff(29,9,37,33,33,34,0,0); //主机延时时间
                        LcmPutSongStr(1,0,BuffCharDot,6,0);
                        nParamValue = sKYJ.sUserParam.nMCUDelayTime;
                        LcmPutFixDigit(4,56,nParamValue,4,0);
                        LcmSetSongBuff(19,0,0,0,0,0,0,0); //秒
                        LcmPutSongStr(4,96,BuffCharDot,1,0);
                        
                        break;

                    case 4:
                        LcmSetSongBuff(35,36,37,33,33,34,0,0); //加载延时时间
                        LcmPutSongStr(1,0,BuffCharDot,6,0);
                        nParamValue = sKYJ.sUserParam.nLoadDelayTime;
                        LcmPutFixDigit(4,56,nParamValue,4,0);
                        LcmSetSongBuff(19,0,0,0,0,0,0,0); //秒
                        LcmPutSongStr(4,96,BuffCharDot,1,0);                        
                        break;
                    case 5:
                        LcmSetSongBuff(43,36,37,33,33,34,0,0); //空载延时时间
                        LcmPutSongStr(1,0,BuffCharDot,6,0);
                        nParamValue = sKYJ.sUserParam.nNoLoadDelayTime;
                        LcmPutFixDigit(4,56,nParamValue,4,0);
                        LcmSetSongBuff(19,0,0,0,0,0,0,0); //秒
                        LcmPutSongStr(4,96,BuffCharDot,1,0);                        
                        break;
                    case 6:
                        LcmSetSongBuff(17,9,37,33,33,34,0,0); //停机延时时间
                        LcmPutSongStr(1,0,BuffCharDot,6,0);
                        nParamValue = sKYJ.sUserParam.nStopDelayTime;
                        LcmPutFixDigit(4,56,nParamValue,4,0);
                        LcmSetSongBuff(19,0,0,0,0,0,0,0); //秒
                        LcmPutSongStr(4,96,BuffCharDot,1,0);                        
                        break;
                    case 7:
                        LcmSetSongBuff(44,31,37,33,33,34,0,0); //重启延时时间
                        LcmPutSongStr(1,0,BuffCharDot,6,0);
                        nParamValue = sKYJ.sUserParam.nRestartDelayTime;
                        LcmPutFixDigit(4,56,nParamValue,4,0);
                        LcmSetSongBuff(19,0,0,0,0,0,0,0); //秒
                        LcmPutSongStr(4,96,BuffCharDot,1,0);                        
                        break;
                    case 8:
                        LcmSetSongBuff(35,36,7,56,0,0,0,0); //加载压力
                        LcmPutSongStr(1,0,BuffCharDot,4,0);
                        nParamValue = sKYJ.sUserParam.nSlaveLoadPress;
                        //LcmPutFixDigit(4,56,nParamValue,4,0);
                        LcmPutFloatDigit(4,56,nParamValue,4,0,2);
                        //LcmSetSongBuff(19,0,0,0,0,0,0,0); //秒
                        //LcmPutSongStr(4,96,BuffCharDot,1,0); 
                        LcmPutStr(96,4,"MPa");
                        break;
                    case 9:
                         LcmSetSongBuff(57,36,7,56,0,0,0,0); //卸载压力
                        LcmPutSongStr(1,0,BuffCharDot,4,0);
                        nParamValue = sKYJ.sUserParam.nSlaveUnLoadPress;
                        //LcmPutFixDigit(4,56,nParamValue,4,0);
                        LcmPutFloatDigit(4,56,nParamValue,4,0,2);
                        //LcmSetSongBuff(19,0,0,0,0,0,0,0); //秒
                        //LcmPutSongStr(4,96,BuffCharDot,1,0);
                        LcmPutStr(96,4,"MPa");
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
                        //LcmPutFixDigit(4,56,nParamValue,4,0);
                        LcmPutFloatDigit(4,56,nParamValue,4,0,1);
//                        LcmSetSongBuff(12,0,0,0,0,0,0,0); //℃
//                        LcmPutSongStr(4,96,BuffCharDot,1,0);
                        LcmPutChar(96,4,'A');
                        break;
                    case 2:
                        LcmSetSongBuff(81,10,69,82,10,11,0,0); //排温预警温度
                        LcmPutSongStr(1,0,BuffCharDot,6,0);
                        nParamValue = sKYJ.sFactoryParam.nWarningTemp;
                        LcmPutFixDigit(4,56,nParamValue,4,0);
                        LcmSetSongBuff(12,0,0,0,0,0,0,0); //℃
                        LcmPutSongStr(4,96,BuffCharDot,1,0);
                        
                        break;
                    case 3:
                        LcmSetSongBuff(81,10,17,9,10,11,0,0); //排温停机温度
                        LcmPutSongStr(1,0,BuffCharDot,6,0);
                        nParamValue = sKYJ.sFactoryParam.nWarningTemp;
                        LcmPutFixDigit(4,56,nParamValue,4,0);
                        LcmSetSongBuff(12,0,0,0,0,0,0,0); //℃
                        LcmPutSongStr(4,96,BuffCharDot,1,0);
                        
                        break;

                    case 4:
                        LcmSetSongBuff(83,84,17,9,7,56,0,0); //供气停机压力
                        LcmPutSongStr(1,0,BuffCharDot,6,0);
                        nParamValue = sKYJ.sFactoryParam.nStopPress;
                        //LcmPutFixDigit(4,56,nParamValue,4,0);
                        LcmPutFloatDigit(4,56,nParamValue,4,0,2);
//                        LcmSetSongBuff(12,0,0,0,0,0,0,0); //℃
//                        LcmPutSongStr(4,96,BuffCharDot,1,0);      
                        LcmPutStr(96,4,"MPa");
                        break;
                    case 5:
                        LcmSetSongBuff(57,36,7,56,85,86,0,0); //卸载压力高限
                        LcmPutSongStr(1,0,BuffCharDot,6,0);
                        nParamValue = sKYJ.sFactoryParam.nUnloadPressLimit;
                        //LcmPutFixDigit(4,56,nParamValue,4,0);
                        LcmPutFloatDigit(4,56,nParamValue,4,0,2);
//                        LcmSetSongBuff(12,0,0,0,0,0,0,0); //℃
//                        LcmPutSongStr(4,96,BuffCharDot,1,0);      
                        LcmPutStr(96,4,"MPa");                        
                        break;
                    case 6:
                        LcmSetSongBuff(20,21,87,33,34,0,0,0); //运行总时间
                        LcmPutSongStr(1,0,BuffCharDot,5,0);
                        nParamValue = sKYJ.sFactoryParam.nTotalRunTime;
                        LcmPutFixDigit(4,56,nParamValue,4,0);
                        LcmSetSongBuff(119,33,0,0,0,0,0,0); //秒
                        LcmPutSongStr(4,96,BuffCharDot,2,0);                       
                        break;
                    case 7:
                        LcmSetSongBuff(88,36,87,33,34,0,0,0); //负载总时间
                        LcmPutSongStr(1,0,BuffCharDot,5,0);
                        nParamValue = sKYJ.sFactoryParam.nTotalLoadTime;
                        LcmPutFixDigit(4,56,nParamValue,4,0);
                        LcmSetSongBuff(119,33,0,0,0,0,0,0); //秒
                        LcmPutSongStr(4,96,BuffCharDot,2,0);                         
                        break;
                    case 8:
                        LcmSetSongBuff(109,10,98,99,0,0,0,0); //低温保护
                        LcmPutSongStr(1,0,BuffCharDot,4,0);
                        nParamValue = sKYJ.sFactoryParam.nLowTempProtect;
                        LcmPutFixDigit(4,56,nParamValue,4,0);
                        LcmSetSongBuff(12,0,0,0,0,0,0,0); //℃
                        LcmPutSongStr(4,96,BuffCharDot,1,0); 
                        break;
                    case 9:
                         LcmSetSongBuff(33,86,0,0,0,0,0,0); //时限
                        LcmPutSongStr(1,0,BuffCharDot,2,0);
                        nParamValue = sKYJ.sFactoryParam.nTimeLimit;
                        LcmPutFixDigit(4,56,nParamValue,4,0);
                        LcmSetSongBuff(119,33,0,0,0,0,0,0); //时
                        LcmPutSongStr(4,96,BuffCharDot,2,0);
                        break;                        
                    default:
                        break;
                }    
}

void KYJ_EnterParamValue(unsigned char nMI,unsigned char nPI, int nValue)
{
    nRefreshInterface = 1;
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
                sKYJ.sUserParam.nSlaveLoadPress = nValue;
                break;
            case 9:
                sKYJ.sUserParam.nSlaveUnLoadPress = nValue;
                break;                        
            default:
                break;            
        }
        KYJ_SwitchToInterface(INTERFACE_USERPARAM);
    }
    else if(nMI == 3) //厂家参数
    {
        KYJ_SwitchToInterface(INTERFACE_FACTORYPARAM);
    }
    else if(nMI == 4) //调整参数
    {
        KYJ_SwitchToInterface(INTERFACE_REGPARAM);
    }
    else if(nMI == 5) //密码设置
    {
        KYJ_SwitchToInterface(INTERFACE_PASSWORD);
    }
    EEPROM_Save_Param(PARAM_STORE_BYTES);
}

void KYJ_UpdateData(void)  //更新压力、温度、电流
{
    sKYJ.sRunParam.fPressure = adc_Get_Value(CH_Pressure);
    sKYJ.sRunParam.fTemperature = adc_Get_Value(CH_Temperature);
    sKYJ.sRunParam.fCurrentA = adc_Get_Value(CH_CurrentA);
    sKYJ.sRunParam.fCurrentB = adc_Get_Value(CH_CurrentB);
    sKYJ.sRunParam.fCurrentC = adc_Get_Value(CH_CurrentC);
}