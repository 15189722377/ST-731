/**
  ******************************************************************************
  * @file    LTC2630ISC6.h
  * @author  bo.zhu
  * @version V1.0
  * @date    2016-12-15
  * @brief   
  ******************************************************************************
  * @attention
  *
  *  
  ******************************************************************************
  */ 
#ifndef __LTC2630ISC6_H__
#define __LTC2630ISC6_H__

#include "stm32f10x.h"
#include "delay.h"

#define  DAC_CS_HIGH  GPIO_SetBits(GPIOB,GPIO_Pin_12)
#define  DAC_CS_LOW  GPIO_ResetBits(GPIOB,GPIO_Pin_12)

#define  DAC_CS1_HIGH  GPIO_SetBits(GPIOB,GPIO_Pin_11)
#define  DAC_CS1_LOW  GPIO_ResetBits(GPIOB,GPIO_Pin_11)

#define SPI_SLAVE_IN_BB_HIGH    GPIO_SetBits(GPIOA,GPIO_Pin_5)
#define SPI_SLAVE_IN_BB_LOW     GPIO_ResetBits(GPIOA,GPIO_Pin_5)

#define SPI_CLOCK_HIGH   GPIO_SetBits(GPIOA,GPIO_Pin_4)
#define SPI_CLOCK_LOW    GPIO_ResetBits(GPIOA,GPIO_Pin_4)

#define LTC2630ISC6_POWER_DOWN_ 0X70
#define LTC2630ISC6_WRITE_TO_AND_UPDATE 0X30

void LTC2630ISC6_Init(void );

void write_to_LTC2630ISC6(u8 Cmd, u16 Dat);

#endif
