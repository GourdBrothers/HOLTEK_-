asm (" message' **************************************************** ' ");
asm (" message' *       2018 BY BEST HEALTH ELECTRONIC INC         * ' ");
asm (" message' *__________________________________________________* ' ");
asm (" message' *        SDK  NAME  :      BFScales.c   	       * ' ");
asm (" message' *   Compiler   Ver. :      V3.53                   * ' ");
asm (" message' *   IDE3000    Ver. :      V7.97                   * ' ");
asm (" message' *   RELEASE    Ver. :      2.0.2                   * ' ");
asm (" message' *   RELEASE   DATA  :     2018/05/29               * ' ");
asm (" message' *__________________________________________________* ' ");
asm (" message' *    MCU / CFG Ver. :   BH66F2652 / 1.0            * ' ");
asm (" message' *                       BH66F2662 / 1.0            * ' ");
asm (" message' **************************************************** ' ");
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// ====================================================================================@
//                              此文件不能修改!!!                                      @
// ====================================================================================@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
#include "SDK_UserSetting.h"
#include "SDK_Interface.h"
#include "BH66F2652.h"


// ADC DATA RARE 計算方式:
// FMCLK = Fsys = 4000000,CHOP = 2, N = 12,OSR = 16384
// FADCK = FMCLK/(CHOP/N) =166667=167K
// DataRate = FADCK/OSR = 10.2HZ
#define CHOP2_FLMS30()              { _flms2=0; _flms1=0; _flms0=0;}
#define CHOP2_FLMS12()              { _flms2=0; _flms1=1; _flms0=0;}
#define CHOP1_FLMS30()              { _flms2=1; _flms1=0; _flms0=0;}
#define CHOP1_FLMS12()              { _flms2=1; _flms1=1; _flms0=0;}
#define OSR_16384()                 { _ador2=0; _ador1=0; _ador0=0;}
#define OSR_8192()                  { _ador2=0; _ador1=0; _ador0=1;}
#define OSR_4096()                  { _ador2=0; _ador1=1; _ador0=0;}
#define OSR_2048()                  { _ador2=0; _ador1=1; _ador0=1;}
#define OSR_1024()                  { _ador2=1; _ador1=0; _ador0=0;}
#define OSR_512()                   { _ador2=1; _ador1=0; _ador0=1;}
#define OSR_256()                   { _ador2=1; _ador1=1; _ador0=0;}
#define OSR_128()                   { _ador2=1; _ador1=1; _ador0=1;}

#define SET_ADC_DATARATE_10HZ()		{ _adcs=0x00; CHOP2_FLMS12(); OSR_16384(); }
#define SET_ADC_DATARATE_64HZ()		{ _adcs=0x00; CHOP2_FLMS30(); OSR_1024(); }
#define SET_ADC_DATARATE_1300HZ()	{ _adcs=0x00; CHOP2_FLMS12(); OSR_128();  }

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// ======================================================@
//                用戶設置  重量接口                      @
// ======================================================@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
void fun_LoadUserSetting()
{
	SDKWeightSetting.WeightMax             = WEIGHT_MAX;
	SDKWeightSetting.WeightMin             = WEIGHT_MIN;
	SDKWeightSetting.WeightUnLockTemp      = WEIGHT_UNLOCK_TEMP;
	SDKWeightSetting.WeightUnLockStable    = WEIGHT_UNLOCK_STATE;
	SDKWeightSetting.WeightAutoOn          = WEIGHT_AUTOON;
	SDKWeightSetting.flag.b.IsAutoCalOn    = WEIGHT_AUTOCAL;
	SDKWeightSetting.flag.b.IsAutoUnlockOn = WEIGHT_AUTOUNLOCK;
}
void fun_LoadWeightSetting()
{
	SET_ADC_DATARATE_10HZ();
	SDKADCFilterData.StableCntTag = ADCSTABLE_WEIGHT_CNT;
	SDKADCFilterData.StableThreshold   = ADCSTABLE_WEIGHT_THRESHOLD;
}
void fun_LoadAutoOnSetting()
{
	SET_ADC_DATARATE_1300HZ();
}

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// ======================================================@
//                用戶設置  阻抗接口                      @
// ======================================================@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
void fun_LoadImpedanceSetting()
{
	// 採樣率設置
	SET_ADC_DATARATE_64HZ();
	// MCU封裝選擇
	SDKImpedance.flag.b.IsUseQFN32 = MCU_PACKAGE_IS_QFN32;
	// 濾波參數設置
	SDKADCFilterData.StableCntTag  = ADCSTABLE_IMPEDANCE_CNT;
	SDKADCFilterData.StableThreshold   = ADCSTABLE_IMPEDANCE_THRESHOLD;
}