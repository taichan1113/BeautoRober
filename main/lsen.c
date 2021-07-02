#include <stdio.h>
#include "iodefine.h"
#include "lsen.h"

void Lsen_init(void)
{

	AD.ADCSR.BIT.SCAN = 0;
	AD.ADCSR.BIT.CKS = 0;
	AD.ADCSR.BIT.ADIE = 0;
	
}

int Lsen_getSensor(unsigned short * sen1, unsigned short * sen2)
{
	if (sen1 == NULL || sen2 == NULL)
	{
		return -1;
	}
	
	AD.ADCSR.BIT.CH = 0;
	AD.ADCSR.BIT.ADST = 1;
	while (AD.ADCSR.BIT.ADF == 0);
	AD.ADCSR.BIT.ADF = 0;
	*sen1 =  AD.ADDRA >> 6;
	
	AD.ADCSR.BIT.CH = 1;
	AD.ADCSR.BIT.ADST = 1;
	while (AD.ADCSR.BIT.ADF == 0);
	AD.ADCSR.BIT.ADF = 0;
	*sen2 = AD.ADDRB >> 6;
	
	return 0;
}