#include <stdio.h>
#include "iodefine.h"
#include "sci.h"

void Sci_init(void)
{
	long i;
	
	SCI3.SCR3.BIT.TE = 0;
	SCI3.SCR3.BIT.RE = 0;
	
	//SCI3.SCR3.BIT.CKE = 0;
	
	SCI3.SMR.BIT.CKS = 0;
	SCI3.SMR.BIT.COM = 0;
	SCI3.SMR.BIT.CHR = 0;
	SCI3.SMR.BIT.PE = 0;
	SCI3.SMR.BIT.PM = 0;
	SCI3.SMR.BIT.STOP = 0;;
	SCI3.SMR.BIT.MP = 0;
	
	SCI3.BRR = 19;
	
	for (i=0; i<1000; i++);
	
	SCI3.SCR3.BIT.TE = 1;
	IO.PMR1.BIT.TXD = 1;
	
}

int Sci_putChar(char moji)
{
	while (SCI3.SSR.BIT.TDRE == 0);
	SCI3.TDR = moji;
	
	while (SCI3.SSR.BIT.TEND == 0);
	
	return 0;
}

int Sci_putString(char * str)
{
	if (str == NULL)
	{
		return -1;
	}
	
	while (*str != '\0')
	{
		Sci_putChar(*str);
		str++;
	}
	
	return 0;
}