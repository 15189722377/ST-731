#ifndef __ADG1613_H__
#define __ADG1613_H__

#include "stm32f10x.h"

#define BACKPATH_CONNECT     GPIO_SetBits(GPIOB,GPIO_Pin_5)  
#define BACKPATH_DISCONNECT  GPIO_ResetBits(GPIOB,GPIO_Pin_5)

#define DAC1_CONNECT         GPIO_SetBits(GPIOB,GPIO_Pin_6)  
#define DAC1_DISCONNECT      GPIO_ResetBits(GPIOB,GPIO_Pin_6)

#define PD1_MAIN_OUT_CONNECT     GPIO_SetBits(GPIOB,GPIO_Pin_7)  
#define PD1_MAIN_OUT_DISCONNECT  GPIO_ResetBits(GPIOB,GPIO_Pin_7)

#define PD2_BACK_OUT_CONNECT    GPIO_SetBits(GPIOB,GPIO_Pin_8)  
#define PD2_BACK_OUT_DISCONNECT  GPIO_ResetBits(GPIOB,GPIO_Pin_8)

#endif
