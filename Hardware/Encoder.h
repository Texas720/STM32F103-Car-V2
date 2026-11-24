#ifndef __ENCODER_H
#define __ENCODER_H

void Encoder_Init(void);
int16_t Encoder_Get_L(void);
int16_t Encoder_Get_R(void);
void Encoder_Clear_L(void) ;
void Encoder_Clear_R(void);
int32_t Encoder_Get_Total_L(void);
int32_t Encoder_Get_Total_R(void);

#endif
