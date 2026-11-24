#include "stm32f10x.h"                  // Device header

uint8_t KeyNumber;

void Key_Init(void)
{
	RCC_APB2PeriphClockCmd (RCC_APB2Periph_GPIOA ,ENABLE );
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU ;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_0 ;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz ;
	GPIO_Init(GPIOA ,&GPIO_InitStructure);
}

uint8_t Key_Getnum(void)
{
	uint8_t read;
	if(KeyNumber != 0)
	{
		read = KeyNumber ;
		KeyNumber = 0;
		return read;
	}
	return 0;
}

uint8_t Key_GetState(void)
{
	if(GPIO_ReadInputDataBit (GPIOA ,GPIO_Pin_1 ) == 0)//检测按键2是否按下
	{
		return 2;
	}
	if(GPIO_ReadInputDataBit (GPIOA ,GPIO_Pin_0 ) == 0)//检测按键1是否按下
	{
		return 1;
	}
	return 0;
}

void Key_Tick(void)
{
	static uint16_t  Count ;
	static uint16_t  NowState, LastState;//分别代表本次和上一次的状态
	Count ++;
	if(Count >= 20)
	{
		Count = 0;
		LastState = NowState ;
		NowState = Key_GetState ();
		if(NowState == 0 && LastState != 0)//上一次的返回值有可能是2，故此处用不等于0
		{
			KeyNumber = LastState;//在松手之后检测，按下，松手后，Last存储的就是第一次按下按的键的返回值
		} 
	}
	//Count = 0; 不要放在外面，放在外面的话，由于第一次Count小于20，因此永远不会进入if;
}
