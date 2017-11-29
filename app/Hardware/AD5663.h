/**
  ******************************************************************************
  * @file    AD5663.h
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
#ifndef __AD5663_H__
#define __AD5663_H__

#include "stm32f10x.h"
#include "delay.h"

#define  AD5663_LDAC_H  GPIO_SetBits(GPIOA,GPIO_Pin_7)
#define  AD5663_LDAC_L  GPIO_ResetBits(GPIOA,GPIO_Pin_7)

#define  AD5663_CLR_H   GPIO_SetBits(GPIOA,GPIO_Pin_8)
#define  AD5663_CLR_L   GPIO_ResetBits(GPIOA,GPIO_Pin_8)

#define  AD5663_CS_H    GPIO_SetBits(GPIOA,GPIO_Pin_9)
#define  AD5663_CS_L    GPIO_ResetBits(GPIOA,GPIO_Pin_9)

#define  AD5663_CLK_H   GPIO_SetBits(GPIOA,GPIO_Pin_4)
#define  AD5663_CLK_L   GPIO_ResetBits(GPIOA,GPIO_Pin_4)

#define  AD5663_MOSI_H  GPIO_SetBits(GPIOA,GPIO_Pin_5)
#define  AD5663_MOSI_L  GPIO_ResetBits(GPIOA,GPIO_Pin_5)

#define  dacA  0X18   //write to and update dac channel A 
#define  dacB  0X19   //write to and update dac channel B

void AD5663_GpioInit(void);
void AD5663_Vout(u8 dacChannel,float Vout);

#endif
