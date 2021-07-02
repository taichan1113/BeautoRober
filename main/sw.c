#include "iodefine.h"
#include "sw.h"

void Sw_init(void)
{
	
}


int Sw_getPressed(void)
{
	if (IO.PDR7.BIT.B4 == 0)
	{
		return D_SW_PRESSED_ON;
	}
	else 
	{
		return D_SW_PRESSED_OFF;
	}
}