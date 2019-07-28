#include "common.h"

volatile unsigned char Version[3];
volatile unsigned long temp1;
volatile unsigned long temp2;
void main()
{
	// 判斷是否為上電復位或者非正常情況下的復位
	// 如果是上電復位，執行上電復位初始化，反之執行WDT溢出初始化
	if (_to == 0 || _pdf ==0)
	{
		fun_SysPowerOnInit();
		// 上電后調用fun_BodyFatScalesSDK_PowerOn()函數
		fun_BodyFatScalesSDK_PowerOn();
		// 切換為阻抗模式
		BHSDKState = ENTER_IMPEDANCE;
		// 切換為稱重模式
		// BHSDKState = ENTER_WEIGHT_NORMAL;
		// SDKWeight.flag.b.IsNeedTare = 1;			// 上電重量默認為0kg
		// 切換為標定模式
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
		// WDT溢出復位初始化
		GCC_CLRWDT();
	}
	//主循環
	while(1)
	{
		GCC_CLRWDT();
		Version[0] = SDKVersion[0];
		Version[1] = SDKVersion[1];
		Version[2] = SDKVersion[2];
		// 主LOOP循環調用 fun_BodyFatScalesSDK()
		fun_BodyFatScalesSDK();
//		fun_UserProtocol();
//		if (SDKADCFilterData.flag.b.IsReady)
//		{
//			SDKADCFilterData.flag.b.IsReady = 0;
//			gbv_TxSDKADCStatus = 1;
//		}
		// 依據gu8v_BodyfatSDKState 完成UI或者其他動作
		switch (BHSDKState)
		{
			case STATE_WEIGHT_PREPARE:	// 稱重準備中
				// 切換為ENTER_WEIGHT_NORMAL后,通常有300ms左右稱重準備時間
				break;
			case STATE_WEIGHT_NOLOAD:	// 空載/當前重量小於最小稱重重量
				// fun_DisplayMode_NoLoad();此處寫User UI,比如顯示臨時重量SDKWeight.DataCurrent
				break;
			case STATE_WEIGHT_LOADUP:	// 有上稱動作/鎖定狀態下加載解鎖重量,重量由0點變成>最小稱重重量
				// fun_DisplayMode_LoadUp();此處寫User UI,比如顯示臨時重量SDKWeight.DataCurrent
				break;
			case STATE_WEIGHT_LOADOK:	// 完成一次稱重測量
	            // fun_DisplayMode_LoadOk();此處寫User UI,比如開始閃爍穩定重量SDKWeight.DataState等
				break;
			case STATE_WEIGHT_LOADFIX:	// 完成一次稱重測量后重量穩定沒有解鎖
				// fun_DisplayMode_LoadFix();此處寫User UI,,比如開始閃爍穩定重量SDKWeight.DataState等
				break;
			case STATE_WEIGHT_LOADDOWN:	// 下秤動作
	            // fun_DisplayMode_LoadDown();此處寫User UI,,比如顯示鎖定SDKWeight.DataState等
				break;
			case STATE_WEIGHT_OVERLOAD:	// 超重,當前重量大於最大稱重重量
				// fun_DisplayMode_OverLoad();此處寫User UI,,比如顯示-OL-等
				break;
			case STATE_IMPEDANCE_REFERENCE1:// 正在量測參考電阻1
			case STATE_IMPEDANCE_REFERENCE2:// 正在量測參考電阻2
			case STATE_IMPEDANCE_CHECKBODY: // 判斷是否有人體
			case STATE_IMPEDANCE_RX:		// 正在量測待測阻抗
				// fun_DisplayMode_Impedanceing();此處寫User UI,,比如跑----/oooo提示阻抗測量中
				break;
			case STATE_IMPEDANCE_FINISH:	// 阻抗量測結束,此時可以讀取gu16v_CurrentImpedance_ohm
				// fun_DisplayMode_ImpedanceFinish();
				
				gbv_TxSDKImpedanceStatus = 1;
				fun_HEX2BCD4(SDKImpedance.Data);
				temp2 = SDKImpedance.Data;
				fun_FW_LEDBuf2HW_LEDBuf();
				fun_TxSDKImpedanceStatus();
				BHSDKState = ENTER_IMPEDANCE;
				
			    break;
			case STATE_AUTOON_FASTMODE:		// 快速ADC自動上稱判斷
			case STATE_AUTOON_SLOWMODE:		// 慢速ADC自動上稱判斷
				// 通常這個時候無任何UI
				break;
			case STATE_AUTOON_PASS:			// 自動上稱OK
				// 此時可以點亮顯示,并切換到普通稱重模式進行MCU的正常工作
				// BHSDKState = ENTER_WEIGHT_NORMAL;
				break;
			case STATE_AUTOON_FAIL:			// 自動上秤失敗,此時請繼續讓 MCU 進入HALT狀態
				fun_BodyFatScalesSDK_PowerDown();
				GCC_HALT();
				break;
			case STATE_WEIGHT_CAL0:	// 正在標定零點
				// fun_DisplayMode_CAL0();此處寫User UI,,比如提示CAL 0kg
				break;
			case STATE_WEIGHT_CAL1:	// 正在標定第1點
				// fun_DisplayMode_CAL1();此處寫User UI,,比如提示CAL 50kg
				break;
			case STATE_WEIGHT_CAL2:	// 正在標定第2點
				// fun_DisplayMode_CAL2();此處寫User UI,,比如提示CAL 100kg
				break;
			case STATE_WEIGHT_CAL3:	// 正在標定第3點
				// fun_DisplayMode_CAL3();此處寫User UI,,比如提示CAL 150kg
				break;
			case STATE_WEIGHT_CALPASS:	// 標定成功
				// fun_DisplayMode_CALPASS();此處寫User UI,,比如提示PASS
				break;
			case STATE_WEIGHT_CALFAIL:	// 標定失敗功
				// fun_DisplayMode_CALFAIL();此處寫User UI,,比如提示FIAS
				break;
			default:
				break;
		}
	}
}