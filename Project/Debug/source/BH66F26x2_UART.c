#include "common.h"



volatile unsigned char 	gu8v_UartTxBuf[UART_LENGTH_TX];
volatile unsigned char 	gu8v_UartRxBuf[UART_LENGTH_RX];
volatile unsigned char  lu8v_TxBufoffset;   // TX ƫ����
volatile unsigned char  lu8v_TxBufLength;   // TX ���L��
volatile unsigned char  gu8v_UartTxCycle;   // TX �l���L��
volatile bit gbv_IsBusyUartTx;              // TX is busy

volatile unsigned char  lu8v_RxBufoffset;   // RX ƫ����
volatile unsigned char  lu8v_RxBufLength;   // RX ���L��
volatile unsigned char  gu8v_TBRxTimeOutCnt;// RX ��timeout
volatile bit gbv_UartRxSuccess;             // Rx is ok,user can process the rx buf data
/********************************************************************
Function: Uart��ʼ������
INPUT	:
OUTPUT	:
NOTE	:
********************************************************************/
void fun_UARTPowerOnInit()
{
    // ������ݔ��ʽ�O��
	SET_UART_Format_D8_P0_S1();
    // �������O��
	SET_UART_BAUTRATE_9600();
	SET_UART_ADDRESS_DISABLE();
	SET_UART_RECEIVER_IE_ENABLE();
	SET_UART_TRANSMITTER_IE_ENABLE();
	SET_UART_TRANSMITTER_EMPTY_ENABLE();
	SET_UART_ENABLE();
	// UART0 IO
	SET_UART_PIN();
}
///********************************************************************
//Function: Uart�����l�ͺͽ����Д��ӳ���
//INPUT	:
//OUTPUT:
//NOTE	:
//********************************************************************/
DEFINE_ISR(UART_ISR, 0x028)
{
	// ��żУ�����
//	if (_perr0)
//	{
//		_acc = _usr;
//		_acc = _txr_rxr;
//	}
//	 �������Ŵ���
	if (_nf)
	{
		_acc = _usr;
		_acc = _txr_rxr;
		lu8v_RxBufoffset = 0;
	}
	// ֡����
	if (_ferr)
	{
		_acc = _usr;
		_acc = _txr_rxr;
		lu8v_RxBufoffset = 0;
	}
	// �������
	if (_oerr)
	{
		_acc = _usr;
		_acc = _txr_rxr;
		lu8v_RxBufoffset = 0;
	}
	// ��������
	if (_txif && gbv_IsBusyUartTx)
	{
		if (lu8v_TxBufoffset <= lu8v_TxBufLength)
		{
			_txr_rxr = gu8v_UartTxBuf[lu8v_TxBufoffset];
			_pa6 = ~_pa6;
		}
		else
		{
            if (_tidle)
            {
                gbv_IsBusyUartTx = 0;
            }
		}
		lu8v_TxBufoffset++;
	}
	// ��������
	if (_rxif)
	{
        gu8v_UartRxBuf[lu8v_RxBufoffset] = _txr_rxr;
		gu8v_TBRxTimeOutCnt = 0;
        lu8v_RxBufoffset++;
        // �Ñ���Ҫ�ڴˌ�Rx�����L��
        // 1 �̶��L��,�t�ڳ�ʼ���ĕr���ʼ��Ԓlu8v_RxBufLength
        // 2 �f�h�Ԏ��L����Ϣ
        if (lu8v_RxBufoffset == 3)
        {
        	lu8v_RxBufLength = gu8v_UartRxBuf[2];
        }
        if (lu8v_RxBufoffset >= lu8v_RxBufLength)
        {
            lu8v_RxBufoffset = 0;
            lu8v_RxBufLength = 0xff;
            gbv_UartRxSuccess  = 1;
        }
	}
}

/********************************************************************
Function: uart�l���_ʼ
INPUT	:
OUTPUT	:
NOTE	:
********************************************************************/
void  fun_UartStartTx( unsigned char TxLength)
{
	lu8v_TxBufLength = TxLength;
	// Start TX
	gbv_IsBusyUartTx = 1; // uart æµ
	lu8v_TxBufoffset = 1; // ���0�ѽ�ֱ�Ӱl����
	_acc = _usr;
	_txr_rxr = gu8v_UartTxBuf[0];
}