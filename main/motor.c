#include "iodefine.h"
#include "motor.h"

#define D_MOTOR_DUTY_TARGET (30)
#define D_MOTOR_DUTY_WIDTH (25)
#define D_MOTOR_BRIGHTNESS_TARGET (435.0)
#define D_MOTOR_KP (0.5)


void Motor_init(void)
{
	
	TZ0.TCR.BIT.TPSC = 2; // (1) 分周 Φ/4
	TZ0.TCR.BIT.CCLR = 1; // (2) カウンタクリア GRAとコンペアマッチ
	
	TZ.TPMR.BIT.PWMB0 = 1; // (3) FTIOB0をPWMモード（左モータ）
	TZ.TPMR.BIT.PWMC0 = 1; // (3) FTIOC0をPWMモード（右モータ）
	
	TZ.TOCR.BIT.TOB0 = 0; // (4)
	TZ.TOCR.BIT.TOC0 = 0;
	TZ0.POCR.BIT.POLB = 0; // (5)
	TZ0.POCR.BIT.POLC = 0;
	
	TZ0.GRA = 3000; // (6) 1msでカウンターリセット
	//TZ0.GRB = 0; // 仮
	//TZ0.GRC = 0; // 仮
	
	// TZ.TOER.BIT.EA0 = 0; // (7) タイマ出力許可
	TZ.TOER.BIT.EB0 = 0;
	TZ.TOER.BIT.EC0 = 0;
	
	TZ.TSTR.BIT.STR0 = 0; // (8) カウント動作停止
	
	TZ0.TCNT = 0;
	

}

int Motor_runStart(E_MOTOR_DIR dir, unsigned char duty)
{
	if (duty>100)
	{
		return -1;
	}
	
	switch (dir)
	{
	case E_MOTOR_FORWARD:
		IO.PDR3.BIT.B0 = 1;
		IO.PDR3.BIT.B1 = 0;
		IO.PDR3.BIT.B2 = 1;
		IO.PDR3.BIT.B3 = 0;
	break;
	
	case E_MOTOR_BACKWARD:
		IO.PDR3.BIT.B0 = 0;
		IO.PDR3.BIT.B1 = 1;
		IO.PDR3.BIT.B2 = 0;
		IO.PDR3.BIT.B3 = 1;
	break;
	
	case E_MOTOR_TURN_RIGHT:
		IO.PDR3.BIT.B0 = 0;
		IO.PDR3.BIT.B1 = 1;
		IO.PDR3.BIT.B2 = 1;
		IO.PDR3.BIT.B3 = 0;
	break;
	
	case E_MOTOR_TURN_LEFT:
		IO.PDR3.BIT.B0 = 1;
		IO.PDR3.BIT.B1 = 0;
		IO.PDR3.BIT.B2 = 0;
		IO.PDR3.BIT.B3 = 1;
	break;
	
	default:
	return -1;
	}
	
	
	TZ0.GRB = TZ0.GRA * (duty / 100.0);
	TZ0.GRC = TZ0.GRA * (duty / 100.0);
	TZ.TSTR.BIT.STR0 = 1;
	
	return 0;
}

int Motor_runOnOff(unsigned short brightness, unsigned char duty)
{
	if (brightness > 1023 || duty > 99)
	{
		return -1;
	}
	
	if (brightness >= 512)
	{
		IO.PDR3.BIT.B0 = 1;
		IO.PDR3.BIT.B1 = 0;
		IO.PDR3.BIT.B2 = 0;
		IO.PDR3.BIT.B3 = 0;
	}
	else
	{
		IO.PDR3.BIT.B0 = 0;
		IO.PDR3.BIT.B1 = 0;
		IO.PDR3.BIT.B2 = 1;
		IO.PDR3.BIT.B3 = 0;
	}
	
	TZ0.GRB = TZ0.GRA * (duty / 100.0);
	TZ0.GRC = TZ0.GRA * (duty / 100.0);
	TZ.TSTR.BIT.STR0 = 1;
	
	return 0;
}

int Motor_runPcon(unsigned short brightness)
{
	long dutyDiff;
	
	IO.PDR3.BIT.B0 = 1;
	IO.PDR3.BIT.B1 = 0;
	IO.PDR3.BIT.B2 = 1;
	IO.PDR3.BIT.B3 = 0;
	
	dutyDiff = D_MOTOR_KP * (brightness - D_MOTOR_BRIGHTNESS_TARGET);
	
	if (dutyDiff > D_MOTOR_DUTY_WIDTH)
	{
		dutyDiff = D_MOTOR_DUTY_WIDTH;
	}
	else if (dutyDiff < -D_MOTOR_DUTY_WIDTH)
	{
		dutyDiff = -D_MOTOR_DUTY_WIDTH;
	}
	
	
	TZ0.GRC = TZ0.GRA * ((D_MOTOR_DUTY_TARGET - dutyDiff) / 100.0); // left
	TZ0.GRB = TZ0.GRA * ((D_MOTOR_DUTY_TARGET + dutyDiff) / 100.0); // right
	
	TZ.TSTR.BIT.STR0 = 1;
	
	return 0;
	
}

int Motor_runStop(void)
{
	IO.PDR3.BIT.B0 = 0;
	IO.PDR3.BIT.B1 = 0;
	IO.PDR3.BIT.B2 = 0;
	IO.PDR3.BIT.B3 = 0;
	
	TZ.TSTR.BIT.STR0 = 0;
	TZ0.TCNT = 0;
}