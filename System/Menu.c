#include "stm32f10x.h"                  // Device header
#include "Key.h"
#include "OLED.h"
#include "Encoder.h"
#include "Menu.h"


uint8_t Menu1_Flag = 1;

extern float Base_Speed;//基准速度
volatile uint8_t Plus_Flag = 0; //

//PID参数
extern float Kp1 ;
extern float Ki1 ;
extern float Kp2 ;
extern float Kd2 ;
//PID参数

void Plus_Tick(void)
{
	static uint16_t Count = 0;
	Count ++ ;
	if(Count >= 800)//每800ms检查一次
	{
		Count = 0;
		Plus_Flag = 1;
	}
}

/***********************************************************************************************************************/
/*==============================================一级菜单===============================================================*/
/***********************************************************************************************************************/
uint8_t  Menu_1 (void)
{
	int Key;
	static uint8_t End_Flag = 0;//屏保结束标志位
	
	while(Key_Getnum() == 0 && End_Flag == 0)
	{
		OLED_ShowImage (0,0,60,60,Keil5);
		OLED_ShowString (70,0,"寻",OLED_8X16);
		OLED_ShowString (95,0,"迹",OLED_8X16);
		OLED_ShowString (70,30,"小",OLED_8X16);
		OLED_ShowString (95,30,"车",OLED_8X16);
		OLED_Update ();
		
		if(Key_Getnum() == 1)
		{
			End_Flag ++;
		}
	}
	
	OLED_ShowString (0,0,"速",OLED_8X16);
	OLED_ShowString (20,0,"度",OLED_8X16);
	OLED_ShowString (40,0,"设",OLED_8X16);
	OLED_ShowString (60,0,"置",OLED_8X16);
	OLED_ShowString (0,20,"P",OLED_8X16);
	OLED_ShowString (20,20,"I",OLED_8X16);
	OLED_ShowString (40,20,"D",OLED_8X16);
	OLED_ShowString (0,40,"开",OLED_8X16);
	OLED_ShowString (20,40,"始",OLED_8X16);
	OLED_Update ();
	
	while(1)
	{
		Key = Key_Getnum ();
		OLED_Clear ();
		if(Key == 2)
		{
			Menu1_Flag ++;
			if(Menu1_Flag > 3)
			{
				Menu1_Flag = 1;
			}
		}
	
		
		if(Key == 1)
		{
			return Menu1_Flag ;//左按键为确认
		}
	
		switch (Menu1_Flag)
		{
			case 1:
			{
				OLED_ShowString (0,0,"速",OLED_8X16);
				OLED_ShowString (20,0,"度",OLED_8X16);
				OLED_ShowString (40,0,"设",OLED_8X16);
				OLED_ShowString (60,0,"置",OLED_8X16);
				OLED_ShowString (0,20,"P",OLED_8X16);
				OLED_ShowString (20,20,"I",OLED_8X16);
				OLED_ShowString (40,20,"D",OLED_8X16);
				OLED_ShowString (0,40,"开",OLED_8X16);
				OLED_ShowString (20,40,"始",OLED_8X16);
				OLED_ReverseArea (0,0,100,18);//刷新第一行
				OLED_Update ();
			}
			break ;
			
			case 2:
			{
				OLED_ShowString (0,0,"速",OLED_8X16);
				OLED_ShowString (20,0,"度",OLED_8X16);
				OLED_ShowString (40,0,"设",OLED_8X16);
				OLED_ShowString (60,0,"置",OLED_8X16);
				OLED_ShowString (0,20,"P",OLED_8X16);
				OLED_ShowString (20,20,"I",OLED_8X16);
				OLED_ShowString (40,20,"D",OLED_8X16);
				OLED_ShowString (0,40,"开",OLED_8X16);
				OLED_ShowString (20,40,"始",OLED_8X16);
				OLED_ReverseArea (0,20,100,18);//刷新第二行
				OLED_Update ();
			}
			break ;
			
			case 3:
			{
				OLED_ShowString (0,0,"速",OLED_8X16);
				OLED_ShowString (20,0,"度",OLED_8X16);
				OLED_ShowString (40,0,"设",OLED_8X16);
				OLED_ShowString (60,0,"置",OLED_8X16);
				OLED_ShowString (0,20,"P",OLED_8X16);
				OLED_ShowString (20,20,"I",OLED_8X16);
				OLED_ShowString (40,20,"D",OLED_8X16);
				OLED_ShowString (0,40,"开",OLED_8X16);
				OLED_ShowString (20,40,"始",OLED_8X16);
				OLED_ReverseArea (0,40,100,18);//刷新第三行
				OLED_Update ();
			}
			break ;
			
		}
	}
}




