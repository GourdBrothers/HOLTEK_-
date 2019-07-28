asm(" message' **************************************************** ' ");
asm(" message' *       2018 BY BEST HEALTH ELECTRONIC INC         * ' ");
asm(" message' *__________________________________________________* ' ");
asm(" message' *        SDK  NAME  : 	 BH66F26x2.c	          * ' ");
asm(" message' *   Compiler   Ver. :      V3.53                   * ' ");
asm(" message' *   IDE3000    Ver. :      V7.97                   * ' ");
asm(" message' *   RELEASE    Ver. :      1.0.0                   * ' ");
asm(" message' *   RELEASE   DATA  :     2018/07/20               * ' ");
asm(" message' *__________________________________________________* ' ");
asm(" message' *    MCU / CFG Ver. :   BH66F2652 / 1.0            * ' ");
asm(" message' *                       BH66F2662 / 1.0            * ' ");
asm(" message' **************************************************** ' ");
#include "common.h"
//__________________________________________________________________//
//					-----ISR VECTOR Defination------;
//中斷入口地址
#define	START_VECTOR			0x000		// 主程序
#define INT0_VECTOR				0x004		// Interrupt 0
#define INT1_VECTOR				0x008		// Interrupt 1
#define ADC_VECTOR				0x00C		// ADC
#define MuFunction0_VECTOR		0x010		// Multi function0 CTM0
#define CTMP_VECTOR				0x010		// CTMP
#define CTMA_VECTOR				0x010		// CTMA
#define MuFunction1_VECTOR		0x018		// Multi function1 LVD & EEPROM
#define LVD_VECTOR				0x018		// LVD
#define EEPROM_VECTOR			0x018		// EEPROM
#define SPI_VECTOR				0x01C		// SPI
#define Timebase0_VECTOR		0x020		// timebase0
#define Timebase1_VECTOR		0x024		// timebase1
#define UART_VECTOR		    	0x028		// UART

volatile unsigned char gu8v_HaltTime ;
/********************************************************************
Function: Ram_Init
INPUT	:
OUTPUT	:
NOTE	:
********************************************************************/
static void fun_RamInit()
{
	_mp1h = 0;
	_mp1l = 0x80;
	while(_mp1h < 3)
	{
		for(_tblp = 0x00;_tblp < 128;_tblp++)
		{
			 _iar1 = 0;
			  _mp1l++;
		}
		_mp1l = 0x80;
		_mp1h++;
	}
}
/********************************************************************
Function: GPIO初始化
INPUT	: none
OUTPUT	: none
NOTE	: 依據 Hard ware 設置對應IO狀態
********************************************************************/
void  fun_GPIOPowerOnInit()
{
// PA0-SEG0         PA1-SEG1
// PA2-SEG2         PA3-SEG3
// PA4-SEG4         PA5-SEG5
// PA6-BT_EN        PA7-KEY
	_pa   = 0B01000000;
	_pac  = 0B10111111;
	_papu = 0B10111111;
	_pawu = 0B10000000;
	_pas0 = 0B00000000;
	_pas1 = 0B00000000;
// PB0-BT_RET     PB1-BT_INT
// PB2-BT_MOSI    PB3-BT_MISO
// PB4-BT_SCK     PB5-BT_CSC
// PB6-VDDIO      PB7-Unused // 28SSOP PC0 不使用
	_pb   = 0B00000000;
	_pbc  = 0B00000000;
	_pbpu = 0B00000000;
	_pbs0 = 0B01010000;
//	_pbs1 = 0B00010101;
// PC0-LEDPoint       PC1-None
// PC2-None           PC3-None
// PC4-None           PC5-None
// PC6-None           PC7-None
	_pc   = 0B00000000;
	_pcc  = 0B00000001;		// 28SSOP PC0 不使用
	_pcpu = 0B00000000;

	SET_LEDCURRENT_LEVEL3();
	SET_PB025_PA6_POWER_VDDIO();
}
/********************************************************************
Function: GPIO初始化
INPUT	: none
OUTPUT	: none
NOTE	: 依據 Hard ware 設置對應IO狀態
********************************************************************/
void  fun_GPIOPowerDownInit()
{
// PA0-SEG0         PA1-SEG1
// PA2-SEG2         PA3-SEG3
// PA4-SEG4         PA5-SEG5
// PA6-BT_EN        PA7-KEY
	_pa   = 0B01000000;
	_pac  = 0B10111111;
// PB0-BT_RET     PB1-BT_INT
// PB2-BT_MOSI    PB3-BT_MISO
// PB4-BT_SCK     PB5-BT_CSC
// PB6-VDDIO      PB7-Unused // 28SSOP PC0 不使用
	_pb   = 0B00000000;
	_pbc  = 0B00000000;
// PC0-LEDPoint       PC1-None
// PC2-None           PC3-None
// PC4-None           PC5-None
// PC6-None           PC7-None
	_pc   = 0B00000000;
	_pcc  = 0B00000001;		// 28SSOP PC0 不使用
	// SET_LEDCURRENT_LEVEL3();
	// SET_PB025_PA6_POWER_VDDIO();
}
/********************************************************************
Function: MCU上電初始化
INPUT	:
OUTPUT	:
NOTE	:
********************************************************************/
void fun_SysPowerOnInit()
{
	//EEPROM not need to init
	// Sys Clock MCU fixed HIRC 8MHz
	fun_GPIOPowerOnInit();	// GPIO
	fun_RamInit();			// RAM
	SET_WDTTIME_125MS(); 	// WDT
	SET_LVR_2_55V();		// LVR
	SET_LVD_DISABLE();		// LVD use ADC
	SET_CTM_TIMER2MS();		// CTM
	SET_CTM_ISRENABLE();
	SET_CTM_ENABLE();

	SET_TIMEBASE0_8MS();	// Timebase0
	SET_TIMEBASE0_ENABLE();
	SET_TIMEBASE1_1000MS();// Timebase1
	SET_TIMEBASE1_ENABLE();
	// SPIA
	// UART
	// ADC
	// BodyFat
}

