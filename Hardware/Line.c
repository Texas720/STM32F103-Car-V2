//#include "stm32f10x.h"
//#include "Sensor.h"
//#include "Delay.h"
//#include "Encoder.h"  

//extern float SpeedTarget;//目标速度值
//extern float Base_Speed;//基础速度
//extern int8_t SensorGet[5];
//float rFinal_Left ; 
//float rFinal_Right;
//int8_t Error1, Error2, Error3;
//int32_t enc_diff;
//uint8_t Line_Flag;
//static uint8_t Ring_Flag;
//int8_t RSensorGet[5];
//uint8_t Turn_Flag1 = 0;//圆环处转向标志位
//uint8_t Turn_Flag2 = 0;//直角处转向标志位
//uint8_t Flag1 = 0;//如果有类似直角的状态出现，此标志位将置1
//static uint8_t Ring_Out = 0;
//uint16_t Check_Start = 0;//如果监测到在Outer——Masked置1后，丢线，则开始计时
//uint16_t Check_Flag = 0; //计时结束后，再次检查传感器结果，若还为全丢，则为直角弯
//uint8_t Outer_Masked = 0;//屏蔽标志位
//uint8_t Masked_Step = 0;//圆环内屏蔽阶段标志位
//uint8_t Masked_Step0_OK = 0;//入环完成标志位
//#define MASK_ENCODER_THRESHOLD 1200

///****************************************普通线路与圆环****************************************/
//uint8_t Find_Line(void)
//{
//  Sensor_Get(SensorGet);
//	uint8_t i = 0;
//	for(i = 0 ; i < 5 ;i ++ )
//	{
//		RSensorGet [i] = SensorGet [i];
//	}
//		//进入屏蔽条件,在非直角处，且屏蔽标志位为0
//    if (Turn_Flag2 == 0 && ((Outer_Masked == 0 && Masked_Step == 0) || (Outer_Masked == 0 && Masked_Step == 1)))
//    {
//        if ((SensorGet[0] < 0 && SensorGet[2] > 0 && SensorGet[1] == 0 ) || (SensorGet[4] > 0 && SensorGet[2] > 0 && SensorGet[3] == 0))
//        {
//            Outer_Masked = 1;//屏蔽标志位
//            Encoder_Clear_L();   // 清零编码器，开始计数
//            if(SensorGet[4] > 0 && SensorGet[2] > 0)
//            {
//              Turn_Flag1 = 1;//顺时针进入圆环
//							Ring_Out = 2;//逆时针出圆环
//            }
//            if(SensorGet[0] < 0 && SensorGet[2] > 0)
//            {
//              Turn_Flag1 = 2;//逆时针进入圆环
//							Ring_Out = 1;//顺时针出圆环
//            }
//        }
//    }
//    
//    // 退出屏蔽条件：编码器累积走过 1200 个脉冲，对应轮子转4/3圈
//    if (Outer_Masked != 0)
//    {
//         enc_diff = Encoder_Get_Total_L();  // 从清零后的累积值
//        if (enc_diff >= MASK_ENCODER_THRESHOLD || enc_diff <= -MASK_ENCODER_THRESHOLD)
//        {
//          Outer_Masked = 0;
//					Masked_Step0_OK = 1;//一阶段完成
//          Turn_Flag1 = 0;
//					if(Masked_Step == 1)
//					{
//						Masked_Step = 2;//结束圆环
//					}
//        }
//    }
//		//出环前，减速
//		if(Masked_Step == 1)
//		{
//			SpeedTarget = 0.5 * Base_Speed; 
//		}
//			if(Masked_Step == 2)
//		{
//			SpeedTarget =  Base_Speed; 
//		}
//    //执行屏蔽
//		if(Outer_Masked != 0)
//		{
//			if (Masked_Step == 0)
//			{
//				/*首先屏蔽最外侧两个传感器*/
//					SensorGet[0] = 0;
//					SensorGet[4] = 0;
//					if(Turn_Flag1 == 1)
//					{
//							SensorGet[1] = 0;
//					}
//					else if(Turn_Flag1 == 2)
//					{
//							SensorGet[3] = 0;
//					}
//			}
//			
//			if(Masked_Step == 1)//出环,执行屏蔽
//					{
//						SensorGet[0] = 0;
//						SensorGet[4] = 0;
//							if(Ring_Out == 2)
//						{
//								SensorGet[3] = 0;
//						}
//						else if(Ring_Out == 1)
//						{
//								SensorGet[1] = 0;
//						}
//					}
//		}