/***********************************************************************************************************************/
/*==============================================二级菜单===============================================================*/
/***********************************************************************************************************************/
uint8_t Menu2_Speed(void)
{
	uint8_t  Menu2_Flag = 1;//光标位置，初始为第一行
	uint8_t  Menu2Return_Flag;//暂存Menu_Flag2的值（若直接使用Menu2_Flag则会重复进入if）
	uint8_t  Key;

	//初始显示
	OLED_ShowString (0,0,"<-  ",OLED_8X16 );
	OLED_ShowString (0,20,"Base Speed",OLED_8X16);
	OLED_ShowFloatNum (0,40,Base_Speed ,2,2,OLED_8X16);
	OLED_Update ();
	while(1)
	{
		Key = Key_Getnum();
		if(Key == 2)//下一项
		{
			Menu2_Flag ++;
			if(Menu2_Flag >2)
			{
				Menu2_Flag = 1;
			}
		}
			if(Key == 1)//确认
		{
			OLED_Clear ();
			OLED_Update ();
			Menu2Return_Flag = Menu2_Flag ;
		}
		if(Encoder_Get_R()>0 && Plus_Flag == 1)
		{
			Plus_Flag = 0;
			Base_Speed += 1.0;
		}
			if(Encoder_Get_L()<0 && Plus_Flag == 1)
		{
			Plus_Flag = 0;
			Base_Speed -= 1.0;
		}
		
		if(Menu2Return_Flag == 1)
		{
			return 0;//return 0,直接返回一级菜单
		}
		
		switch(Menu2_Flag)
		{
			case 1:
			{
				OLED_ShowString (0,0,"<-  ",OLED_8X16 );
				OLED_ShowString (0,20,"Base Speed",OLED_8X16);
				OLED_ShowFloatNum (0,40,Base_Speed ,2,2,OLED_8X16);
				OLED_ReverseArea (0,0,32,16);
				OLED_Update ();
			}
			break;
			case 2:
			{
				OLED_ShowString (0,0,"<-  ",OLED_8X16 );
				OLED_ShowString (0,20,"Base Speed",OLED_8X16);
				OLED_ShowFloatNum (0,40,Base_Speed ,2,2,OLED_8X16);
				OLED_ReverseArea (0,20,80,16);
				OLED_Update ();
			}
			break;
		}
	}
}

uint8_t Menu2_PID(void)
{
	uint8_t  Menu2_Flag = 1;
	uint8_t  Menu2Return_Flag;
	uint8_t  Key;

	OLED_ShowString (0,0,"<-  ",OLED_8X16 );
	OLED_ShowString (0,20,"Speed PID Set",OLED_8X16);
	OLED_ShowString (0,40,"Turn PID Set",OLED_8X16);
	OLED_Update ();
	while(1)
	{
		Key = Key_Getnum();
		if(Key == 2)//下一项
		{
			Menu2_Flag ++;
			if(Menu2_Flag >3)
			{
				Menu2_Flag = 1;
			}
		}
			if(Key == 1)//确认
		{
			OLED_Clear ();
			OLED_Update ();
			Menu2Return_Flag = Menu2_Flag ;//
		}
		if(Menu2Return_Flag == 1)
		{
			return 0;
		}
		if(Menu2Return_Flag == 2)//跳转到速度PID设置
		{
			OLED_Clear ();
			Menu3_SpeedPID();
			Menu2Return_Flag = 0;//跳过if判断，继续往下到switch绘制二级菜单
		}
		if(Menu2Return_Flag == 3)//跳转到角度PID设置
		{
			OLED_Clear ();
			Menu3_TurnPID ();
			Menu2Return_Flag = 0;
		}
		
		switch(Menu2_Flag)
		{
			case 1:
			{
				OLED_ShowString (0,0,"<-  ",OLED_8X16 );
				OLED_ShowString (0,20,"Speed PID Set  ",OLED_8X16);
				OLED_ShowString (0,40,"Turn PID Set   ",OLED_8X16);
				OLED_ReverseArea (0,0,32,16);
				OLED_Update ();
			}
			break;
			case 2:
			{
				OLED_ShowString (0,0,"<-  ",OLED_8X16 );
				OLED_ShowString (0,20,"Speed PID Set  ",OLED_8X16);
				OLED_ShowString (0,40,"Turn PID Set   ",OLED_8X16);
				OLED_ReverseArea (0,20,105,16);
				OLED_Update ();
			}
			break;
			case 3:
			{
				OLED_ShowString (0,0,"<-  ",OLED_8X16 );
				OLED_ShowString (0,20,"Speed PID Set  ",OLED_8X16);
				OLED_ShowString (0,40,"Turn PID Set   ",OLED_8X16);
				OLED_ReverseArea (0,40,105,16);
				OLED_Update ();
			}
			break;
		}
	}
}


