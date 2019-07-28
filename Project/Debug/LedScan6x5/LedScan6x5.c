asm (" message' **************************************************** ' ");
asm (" message' *       2018 BY BEST HEALTH ELECTRONIC INC         * ' ");
asm (" message' *__________________________________________________* ' ");
asm (" message' *        SDK  NAME  :      LedScan6x5.c   	       * ' ");
asm (" message' *   Compiler   Ver. :      V3.53                   * ' ");
asm (" message' *   IDE3000    Ver. :      V7.97                   * ' ");
asm (" message' *   RELEASE    Ver. :      1.0.1                   * ' ");
asm (" message' *   RELEASE   DATA  :     2018/07/30               * ' ");
asm (" message' *__________________________________________________* ' ");
asm (" message' *    MCU / CFG Ver. :      None                    * ' ");
asm (" message' **************************************************** ' ");

#include "LedScan6x5.h"
#include "LedScan6x5_API.h"

unsigned char gu8v_LED_BCD_Buffer[4];

#define SEG_MAP(x)		(1 << x)	// 段碼位置

#define      a  	SEG_MAP(0)
#define      b  	SEG_MAP(1)
#define      c   	SEG_MAP(2)
#define      d   	SEG_MAP(3)
#define      e   	SEG_MAP(4)
#define      f   	SEG_MAP(5)
#define      g   	SEG_MAP(6)
#define      h   	SEG_MAP(7)
const unsigned char DisplayNumber_Table[]=
{
	a + b + c + d + e + f,						// Displays "0"  	// 0
	b + c,										// Displays "1"  	// 1
	a + b + d + e + g,							// Displays "2"  	// 2
	a + b + c + d + g,							// Displays "3"  	// 3
	b + c + f + g,								// Displays "4"  	// 4
	a + c + d + f +g,							// Displays "5"  	// 5
	a + c + d + e + f + g,						// Displays "6"  	// 6
	a + b + c,									// Displays "7"  	// 7
	a + b + c + d + e + f + g,					// Displays "8"  	// 8
	a + b + c + d + f + g,						// Displays "9"  	// 9

	a + b + c + e + f + g,						// Displays "A"  	// 10
	c + d + e + f + g,							// Displays "B"  	// 11
	a + d + e + f,								// Displays "C"  	// 12
	b + c + d + e + g,							// Displays "D"  	// 13
	a + d + e + f + g,							// Displays "E"  	// 14
	a + e + f + g,								// Displays "F"  	// 15
	a + c + d + e + f,							// Displays "G"  	// 16
	b + c + e + f + g,							// Displays "H"  	// 17
	e + f,										// Displays "I"  	// 18
	b + c + d + e,								// Displays "J"  	// 19
	d + e + f,									// Displays "L"  	// 20
	a + b + c + e + f,							// Displays "N"  	// 21
	c + e + g,									// Displays "n"  	// 22
	c + d + e + g,								// Displays "o"  	// 23
	a + b + e + f + g,							// Displays "P"  	// 24
	a + b + c + f + g,							// Displays "Q"  	// 25
	e + g,										// Displays "r"  	// 26
	b + c + d + e + f,							// Displays "U" 	// 27
	c + d + e,									// Displays "u"   	// 28
	b + c + d + f + g,							// Displays "Y"   	// 29
	g,											// Displays "-"  	// 30
	b,											// Displays "'"   	// 31
	0,											// Displays " "  	// 32
	a + b + c + d + e + f + g + h				// Displays "8."  	// 33
};

SDK_LED_t LED_HW_MAP;
SDK_LED_t LED_FW_Map;
volatile unsigned char LEDScanCnt;