//    Error1 = 7 * SensorGet[0] + 4 * SensorGet[1] + (2 * SensorGet[3]) + (5 * SensorGet[4]);
//    
//    if(SensorGet[0]==0 && SensorGet[1]==0 && SensorGet[3]==0 && SensorGet[2]==0 && SensorGet[4]==0)
//    {
//        Ring_Flag = 0;
//        Line_Flag = 1;
//    }
//    else if(SensorGet[0]==0 && SensorGet[1]==0 && SensorGet[3]==0 && SensorGet[2]==1 && SensorGet[4]==7 && Ring_Flag==0)
//    {
//        Line_Flag = 2;
//    }
//    else if(SensorGet[0]==0 && SensorGet[1]==0 && SensorGet[3]==1 && SensorGet[2]==1 && SensorGet[4]==0)
//    {
//        Ring_Flag = 1;
//        Line_Flag = 3;
//    }
//    else if(SensorGet[0]==-5 && SensorGet[1]==0 && SensorGet[3]==0 && SensorGet[2]==1 && SensorGet[4]==0 && Ring_Flag==0)
//    {
//        Line_Flag = 4;
//    }
//    else if(SensorGet[0]==0 && SensorGet[1]==1 && SensorGet[3]==0 && SensorGet[2]==1 && SensorGet[4]==0)
//    {
//        Ring_Flag = 1;
//        Line_Flag = 5;
//    }
//    else if(SensorGet[0]==0 && SensorGet[1]==0 && SensorGet[2]==1 && SensorGet[3]==4 && SensorGet[4]==7)
//    {
//        Line_Flag = 6;
//    }
//    else if(SensorGet[0]==-5 && SensorGet[1]==-2 && SensorGet[2]==1 && SensorGet[3]==0 && SensorGet[4]==0)
//    {
//        Line_Flag = 7;
//    }
//    
//    return Line_Flag;
//}

//   //定时，到时间刷新屏蔽状态
//void Find_Line_Tick(void)
//{
//	static uint16_t Tick = 0;
//	if(Masked_Step0_OK  == 1)
//		Tick ++;
//	if(Tick > 300)
//	{
//		Tick = 0;
//		Masked_Step = 1 ;//准备进入出环状态
//	}
//	if (Masked_Step == 2)
//    {
//        Masked_Step = 0;
//        Masked_Step0_OK = 0;       // 清除标志，允许下次入环
//        Tick = 0;                  // 清零计时器防残留
//    }
//}



///************************************直角处转弯相关函数********************************************/
//void RightAngle_Turn(void)
//{

//    static uint16_t Flag1_Tick = 0;
//    
//	//检测直角，条件：在圆环阶段之外
//    if (Flag1 == 0 )
//    {
//        if ((RSensorGet[0] < 0 && RSensorGet[1] < 0 && RSensorGet[2] > 0))
//        {
//            Flag1 = 1;
//            Turn_Flag2 = 2;   // 左转
//        }
//        else if ((RSensorGet[2] > 0 && RSensorGet[3] > 0 && RSensorGet[4] > 0))
//        {
//            Flag1 = 1;
//            Turn_Flag2 = 1;   // 右转
//        }
//    }
//    
//    //Flag1 超时保护
//    if (Flag1 == 1)
//    {
//        Flag1_Tick++;
//        if (Flag1_Tick > 400)
//        {
//            Flag1 = 0;
//            Flag1_Tick = 0;
//            Turn_Flag2 = 0;
//        }
//    }
//    else
//    {
//        Flag1_Tick = 0;
//    }
//    

