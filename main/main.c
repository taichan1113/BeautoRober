#include <stdio.h>
#include "iodefine.h"
#include "led.h"
#include "sw.h"
#include "timer.h"
#include "lsen.h"
#include "sci.h"
#include "spk.h"
#include "motor.h"

//------------------------------------------------
//  内部プロトタイプ宣言
//------------------------------------------------
void main_init(void);

//------------------------------------------------
//  概  要：エントリーポイント
//------------------------------------------------
void main(void)
{	
	unsigned long time;
	
	main_init();
	
	Led_setLight(D_LED_KIND_ORANGE, D_LED_LIGHT_ON);
	Led_setLight(D_LED_KIND_GREEN, D_LED_LIGHT_ON);
	
	while(1)
	{	
		//unsigned short sen1;
		//unsigned short sen2;
		
		if (Sw_getPressed() == D_SW_PRESSED_ON)
		{
			int scale;
			for (scale = E_SPK_SCALE_DO; scale <= E_SPK_SCALE_MI; scale++)
			{
				Spk_start(scale);
				Timer_waitTime(1000);
			}
			Spk_stop();
			break;
		}
	}
	
	time = Timer_getTime();
	
	while(1)
	{	
		unsigned short sen1;
		unsigned short sen2;
		
		Lsen_getSensor(&sen1, &sen2);
		Motor_runPcon(sen1);
		
		if (Timer_getTime() > time + 1000)
		{
			Led_toggleLight(D_LED_KIND_ORANGE);
			Led_toggleLight(D_LED_KIND_GREEN);
			time = Timer_getTime();
		}
	}	
}

//------------------------------------------------
//  概  要：システム初期化
//------------------------------------------------
void main_init(void){
	//---------------------------------------------------
    //  ウォッチドッグタイマの停止(消さないこと)
    //---------------------------------------------------
	WDT.TCSRWD.BYTE = 0x92;
    WDT.TCSRWD.BYTE = 0x92;
	
	//---------------------------------------------------
    //  PCRの設定(PCRは書き込み専用レジスタ)
    //---------------------------------------------------
	IO.PCR3 = 0x0F;
	IO.PCR6 = 0x11;
	IO.PCR7 = 0x00;
	
	
	//---------------------------------------------------
    //  モジュールの初期化(各モジュールの初期化を実施)
    //---------------------------------------------------
	Led_init();
	Sw_init();
	Timer_init();
	Lsen_init();
	Sci_init();
	Spk_init();
	Motor_init();
	
}