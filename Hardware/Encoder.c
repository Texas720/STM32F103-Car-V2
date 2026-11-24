#include "stm32f10x.h"                  // Device header

int16_t Speed_L,Speed_R;

void Encoder_Init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
		
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period = 65536 - 1;		//ARR
	TIM_TimeBaseInitStructure.TIM_Prescaler = 1 - 1;		//PSC
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStructure);
	
	TIM_ICInitTypeDef TIM_ICInitStructure;
	TIM_ICStructInit(&TIM_ICInitStructure);
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;
	TIM_ICInitStructure.TIM_ICFilter = 0xF;
	TIM_ICInit(TIM3, &TIM_ICInitStructure);
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;
	TIM_ICInitStructure.TIM_ICFilter = 0xF;
	TIM_ICInit(TIM3, &TIM_ICInitStructure);
	
	TIM_EncoderInterfaceConfig(TIM3, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Falling);
	
	TIM_Cmd(TIM3, ENABLE);
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
		
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period = 65536 - 1;		//ARR
	TIM_TimeBaseInitStructure.TIM_Prescaler = 1 - 1;		//PSC
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseInitStructure);
	
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;
	TIM_ICInitStructure.TIM_ICFilter = 0xF;
	TIM_ICInit(TIM4, &TIM_ICInitStructure);
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;
	TIM_ICInitStructure.TIM_ICFilter = 0xF;
	TIM_ICInit(TIM4, &TIM_ICInitStructure);
	
	TIM_EncoderInterfaceConfig(TIM4, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Falling);
	
	TIM_Cmd(TIM4, ENABLE);
	
}

//int16_t Encoder_Get_L(void)
//{
//	int16_t Temp1;
//    Temp1 = TIM_GetCounter(TIM4); // 先获取计数值
//    Speed_L= Temp1;         // 再赋值给临时变量
//    TIM_SetCounter(TIM4, 0);      // 重置计数器
//    return Temp1;
//}

//int16_t Encoder_Get_R(void)
//{
//    int16_t Temp2;
//    Temp2 = -TIM_GetCounter(TIM3); // 先获取计数值
//    Speed_R = Temp2;         // 再赋值给临时变量
//    TIM_SetCounter(TIM3, 0);      // 重置计数器
//    return Temp2;
//}

static int32_t Last_Cnt_L = 0;
static int32_t Last_Cnt_R = 0;



//  获取左轮瞬时速度（脉冲数/40ms）
int16_t Encoder_Get_L(void) 
{
    int32_t Current_Cnt = (int32_t)TIM_GetCounter(TIM4);
    int16_t Speed = (int16_t)(Current_Cnt - Last_Cnt_L); // 算差值
    Last_Cnt_L = Current_Cnt;                            // 更新上一次的值
    return Speed;
}


//获取右轮瞬时速度（脉冲数/40ms）
int16_t Encoder_Get_R(void) 
{
    int32_t Current_Cnt = (int32_t)(-TIM_GetCounter(TIM3)); // 右轮取反
    int16_t Speed = (int16_t)(Current_Cnt - Last_Cnt_R); 
    Last_Cnt_R = Current_Cnt;
    return Speed;
}

void Encoder_Clear_L(void) 
{
    TIM_SetCounter(TIM4, 0);
    Last_Cnt_L = 0; // 清零计数器时，必须把上一次的基准值也清零
}

void Encoder_Clear_R(void) 
{
    TIM_SetCounter(TIM3, 0);
    Last_Cnt_R = 0; 
}

int32_t Encoder_Get_Total_L(void) {
    return (int32_t)TIM_GetCounter(TIM4);
}

int32_t Encoder_Get_Total_R(void) {
    return (int32_t)(-TIM_GetCounter(TIM3));
}
