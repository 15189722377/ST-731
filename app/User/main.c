#include "app.h"
#include "AD5663.h"
#include "AD7792.h"
#include "mb.h"
#include "flash.h"
extern void AD5663_dacData_Out(u16 dacChannel,u16 dacData);
extern u8 bitmodbus;
extern void write_to_LTC2630ISC6(u8 Cmd, u16 Dat);
extern void write_to_LTC2630_1(u8 Cmd, u16 Dat);
u8 i=0;
extern u8 isMeasureFlg;

void Measure(void)
{
  u16 PD_End;
	
	LED_TurnOn();
	write_to_LTC2630_1(0X30,sensor_param.DAC2); 
	delay_ms(200);
	sensor_param.pdEnd=AD_GetPD(PD_measure);
	
	LED_TurnOff();
}

int main(void)
{
	#define VECT_TAB_OFFSET  0x3000

	/* Set the Vector Table base address */
	NVIC_SetVectorTable(NVIC_VectTab_FLASH, VECT_TAB_OFFSET);
	
	System_Init();
	
	RestoreModbusReg();

	eMBInit(MB_RTU, comm_settings.modbusAddr, 0x02, comm_settings.modbusBaud, comm_settings.modbusParity); 
	eMBEnable();
	
	while(1)
	{		
		eMBPoll();	
		FunctionPoll();
		
//		AD5663_dacData_Out(dacA,sensor_param.VGA1);
//		AD5663_dacData_Out(dacB,sensor_param.VGA2);
//		delay_us(10);

		if(isMeasureFlg==1)
		{
			isMeasureFlg=0;
			Measure();
		}
	}
}
