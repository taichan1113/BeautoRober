#ifndef LED_H
#define LED_H
//------------------------------------------------


//------------------------------------------------
//  �}�N����`(Macro definition)
//------------------------------------------------

#define D_LED_KIND_ORANGE (0)
#define D_LED_KIND_GREEN (1)
#define D_LED_LIGHT_OFF (0)
#define D_LED_LIGHT_ON (1)


//------------------------------------------------
//  �^��`(Type definition)
//------------------------------------------------


//------------------------------------------------
//  �v���g�^�C�v�錾(Prototype declaration)
//------------------------------------------------
void Led_init(void);
int Led_setLight(int kind, int onoff);
int Led_toggleLight(int kind);


//------------------------------------------------
#endif