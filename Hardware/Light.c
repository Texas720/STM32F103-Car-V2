#include "stm32f10x.h"
#include "Light.h"

extern uint8_t Line_Flag;
extern int16_t case1_Flag;

void Light_Init(void)
{
	RCC_APB2PeriphClockCmd (RCC_APB2Periph_GPIOC ,ENABLE );
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode =GPIO_Mode_Out_PP ; 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz ;
	GPIO_Init (GPIOC,&GPIO_InitStructure);
	
	GPIO_SetBits (GPIOC,GPIO_Pin_13);
}


void Light_On(void)
{
  GPIO_ResetBits (GPIOC,GPIO_Pin_13 ); 
    
}


void Light_Off(void)
{
  GPIO_SetBits (GPIOC,GPIO_Pin_13);
}

void LED_Status_Update(void)
{
    static uint8_t last_flag = 0;
    
    // 只在 Line_Flag 变化时才更新 LED
    if (Line_Flag != last_flag)
    {
        last_flag = Line_Flag;
        
        switch(Line_Flag)
        {
            case 1: 
						{
						  Light_Off();
						}
						break ;
            case 2: 
						case 4: 
						case 6: 
						case 7:
						{
							Light_On();
						}
            break;
            default:
                Light_Off();
                break;
        }
    }
    
    // 断线
    if (Line_Flag == 1 && case1_Flag >= 1200)
    {
        Light_On();
    }
}
