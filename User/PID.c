#include "stm32f10x.h"                  // Device header
#include "Encoder.h"
#include "Motor.h"
#include "Line.h"

//速度环参数
float SpeedActual,SpeedError0,SpeedError1,out1;
float AverageSpeed,LeftSpeed,RightSpeed;
float Kp1 = 2.0;
float Ki1 = 0.4;
//以上为速度环参数

//以下为转向环参数
extern int8_t Error1,Error2,Error3;
float FacingTarget,FacingActual,FacingError0,FacingError1,out2;
float DifSpeed,LeftSpeed2,RightSpeed2;
float Kp2 = 1.2;
float Kd2 = 0.6;
//转向环参数

int16_t Speed_PI(float SpeedTarget)
{

	LeftSpeed = Encoder_Get_L () / 28.0 / 0.04 / 30;//28是电机极数，速度单位是r/s
	RightSpeed = Encoder_Get_R () / 28.0 / 0.04 / 30;
	AverageSpeed = (LeftSpeed + RightSpeed ) / 2.0;
	

	SpeedActual = AverageSpeed ;//实际值
	SpeedError1 = SpeedError0 ;
	SpeedError0 = SpeedTarget - SpeedActual ;
	
	out1 += Kp1 * (SpeedError0 - SpeedError1 ) + Ki1 * SpeedError0 ;//输出平均PWM
	
	if(out1 >= 100)
	{
		out1 = 100;
	}
	if(out1 <= -100)
	{
		out1 = -100;
	}
	return out1;
//	Motor_SetLeftSpeed (out1 / 2);
//	Motor_SetRightSpeed(out1 / 2); 
//	测试用
}


/******以下为转向环**********/

int16_t Turn_PD(void)
{
	FacingTarget = 0;
	LeftSpeed2 = Encoder_Get_L () / 28.0 / 0.04 / 30;//28是电机极数，速度单位是r/s
	RightSpeed2 = Encoder_Get_R () / 28.0 / 0.04 / 30;
	DifSpeed   = (LeftSpeed2 - RightSpeed2 ) ;
	
	FacingActual = Error1     ;//实际值
	FacingError1 = FacingError0 ;
	FacingError0 = FacingTarget - Error1 ;//左正右负，向左偏的时候，FacingError0为负数，
	
	out2 = Kp2 * FacingError0 + Kd2 * (FacingError0 - FacingError1 );
	
	if(out2 >= 50)
	{
		out2 = 50;
	}
	if(out2 <= -50)
	{
		out2 = -50;
	}
	return out2;
//	Motor_SetLeftSpeed (-out2 );
//	Motor_SetRightSpeed(out2 );

}
