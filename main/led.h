#ifndef LED_H
#define LED_H
//------------------------------------------------


//------------------------------------------------
//  マクロ定義(Macro definition)
//------------------------------------------------

#define D_LED_KIND_ORANGE (0)
#define D_LED_KIND_GREEN (1)
#define D_LED_LIGHT_OFF (0)
#define D_LED_LIGHT_ON (1)


//------------------------------------------------
//  型定義(Type definition)
//------------------------------------------------


//------------------------------------------------
//  プロトタイプ宣言(Prototype declaration)
//------------------------------------------------
void Led_init(void);
int Led_setLight(int kind, int onoff);
int Led_toggleLight(int kind);


//------------------------------------------------
#endif