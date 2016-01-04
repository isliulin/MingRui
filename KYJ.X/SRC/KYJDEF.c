#include "KYJDEF.h"
#include "LCD_LIXIAN.h"
#include "key.h"

struct KYJ_s sKYJ;
unsigned char nRefreshInterface;
unsigned char nMenuIndex;  //当前菜单序号  1-运行参数；2-用户参数；3-厂家参数；4-注册参数；5-用户密码
unsigned char nParamIndex;   //当前参数序号
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
    sKYJ.sUserParam.nSlaveLoadPress = 100;//联动加载压力
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
    switch(nStatus)
    {
        case STATUS_POWERSTOP:
            break;
        case STATUS_KEYSTOP:
            break;
        case STATUS_DELAYSTOP:
            break;
        case STATUS_FAULTSTOP:
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
    return 0;    
}

void KYJ_SwitchToStatus(unsigned char nStatus)
{
    switch(nStatus)
    {
        case STATUS_POWERSTOP:
            break;
        case STATUS_KEYSTOP:
            break;
        case STATUS_DELAYSTOP:
            break;
        case STATUS_FAULTSTOP:
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
    sKYJ.nStatus = nStatus;
    sKYJ.nStatusTimeElapse = 0;
    return;      
}

void KYJ_ExcecuteStatus(void)
{
    switch(sKYJ.nStatus)
    {
        case STATUS_POWERSTOP:
            break;
        case STATUS_KEYSTOP:
            break;
        case STATUS_DELAYSTOP:
            break;
        case STATUS_FAULTSTOP:
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
                    ((sKYJ.nInterface!=INTERFACE_MAIN) && sKYJ.nInterfaceTimeElapse > 60)
                    ) nRet = 1;
            break;
        case INTERFACE_MENU:
            if(sKYJ.nInterface == INTERFACE_MAIN && Key_Release(KEY_DOWN)) nRet = 1;
            break;
        case INTERFACE_RUNPARAM:
            if(sKYJ.nInterface == INTERFACE_MENU && nMenuIndex == 1 && Key_Release(KEY_MOVE)) nRet = 1;
            break;
        case INTERFACE_USERPARAM:
            if(sKYJ.nInterface == INTERFACE_MENU && nMenuIndex == 2 && Key_Release(KEY_MOVE)) nRet = 1;
            break;
        case INTERFACE_FACTORYPARAM:
            if(sKYJ.nInterface == INTERFACE_MENU && nMenuIndex == 3 && Key_Release(KEY_MOVE)) nRet = 1;
            break;
        case INTERFACE_REGPARAM:
            if(sKYJ.nInterface == INTERFACE_MENU && nMenuIndex == 4 && Key_Release(KEY_MOVE)) nRet = 1;
            break;
        case INTERFACE_PASSWORD:
            if(sKYJ.nInterface == INTERFACE_MENU && nMenuIndex == 5 && Key_Release(KEY_MOVE)) nRet = 1;
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
    LcmClear(0x00);
    switch(nInterface)
    {
        case INTERFACE_MAIN:
                LcmSetSongBuff(10,11,0,0,0,0,0,0); //温度
                LcmPutSongStr(1,0,BuffCharDot,2,0);
                
                LcmSetSongBuff(12,0,0,0,0,0,0,0); //℃
                LcmPutSongStr(1,64,BuffCharDot,1,0);
                
                LcmSetSongBuff(13,14,15,17,18,0,0,0);//设备已停止
                LcmPutSongStr(4,0,BuffCharDot,5,0);
                
                LcmSetSongBuff(19,0,0,0,0,0,0,0); //秒
                LcmPutSongStr(4,112,BuffCharDot,1,0);
            break;
        case INTERFACE_MENU:
            nMenuIndex = 1;
            nParamIndex = 0;
            nRefreshInterface = 1;
            break;
        case INTERFACE_RUNPARAM:
            break;
        case INTERFACE_USERPARAM:
            break;
        case INTERFACE_FACTORYPARAM:
            break;
        case INTERFACE_REGPARAM:
            break;
        case INTERFACE_PASSWORD:
            break;
        case INTERFACE_PARAM:
            nParamIndex = 1;
            nRefreshInterface = 1;
            break;
        default:
            break;
    }
    sKYJ.nInterface = nInterface;
    sKYJ.nInterfaceTimeElapse = 0;
    

    return;      
}

void KYJ_ExecuteInterface(void)
{
    switch(sKYJ.nInterface)
    {
        case INTERFACE_MAIN:
            LcmPutNum(80,4,sKYJ.nStatusTimeElapse/100);
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
                    
                    LcmSetSongBuff(27,28,22,23,0,0,0,0); //运行参数
                    if(nMenuIndex == 4)LcmPutSongStr(6,0,BuffCharDot,4,1); else  LcmPutSongStr(6,0,BuffCharDot,4,0);    
                }
                else  //显示第5项
                {
                    LcmSetSongBuff(40,41,0,0,0,0,0,0); //运行参数
                    LcmPutSongStr(0,0,BuffCharDot,2,1);
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
                        LcmPutStr(80,2,"A");
                        
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
        case INTERFACE_USERPARAM:
            break;
        case INTERFACE_FACTORYPARAM:
            break;
        case INTERFACE_REGPARAM:
            break;
        case INTERFACE_PASSWORD:
            break;
        case INTERFACE_PARAM:
            break;
        default:
            break;
    }
    
    nRefreshInterface = 0;
    return;      
}