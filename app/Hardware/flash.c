/**
  ******************************************************************************
  * @file    flash.c
  * @author  bo.zhu
  * @version V1.1
  * @date    2016-12-14
  * @brief   
  ******************************************************************************
  * @attention
  *
  *  
  ******************************************************************************
  */ 

/* Includes -------------------------------------------------------------------*/

#include "flash.h"
#include "string.h"
#include "app.h"
#include "stdlib.h"
#include "delay.h"

/* Private_Macros -------------------------------------------------------------*/

//���洢�ļĴ���������
#define REG_TYPE_NUM	6

/* Private_TypesDefinitions ---------------------------------------------------*/

typedef struct
{
	//ָ��modbus��ؼĴ�����ָ��
	void *p_reg;
	
	//һ�����͵ļĴ����ṹ���������Ĵ����ĸ���
	uint8_t reg_num;
	
}RegStoreType;

//������洢�Ĵ������׵�ַ�ͼĴ�������
RegStoreType regs_sturct[REG_TYPE_NUM]=
{
	{&system_status,SYSREG_NREGS},
	{&comm_settings,COMSREG_NREGS},	
	{&measure_settings,MSREG_NREGS},
	{&calib_settings,CALSREG_NREGS},
	{&filter_settings,FSREG_NREGS},
	//{&measure_values,MVREG_NREGS},
	{&sensor_param,SENSOR_NREGS}  
};

/* Private_Variables ----------------------------------------------------------*/

/* Private_Functions ----------------------------------------------------------*/

/**
  * @brief  ��ȡstm32�ڲ�flash���ݣ����֣�
  * @param  ��ַ
  * @retval ����������
  */
uint16_t STMFLASH_ReadHalfWord(uint32_t rd_addr)
{
	return *( (__IO uint16_t *)rd_addr );
}

/**
  * @brief  ����Ƿ���Ҫ����
  * @param  ��ַ
  * @retval ִ��״̬
  */
static FLASH_Status STMFLASH_Erase(uint32_t e_addr)
{
	uint16_t i,tmp;
	FLASH_Status status=FLASH_COMPLETE;
	
	//flash����
	FLASH_Unlock();
	
	//��������Ƿ��ѱ�����
	for(i=0;i < (PAGE_SIZE/2);i++)
	{
		tmp = *( (uint16_t*)(REG_STORAGE_ADDR + i*2));
		if(tmp != 0xffff)
			break;
	}
	
	//����δ������ִ�в�������
	if(i<PAGE_SIZE)
	{
		status=FLASH_ErasePage(REG_STORAGE_ADDR);
// 		/////1us   ---zb
 		delay_us(2);
		if(status!=FLASH_COMPLETE)
			return status;
	}
	
	//flash����
	FLASH_Lock();
	
	return status;
}

/**
  * @brief  �������ݵ�stm32�ڲ�flash
  * @param  pdata-ָ����������ݵ�ָ�룬w_addr-��ʼ��ַ��num_to_write-���ֵĸ���
  * @retval ִ��״̬
  */
static FLASH_Status STMFLASH_Write(void *pdata,uint8_t num_to_write)
{
	static uint16_t cnt=0;
	uint16_t i,*pd=pdata;
	uint32_t w_addr;
	FLASH_Status status=FLASH_COMPLETE;
	
	//flash����
	FLASH_Unlock();
	
	//�ṹ��洢��ʼ��ַ
	w_addr=REG_STORAGE_ADDR+cnt;	
	
	//д������
	for(i=0;i<num_to_write && status==FLASH_COMPLETE;i++)
	{
		status=FLASH_ProgramHalfWord(w_addr,*pd);		
		w_addr += 2;
		pd++;
	}		
	
	//��һ���ṹ��Ĵ洢��ʼ��ַ
	cnt += BYTE_OF_PER_REG;
	//zb  ����ƫ��
	if(cnt == REG_TYPE_NUM*BYTE_OF_PER_REG)
	{
		cnt=0;
	}
	
	//flash����
	FLASH_Lock();
	
	return status;
}

/**
  * @brief  �洢modbus�Ĵ���
  * @param  ��
  * @retval ִ��״̬
  */
FLASH_Status StoreModbusReg(void)
{
	u8 i;
	FLASH_Status s_status;
	
	//����flash
	s_status=STMFLASH_Erase(REG_STORAGE_ADDR);
	if(s_status != FLASH_COMPLETE)
		return s_status;
	
	//����Ĵ�����flash
	for( i=0 ; i < REG_TYPE_NUM ; i++ )
	{
		s_status=STMFLASH_Write(regs_sturct[i].p_reg , regs_sturct[i].reg_num);
		if(s_status != FLASH_COMPLETE)
			return s_status;
	}
	
	return s_status;
}

/**
  * @brief  ���ڲ�flash�ָ�modbus�Ĵ�������
  * @param  ��
  * @retval ��
  */
void RestoreModbusReg(void)
{
	system_status= *((__IO SYS_STATUS_T *)SYS_STATUS_SADDR);
	
	comm_settings= *((__IO COMM_SETTINGS_T *)COM_SET_SADDR);
	
	measure_settings= *((__IO MEASURE_SETTINGS_T *)MEASURE_SET_SADDR);
	
	calib_settings= *((__IO CALIB_SETTINGS_T *)CAL_SET_SADDR);
	
	filter_settings= *((__IO FILTER_SETTINGS_T *)FILTER_SET_SADDR);
	
	sensor_param= *((__IO SENSOR_PARAM_T *)PTSA_PARA_SADDR);
	
	//Check for the first time on power
	if(system_status.configStatus != 1)   
  {
		//Default parameters
		Parameters_Reset();
		StoreModbusReg();
	} 
	//�Է�̽ͷ����ʱ�������flash�����²���ÿ���ϵ�Ӧ��λ
	
}

/******************* (C) COPYRIGHT 2015 AndyChen *******END OF FILE*************/
