#include "stm32f10x.h"                  // Device header
#include "Key.h"

uint16_t LED1_Count;
uint16_t LED_1_Mood;
uint16_t Mood;

void LED1_Mood(uint16_t LED_1_Mood)
{
	Mood = LED_1_Mood ;
}
	

void LED_Init(void)
{
	RCC_APB2PeriphClockCmd (RCC_APB2Periph_GPIOA ,ENABLE );
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode =GPIO_Mode_Out_PP ;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz ;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	GPIO_ResetBits (GPIOA ,GPIO_Pin_2);
	GPIO_ResetBits (GPIOA ,GPIO_Pin_3);
}

void LED1_ON(void)
{
	GPIO_SetBits (GPIOA ,GPIO_Pin_2);
}

void LED2_ON(void)
{
	GPIO_SetBits (GPIOA ,GPIO_Pin_3);
}


void LED1_OFF(void)
{
	GPIO_ResetBits(GPIOA ,GPIO_Pin_2 );
}
void LED2_OFF(void)
{
	GPIO_ResetBits(GPIOA ,GPIO_Pin_3);
}


void LED_Tick(void)
{
	LED_1_Mood = Key_Getnum ();
	if(LED_1_Mood == 0)
	{
		LED1_OFF() ;
	}
	if(LED_1_Mood == 1)
	{
		LED1_Count ++;
			if(LED1_Count > 999)
		{
			LED1_Count = 0;
		}
		if(LED1_Count < 500)
		{
			LED1_ON() ;
		}
		else 
		{
			LED1_OFF() ;
		}
	}
	
}

