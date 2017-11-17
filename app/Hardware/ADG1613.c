#include "ADG1613.h"

void ADG1613_GpioInit(void)  //switch, used to choose PD channal
{
	GPIO_InitTypeDef g;
	
	g.GPIO_Mode=GPIO_Mode_Out_PP;
	g.GPIO_Speed=GPIO_Speed_50MHz;	
	g.GPIO_Pin=GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8;  
	
	GPIO_Init(GPIOB,&g);
}

void BackgroundPath_Connect(void)
{
	BACKPATH_CONNECT;
	DAC1_DISCONNECT;
}

void DAC1_Connect(void)
{
	DAC1_CONNECT;
	BACKPATH_DISCONNECT;
}

void PD1_Main_Out_Connect(void)
{
	PD1_MAIN_OUT_CONNECT;
  PD2_BACK_OUT_DISCONNECT;
}

void PD2_Back_Out_Connect(void)
{
	PD2_BACK_OUT_CONNECT;
	PD1_MAIN_OUT_DISCONNECT;
}
