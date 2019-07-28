#ifndef _LEDSCAN6X5_H_
#define _LEDSCAN6X5_H_



#define SET_COM0_ON()   {PINSEG_D0 = 0; PINSEG_C0 = 0;}
#define SET_COM1_ON()   {PINSEG_D1 = 0; PINSEG_C1 = 0;}
#define SET_COM2_ON()   {PINSEG_D2 = 0; PINSEG_C2 = 0;}
#define SET_COM3_ON()   {PINSEG_D3 = 0; PINSEG_C3 = 0;}
#define SET_COM4_ON()   {PINSEG_D4 = 0; PINSEG_C4 = 0;}
#define SET_COM5_ON()   {PINSEG_D5 = 0; PINSEG_C5 = 0;}

#define SET_SEG0_ON()   { PINSEG_D0 = 1; PINSEG_C0 = 0;}
#define SET_SEG0_OFF()  { PINSEG_P0 = 0; PINSEG_C0 = 1;}
#define SET_SEG1_ON()   { PINSEG_D1 = 1; PINSEG_C1 = 0;}
#define SET_SEG1_OFF()  { PINSEG_P1 = 0; PINSEG_C1 = 1;}
#define SET_SEG2_ON()   { PINSEG_D2 = 1; PINSEG_C2 = 0;}
#define SET_SEG2_OFF()  { PINSEG_P2 = 0; PINSEG_C2 = 1;}
#define SET_SEG3_ON()   { PINSEG_D3 = 1; PINSEG_C3 = 0;}
#define SET_SEG3_OFF()  { PINSEG_P3 = 0; PINSEG_C3 = 1;}
#define SET_SEG4_ON()   { PINSEG_D4 = 1; PINSEG_C4 = 0;}
#define SET_SEG4_OFF()  { PINSEG_P4 = 0; PINSEG_C4 = 1;}
#define SET_SEG5_ON()   { PINSEG_D5 = 1; PINSEG_C5 = 0;}
#define SET_SEG5_OFF()  { PINSEG_P5 = 0; PINSEG_C5 = 1;}
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// ======================================================@
//              LED符號  LED編號對應表                    @
// ======================================================@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// LEDScan
typedef struct
{
    union {
        struct
        {
            unsigned char BIT0 : 1;
            unsigned char BIT1 : 1;
            unsigned char BIT2 : 1;
            unsigned char BIT3 : 1;
            unsigned char BIT4 : 1;
            unsigned char BIT5 : 1;
            unsigned char BIT6 : 1;
            unsigned char BIT7 : 1;
        } bits;
        unsigned char byte;
    } Buf0;
    union {
        struct
        {
            unsigned char BIT0 : 1;
            unsigned char BIT1 : 1;
            unsigned char BIT2 : 1;
            unsigned char BIT3 : 1;
            unsigned char BIT4 : 1;
            unsigned char BIT5 : 1;
            unsigned char BIT6 : 1;
            unsigned char BIT7 : 1;
        } bits;
        unsigned char byte;
    } Buf1;
    union {
        struct
        {
            unsigned char BIT0 : 1;
            unsigned char BIT1 : 1;
            unsigned char BIT2 : 1;
            unsigned char BIT3 : 1;
            unsigned char BIT4 : 1;
            unsigned char BIT5 : 1;
            unsigned char BIT6 : 1;
            unsigned char BIT7 : 1;
        } bits;
        unsigned char byte;
    } Buf2;
    union {
        struct
        {
            unsigned char BIT0 : 1;
            unsigned char BIT1 : 1;
            unsigned char BIT2 : 1;
            unsigned char BIT3 : 1;
            unsigned char BIT4 : 1;
            unsigned char BIT5 : 1;
            unsigned char BIT6 : 1;
            unsigned char BIT7 : 1;
        } bits;
        unsigned char byte;
    } Buf3;
    union {
        struct
        {
            unsigned char BIT0 : 1;
            unsigned char BIT1 : 1;
            unsigned char BIT2 : 1;
            unsigned char BIT3 : 1;
            unsigned char BIT4 : 1;
            unsigned char BIT5 : 1;
            unsigned char BIT6 : 1;
            unsigned char BIT7 : 1;
        } bits;
        unsigned char byte;
    } Buf4;
    union {
        struct
        {
            unsigned char BIT0 : 1;
            unsigned char BIT1 : 1;
            unsigned char BIT2 : 1;
            unsigned char BIT3 : 1;
            unsigned char BIT4 : 1;
            unsigned char BIT5 : 1;
            unsigned char BIT6 : 1;
            unsigned char BIT7 : 1;
        } bits;
        unsigned char byte;
    } Buf5;
} SDK_LED_t;

#define CHAR_0	   0
#define CHAR_1	   1
#define CHAR_2	   2
#define CHAR_3	   3
#define CHAR_4	   4
#define CHAR_5	   5
#define CHAR_6	   6
#define CHAR_7	   7
#define CHAR_8	   8
#define CHAR_9	   9
#define CHAR_A	  10
#define CHAR_B	  11
#define CHAR_C	  12
#define CHAR_D	  13
#define CHAR_E	  14
#define CHAR_F	  15
#define CHAR_G	  16
#define CHAR_H	  17
#define CHAR_I	  18
#define CHAR_J	  19
#define CHAR_L	  20
#define CHAR_N	  21
#define CHAR_n	  22
#define CHAR_o	  23
#define CHAR_P	  24
#define CHAR_Q	  25
#define CHAR_r    26
#define CHAR_U	  27
#define CHAR_u	  28
#define CHAR_Y	  29
#define CHAR__	  30
#define CHAR_	  31
#define CHAR_OFF  32
#define CHAR_ALL  33




#endif