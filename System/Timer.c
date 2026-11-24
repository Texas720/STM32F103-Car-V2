#include "stm32f10x.h"                  // Device header
#include "Key.h"
#include "LED.h"
#include "PID.h"
#include "Motor.h"
#include "Elementselect.h"
#include "Line.h"
#include "Menu.h"
#include "Light.h"
#include "Menu.h"

extern uint8_t System_Start_Flag;
extern uint16_t num;
extern float SpeedTarget;
extern float out1,out2;//分别为速度环和转向环的输出
extern int8_t Error;//在Line中定义，用于储存相对中线的偏移
extern uint16_t Check_Start;
extern uint8_t Turn_Flag2;
extern float rFinal_Left ; 
extern float rFinal_Right;
int Menu_Flag;
float Final_Left = 0;
float Final_Right = 0;

void Timer_Init(void)
{
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); // 开启TIM2的时钟
    
    TIM_InternalClockConfig(TIM2); // 选择TIM2为内部时钟   
   
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInitStructure.TIM_Period = 100 - 1;       // ARR = 99
    TIM_TimeBaseInitStructure.TIM_Prescaler = 720 - 1;    // PSC = 719 -> 计数频率 = 72MHz/720 = 100kHz
    TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;   
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);              
   
    TIM_ClearFlag(TIM2, TIM_FLAG_Update); // 清除更新标志位，防止一开中断就进一次
    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE); // 开启TIM2的更新中断

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    
   
    NVIC_InitTypeDef NVIC_InitStructure;
    
    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;             
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_Init(&NVIC_InitStructure);
    

    TIM_Cmd(TIM2, ENABLE); // 使能TIM2
}    

void TIM2_IRQHandler (void)
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)
	{
		num ++;
		Find_Line();
		Element_Select ();
		RightAngle_Turn ();
		
		static uint8_t Count1;
		static uint8_t Count2;
		
		if(Turn_Flag2 != 0)//在直角处不使用PID
		{
			Final_Left = rFinal_Left ;
			Final_Right = rFinal_Right ;
		}
		else
		{
			Count1 ++;
			if(Count1 >= 40 && System_Start_Flag == 1)//速度环
			{
				Count1 = 0;
				Speed_PI (SpeedTarget);
			}
			
			Count2 ++;
			if(Count2 >= 40 && System_Start_Flag == 1)//角度环
			{
				Count2 = 0;
				Turn_PD ();
			}
		
			Final_Left  = out1 - (out2)  ; 
			Final_Right = out1 + (out2)  ;
		}
		
		//限幅 (防止叠加后的值超出 PWM 范围)
		if(Final_Left > 100) Final_Left = 100;
		if(Final_Left < -100) Final_Left = -100;
		if(Final_Right > 100) Final_Right = 100;
		if(Final_Right < -100) Final_Right = -100;
    if(System_Start_Flag == 0)
		{
			Final_Left = 0;
			Final_Right = 0;
		}			
		
		Motor_SetLeftSpeed(Final_Left);
		Motor_SetRightSpeed(Final_Right);
		
		if(Check_Start == 1)
		{
			RightAngle_Tick ();
		}
		Key_Tick ();
		Plus_Tick ();
		Find_Line_Tick ();
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	}
}
