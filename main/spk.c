#include "iodefine.h"
#include "spk.h"

void Spk_init(void)
{
	TV.TCRV0.BIT.CCLR = 1;
	
	TV.TCSRV.BIT.OS = 9;
	
	TV.TCRV1.BIT.ICKS = 1;
	TV.TCRV0.BIT.CKS = 0;
}

int Spk_start(E_SPK_SCALE scale)
{
	switch (scale)
	{
	case E_SPK_SCALE_DO:
		TV.TCORA = 179;
		break;
	case E_SPK_SCALE_RE:
		TV.TCORA = 160;
		break;
	case E_SPK_SCALE_MI:
		TV.TCORA = 142;
		break;
	case E_SPK_SCALE_FA:
		TV.TCORA = 134;
		break;
	case E_SPK_SCALE_SO:
		TV.TCORA = 120;
		break;
	case E_SPK_SCALE_RA:
		TV.TCORA = 107;
		break;
	case E_SPK_SCALE_SI:
		TV.TCORA = 95;
		break;
	case E_SPK_SCALE_DO2:
		TV.TCORA = 90;
		break;

	default:
		return -1;	
	}
	
	TV.TCORB = TV.TCORA >> 1;
	
	TV.TCRV0.BIT.CKS = 3;
	
	return 0;
}

int Spk_stop(void)
{
	TV.TCRV0.BIT.CKS = 0;
	TV.TCNTV = 0;
	
	return 0;
}