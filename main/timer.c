#include "iodefine.h"
#include "timer.h"

volatile static unsigned long gTimer_systemTime = 0;

void Timer_init(void)
{
	TB1.TMB1.BIT.RLD = 1;
	TB1.TMB1.BIT.CKS = 4;
	TB1.TCB1 = 256 - 187;
	
	IENR2.BIT.IENTB1 = 1;
}

unsigned long Timer_getTime(void)
{
	return gTimer_systemTime;
}

void Timer_waitTime(unsigned long msec)
{
	unsigned long nowTime = gTimer_systemTime;
	while(1)
	{
		if (gTimer_systemTime - nowTime >= msec)
		{
			break;
		}
	}
}

void Timer_interruptHandler(void)
{
	gTimer_systemTime++;
	IRR2.BIT.IRRTB1 = 0;
}
	