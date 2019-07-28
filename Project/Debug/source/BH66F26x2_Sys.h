#ifndef _BH66F26X2_SYS_H_
#define _BH66F26X2_SYS_H_


//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ 共用函數 @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
void fun_SysPowerOnInit();
void fun_PowerDownInit();
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ 共用函數 @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
extern volatile unsigned char gu8v_HaltTime;
// 系統自動休眠時間設定
#define TIMEBASE0_CYCLE8MS    	8	    // 8ms
#define TIMEBASE1_CYCLE1S    	1000 	// 1000ms
#define HALTTIME60S			(60000/TIMEBASE1_CYCLE1S)
#define HALTTIME30S			(30000/TIMEBASE1_CYCLE1S)
#define HALTTIME20S			(20000/TIMEBASE1_CYCLE1S)
#define HALTTIME17S			(17000/TIMEBASE1_CYCLE1S)
#define HALTTIME15S			(15000/TIMEBASE1_CYCLE1S)
#define HALTTIME12S			(12000/TIMEBASE1_CYCLE1S)
#define HALTTIME10S			(10000/TIMEBASE1_CYCLE1S)
#define HALTTIME5S			(5000/TIMEBASE1_CYCLE1S)
#define HALTTIME4S			(4000/TIMEBASE1_CYCLE1S)
#define HALTTIME3S			(3000/TIMEBASE1_CYCLE1S)
#define HALTTIME2S			(2000/TIMEBASE1_CYCLE1S)
#define HALTTIME1S			(1000/TIMEBASE1_CYCLE1S)
#define HALTTIME_DEFAULT	HALTTIME60S
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ 預處理 @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//					@-------------IO config--------------@
#define SET_PB025_PA6_POWER_VDDIO() { _pmps = 0x3F;}
#define SET_PB025_PA6_POWER_VDD()   { _pmps = 0x00;}
//					@-------------LED Current-------------@
#define SET_LEDCURRENT_LEVEL0()	{ _sledc0 = 0x00; _sledc1 = 0x00;}
#define SET_LEDCURRENT_LEVEL1()	{ _sledc0 = 0x55; _sledc1 = 0x05;}
#define SET_LEDCURRENT_LEVEL2()	{ _sledc0 = 0xAA; _sledc1 = 0x0A;}
#define SET_LEDCURRENT_LEVEL3()	{ _sledc0 = 0xFF; _sledc1 = 0xFF;}
//					@---------------IAP config---------------@
// Setting in IAP.h
//					@-------------EEPROM config--------------@
// Setting in EEPROM.h , EEPROM.C
//					@---------------RAM config---------------@
// Seting in Sys_Init.c
//					@-----------SysClock config--------------@
// Seting in Sys_Init.c
//					@---------------WDT config---------------@
// WDT clock Source fs =fsub
// WDT time计算方式: WDT time =  2^18/fsub
// example:(max time 周期最长2^18，Source fs = 32000)
// WDT time = 2^18/32000= 8s
#define SET_WDT_DISABLE()		{ _wdtc = 0xA8;}
#define SET_WDTTIME_8MS()		{ _wdtc = 0x50;}
#define SET_WDTTIME_32MS()		{ _wdtc = 0x51;}
#define SET_WDTTIME_125MS()		{ _wdtc = 0x52;}
#define SET_WDTTIME_500MS()		{ _wdtc = 0x53;}
#define SET_WDTTIME_1000MS()	{ _wdtc = 0x54;}
#define SET_WDTTIME_2000MS()	{ _wdtc = 0x55;}
#define SET_WDTTIME_4000MS()	{ _wdtc = 0x56;}
#define SET_WDTTIME_8000MS()	{ _wdtc = 0x57;}
//					@-------------LVR config--------------@
#define  SET_LVR_2_1V()			{ _lvrc = 0x55;}
#define  SET_LVR_2_55V()		{ _lvrc = 0x33;}
#define  SET_LVR_3_15V()		{ _lvrc = 0x88;}
#define  SET_LVR_3_8V()			{ _lvrc = 0xAA;}
#define  SET_RESET_MCU()        { _rstc = 0x00;}
//					@-------------LVD config--------------@
#define SET_LVD_DISABLE()       { _lvden = 0; _vbgen = 0;}
#define SET_LVD_LVDIN_EN()      { _lvdc = 0x18;}
#define SET_LVD_2V2_EN()        { _lvdc = 0x19;}
#define SET_LVD_2V4_EN()        { _lvdc = 0x1A;}
#define SET_LVD_2V7_EN()        { _lvdc = 0x1B;}
#define SET_LVD_3V0_EN()        { _lvdc = 0x1C;}
#define SET_LVD_3V3_EN()        { _lvdc = 0x1D;}
#define SET_LVD_3V6_EN()        { _lvdc = 0x1E;}
#define SET_LVD_4V0_EN()        { _lvdc = 0x1F;}
//                  @-------------CTM config--------------@
#define SET_CTM_TIMER2MS()      { _ctmc0 = 0x20; _ctmc1 = 0xC1; _ctmal = 1000%256;_ctmah = 1000/256;}
#define SET_CTM_ISRENABLE()     { _ctmaf = 0; _ctmae=1; _mf0f = 0;_mf0e = 1;}
#define SET_CTM_ISRDISABLE()    { _ctmpe = 0;}
#define SET_CTM_DISABLE()       { _cton = 0;}
#define SET_CTM_ENABLE()        { _cton = 1;}
//                  @-----------TimeBase config----------@
// 默認使用fs =fsub, LIRC/LXT
#define SET_TIMEBASE0_8MS()		{ _pscr = 0x03; _tb0c = 0x00;}
#define SET_TIMEBASE0_16MS()	{ _pscr = 0x03; _tb0c = 0x01;}
#define SET_TIMEBASE0_32MS()	{ _pscr = 0x03; _tb0c = 0x02;}
#define SET_TIMEBASE0_62MS()	{ _pscr = 0x03; _tb0c = 0x03;}
#define SET_TIMEBASE0_124MS()	{ _pscr = 0x03; _tb0c = 0x04;}
#define SET_TIMEBASE0_250MS()	{ _pscr = 0x03; _tb0c = 0x05;}
#define SET_TIMEBASE0_500MS()	{ _pscr = 0x03; _tb0c = 0x06;}
#define SET_TIMEBASE0_1000MS()	{ _pscr = 0x03; _tb0c = 0x07;}
#define SET_TIMEBASE0_ENABLE()	{ _tb0f = 0x00; _tb0e = 0x01; _tb0on = 1;}
#define SET_TIMEBASE0_DISABLE()	{ _tb0on = 0;}