//    if (Flag1 == 1)//有时在直角弯会错误识别，进入屏蔽
//    {
//        if (SensorGet[0]==0 && SensorGet[1]==0 && SensorGet[2]==0 && SensorGet[3]==0 && SensorGet[4]==0)//如果全丢
//        {
//            Check_Start = 1;//开始计数
//            if (Check_Flag == 1)//计数完成
//            {
//                if (SensorGet[0]==0 && SensorGet[1]==0 && SensorGet[2]==0 && SensorGet[3]==0 && SensorGet[4]==0)//若依旧全丢
//                {
//									// 确认为直角
//                    Check_Flag = 0;
//                    Check_Start = 0;
//                    Outer_Masked = 0;
//                    Masked_Step = 0;
//                    Masked_Step0_OK = 0;
//                    Flag1 = 0;
//                    Flag1_Tick = 0;
//                }
//                else
//                {
//									//不是直角
//                    Check_Start = 0;
//                    Check_Flag = 0;
//                    Flag1 = 0;
//                    Flag1_Tick = 0;
//                }
//            }
//        }
//        else
//        {
//            Check_Start = 0;
//            Check_Flag = 0;
//        }
//    }
//    
//		
//    if (Turn_Flag2 == 1  && Outer_Masked == 0)       // 右转
//    {
//        rFinal_Left = 40.0f;
//        rFinal_Right = -40.0f;
//        if (SensorGet[3] > 0 || SensorGet[4] > 0)  // 右侧找到线
//        {
//            rFinal_Left = 0.0f;
//            rFinal_Right = 0.0f;
//            Turn_Flag2 = 0;
//        }
//    }
//    else if (Turn_Flag2 == 2 && Outer_Masked == 0)  // 左转
//    {
//        rFinal_Left =-40.0f;
//        rFinal_Right = 40.0f;
//        if (SensorGet[0] < 0 || SensorGet[1] < 0)  // 左侧找到线
//        {
//            rFinal_Left = 0.0f;
//            rFinal_Right = 0.0f;
//            Turn_Flag2 = 0;
//        }
//    }
//		
//		if(Masked_Step == 1)//出环之前，防止直角处转弯干扰
//		{
//			Turn_Flag2 = 0;
//		}
//}

//void RightAngle_Tick(void)
//{
//	static uint16_t Tick = 0;
//	Tick ++;
//	if(Tick > 300)//计时时间
//	{
//		Tick = 0;
//		Check_Flag = 1;
//	}
//	if(Check_Start == 0)
//	{
//		Tick = 0;
//	}
//}

#include "stm32f10x.h"
#include "Sensor.h"
#include "Delay.h"
#include "Encoder.h"  


extern float SpeedTarget;
extern float Base_Speed;
extern int8_t SensorGet[5];


float rFinal_Left;
float rFinal_Right;
int8_t Error1, Error2, Error3;
int32_t enc_diff;
uint8_t Line_Flag;
static uint8_t Ring_Flag;
int8_t RSensorGet[5];

/*==================== 圆环相关 ====================*/
uint8_t Turn_Flag1 = 0;         // 圆环转向: 1=顺时针入, 2=逆时针入
uint8_t Outer_Masked = 0;       // 屏蔽标志
uint8_t Masked_Step = 0;        // 0=入环屏蔽, 1=出环屏蔽, 2=结束
uint8_t Masked_Step0_OK = 0;    // 入环完成
static uint8_t Ring_Out = 0;    // 出环方向: 1=顺时针出, 2=逆时针出

/*==================== 直角相关 ====================*/
uint8_t Turn_Flag2 = 0;         // 直角转向: 1=右转, 2=左转
uint8_t Flag1 = 0;              // 直角检测,如果怀疑是直角，那么置1
uint16_t Check_Start = 0;       // 丢线计时开始
uint16_t Check_Flag = 0;        // 计时完成

/*==================== 宏定义 ====================*/
#define MASK_ENCODER_THRESHOLD  1200