/**************************************
Function: LED 上電初始化
INPUT	:
OUTPUT	:
NOTE	: 應該在IO初始化之後，防止被改寫
***************************************/
void SDK_LED_PowerOnInit(void)
{
    SET_SEG0_OFF();
    SET_SEG1_OFF();
    SET_SEG2_OFF();
    SET_SEG3_OFF();
    SET_SEG4_OFF();
    SET_SEG5_OFF();
    LEDScanCnt = 0;

    gu8v_LED_BCD_Buffer[3] = CHAR_1;
    gu8v_LED_BCD_Buffer[2] = CHAR_2;
    gu8v_LED_BCD_Buffer[1] = CHAR_3;
    gu8v_LED_BCD_Buffer[0] = CHAR_4;
}
/**************************************
Function: 將FW_buf的對應值 輪詢掃描更新到LED上
INPUT	:
OUTPUT	:
NOTE	: 放置在time中斷，中斷時間建議2ms
***************************************/
void SDK_LED_Scan(void)
{
    SET_SEG0_OFF();
    SET_SEG1_OFF();
    SET_SEG2_OFF();
    SET_SEG3_OFF();
    SET_SEG4_OFF();
    SET_SEG5_OFF();
    // LEDScanDuty = 0;
    switch (LEDScanCnt)
    {
        case 0:
            if (LED_HW_MAP.Buf0.bits.BIT1) { SET_SEG1_ON();} else { SET_SEG1_OFF();}
            if (LED_HW_MAP.Buf0.bits.BIT2) { SET_SEG2_ON();} else { SET_SEG2_OFF();}
            if (LED_HW_MAP.Buf0.bits.BIT3) { SET_SEG3_ON();} else { SET_SEG3_OFF();}
            if (LED_HW_MAP.Buf0.bits.BIT4) { SET_SEG4_ON();} else { SET_SEG4_OFF();}
            if (LED_HW_MAP.Buf0.bits.BIT5) { SET_SEG5_ON();} else { SET_SEG5_OFF();}
            SET_COM0_ON();
            break;
        case 1:
            if (LED_HW_MAP.Buf1.bits.BIT0) { SET_SEG0_ON();} else { SET_SEG0_OFF();}
            if (LED_HW_MAP.Buf1.bits.BIT2) { SET_SEG2_ON();} else { SET_SEG2_OFF();}
            if (LED_HW_MAP.Buf1.bits.BIT3) { SET_SEG3_ON();} else { SET_SEG3_OFF();}
            if (LED_HW_MAP.Buf1.bits.BIT4) { SET_SEG4_ON();} else { SET_SEG4_OFF();}
            if (LED_HW_MAP.Buf1.bits.BIT5) { SET_SEG5_ON();} else { SET_SEG5_OFF();}
            SET_COM1_ON();
            break;
        case 2:
            if (LED_HW_MAP.Buf2.bits.BIT0) { SET_SEG0_ON();} else { SET_SEG0_OFF();}
            if (LED_HW_MAP.Buf2.bits.BIT1) { SET_SEG1_ON();} else { SET_SEG1_OFF();}
            if (LED_HW_MAP.Buf2.bits.BIT3) { SET_SEG3_ON();} else { SET_SEG3_OFF();}
            if (LED_HW_MAP.Buf2.bits.BIT4) { SET_SEG4_ON();} else { SET_SEG4_OFF();}
            if (LED_HW_MAP.Buf2.bits.BIT5) { SET_SEG5_ON();} else { SET_SEG5_OFF();}
            SET_COM2_ON();
            break;
        case 3:
            if (LED_HW_MAP.Buf3.bits.BIT0) { SET_SEG0_ON();} else { SET_SEG0_OFF();}
            if (LED_HW_MAP.Buf3.bits.BIT1) { SET_SEG1_ON();} else { SET_SEG1_OFF();}
            if (LED_HW_MAP.Buf3.bits.BIT2) { SET_SEG2_ON();} else { SET_SEG2_OFF();}
            if (LED_HW_MAP.Buf3.bits.BIT4) { SET_SEG4_ON();} else { SET_SEG4_OFF();}
            if (LED_HW_MAP.Buf3.bits.BIT5) { SET_SEG5_ON();} else { SET_SEG5_OFF();}
            SET_COM3_ON();
            break;
        case 4:
            if (LED_HW_MAP.Buf4.bits.BIT0) { SET_SEG0_ON();} else { SET_SEG0_OFF();}
            if (LED_HW_MAP.Buf4.bits.BIT1) { SET_SEG1_ON();} else { SET_SEG1_OFF();}
            if (LED_HW_MAP.Buf4.bits.BIT2) { SET_SEG2_ON();} else { SET_SEG2_OFF();}
            if (LED_HW_MAP.Buf4.bits.BIT3) { SET_SEG3_ON();} else { SET_SEG3_OFF();}
            if (LED_HW_MAP.Buf4.bits.BIT5) { SET_SEG5_ON();} else { SET_SEG5_OFF();}
            SET_COM4_ON();
            break;
        case 5:
            if (LED_HW_MAP.Buf5.bits.BIT0) { SET_SEG0_ON();} else { SET_SEG0_OFF();}
            if (LED_HW_MAP.Buf5.bits.BIT1) { SET_SEG1_ON();} else { SET_SEG1_OFF();}
            if (LED_HW_MAP.Buf5.bits.BIT2) { SET_SEG2_ON();} else { SET_SEG2_OFF();}
            if (LED_HW_MAP.Buf5.bits.BIT3) { SET_SEG3_ON();} else { SET_SEG3_OFF();}
            if (LED_HW_MAP.Buf5.bits.BIT4) { SET_SEG4_ON();} else { SET_SEG4_OFF();}
            SET_COM5_ON();
            break;
        default:
            break;
    }
	LEDScanCnt++;
	if (LEDScanCnt > 5)
	{
	   LEDScanCnt = 0;
	}
}


