#include "app.h"
#include "AD5663.h"
#include "AD7792.h"
#include "mb.h"
#include "flash.h"
extern void AD5663_dacData_Out(u16 dacChannel,u16 dacData);
extern u8 bitmodbus;
extern void write_to_LTC2630ISC6(u8 Cmd, u16 Dat);
u8 i=0;
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

		if(bitmodbus==1)
		{
			StoreModbusReg();
		}
		AD5663_dacData_Out(0X19,39718);
		LED_TurnOn();
		delay_ms(500);
		LED_TurnOff();
		delay_ms(500);
//		delay_ms(100);			
//		AD_GetPD(PD_measure);	
	}
}
