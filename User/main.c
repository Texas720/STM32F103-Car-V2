#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Timer.h"
#include "Key.h"
#include "LED.h"
#include "Encoder.h"
#include "Sensor.h"
#include "Line.h"
#include "PWM.h"
#include "Motor.h"
#include "PID.h"
#include "Light.h"
#include "Menu.h"

uint16_t num;
int16_t Key;
int8_t SensorGet[5];
uint8_t Flag;
uint8_t System_Start_Flag = 0;
int Menu2_Flag;
float Base_Speed = 0.0;//定义初始速度
float SpeedTarget;//传输基础速度的中间变量，在PID.C中使用

//调试所调用的参数
extern int8_t Error1;
extern float AverageSpeed,LeftSpeed,RightSpeed,out1;
extern int32_t enc_diff;
extern uint8_t Outer_Masked;
extern uint8_t Masked_Step;
extern uint16_t Check_Start;
extern uint8_t Turn_Flag2;
extern uint8_t Flag1;
//

int main(void)
{
	OLED_Init();
	Light_Init ();
	Timer_Init ();
	Encoder_Init ();
	Key_Init ();
	LED_Init ();
	PWM_Init ();
	Motor_Init ();
	Sensor_Init ();
	
	while (1)
	{
		Menu2_Flag = Menu_1();//将Menu_1的返回值赋给Menu2_Flag,进入二级菜单
		if(Menu2_Flag == 1)
		{
			Menu2_Speed();
		}
		if(Menu2_Flag == 2)
		{
			Menu2_PID ();
		}
		while(Menu2_Flag == 3)//确认之后，开始运行
		{
			System_Start_Flag = 1;
			Key = Key_Getnum ();
			if(Key == 1)
			{
				Base_Speed  += 1.0;
			}
			if(Key == 2)
			{
				Base_Speed  -= 1.0;
			}
			OLED_Clear ();
			OLED_ShowNum (1,1,num,5,OLED_8X16 );
			OLED_ShowSignedNum (50,1,Turn_Flag2 ,3,OLED_8X16 );
			OLED_ShowSignedNum (90,1,Flag1,3,OLED_8X16 );
			OLED_ShowSignedNum (1,20,Check_Start,5,OLED_8X16 );
			OLED_ShowSignedNum (50,20,Outer_Masked,5,OLED_8X16 );
			OLED_ShowSignedNum (1,40,Masked_Step,5,OLED_8X16 );
			OLED_ShowSignedNum (50,40,SpeedTarget,5,OLED_8X16 );
			OLED_Update ();
				//运行到return时，可以结束循环
		}
		
	}
}



