#include "iodefine.h"
#include "led.h"


void Led_init(void){
	/* IO.PDR6.BYTE = 0x01; */
	IO.PDR6.BIT.B0 = 1;
	IO.PDR6.BIT.B4 = 1;
}


int Led_setLight(int kind, int onoff)
{
	if (kind == D_LED_KIND_ORANGE) 
	{
		if (onoff == D_LED_LIGHT_OFF)
		{
			IO.PDR6.BIT.B0 = 1;
		}
		else 
		{
			IO.PDR6.BIT.B0 = 0;
		}
	}
	else if (kind == D_LED_KIND_GREEN) 
	{
		if (onoff == D_LED_LIGHT_OFF)
		{
			IO.PDR6.BIT.B4 = 1;
		}
		else 
		{
			IO.PDR6.BIT.B4 = 0;
		}
	}
	else 
	{
		return -1;
	}
	
	return 0;
	
}

int Led_toggleLight(int kind)
{
	if (kind == D_LED_KIND_ORANGE)
	{
		if (IO.PDR6.BIT.B0 == 1)
		{
			IO.PDR6.BIT.B0 = 0;
		}
		else
		{
			IO.PDR6.BIT.B0 = 1;
		}
	}
	else if (kind == D_LED_KIND_GREEN)
	{
		if (IO.PDR6.BIT.B4 == 1)
		{
			IO.PDR6.BIT.B4 = 0;
		}
		else
		{
			IO.PDR6.BIT.B4 = 1;
		}
	}
	else
	{
		return -1;
	}
	return 0;
	
}