/* 
 * File:   KYJDEF.h
 * Author: tlan
 *
 * Created on 2015年12月8日, 下午12:21
 */

#ifndef KYJDEF_H
#define	KYJDEF_H

#ifdef	__cplusplus
extern "C" {
#endif

struct KYJ_RunParam_s
{
    float fCurrentA; //主机A相电流，单位：A
    float fCurrentB; //主机B相电流，单位：A
    float fCurrentC; //主机C相电流，单位：A
    float fCurrentFan; //风机电流，单位：A
    int nTotaleTime; //运行总时间，单位：分钟
    int nLoadTime; //负载总时间：单位：分钟
};

struct KYJ_UserParam_s
{
    unsigned char nFanStartTemp; //风机启温度
    unsigned char nFanStopTemp; //风机停温度
    unsigned char nMCUDelayTime; //主机延时时间，单位：秒
    unsigned char nLoadDelayTime; //加载延时时间，单位：秒
    unsigned char nNoLoadDelayTime; //空载延时时间
    unsigned char nStopDelayTime; //停机延时时间
    unsigned char nRestartDelayTime; //重启延时时间
    unsigned char nStartStopMode; //启停方式
    unsigned char nLoadMode; //加载方式
    unsigned char nCommMode; //通讯方式
    unsigned char nCommCode; //通讯编码
    unsigned char nSlaveMode; //联动状态
    unsigned char nInTurnTime; //轮换时间，单位：小时
    unsigned char nSlaveCount; //联动机数
    unsigned char nSlaveLoadPress;//联动加载压力
    unsigned char nSlaveUnLoadPress;//联动卸载压力
    unsigned char nSlaveDelayTime;//联动延时时间
    unsigned char nOilFilterTime;//油滤器时间复位
    unsigned char nOilDeployTime;//油分器时间复位
    unsigned char nAirFilterTime; //空滤器时间复位
    unsigned char nOil2Time; //润滑油时间复位
    unsigned char nOil3Time; //润滑脂时间复位
    unsigned char nBeltTime; //皮带时间复位
    unsigned char nOilFilterPresetTime; //油滤器时间预置
    unsigned char nOilDeployPresetTime; //油分器时间预置
    unsigned char nAirFilterPresetTime; //空滤器时间预置
    unsigned char nOil2PresetTime; //润滑油时间预置
    unsigned char nOil3PresetTime; //润滑脂时间预置
    unsigned char nBeltPresetTime; //皮带时间预置
    unsigned char nLanguage;//中文/英文
    unsigned int nPassword;//修改用户密码
};
struct KYJ_FactoryParam_s
{
    unsigned int nMainMotorNormalCurrent;  //主机额定电流
    unsigned char nWarningTemp; //排温预警温度
    unsigned char nStopTemp;//排温停机温度
    unsigned char nStopPress; //供气停机压力
    unsigned char nUnloadPressLimit; //卸载压力高限
    unsigned int nTotalRunTime; //运行总时间
    unsigned int nTotalLoadTime; //负载总时间
    unsigned char nHistoryFaultRest; //历史故障复位
    unsigned char nCurrentNotBalance; //电流不平衡度
    unsigned char nNoPhaseProtectTime; //断相保护时间
    unsigned int nProductDate; //出厂日期
    unsigned int nProductSN;//出厂编号
    unsigned char nPhaseProtect; //相序保护
    unsigned char nFreqSelect; //频率选择
    unsigned char nCooperationMode; //联动方式
    char nLowTempProtect; //低温保护
    unsigned int nTimeLimit;//时限
    unsigned char nWarningOverTime;//预警过久停机
    unsigned char nCommParam;//通信预置参数
    unsigned char nParam1;//参数1

};

struct KYJ_RegParam_s
{
    unsigned char nStandCurrentA;//标准电流
    unsigned char nStandCurrentAFactor;//系数
    unsigned char nCurrentA;//现行电流
    unsigned char nStandCurrentB;//标准电流
    unsigned char nStandCurrentBFactor;//系数
    unsigned char nCurrentB;//现行电流
    unsigned char nStandCurrentC; //标准电流
    unsigned char nStandCurrentCFactor;//系数
    unsigned char nCurrentC;//现行电流
    unsigned char nStandTemp;//标准温度
    unsigned char nStandTempFactor;//系数
    unsigned char nZeroBias;//零点
    unsigned char nTemp;//现行温度
    unsigned char nCurrMode;//CURR MODE
};
struct KYJ_Password_s
{
    unsigned int nOpPass; //操作密码
    unsigned int nUserPass; //用户密码
    unsigned int nSalePass; //销售密码
    unsigned int nFactoryPass; //厂家密码
    unsigned int nRegPass;//校准密码
    unsigned int nSuperPass;//厂家超级密码
};

#define STATUS_POWERSTOP 0x10
#define STATUS_KEYSTOP 0x20
#define STATUS_DELAYSTOP 0x40
#define STATUS_FAULTSTOP 0x80
#define STATUS_STARTUP 0x01
#define STATUS_LOAD 0x02
#define STATUS_UNLOAD 0x04
#define STATUS_MANUAL 0x08

#define INTERFACE_MAIN 0x01
#define INTERFACE_MENU 0x02
#define INTERFACE_RUNPARAM 0x03
#define INTERFACE_USERPARAM 0x04
#define INTERFACE_FACTORYPARAM 0x05
#define INTERFACE_REGPARAM 0x06
#define INTERFACE_PASSWORD 0x07
#define INTERFACE_PARAM 0x08

#define LED_ON RE0=1
#define LED_OFF RE0=0
#define MOTOR_SW_ON RC2=1
#define MOTOR_SW_OFF RC2=0
#define LOAD_SW_ON RA6=1
#define LOAS_SW_OFF RA6=0
#define FAN_SW_ON RA7=1
#define FAN_SW_OFF RA7=0

#define PARAM_STORE_BYTES 85 //EEPROM保存的参数字节数
struct KYJ_s
{
    unsigned char nStatus; //空压机状态值：D7~D4停止标志，0001上电停止；0010停机键停止；0100空久停止；1000故障停止；
                           //D3~D0工作状态，0001启动；0010加载运行；0100空载运行；1000手动加载
    unsigned char nInterface; //显示的界面
    unsigned int nStatusTimeElapse;  //进入某一状态后的时间持续值，单位：秒
    unsigned char nInterfaceTimeElapse;
    struct KYJ_RunParam_s sRunParam;
    struct KYJ_UserParam_s sUserParam;
    struct KYJ_FactoryParam_s sFactoryParam;
    struct KYJ_RegParam_s sRegParam;
    struct KYJ_Password_s sPassword;
};
extern    struct KYJ_s sKYJ;
void KYJ_Param_Default(void);

unsigned char KYJ_CheckStatus(unsigned char nStatus);
void KYJ_SwitchToStatus(unsigned char nStatus);
void KYJ_ExcecuteStatus(void);
unsigned char KYJ_CheckInterface(unsigned char nInterface);
void KYJ_SwitchToInterface(unsigned char nInterface);
void KYJ_ExecuteInterface(void);

#ifdef	__cplusplus
}
#endif

#endif	/* KYJDEF_H */