void fun_FW_LEDBuf2HW_LEDBuf()
{
    // 將要顯示的值查表后傳遞給FW_buf
    LED_FW_Map.Buf0.byte = DisplayNumber_Table[gu8v_LED_BCD_Buffer[3]];
    LED_FW_Map.Buf1.byte = DisplayNumber_Table[gu8v_LED_BCD_Buffer[2]];
    LED_FW_Map.Buf2.byte = DisplayNumber_Table[gu8v_LED_BCD_Buffer[1]];
    LED_FW_Map.Buf3.byte = DisplayNumber_Table[gu8v_LED_BCD_Buffer[0]];

    // 將FW_buf  映射到 HW_buf
    LED_HW_MAP.Buf0.byte = 0;
    LED_HW_MAP.Buf1.byte = 0;
    LED_HW_MAP.Buf2.byte = 0;
    LED_HW_MAP.Buf3.byte = 0;
    LED_HW_MAP.Buf4.byte = 0;
    LED_HW_MAP.Buf5.byte = 0;

    if (LED_FW_Map.Buf0.bits.BIT0) { SEG0_A = 1;}
    if (LED_FW_Map.Buf0.bits.BIT1) { SEG0_B = 1;}
    if (LED_FW_Map.Buf0.bits.BIT2) { SEG0_C = 1;}
    if (LED_FW_Map.Buf0.bits.BIT3) { SEG0_D = 1;}
    if (LED_FW_Map.Buf0.bits.BIT4) { SEG0_E = 1;}
    // if (LED_FW_Map.Buf0.bits.BIT5) { SEG0_F = 1;}
    if (LED_FW_Map.Buf0.bits.BIT6) { SEG0_G = 1;}
    if (LED_FW_Map.Buf0.bits.BIT7) { SIGN_KG = 1;}

    if (LED_FW_Map.Buf1.bits.BIT0) { SEG1_A = 1;}
    if (LED_FW_Map.Buf1.bits.BIT1) { SEG1_B = 1;}
    if (LED_FW_Map.Buf1.bits.BIT2) { SEG1_C = 1;}
    if (LED_FW_Map.Buf1.bits.BIT3) { SEG1_D = 1;}
    if (LED_FW_Map.Buf1.bits.BIT4) { SEG1_E = 1;}
    if (LED_FW_Map.Buf1.bits.BIT5) { SEG1_F = 1;}
    if (LED_FW_Map.Buf1.bits.BIT6) { SEG1_G = 1;}
    if (LED_FW_Map.Buf1.bits.BIT7) { SIGN_BLE = 1;}

    if (LED_FW_Map.Buf2.bits.BIT0) { SEG2_A = 1;}
    if (LED_FW_Map.Buf2.bits.BIT1) { SEG2_B = 1;}
    if (LED_FW_Map.Buf2.bits.BIT2) { SEG2_C = 1;}
    if (LED_FW_Map.Buf2.bits.BIT3) { SEG2_D = 1;}
    if (LED_FW_Map.Buf2.bits.BIT4) { SEG2_E = 1;}
    if (LED_FW_Map.Buf2.bits.BIT5) { SEG2_F = 1;}
    if (LED_FW_Map.Buf2.bits.BIT6) { SEG2_G = 1;}
    if (LED_FW_Map.Buf2.bits.BIT7) { SIGN_JIN = 1;}

    if (LED_FW_Map.Buf3.bits.BIT0) { SEG3_A = 1;}
    if (LED_FW_Map.Buf3.bits.BIT1) { SEG3_B = 1;}
    if (LED_FW_Map.Buf3.bits.BIT2) { SEG3_C = 1;}
    if (LED_FW_Map.Buf3.bits.BIT3) { SEG3_D = 1;}
    if (LED_FW_Map.Buf3.bits.BIT4) { SEG3_E = 1;}
    if (LED_FW_Map.Buf3.bits.BIT5) { SEG3_F = 1;}
    if (LED_FW_Map.Buf3.bits.BIT6) { SEG3_G = 1;}
    // if (LED_FW_Map.Buf3.bits.BIT7) { SEG3_B = 1;}
}


/********************************************************************
Function: HEX 轉換為4位BCD碼顯示
IO_IS_INPUT	:
OUTPUT	: gu8v_LED_BCD_Buffer[4] High → gu8v_LED_BCD_Buffer[4] Low
NOTE	: 最大顯示9999,超過萬位以上不顯示,比如10000,顯示0000,54321顯示4321
NOTE	: 此顯示用於LED秤上,通常有一位小數點,所以小於10,比如9顯示09,十位0會顯示
********************************************************************/
void fun_HEX2BCD4(unsigned int DisplayNum)
{
	unsigned char i,j;
	if (DisplayNum < 100)
	{
		gu8v_LED_BCD_Buffer[2] = CHAR_OFF;
		gu8v_LED_BCD_Buffer[3] = CHAR_OFF;
		j = 2;
	}
	else if (DisplayNum < 1000)
	{
		gu8v_LED_BCD_Buffer[3] = CHAR_OFF;
		j = 3;
	}
	else
	{
		j = 4 ;
	}
	for(i=0;i<j;)
	{
		gu8v_LED_BCD_Buffer[i]=DisplayNum%10;
		DisplayNum/=10;
		i++;
	}
}