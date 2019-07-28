//___________________________________________________________________
//___________________________________________________________________
//  Copyright : 2015 BY HOLTEK SEMICONDUCTOR INC
//  File Name : UART.c
// Description: UART收發
//   Customer : Holtek Demo Code
//Targer Board: None
//     Note   :
//___________________________________________________________________
//___________________________________________________________________
#ifndef _UART_H_
#define _UART_H_

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ 共用變量 @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
extern volatile bit gbv_TxSDKStatus;
extern volatile bit gbv_TxSDKImpedanceStatus;
extern volatile bit gbv_TxSDKADCStatus;


//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ 共用函數 @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

void fun_UserProtocol();




#endif