/***********************************************************************************************************************/
/*==============================================三级菜单===============================================================*/
/***********************************************************************************************************************/
uint8_t Menu3_SpeedPID(void)
{
	uint8_t  Key;
	uint8_t  Menu3S_Flag = 1;//三级菜单光标位置
	uint8_t  Temp = 0; //编辑标志
	
	OLED_ShowString (0,0,"<-  ",OLED_8X16 );
	OLED_ShowString (0,20,"Speed P ",OLED_8X16 );
	OLED_ShowString (0,40,"Speed I  ",OLED_8X16);
	OLED_Update ();
	while(1)
	{
		Key =Key_Getnum ();
		if(Key == 2 && Temp != 2 && Temp != 3)
		{
			Menu3S_Flag ++ ;
			if(Menu3S_Flag > 3)
			{
				Menu3S_Flag = 1;
			}
		}
		if(Key == 1)//确认
		{
			Temp = Menu3S_Flag ;
		}
		
		if(Temp != 2 && Temp != 3)
		{
			switch(Menu3S_Flag)
			{
				case 1:
				{
					OLED_ShowString (0,0,"<-  ",OLED_8X16 );
					OLED_ShowString (0,20,"Speed P ",OLED_8X16 );
					OLED_ShowString (0,40,"Speed I  ",OLED_8X16);
					OLED_ReverseArea (0,0,20,16);
					OLED_Update ();
				}
				break;
				
				case 2:
				{
					OLED_ShowString (0,0,"<-  ",OLED_8X16 );
					OLED_ShowString (0,20,"Speed P ",OLED_8X16 );
					OLED_ShowString (0,40,"Speed I  ",OLED_8X16);
					OLED_ReverseArea (0,20,60,16);
					OLED_Update ();
				}
				break;
				
				case 3:
				{
					OLED_ShowString (0,0,"<-  ",OLED_8X16 );
					OLED_ShowString (0,20,"Speed P ",OLED_8X16 );
					OLED_ShowString (0,40,"Speed I  ",OLED_8X16);
					OLED_ReverseArea (0,40,60,16);
					OLED_Update ();
				}
				break;
			}
		}
		
		if(Temp == 1)
		{
		 return 0;
		}
		
		if(Temp == 2)
		{
			OLED_Clear ();
			OLED_ShowString (0,0,"<-  ",OLED_8X16 );
			OLED_ShowString (0,20,"Speed P ",OLED_8X16 );
			OLED_ShowFloatNum (0,40,Kp1 ,2,2,OLED_8X16 );
			OLED_ReverseArea (0,40,50,16);
			if(Key  == 2) // 由于按键一被用于检测到哪一行，这里若仍用按键一判断，会直接退出
			{
				Temp = 0; // 清除编辑标志，下次循环将回到 switch 列表显示
				OLED_Clear(); 
			}
				if(Encoder_Get_R()>0 && Plus_Flag == 1)
			{
				Plus_Flag = 0;
				Kp1  += 0.01;
			}
				if(Encoder_Get_L()<0 && Plus_Flag == 1)
			{
				Plus_Flag = 0;
				Kp1  -= 0.01;
			}
			OLED_Update ();
		}
		
		if(Temp == 3)
		{
			OLED_Clear ();
			OLED_ShowString (0,0,"<-  ",OLED_8X16 );
			OLED_ShowString (0,20,"Speed I ",OLED_8X16 );
			OLED_ShowFloatNum (0,40,Ki1  ,2,2,OLED_8X16 );
			OLED_ReverseArea (0,40,50,16);
			if(Key  == 2) // 由于按键一被用于检测到哪一行，这里若仍用按键一判断，会直接退出
			{
				Temp = 0; // 清除编辑标志，下次循环将回到 switch 列表显示
				OLED_Clear(); 
			}
				if(Encoder_Get_R()>0 && Plus_Flag == 1)
			{
				Plus_Flag = 0;
				Ki1   += 0.01;
			}
				if(Encoder_Get_L()<0 && Plus_Flag == 1)
			{
				Plus_Flag = 0;
				Ki1   -= 0.01;
			}
			OLED_Update ();
		}
		
	}
}