/****************************************普通线路与圆环****************************************/
uint8_t Find_Line(void)
{
    Sensor_Get(SensorGet);
    
    for (uint8_t i = 0; i < 5; i++)
		{
				RSensorGet[i] = SensorGet[i];//如果进入屏蔽，SensorGet[]的值有可能会被改变，
		}																 //于是在每次检测后都进行一次存储
    
    /*-------- 进入屏蔽条件 --------*/
    if (Turn_Flag2 == 0 && ((Outer_Masked == 0 && Masked_Step == 0) || (Outer_Masked == 0 && Masked_Step == 1)))
    {
        if ((SensorGet[0] < 0 && SensorGet[2] > 0 && SensorGet[1] == 0) 
					|| (SensorGet[4] > 0 && SensorGet[2] > 0 && SensorGet[3] == 0))
        {
            Outer_Masked = 1;
            Encoder_Clear_L();
            
            if (SensorGet[4] > 0 && SensorGet[2] > 0)
            {
                Turn_Flag1 = 1;     // 顺时针进入圆环
                Ring_Out = 2;       // 逆时针出圆环
            }
            if (SensorGet[0] < 0 && SensorGet[2] > 0)
            {
                Turn_Flag1 = 2;     // 逆时针进入圆环
                Ring_Out = 1;       // 顺时针出圆环
            }
        }
    }
    
    /*-------- 退出屏蔽条件 --------*/
    if (Outer_Masked != 0)
    {
        enc_diff = Encoder_Get_Total_L();
        if (enc_diff >= MASK_ENCODER_THRESHOLD || enc_diff <= -MASK_ENCODER_THRESHOLD)
        {
            Outer_Masked = 0;
            Masked_Step0_OK = 1;
            Turn_Flag1 = 0;
            if (Masked_Step == 1)
                Masked_Step = 2;
        }
    }
    
    /*-------- 速度控制 --------*/
    if (Masked_Step == 1)
		{
			float Temp1 = 0.5 * Base_Speed ;
			if(Temp1 > 1.0)//如果速度大于这个值，有可能会冲出跑道
			{
				Temp1 = 1.0;
			}
			SpeedTarget = Temp1;
		}
    if (Masked_Step == 2)
        SpeedTarget = Base_Speed;
    
    /*-------- 执行屏蔽 --------*/
    if (Outer_Masked != 0)
    {
        if (Masked_Step == 0)
        {
					float Temp2 = Base_Speed ;
					if(Temp2 > 2.0)
					{
						Temp2 = 2.0;
					}
					SpeedTarget = Temp2 ;
            SensorGet[0] = 0;
            SensorGet[4] = 0;
            if (Turn_Flag1 == 1)
							SensorGet[1] = 0;
            else if (Turn_Flag1 == 2)
							SensorGet[3] = 0;
        }
        
        if (Masked_Step == 1)
        {
            SensorGet[0] = 0;
            SensorGet[4] = 0;
            if (Ring_Out == 2)
							SensorGet[3] = 0;
            else if (Ring_Out == 1)
							SensorGet[1] = 0;
        }
    }
    
    /*-------- 误差计算 --------*/
    Error1 = 7 * SensorGet[0] + 4 * SensorGet[1] + (2 * SensorGet[3]) + (5 * SensorGet[4]);
    
    /*-------- 线路判断 --------*/
    if (SensorGet[0]==0 && SensorGet[1]==0 && SensorGet[3]==0 && SensorGet[2]==0 && SensorGet[4]==0)
    {
        Ring_Flag = 0;
        Line_Flag = 1;//断线
    }
    else if (SensorGet[0]==0 && SensorGet[1]==0 && SensorGet[3]==0 && SensorGet[2]==1 && SensorGet[4]==7 && Ring_Flag==0)
        Line_Flag = 2;//顺时针入环
    else if (SensorGet[0]==0 && SensorGet[1]==0 && SensorGet[3]==1 && SensorGet[2]==1 && SensorGet[4]==0)
    {
        Ring_Flag = 1;
        Line_Flag = 3;//顺时针入环
    }
    else if (SensorGet[0]==-5 && SensorGet[1]==0 && SensorGet[3]==0 && SensorGet[2]==1 && SensorGet[4]==0 && Ring_Flag==0)
        Line_Flag = 4;//逆时针入环
    else if (SensorGet[0]==0 && SensorGet[1]==1 && SensorGet[3]==0 && SensorGet[2]==1 && SensorGet[4]==0)
    {
        Ring_Flag = 1;
        Line_Flag = 5;//逆时针入环
    }
    else if (SensorGet[0]==0 && SensorGet[1]==0 && SensorGet[2]==1 && SensorGet[3]==4 && SensorGet[4]==7)
        Line_Flag = 6;//右侧直角
    else if (SensorGet[0]==-5 && SensorGet[1]==-2 && SensorGet[2]==1 && SensorGet[3]==0 && SensorGet[4]==0)
        Line_Flag = 7;//左侧直角
    
    return Line_Flag;
}

/*-------- 圆环定时器 --------*/
void Find_Line_Tick(void)
{
    static uint16_t Tick = 0;
    
    if (Masked_Step0_OK == 1)
        Tick++;
    
    if (Tick > 300)
    {
        Tick = 0;
        Masked_Step = 1;
    }
    
    if (Masked_Step == 2)
    {
        Masked_Step = 0;
        Masked_Step0_OK = 0;
        Tick = 0;
    }
}




