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

#define STATUS_POWERSTOP 0x10;
#define STATUS_KEYSTOP 0x20;
#define STATUS_DELAYSTOP 0x40;
#define STATUS_FAULTSTOP 0x80;
#define STATUS_STARTUP 0x01;
#define STATUS_LOAD 0x02;
#define STATUS_UNLOAD 0x04;
#define STATUS_MANUAL 0x08;

struct KYJ_s
{
    unsigned char nStatus; //空压机状态值：D7~D4停止标志，0001上电停止；0010停机键停止；0100空久停止；1000故障停止；
                           //D3~D0工作状态，0001启动；0010加载运行；0100空载运行；1000手动加载
    unsigned int nStatusTimeElapse;  //进入某一状态后的时间持续值，单位：秒
    struct KYJ_RunParam_s sRunParam;
    struct KYJ_UserParam_s sUserParam;
};

#ifdef	__cplusplus
}
#endif

#endif	/* KYJDEF_H */

