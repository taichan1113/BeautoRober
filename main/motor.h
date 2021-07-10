#ifndef MOTOR_H
#define MOTOR_H
//------------------------------------------------

//------------------------------------------------
//  マクロ定義(Macro definition)
//------------------------------------------------
#define D_MOTOR_DUTY_TARGET (40)
#define D_MOTOR_DUTY_WIDTH (40)
#define D_MOTOR_BRIGHTNESS_TARGET (435.0)
#define D_MOTOR_KP (1)

#if(1)
#define D_MOTOR_KD (0.01)
#define D_MOTOR_KI (0.001)
#else
#define D_MOTOR_KD (0.001)
#define D_MOTOR_KI (0.0001)
#endif



//------------------------------------------------
//  型定義(Type definition)
//------------------------------------------------
typedef enum
{
	E_MOTOR_FORWARD = 0,
	E_MOTOR_BACKWARD,
	E_MOTOR_TURN_RIGHT,
	E_MOTOR_TURN_LEFT,
	
	E_MOTOR_END,
} E_MOTOR_DIR;

//------------------------------------------------
//  プロトタイプ宣言(Prototype declaration)
//------------------------------------------------
void Motor_init(void);
int Motor_runStart(E_MOTOR_DIR dir, unsigned char duty);
int Motor_runOnOff(unsigned short brightness, unsigned char duty);
int Motor_runPcon(unsigned short brightness);
int Motor_runPDcon(unsigned short brightness, long brightnessDiff);
int Motor_runPIDcon(unsigned short brightness, long brightnessDiff, float brightInt);
int Motor_runStop(void);

//------------------------------------------------
#endif