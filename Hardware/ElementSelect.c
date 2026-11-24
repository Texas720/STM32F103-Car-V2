//#include "stm32f10x.h"                  // Device header
//#include "Line.h"

//extern int8_t SensorGet[5];
//extern float AverageSpeed;
//extern uint8_t Line_Flag;
//extern float Base_Speed; // 在 main.c 中定义，由按键控制
//extern float SpeedTarget;//中转量
//float Out_Re;
//int16_t case1_Flag;
//void Element_Select(void)
//{
//	
//	switch(Line_Flag)
//	{
//		case 0://正常行驶
//		{
//			
//			Out_Re = 0;
//			SpeedTarget = Base_Speed ;
//		}
//		break;
//		
//		case 1:   // 断线
//    {
//            // 检查传感器是否依然全部为0（即依然处于断线状态）
//       if(SensorGet[0]==0 && SensorGet[1]==0 && SensorGet[2]==0 &&  SensorGet[3]==0 && SensorGet[4]==0)
//          {
//                // 若依然断线，降低速度
//                SpeedTarget = Base_Speed * 0.8f; 
//								case1_Flag ++;
//          }
//        else
//          {
//                // 传感器有值了，说明找到线了
//						case1_Flag = 0;
//            SpeedTarget = Base_Speed;
//          }
//					if(case1_Flag >= 1200)//断线标志位计数到1200，则证明真的到断线位置了
//					{
//					 SpeedTarget = 0;
//					}
//     }
//     break;		
//		
//		case 2:  //值为2，判断圆环,顺时针方向
//		{
//			Out_Re = 0;
//			SpeedTarget = Base_Speed  * 0.8;//减速
//		}
//		break;
//		
//		case 3:  //值为3，准备右转进入圆环
//		{
//			Out_Re  = - 2;//对左轮加速
//			SpeedTarget =Base_Speed  * 0.8;//减速
//		}
//		break;
//		
//		case 4:  //值为4，判断圆环,逆时针方向
//		{
//			Out_Re = 0;
//			SpeedTarget = Base_Speed  * 0.8;
//		}
//		break;
//		
//		case 5:
//		{
//			Out_Re = + 2;//对右轮加速
//			SpeedTarget = Base_Speed  * 0.8;//减速
//		}
//		break;
//		
////		case 6://判断直角,顺时针方向
////		{
////			//亮灯
////		}
////		break;
////		
////		case 7://判断直角,逆时针方向
////		{
////			//亮灯
////		}
////		break;
////		
//		default:
//						case1_Flag = 0;
//            Out_Re = 0;
//            SpeedTarget = Base_Speed;
//            break;
//	 }
//}

#include "stm32f10x.h"
#include "Line.h"
#include "Light.h"

extern int8_t SensorGet[5];
extern float AverageSpeed;
extern uint8_t Line_Flag;
extern float Base_Speed; 
extern float SpeedTarget;
extern uint8_t Masked_Step;

int16_t case1_Flag = 0; 

void Element_Select(void)
{
	LED_Status_Update ();
	  if (Masked_Step == 1) 
		{
			return;
		}
    switch(Line_Flag)
    {
        case 0: // 正常行驶
        {
					Light_Off ();
					SpeedTarget = Base_Speed;//只在出环状态下限速
          case1_Flag = 0; // 只要压到线，立刻清零计数器
        }
        break;
        
        case 1:   // 断线标志位
        {
            
            // 检查是否依然处于断线状态
            if(SensorGet[0]==0 && SensorGet[1]==0 && SensorGet[2]==0 && 
               SensorGet[3]==0 && SensorGet[4]==0)
            {
                case1_Flag++; // 断线计数器累加
                
                if(case1_Flag >= 1200)
                {
                    // 超过阈值
                 SpeedTarget = 0;								
                }
                else
                {
                    // 还没超过阈值
                  SpeedTarget = Base_Speed * 0.5f; 
                }
            }
            else
            {
              case1_Flag = 0; 
              SpeedTarget = Base_Speed;
							Light_Off ();
            }
        }
        break;
        
        case 2:   // 顺时针圆环
        {
          
          SpeedTarget = Base_Speed * 0.8f;
          case1_Flag = 0; 
        }
        break;
        
        case 3:   // 准备右转进入圆环
        {
          SpeedTarget = Base_Speed;
          case1_Flag = 0; 
        }
        break;
        
        case 4:   // 逆时针圆环
        {
          SpeedTarget = Base_Speed * 0.8f;
          case1_Flag = 0; 
        }
        break;
        
        case 5:   // 准备左转进入圆环
        {
          SpeedTarget = Base_Speed ;
          case1_Flag = 0; 
        }
        break;
				
				case 6: // 直角顺时针
				{
          SpeedTarget = Base_Speed * 0.5f; 
          case1_Flag = 0;
				}
         break;
				
        case 7: // 直角逆时针
				{           
          SpeedTarget = Base_Speed * 0.5f; 
          case1_Flag = 0;
				}
          break;
        
        default:  
        {
          SpeedTarget = Base_Speed;
          case1_Flag = 0; 
        }
        break;
				
    }
}
