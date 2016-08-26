/* 
 * File:   KYJDEF.h
 * Author: tlan
 *
 * Created on 2015年12月8日, 下午12:21
 */

#ifndef KYJDEF_H
#define	KYJDEF_H
#include <xc.h>
#ifdef	__cplusplus
extern "C" {
#endif

struct KYJ_RunParam_s
{
    unsigned int nCurrentA; //主机A相电流，单位：0.1A
    unsigned int nCurrentB; //主机B相电流，单位：0.1A
    unsigned int nCurrentC; //主机C相电流，单位：0.1A
    //float fCurrentFan; //风机电流，单位：A
    int nPressure; //压力值，0.01MPa
    int nTemperature; //温度值，0.1度
    unsigned int nVoltage; //电压值，V
    unsigned long nTotalTime; //运行总时间，单位：小时
    unsigned long nLoadTime; //负载总时间：单位：小时
};

struct KYJ_UserParam_s
{
    unsigned int nLoadPress; //加载压力，单位：00.01MPa
    unsigned int nUnLoadPress; //卸载压力
    unsigned int nFanStartTemp; //风机启温度
    unsigned int nFanStopTemp; //风机停温度
    unsigned int nMCUDelayTime; //主机延时时间，单位：秒
    unsigned int nSADelayTime; //星角延时时间，单位：秒
    unsigned int nLoadDelayTime; //加载延时时间，单位：秒
    unsigned int nNoLoadDelayTime; //空载延时时间
    unsigned int nStopDelayTime; //停机延时时间
    unsigned int nRestartDelayTime; //重启延时时间
    unsigned char nStartStopMode; //启停方式
    unsigned char nLoadMode; //加载方式；1-自动，0-手动
    unsigned char nCommMode; //通讯方式
    unsigned char nCommCode; //通讯编码
    unsigned char nSlaveMode; //联动状态
    unsigned int nInTurnTime; //轮换时间，单位：小时
    unsigned char nSlaveCount; //联动机数
    unsigned int nSlaveLoadPress;//联动加载压力
    unsigned int nSlaveUnLoadPress;//联动卸载压力
    unsigned int nSlaveDelayTime;//联动延时时间
    unsigned int nOilFilterTime;//油滤器时间复位
    unsigned int nOilDeployTime;//油分器时间复位
    unsigned int nAirFilterTime; //空滤器时间复位
    unsigned int nOil2Time; //润滑油时间复位
    unsigned int nOil3Time; //润滑脂时间复位
    unsigned int nBeltTime; //皮带时间复位
    unsigned int nOilFilterPresetTime; //油滤器时间预置
    unsigned int nOilDeployPresetTime; //油分器时间预置
    unsigned int nAirFilterPresetTime; //空滤器时间预置
    unsigned int nOil2PresetTime; //润滑油时间预置
    unsigned int nOil3PresetTime; //润滑脂时间预置
    unsigned int nBeltPresetTime; //皮带时间预置
    unsigned char nLanguage;//中文/英文
    unsigned int nPassword;//修改用户密码
};
struct KYJ_FactoryParam_s
{
    unsigned int nMainMotorNormalCurrent;  //主机额定电流，单位0.1A
    unsigned int nWarningTemp; //排温预警温度
    unsigned int nStopTemp;//排温停机温度
    unsigned int nStopPress; //供气停机压力
    unsigned int nUnloadPressLimit; //卸载压力高限
    unsigned long nTotalRunTime; //运行总时间，单位：分钟
    unsigned long nTotalLoadTime; //负载总时间，单位：分钟
    unsigned int nHistoryFaultRest; //历史故障复位
    unsigned int nCurrentNotBalance; //电流不平衡度
    unsigned int nNoPhaseProtectTime; //断相保护时间
    unsigned int nProductDate; //出厂日期
    unsigned int nProductSN;//出厂编号
    unsigned char nPhaseProtect; //相序保护
    unsigned char nFreqSelect; //频率选择
    unsigned char nCooperationMode; //联动方式
    unsigned char nLowTempProtect; //低温保护，自动加负号
    unsigned long nTimeLimit;//时限
    unsigned int nWarningOverTime;//预警过久停机
    unsigned char nCommParam;//通信预置参数
    //unsigned char nParam1;//参数1
    unsigned char nStartType; //启动方式：0为直接启动，1为星角启动

};

struct KYJ_RegParam_s
{
    unsigned int nStandCurrentA;//标准电流
    unsigned int nStandCurrentAFactor;//系数, 0.001
    unsigned int nCurrentA;//现行电流
    unsigned int nStandCurrentB;//标准电流
    unsigned int nStandCurrentBFactor;//系数
    unsigned int nCurrentB;//现行电流
    unsigned int nStandCurrentC; //标准电流
    unsigned int nStandCurrentCFactor;//系数
    unsigned int nCurrentC;//现行电流
    unsigned int nStandTemp;//标准温度
    unsigned int nStandTempFactor;//系数, 0.001
    unsigned int nZeroBias;//零点
    int nTemp;//现行温度
    unsigned int nStandVoltage; //标准电压
    unsigned int nVoltage; //现行电压
    unsigned int nStandVoltageFactor; //电压系数,0.001
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

#define LED_ON PORTEbits.RE0=1  //LCD背光
#define LED_OFF PORTEbits.RE0=0
#define MOTOR_SW_ON PORTCbits.RC2=1  //主机继电器
#define MOTOR_SW_OFF PORTCbits.RC2=0
#define LOAD_SW_ON PORTAbits.RA6=1  //加载阀继电器
#define LOAD_SW_OFF PORTAbits.RA6=0
#define FAN_SW_ON PORTAbits.RA7=1  //风扇继电器
#define FAN_SW_OFF PORTAbits.RA7=0

#define LED_RUN_ON PORTBbits.RB6=0  //运行指示灯
#define LED_RUN_OFF PORTBbits.RB6=1
#define LED_ERROR_ON PORTBbits.RB7=0 //故障指示灯
#define LED_ERROR_OFF PORTBbits.RB7=1
#define BEEP_ON PORTEbits.RE1=1  //蜂鸣器开关
#define BEEP_OFF PORTEbits.RE1=0

#define PARAM_STORE_BYTES 0x01B8-0x0127+1 //EEPROM保存的参数字节数
#define CURRENT_TRANS_RATIO 420 //互感器变流比例
#define CURRENT_SAMPLE_RES 10 //电流采样电阻

#define max(x,y) (x)>(y)?(x):(y);
#define min(x,y) (x)<(y)?(x):(y);
struct KYJ_s
{
    
    unsigned char nStatus; //空压机状态值：D7~D4停止标志，0001上电停止；0010停机键停止；0100空久停止；1000故障停止；
                           //D3~D0工作状态，0001启动；0010加载运行；0100空载运行；1000手动加载
    unsigned char nInterface; //显示的界面
    unsigned int nStatusTimeElapse;  //进入某一状态后的时间持续值，单位：秒
    unsigned char nInterfaceTimeElapse;
    unsigned int nFaultFlag;//故障标志，D0 缺相；D1 电流不平衡；D2 过热停机；D3 超压停机；D4低温保护；D5过载保护；D6电源电压保护；D7压力传感器故障；D8温度传感器故障
    unsigned int nCurrentA;  //校正计算后的电流，0.1A
    unsigned int nCurrentB;
    unsigned int nCurrentC;
    int nTemperature; //校正计算后的温度，度
    int nPressure; //校正计算后的压力值，0.01MPa
    unsigned int nVoltage; //校正计算后的电源电压，V
    struct KYJ_RunParam_s sRunParam;
    struct KYJ_UserParam_s sUserParam;
    struct KYJ_FactoryParam_s sFactoryParam;
    struct KYJ_RegParam_s sRegParam;
    struct KYJ_Password_s sPassword;
};
extern    struct KYJ_s sKYJ;
void KYJ_Param_Default(void);

bit KYJ_CheckStatus(unsigned char nStatus);
void KYJ_SwitchToStatus(unsigned char nStatus);
void KYJ_ExcecuteStatus(void);
bit KYJ_CheckInterface(unsigned char nInterface);
void KYJ_SwitchToInterface(unsigned char nInterface);
void KYJ_ExecuteInterface(void);
void KYJ_ShowUserParam(unsigned char nParamIndex);  //显示用户参数
void KYJ_ShowFactoryParam(unsigned char nParamIndex); //显示厂家参数
void KYJ_ShowRegParam(unsigned char nParamIndex); //显示调整参数

void KYJ_EnterParamValue(unsigned char nMI,unsigned char nPI, int nValue);

void KYJ_CalcRegValue(void);  //根据调整参数计算调整后的传感器数值
void KYJ_UpdateData(void);  //更新压力、温度、电流
void KYJ_SampleCurrent(void);  //在定时中断中1ms调用一次
void KYJ_Init(void);
void KYJ_ShowRunParam(void);

#ifdef	__cplusplus
}
#endif

#endif	/* KYJDEF_H */