#define SET_TIMEBASE1_8MS()		{ _pscr = 0x03; _tb1c = 0x00;}
#define SET_TIMEBASE1_16MS()	{ _pscr = 0x03; _tb1c = 0x01;}
#define SET_TIMEBASE1_32MS()	{ _pscr = 0x03; _tb1c = 0x02;}
#define SET_TIMEBASE1_62MS()	{ _pscr = 0x03; _tb1c = 0x03;}
#define SET_TIMEBASE1_124MS()	{ _pscr = 0x03; _tb1c = 0x04;}
#define SET_TIMEBASE1_250MS()	{ _pscr = 0x03; _tb1c = 0x05;}
#define SET_TIMEBASE1_500MS()	{ _pscr = 0x03; _tb1c = 0x06;}
#define SET_TIMEBASE1_1000MS()	{ _pscr = 0x03; _tb1c = 0x07;}
#define SET_TIMEBASE1_ENABLE()	{ _tb1f = 0x00; _tb1e = 0x01; _tb1on = 1;}
#define SET_TIMEBASE1_DISABLE()	{ _tb1on = 0;}
//						@-------------SIM config-------------@
// Setting in SIM.h
//						@------------SPIA config-------------@
// Setting in SIM.h
//						@-------------UART config------------@
// Setting in UART.h
//						@------------ADC config--------------@
// Setting in BodyFatScalesMCUConfig.h
//						@-----------BodyFat config-----------@
// Setting in BodyFatScalesMCUConfig.h


#endif
