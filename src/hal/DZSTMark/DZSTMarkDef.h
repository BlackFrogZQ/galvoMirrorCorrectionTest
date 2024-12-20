﻿#pragma once
#include "system/basic.h"

namespace TIGER_DZSTMarkDef
{
#pragma region "振镜扫描系统参数"
    struct CGalvoScanningSystemParas
    {
        unsigned int MarkSpeed;       //打标速度(mm/s)
        unsigned int JumpSpeed;       //跳转速度(mm/s)
        unsigned int MarkDelay;       //打标延时(us)
        unsigned int JumpDelay;       //跳转延时(us)
        unsigned int PolygonDelay;    //转弯延时(us)
        unsigned int MarkCount;       //打标次数
        CGalvoScanningSystemParas::CGalvoScanningSystemParas()
        {
            MarkSpeed = 1000;
            JumpSpeed = 2000;
            MarkDelay = 0;
            JumpDelay = 0;
            PolygonDelay = 0;
            MarkCount = 1;
        }
    };
    CGalvoScanningSystemParas *scanSystemParas();
#pragma endregion

#pragma region "激光参数"
    enum CLaserDevice: int
    {
        cltIPG = 0,
        cltSPI,
        cltCO2,
        cltUnKnow
    };
    struct CLaserParas
    {
        CLaserDevice LaserDevice = cltIPG;       //激光器类型
        float LaserOnDelay = 111;             //开激光延时(单位us)
        float LaserOffDelay = 111;            //关激光延时(单位us)
        float FPKDelay;                 //首脉冲抑制延时(单位us)
        float FPKLength;                //首脉冲抑制长度(单位us)
        float QDelay;                   //出光Q频率延时(单位us)
        float DutyCycle = 0.5;                //出光时占空比，(0~1)
        float Frequency = 20;                //出光时频率kHz
        float StandbyFrequency = 20;         //不出光Q频率(单位kHz);
        float StandbyDutyCycle = 0.5;         //不出光Q占空比(0~1);
        float LaserPower = 50;               //激光能量百分比(0~100)，50代表50%
        unsigned int AnalogMode = 0;        //1代表使用模拟量输出来控制激光器能量（0~10V）
        unsigned int Waveform = 1;          //SPI激光器波形号（0~63）
        unsigned int PulseWidthMode;    //0,不开启MOPA脉宽使能模式， 1,开启MOPA激光器脉宽使能
        unsigned int PulseWidth;        //MOPA激光器脉宽值 单位（ns）
        CLaserParas::CLaserParas()
        {}
    };
    CLaserParas *laserParas();
#pragma endregion

#pragma region "打标形状参数"
    enum CMarkShape
    {
        cmsRound,
        cmsCross,
        cmsRectangular,
        cmsUnKnow
    };
    const QStringList cmarkSape = {cnStr("圆形"), cnStr("十字叉"), cnStr("矩形")};
    struct CMarkShapeParas
    {
        CMarkShape shapeType = cmsRound;  // 打标形状
        int markRange = 100;              // 打标范围
        int rowAndCol = 3;                // (行/列)数
        int diameter = 5;                 // 形状直径
    };
    CMarkShapeParas *markShapeParas();
#pragma endregion
}