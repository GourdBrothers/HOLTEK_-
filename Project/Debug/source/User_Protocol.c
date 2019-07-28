#include "common.h"
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ ׃�����x @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
volatile bit gbv_TxSDKStatus;		// �l��SDK��B�Ę��I,����Ҫ�l�͵ĵط���λfalg����
volatile bit gbv_TxSDKImpedanceStatus;
volatile bit gbv_TxSDKADCStatus;

/*
void fun_TxExample()
{
	// Ҫ�l�͵Ĕ�������gu8v_UartTxBuf[x],0 > N
	gu8v_UartTxBuf[0] = 0x55;
	gu8v_UartTxBuf[1] = 0x11;
 	gu8v_UartTxBuf[2] = 0x22;
 	gu8v_UartTxBuf[3] = 0x33;
 	gu8v_UartTxBuf[4] = 0x44;
	// -----
 	gu8v_UartTxBuf[N]] = 0xAA;
	fun_UartStartTx(N);�_ʼ�l���L�Ȟ�N�Ĕ�����
}
*/
/********************************************************************
Function: �l���迹���y��B
INPUT	:
OUTPUT	:
NOTE	:
********************************************************************/
void fun_TxSDKImpedanceStatus()
{
	gu8v_UartTxBuf[0] = 0xA4;
	gu8v_UartTxBuf[1] = 0x04;
	gu8v_UartTxBuf[2] = (SDKImpedance.Data & 0xFF00 )>>8; 
 	gu8v_UartTxBuf[3] =  SDKImpedance.Data & 0x00FF;			
 	gu8v_UartTxBuf[4] = gu8v_UartTxBuf[0] + gu8v_UartTxBuf[1] + gu8v_UartTxBuf[2] + gu8v_UartTxBuf[3];
	fun_UartStartTx(4);
}
/********************************************************************
Function: ͬ���r�g��λ������
INPUT	:
OUTPUT	:
NOTE	: MCU���Ѻ�ɜy�B�ӷ�������������ȡ��ǰ��λ���r�g
********************************************************************/
void fun_TxSDKWeightStatus()
{
	gu8v_UartTxBuf[0] = 0xAA;
	gu8v_UartTxBuf[1] = 0x02;
	gu8v_UartTxBuf[2] = BHSDKState;
 	gu8v_UartTxBuf[3] = (SDKWeight.DataCurrent & 0xFF00 )>>8;
 	gu8v_UartTxBuf[4] = SDKWeight.DataCurrent & 0x00FF;
 	gu8v_UartTxBuf[5] = (SDKWeight.DataStable & 0xFF00 )>>8;
 	gu8v_UartTxBuf[6] = SDKWeight.DataStable & 0x00FF;
 	gu8v_UartTxBuf[7] = 0x55;
	fun_UartStartTx(7);
}
/********************************************************************
Function: ͬ���r�g��λ������
INPUT	:
OUTPUT	:
NOTE	: MCU���Ѻ�ɜy�B�ӷ�������������ȡ��ǰ��λ���r�g
********************************************************************/
void fun_TxSDKADCStatus()
{
	gu8v_UartTxBuf[0] = 0x55;
	gu8v_UartTxBuf[1] = 0x00;
 	//gu8v_UartTxBuf[2] = (SDKADCFilterData.Current & 0xFF000000 )>>24;
 	gu8v_UartTxBuf[4] = (SDKADCFilterData.Current & 0x00FF0000 )>>16;
 	gu8v_UartTxBuf[3] = (SDKADCFilterData.Current & 0x0000FF00 )>>8;
 	gu8v_UartTxBuf[2] =  SDKADCFilterData.Current & 0x000000FF;
 	gu8v_UartTxBuf[5] = gu8v_UartTxBuf[0] + gu8v_UartTxBuf[1] + gu8v_UartTxBuf[2] + gu8v_UartTxBuf[3] + gu8v_UartTxBuf[4];
	fun_UartStartTx(5);
}
/********************************************************************
Function: uart ����
INPUT	:
OUTPUT	:
NOTE	:
********************************************************************/
#define TIMEBASE0_CYCLE8MS 8
void fun_UserProtocol()
{
	// �������� Time Out�r�g
	if (gu8v_TBRxTimeOutCnt> 200/TIMEBASE0_CYCLE8MS)
	{
		gu8v_TBRxTimeOutCnt = 0;
		lu8v_RxBufoffset = 0;
		lu8v_RxBufLength =0xff;
		gbv_UartRxSuccess  = 0;
	}
	//	UART TX
	//	if(gu8v_UartTxCycle > (100/TIMEBASE0_CYCLE8MS) && !gbv_IsBusyUartTx)	// ���h���붨�r�l�ͣ���ֹ�����l��̫��
	if(!gbv_IsBusyUartTx)
	{
		// gu8v_UartTxCycle = 0;
		if (gbv_TxSDKStatus)
		{
			gbv_TxSDKStatus = 0;
			fun_TxSDKWeightStatus();
		}
		else if (gbv_TxSDKImpedanceStatus)
		{
			gbv_TxSDKImpedanceStatus = 0;
			fun_TxSDKImpedanceStatus();
			BHSDKState = ENTER_IMPEDANCE;
		}
		else if (gbv_TxSDKADCStatus)
		{
			gbv_TxSDKADCStatus = 0;
			fun_TxSDKADCStatus();
		}
	}
	// UART RX
	if (gbv_UartRxSuccess)	// UART RX
	{
		gbv_UartRxSuccess = 0;
		// У��Д�,�ǅf�h�_�J�Ƿ���Ҫ
		// volatile unsigned char i,CheckSum=0;
		// for(i=0; i<gu8v_UartRxBuf[2]-2;i++)
		// {
		// 	CheckSum ^= gu8v_UartRxBuf[i];
		// }
		// ��������
		/*
		if(gu8v_UartRxBuf[0] == RXFRAME_HEADER && gu8v_UartRxBuf[gu8v_UartRxBuf[2]-1]==RXFRAME_END)
		// if(gu8v_UartRxBuf[0] == RXFRAME_HEADER)
		{
			if(CheckSum ==  gu8v_UartRxBuf[gu8v_UartRxBuf[2]-2] )
			{
				// UART RX ��������
				// WIFI STATUS
				if(gu8v_UartRxBuf[1] == CM_WIFI_STATUS  )
				{
					gu8v_WIFIStatus = gu8v_UartRxBuf[3];
					if (gu8v_WIFIStatus == WIFI_STATUS_AIRKSS_PASS)
					{
						gu8v_AIRKISSStatus  = AIRKISSSTATUS_PASS;
					}
					else if (gu8v_WIFIStatus == WIFI_STATUS_AIRKSS_FAIL)
					{
						gbv_TxSDKImpedanceStatus = 1;	// ��Wʧ�������M����W,֪���@��60S�L�ڵ�
					}
				}
				// AIRKISS ACK
				else if(gu8v_UartRxBuf[1] == CM_WIFI_AIRKISS  )
				{
					gbv_TxSDKImpedanceStatus = 0; // �յ�AIRKISS����,������ٰl��
				}
			}
			else
			{
				lu8v_RxBufoffset = 0;
			}
		}
		else
		{
			lu8v_RxBufoffset =0;
		}
		*/
	}
}