/********************************************************************
Function: 關閉各個模塊進入HLAT模式
INPUT	:
OUTPUT	:
NOTE	:
********************************************************************/
void fun_PowerDownInit()
{
	//EEPROM
	// RAM
	SET_WDTTIME_1000MS();	// wdt overflow for weight auto
	// LVR
	SET_LVD_DISABLE()		// LVD
	fun_GPIOPowerDownInit();// GPIO
	SET_CTM_DISABLE();		// CTM
	SET_TIMEBASE0_DISABLE();	// Timebase0
	SET_TIMEBASE1_DISABLE(); // Timebase1
	// SPI
	// UART
	// ADC
	// BodyFat
	gu8v_HaltTime = 0;
}

//@------------外部中斷0入口函數--------------@
DEFINE_ISR(INT0_ISR, INT0_VECTOR)
{

}
//@------------外部中斷0入口函數--------------@
DEFINE_ISR(INT1_ISR, INT1_VECTOR)
{
}
//@------------ADC 中斷入口函數---------------@
//DEFINE_ISR(ADC_ISR, ADC_VECTOR)
//{
//
//}
//@-------MuFunction0 中斷入口函數------------@
// CTMA & CTMP 共用
DEFINE_ISR(MuFunction0_ISR, MuFunction0_VECTOR)
{
	_ctmaf = 0;
	_ctmpf = 0;
	SDK_LED_Scan();
}
//@-------MuFunction2 中斷入口函數-----------@
// Multi function1 LVD & EEPROM
DEFINE_ISR(MuFunction1_ISR, MuFunction1_VECTOR)
{

}
//@-------------SPI 中斷入口函數--------------@
DEFINE_ISR(SPI_ISR, SPI_VECTOR)
{

}
//@----------Timebase0 中斷入口函數-----------@
DEFINE_ISR(Timebase0_ISR, Timebase0_VECTOR)
{
	gu8v_UartTxCycle++;
}
//@----------Timebase1 中斷入口函數-----------@
DEFINE_ISR(Timebase1_ISR, Timebase1_VECTOR)
{
	gu8v_HaltTime++;
}
//@-----------UART 中斷入口函數--------------@
//DEFINE_ISR(UART_ISR, UART_VECTOR)
//{
//
//}