/************************************直角处转弯相关函数********************************************/
void RightAngle_Turn(void)
{
    static uint16_t Flag1_Tick = 0;
    
    /*直角检测*/
    if (Flag1 == 0 && Outer_Masked == 0 && Masked_Step == 0)
    {
        if (RSensorGet[0] < 0 && RSensorGet[1] < 0 && RSensorGet[2] > 0)
        {
            Flag1 = 1;
            Turn_Flag2 = 2;
        }
        else if (RSensorGet[2] > 0 && RSensorGet[3] > 0 && RSensorGet[4] > 0)
        {
            Flag1 = 1;
            Turn_Flag2 = 1;
        }
    }
    
    /***************Flag1 超时保护********************/
    if (Flag1 == 1)
    {
        Flag1_Tick++;
        if (Flag1_Tick > 400)
        {
            Flag1 = 0;
            Flag1_Tick = 0;
            Turn_Flag2 = 0;
            Check_Start = 0;     
            Check_Flag = 0;        
        }
    }
    else
    {
        Flag1_Tick = 0;
    }
    
    /*检查是否是直角*/
    if (Flag1 == 1)
    {
        if (SensorGet[0]==0 && SensorGet[1]==0 && SensorGet[2]==0 
            && SensorGet[3]==0 && SensorGet[4]==0)
        {
            Check_Start = 1;
            if (Check_Flag == 1)
            {
                if (SensorGet[0]==0 && SensorGet[1]==0 && SensorGet[2]==0 
                    && SensorGet[3]==0 && SensorGet[4]==0)
                {
                    Check_Flag = 0;
                    Check_Start = 0;
                    Outer_Masked = 0;
                    Masked_Step = 0;
                    Masked_Step0_OK = 0;
                    Flag1 = 2;
                    Flag1_Tick = 0;
                }
                else
                {
                    Check_Start = 0;
                    Check_Flag = 0;
                    Flag1 = 0;
                    Flag1_Tick = 0;
                    Turn_Flag2 = 0;  
                }
            }
        }
        else
        {
            Check_Start = 0;
            Check_Flag = 0;
        }
    }
    
    /**************执行转弯***************/
    if (Turn_Flag2 != 0 && Outer_Masked == 0)
    {
        if (Flag1 == 2)
        {
            if (Turn_Flag2 == 1)
            {
								Line_Flag = 6;
								rFinal_Left = 40.0f;
                rFinal_Right = -40.0f;
            }
            else if (Turn_Flag2 == 2)
            {
								Line_Flag = 7;
                rFinal_Left = -40.0f;
                rFinal_Right = 40.0f;
            }
            
            if (Turn_Flag2 == 1 && (SensorGet[3] > 0 || SensorGet[4] > 0))//转弯，直到一侧传感器找到线
            {
                rFinal_Left = 0.0f;
                rFinal_Right = 0.0f;
                Turn_Flag2 = 0;
                Flag1 = 0;           // 转弯完成
            }
            else if (Turn_Flag2 == 2 && (SensorGet[0] < 0 || SensorGet[1] < 0))//同上
            {
                rFinal_Left = 0.0f;
                rFinal_Right = 0.0f;
                Turn_Flag2 = 0;
                Flag1 = 0;           // 转弯完成
            }
        }
    }
    
    /************ 出环前限制直角转弯 ***********/
    if (Masked_Step == 1)
    {
        Turn_Flag2 = 0;
        Flag1 = 0;             
        Check_Start = 0;
        Check_Flag = 0;
    }
}

///***************直角丢线计时器*************/
//void RightAngle_Tick(void)
//{
//    static uint16_t Tick = 0;
//    
//    Tick++;
//    if (Tick > 150)//此处值的设置见下方
//    {
//        Tick = 0;
//        Check_Flag = 1;
//    }
//    if (Check_Start == 0)
//        Tick = 0;
//}


///*    Base_Speed             /        Tick           */
///*        2                  /          300          */
///*        3                  /          150          */

/***************直角丢线计时器*************/
void RightAngle_Tick(void)
{
    static uint16_t Tick = 0;
    
    Tick++;
		uint16_t Time = 0;
		switch((int)Base_Speed)
		{
			case 2:
			{
				Time = 300;
			}
				break ;
			case 3:
			{
				Time = 150;
			}
				break ;
			case 4:
			{
				Time = 40;
		}
				break ;
		}
    if (Tick > Time )//此处值的设置见下方
    {
        Tick = 0;
        Check_Flag = 1;
    }
    if (Check_Start == 0)
        Tick = 0;
}


/*    Base_Speed             /          Time         */
/*        2                  /          300          */
/*        3                  /          150          */
/*        4                  /          100          */
