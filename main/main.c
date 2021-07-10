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
//  �����v���g�^�C�v�錾
//------------------------------------------------
void main_init(void);

//------------------------------------------------
//  �T  �v�F�G���g���[�|�C���g
//------------------------------------------------
void main(void)
{	
	unsigned long time;
	unsigned long time_sys;
	unsigned short sen1_mem;
	float sen1Int = 0;
	
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
	
	
	sen1_mem = D_MOTOR_BRIGHTNESS_TARGET;
	time = Timer_getTime();
	time_sys = Timer_getTime();
	
	
	while(1)
	{	
		unsigned short sen1;
		unsigned short sen2;		
		long sen1Diff;
		
		Lsen_getSensor(&sen1, &sen2);
		sen1Diff = (sen1-sen1_mem)*1000; 
		
		
		//Motor_runPcon(sen1);
		//Motor_runPDcon(sen1, sen1Diff);
		Motor_runPIDcon(sen1, sen1Diff, sen1Int);
		
		
		if (Timer_getTime() > time + 1000)
		{
			Led_toggleLight(D_LED_KIND_ORANGE);
			Led_toggleLight(D_LED_KIND_GREEN);
			time = Timer_getTime();
		}
		
		if (Timer_getTime() > time_sys + 1)
		{
			sen1_mem = sen1;
			sen1Int += (sen1 - D_MOTOR_BRIGHTNESS_TARGET)/1000;
			time_sys = Timer_getTime();
		}
	}	
}

//------------------------------------------------
//  �T  �v�F�V�X�e��������
//------------------------------------------------
void main_init(void){
	//---------------------------------------------------
    //  �E�H�b�`�h�b�O�^�C�}�̒�~(�����Ȃ�����)
    //---------------------------------------------------
	WDT.TCSRWD.BYTE = 0x92;
    WDT.TCSRWD.BYTE = 0x92;
	
	//---------------------------------------------------
    //  PCR�̐ݒ�(PCR�͏������ݐ�p���W�X�^)
    //---------------------------------------------------
	IO.PCR3 = 0x0F;
	IO.PCR6 = 0x11;
	IO.PCR7 = 0x00;
	
	
	//---------------------------------------------------
    //  ���W���[���̏�����(�e���W���[���̏����������{)
    //---------------------------------------------------
	Led_init();
	Sw_init();
	Timer_init();
	Lsen_init();
	Sci_init();
	Spk_init();
	Motor_init();
	
}