uint8_t Menu3_TurnPID(void)
{
	uint8_t  Key;
	uint8_t  Menu3S_Flag = 1;
	uint8_t  Temp = 0;
	
	OLED_ShowString (0,0,"<-  ",OLED_8X16 );
	OLED_ShowString (0,20,"Turn P  ",OLED_8X16 );
	OLED_ShowString (0,40,"Turn D  ",OLED_8X16);
	OLED_Update ();
	while(1)
	{
		Key =Key_Getnum ();
		if(Key == 2 && Temp != 2 && Temp != 3)
		{
			Menu3S_Flag ++ ;
			if(Menu3S_Flag > 3)
			{
				Menu3S_Flag = 1;
			}
		}
		if(Key == 1)
		{
			Temp = Menu3S_Flag ;
		}
		
		if(Temp != 2 && Temp != 3)
		{
			switch(Menu3S_Flag)
			{
				case 1:
				{
					OLED_ShowString (0,0,"<-  ",OLED_8X16 );
					OLED_ShowString (0,20,"Turn P  ",OLED_8X16 );
					OLED_ShowString (0,40,"Turn D  ",OLED_8X16);
					OLED_ReverseArea (0,0,20,16);
					OLED_Update ();
				}
				break;
				
				case 2:
				{
					OLED_ShowString (0,0,"<-  ",OLED_8X16 );
					OLED_ShowString (0,20,"Turn P  ",OLED_8X16 );
					OLED_ShowString (0,40,"Turn D  ",OLED_8X16);
					OLED_ReverseArea (0,20,60,16);
					OLED_Update ();
				}
				break;
				
				case 3:
				{
					OLED_ShowString (0,0,"<-  ",OLED_8X16 );
					OLED_ShowString (0,20,"Turn P  ",OLED_8X16 );
					OLED_ShowString (0,40,"Turn D  ",OLED_8X16);
					OLED_ReverseArea (0,40,60,16);
					OLED_Update ();
				}
				break;
			}
		}
		
		if(Temp == 1)
		{
		 return 0;
		}
		
		if(Temp == 2)
		{
			OLED_Clear ();
			OLED_ShowString (0,0,"<-  ",OLED_8X16 );
			OLED_ShowString (0,20,"Turn P ",OLED_8X16 );
			OLED_ShowFloatNum (0,40,Kp2  ,2,2,OLED_8X16 );
			OLED_ReverseArea (0,40,50,16);
			if(Key  == 2) // 由于按键一被用于检测到哪一行，这里若仍用按键一判断，会直接退出
			{
				Temp = 0; // 清除编辑标志，下次循环将回到 switch 列表显示
				OLED_Clear(); 
			}
				if(Encoder_Get_R()>0 && Plus_Flag == 1)
			{
				Plus_Flag = 0;
				Kp2   += 0.01;
			}
				if(Encoder_Get_L()<0 && Plus_Flag == 1)
			{
				Plus_Flag = 0;
				Kp2   -= 0.01;
			}
			OLED_Update ();
		}
		
		if(Temp == 3)
		{
			OLED_Clear ();
			OLED_ShowString (0,0,"<-  ",OLED_8X16 );
			OLED_ShowString (0,20,"Turn D ",OLED_8X16 );
			OLED_ShowFloatNum (0,40,Kd2   ,2,2,OLED_8X16 );
			OLED_ReverseArea (0,40,50,16);
			if(Key  == 2) // 由于按键一被用于检测到哪一行，这里若仍用按键一判断，会直接退出
			{
				Temp = 0; // 清除编辑标志，下次循环将回到 switch 列表显示
				OLED_Clear(); 
			}
				if(Encoder_Get_R()>0 && Plus_Flag == 1)
			{
				Plus_Flag = 0;
				Kd2    += 0.01;
			}
				if(Encoder_Get_L()<0 && Plus_Flag == 1)
			{
				Plus_Flag = 0;
				Kd2    -= 0.01;
			}
			OLED_Update ();
		}
		
	}
}
