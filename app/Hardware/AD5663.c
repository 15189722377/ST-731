/**
  ******************************************************************************
  * @file    AD5663.c
  * @author  bo.zhu
  * @version V0.0
  * @date    2017-11-01
  * @brief   
  ******************************************************************************
  * @attention
  *
  *  
  ******************************************************************************
  */ 
  /*************************************/
#include "AD5663.h"	
	
void AD5663_GpioInit(void)
{
	GPIO_InitTypeDef g;
	g.GPIO_Mode=GPIO_Mode_Out_PP;
	g.GPIO_Speed=GPIO_Speed_50MHz;
	
	g.GPIO_Pin=GPIO_Pin_4;    //AD5663_CLK
	GPIO_Init(GPIOA,&g);
	
	g.GPIO_Pin=GPIO_Pin_5;    //AD5663_MOSI   
	GPIO_Init(GPIOA,&g);
	
	g.GPIO_Pin=GPIO_Pin_7;    //AD5663_LDAC	 
	GPIO_Init(GPIOA,&g);
  
	g.GPIO_Pin=GPIO_Pin_8;    //AD5663_CLR		
	GPIO_Init(GPIOA,&g);	
  
  g.GPIO_Pin=GPIO_Pin_9;    //AD5663_CS		
	GPIO_Init(GPIOA,&g);	
  
  AD5663_LDAC_H;
  AD5663_CLR_L;  
 }

 /*************************************/
 void AD5663_WriteByteToReg(unsigned char byte)  
{				
	unsigned char i;

	for ( i = 0; i < 8; i++)
	{
			AD5663_CLK_H; 
			if ( byte & 0x80 )
			{
				AD5663_MOSI_H;
				delay_us(1);
			}
			else
			{
				AD5663_MOSI_L;
				delay_us(1);
			}
			AD5663_CLK_L; 
			byte <<= 1;     
	}
}

/**************************************/
void AD5663_dacData_Out(u16 dacChannel,u16 dacData)
{
  u8 Hdata,Ldata;
  Hdata=dacData>>8;
  Ldata=dacData&255;
  AD5663_CS_L;
	AD5663_LDAC_H;
  AD5663_WriteByteToReg(dacChannel);
  AD5663_WriteByteToReg(Hdata);
  AD5663_WriteByteToReg(Ldata);
	AD5663_LDAC_L;
  AD5663_CS_H;
}

/*************************************/
void AD5663_Vout(u16 dacChannel,float Vout)
{
	u16 dacData=0;
	
//	if(Vout<0.1)
//	{
//		Vout=0.1;
//	}
//	else if(Vout>1.1)
//	{
//		Vout=1.1;
//	}
	dacData=(Vout/3.3)*65536;
	AD5663_dacData_Out(dacChannel,dacData);
}
