#include "stm32f10x.h"                  // Device header

void Sensor_Init(void)
{
	RCC_APB2PeriphClockCmd (RCC_APB2Periph_GPIOA ,ENABLE );
	RCC_APB2PeriphClockCmd (RCC_APB2Periph_GPIOB ,ENABLE );
	
	GPIO_InitTypeDef GPIO_InitStructureA;
	GPIO_InitStructureA.GPIO_Mode =GPIO_Mode_IPU ; 
	GPIO_InitStructureA.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 |GPIO_Pin_12 ; 
	GPIO_InitStructureA.GPIO_Speed = GPIO_Speed_50MHz ;
	GPIO_Init (GPIOA ,&GPIO_InitStructureA);
	
	GPIO_InitTypeDef GPIO_InitStructureB;
	GPIO_InitStructureB.GPIO_Mode =GPIO_Mode_IPU ; 
	GPIO_InitStructureB.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1 ; 
	GPIO_InitStructureB.GPIO_Speed = GPIO_Speed_50MHz ;
	GPIO_Init (GPIOB ,&GPIO_InitStructureB);
}


void Sensor_Get(int8_t *sensor_values)
{
    // 检查PA4 (对应L2)
    if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_4) == 1)
    {
        sensor_values[0] = -5;
    }
    else
    {
        sensor_values[0] = 0; // 如果没触发，赋值为0
    }

    // 检查PA5 (对应L1)
    if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_5) == 1)
    {
        sensor_values[1] = -2;
    }
    else
    {
        sensor_values[1] = 0;
    }

    // 检查PA12 (对应M)
    if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_12) == 1)
    {
        sensor_values[2] = 1;
    }
    else
    {
        sensor_values[2] = 0;
    }
    
    // 检查PB0 (对应R1)
    if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_0) == 1)
    {
        sensor_values[3] = 4;
    }
    else
    {
        sensor_values[3] = 0;
    }

    // 检查PB1 (对应R2)
    if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1) == 1)
    {
        sensor_values[4] = 7;
    }
    else
    {
        sensor_values[4] = 0;
    }
}
