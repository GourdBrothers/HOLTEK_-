#include "common.h"

volatile unsigned char Version[3];
volatile unsigned long temp1;
volatile unsigned long temp2;
void main()
{
	// �Д��Ƿ����늏�λ���߷�������r�µď�λ
	// �������늏�λ��������늏�λ��ʼ������֮����WDT�����ʼ��
	if (_to == 0 || _pdf ==0)
	{
		fun_SysPowerOnInit();
		// ��늺��{��fun_BodyFatScalesSDK_PowerOn()����
		fun_BodyFatScalesSDK_PowerOn();
		// �ГQ���迹ģʽ
		BHSDKState = ENTER_IMPEDANCE;
		// �ГQ��Q��ģʽ
		// BHSDKState = ENTER_WEIGHT_NORMAL;
		// SDKWeight.flag.b.IsNeedTare = 1;			// �������Ĭ�J��0kg
		// �ГQ��˶�ģʽ
		// BHSDKState = ENTER_WEIGHT_CAL;
		fun_UARTPowerOnInit();
//		gbv_TxSDKImpedanceStatus = 0;
//        SDK_LED_PowerOnInit();
//		fun_FW_LEDBuf2HW_LEDBuf();
//		_pac6 = 0;
//		_pa6  = 0;
	}
	else
	{
		// WDT�����λ��ʼ��
		GCC_CLRWDT();
	}
	//��ѭ�h
	while(1)
	{
		GCC_CLRWDT();
		Version[0] = SDKVersion[0];
		Version[1] = SDKVersion[1];
		Version[2] = SDKVersion[2];
		// ��LOOPѭ�h�{�� fun_BodyFatScalesSDK()
		fun_BodyFatScalesSDK();
//		fun_UserProtocol();
//		if (SDKADCFilterData.flag.b.IsReady)
//		{
//			SDKADCFilterData.flag.b.IsReady = 0;
//			gbv_TxSDKADCStatus = 1;
//		}
		// ����gu8v_BodyfatSDKState ���UI������������
		switch (BHSDKState)
		{
			case STATE_WEIGHT_PREPARE:	// �Q�؜ʂ���
				// �ГQ��ENTER_WEIGHT_NORMAL��,ͨ����300ms���ҷQ�؜ʂ�r�g
				break;
			case STATE_WEIGHT_NOLOAD:	// ���d/��ǰ����С���С�Q������
				// fun_DisplayMode_NoLoad();��̎��User UI,�����@ʾ�R�r����SDKWeight.DataCurrent
				break;
			case STATE_WEIGHT_LOADUP:	// ���ϷQ����/�i����B�¼��d���i����,������0�c׃��>��С�Q������
				// fun_DisplayMode_LoadUp();��̎��User UI,�����@ʾ�R�r����SDKWeight.DataCurrent
				break;
			case STATE_WEIGHT_LOADOK:	// ���һ�ηQ�؜y��
	            // fun_DisplayMode_LoadOk();��̎��User UI,�����_ʼ�W�q��������SDKWeight.DataState��
				break;
			case STATE_WEIGHT_LOADFIX:	// ���һ�ηQ�؜y�������������]�н��i
				// fun_DisplayMode_LoadFix();��̎��User UI,,�����_ʼ�W�q��������SDKWeight.DataState��
				break;
			case STATE_WEIGHT_LOADDOWN:	// �³ӄ���
	            // fun_DisplayMode_LoadDown();��̎��User UI,,�����@ʾ�i��SDKWeight.DataState��
				break;
			case STATE_WEIGHT_OVERLOAD:	// ����,��ǰ����������Q������
				// fun_DisplayMode_OverLoad();��̎��User UI,,�����@ʾ-OL-��
				break;
			case STATE_IMPEDANCE_REFERENCE1:// �������y�������1
			case STATE_IMPEDANCE_REFERENCE2:// �������y�������2
			case STATE_IMPEDANCE_CHECKBODY: // �Д��Ƿ������w
			case STATE_IMPEDANCE_RX:		// �������y���y�迹
				// fun_DisplayMode_Impedanceing();��̎��User UI,,������----/oooo��ʾ�迹�y����
				break;
			case STATE_IMPEDANCE_FINISH:	// �迹���y�Y��,�˕r�����xȡgu16v_CurrentImpedance_ohm
				// fun_DisplayMode_ImpedanceFinish();
				
				gbv_TxSDKImpedanceStatus = 1;
				fun_HEX2BCD4(SDKImpedance.Data);
				temp2 = SDKImpedance.Data;
				fun_FW_LEDBuf2HW_LEDBuf();
				fun_TxSDKImpedanceStatus();
				BHSDKState = ENTER_IMPEDANCE;
				
			    break;
			case STATE_AUTOON_FASTMODE:		// ����ADC�Ԅ��ϷQ�Д�
			case STATE_AUTOON_SLOWMODE:		// ����ADC�Ԅ��ϷQ�Д�
				// ͨ���@���r��o�κ�UI
				break;
			case STATE_AUTOON_PASS:			// �Ԅ��ϷQOK
				// �˕r�����c���@ʾ,���ГQ����ͨ�Q��ģʽ�M��MCU����������
				// BHSDKState = ENTER_WEIGHT_NORMAL;
				break;
			case STATE_AUTOON_FAIL:			// �Ԅ��ϳ�ʧ��,�˕rՈ�^�m׌ MCU �M��HALT��B
				fun_BodyFatScalesSDK_PowerDown();
				GCC_HALT();
				break;
			case STATE_WEIGHT_CAL0:	// ���ژ˶����c
				// fun_DisplayMode_CAL0();��̎��User UI,,������ʾCAL 0kg
				break;
			case STATE_WEIGHT_CAL1:	// ���ژ˶���1�c
				// fun_DisplayMode_CAL1();��̎��User UI,,������ʾCAL 50kg
				break;
			case STATE_WEIGHT_CAL2:	// ���ژ˶���2�c
				// fun_DisplayMode_CAL2();��̎��User UI,,������ʾCAL 100kg
				break;
			case STATE_WEIGHT_CAL3:	// ���ژ˶���3�c
				// fun_DisplayMode_CAL3();��̎��User UI,,������ʾCAL 150kg
				break;
			case STATE_WEIGHT_CALPASS:	// �˶��ɹ�
				// fun_DisplayMode_CALPASS();��̎��User UI,,������ʾPASS
				break;
			case STATE_WEIGHT_CALFAIL:	// �˶�ʧ����
				// fun_DisplayMode_CALFAIL();��̎��User UI,,������ʾFIAS
				break;
			default:
				break;
		}
	}
}