#ifndef __AD7792_H__
#define __AD7792_H__

#include "stm32f10x.h"

#define  CLK_1  GPIO_SetBits(GPIOA,GPIO_Pin_4)
#define  CLK_0  GPIO_ResetBits(GPIOA,GPIO_Pin_4)
#define  MOSI_1  GPIO_SetBits(GPIOA,GPIO_Pin_5)
#define  MOSI_0  GPIO_ResetBits(GPIOA,GPIO_Pin_5)
#define  AD7792_CS_1  GPIO_SetBits(GPIOA,GPIO_Pin_10)
#define  AD7792_CS_0  GPIO_ResetBits(GPIOA,GPIO_Pin_10)

typedef enum
{
	PD_measure=0,
	PD_main,
	PD_background,
	PD_ref
}PDChannal;

void AD7792_Init(void);
u16 AD_GetPD(PDChannal PD_Channal);

#endif
