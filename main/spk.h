#ifndef SPK_H
#define SKP_H
//------------------------------------------------

//------------------------------------------------
//  マクロ定義(Macro definition)
//------------------------------------------------


//------------------------------------------------
//  型定義(Type definition)
//------------------------------------------------
typedef enum
{
	 E_SPK_SCALE_DO = 0,
 	 E_SPK_SCALE_RE,
	 E_SPK_SCALE_MI,
	 E_SPK_SCALE_FA,
	 E_SPK_SCALE_SO,
	 E_SPK_SCALE_RA,
	 E_SPK_SCALE_SI,
	 E_SPK_SCALE_DO2,
	 E_SPK_SCALE_END,
} E_SPK_SCALE;


//------------------------------------------------
//  プロトタイプ宣言(Prototype declaration)
//------------------------------------------------
void Spk_init(void);
int Spk_start(E_SPK_SCALE scale);
int Spk_stop(void);

//------------------------------------------------
#endif