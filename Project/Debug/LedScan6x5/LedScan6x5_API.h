#ifndef _LEDSCAN6X5_API_H_
#define _LEDSCAN6X5_API_H_

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// ======================================================@
//              SDK接口  函數接口                         @
// ======================================================@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
void SDK_LED_PowerOnInit(void);     // 上電初始化
void SDK_LED_Scan(void);            // 定時輪詢，建議2ms
void fun_FW_LEDBuf2HW_LEDBuf();     // 將要顯示的值更新
void fun_HEX2BCD4(unsigned int DisplayNum);
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// ======================================================@
//              LED符號  LED編號對應表                    @
// ======================================================@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
#include "BH66F2652.h"
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// ====================================================================================@
//                                LED IO config                                        @
// ====================================================================================@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// Port data
#define PINSEG_D0     _pa0
#define PINSEG_D1     _pa1
#define PINSEG_D2     _pa7
#define PINSEG_D3     _pa3
#define PINSEG_D4     _pa4
#define PINSEG_D5     _pa5
// port input or output
#define PINSEG_C0     _pac0
#define PINSEG_C1     _pac1
#define PINSEG_C2     _pac7
#define PINSEG_C3     _pac3
#define PINSEG_C4     _pac4
#define PINSEG_C5     _pac5
// port pump high
#define PINSEG_P0     _papu0
#define PINSEG_P1     _papu1
#define PINSEG_P2     _papu7
#define PINSEG_P3     _papu3
#define PINSEG_P4     _papu4
#define PINSEG_P5     _papu5
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// ====================================================================================@
//                                LED map to IO map                                    @
// ====================================================================================@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// 比如LED 對應的IO為，負端接SEG4，正端接SEG5，則#define MAP_LED1    LED_HW_MAP.Buf4.bits.BIT5
#define MAP_LED1    LED_HW_MAP.Buf4.bits.BIT5
#define MAP_LED2    LED_HW_MAP.Buf0.bits.BIT1
#define MAP_LED3    LED_HW_MAP.Buf1.bits.BIT0
#define MAP_LED4    LED_HW_MAP.Buf2.bits.BIT0
#define MAP_LED5    LED_HW_MAP.Buf3.bits.BIT0
#define MAP_LED6    LED_HW_MAP.Buf5.bits.BIT3
#define MAP_LED7    LED_HW_MAP.Buf5.bits.BIT4
#define MAP_LED8    LED_HW_MAP.Buf0.bits.BIT2
#define MAP_LED9    LED_HW_MAP.Buf5.bits.BIT0
#define MAP_LED10   LED_HW_MAP.Buf5.bits.BIT1
#define MAP_LED11   LED_HW_MAP.Buf5.bits.BIT2
#define MAP_LED12   LED_HW_MAP.Buf1.bits.BIT2
#define MAP_LED13   LED_HW_MAP.Buf2.bits.BIT1
#define MAP_LED14   LED_HW_MAP.Buf3.bits.BIT1
#define MAP_LED15   LED_HW_MAP.Buf4.bits.BIT0
#define MAP_LED16   LED_HW_MAP.Buf4.bits.BIT1
#define MAP_LED17   LED_HW_MAP.Buf4.bits.BIT2
#define MAP_LED18   LED_HW_MAP.Buf4.bits.BIT3
#define MAP_LED19   LED_HW_MAP.Buf0.bits.BIT5
#define MAP_LED20   LED_HW_MAP.Buf1.bits.BIT5
#define MAP_LED21   LED_HW_MAP.Buf0.bits.BIT3
#define MAP_LED22   LED_HW_MAP.Buf1.bits.BIT3
#define MAP_LED23   LED_HW_MAP.Buf2.bits.BIT5
#define MAP_LED24   LED_HW_MAP.Buf2.bits.BIT3
#define MAP_LED25   LED_HW_MAP.Buf3.bits.BIT5
#define MAP_LED26   LED_HW_MAP.Buf3.bits.BIT2
#define MAP_LED27   LED_HW_MAP.Buf0.bits.BIT4
#define MAP_LED28   LED_HW_MAP.Buf1.bits.BIT4
#define MAP_LED29   LED_HW_MAP.Buf2.bits.BIT4
#define MAP_LED30   LED_HW_MAP.Buf3.bits.BIT4
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// ====================================================================================@
//                            7段數碼管 map to LED map                                  @
// ====================================================================================@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//   __		A
//  |  |  F	  B
//   __		G
//  |  |  E   C
//   __  	D

#define SEG0_A      MAP_LED2
#define SEG0_B      MAP_LED8
#define SEG0_C      MAP_LED21
#define SEG0_D      MAP_LED27
#define SEG0_E      MAP_LED19
// #define SEG0_F      MAP_LED
#define SEG0_G      MAP_LED15

#define SEG1_A      MAP_LED3
#define SEG1_B      MAP_LED12
#define SEG1_C      MAP_LED22
#define SEG1_D      MAP_LED28
#define SEG1_E      MAP_LED20
#define SEG1_F      MAP_LED9
#define SEG1_G      MAP_LED16

#define SEG2_A      MAP_LED4
#define SEG2_B      MAP_LED13
#define SEG2_C      MAP_LED24
#define SEG2_D      MAP_LED29
#define SEG2_E      MAP_LED23
#define SEG2_F      MAP_LED10
#define SEG2_G      MAP_LED17

#define SEG3_A      MAP_LED5
#define SEG3_B      MAP_LED14
#define SEG3_C      MAP_LED26
#define SEG3_D      MAP_LED30
#define SEG3_E      MAP_LED25
#define SEG3_F      MAP_LED11
#define SEG3_G      MAP_LED18

#define SIGN_KG     MAP_LED1
#define SIGN_BLE    MAP_LED6
#define SIGN_JIN    MAP_LED7

#endif