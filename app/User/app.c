#include "app.h"
#include "delay.h"
#include "AD7792.h"
#include "AD5663.h"
#include "LTC2630ISC6.h"
#include "string.h"
#include "flash.h"

u8 bitmodbus;

SYS_STATUS_T system_status;

COMM_SETTINGS_T comm_settings;

MEASURE_SETTINGS_T measure_settings;

CALIB_SETTINGS_T calib_settings;

FILTER_SETTINGS_T filter_settings;

MEASURE_VALUES_T measure_values;

SENSOR_PARAM_T sensor_param;

void LED_GpioInit(void);
void System_Init(void)
{
	SysTick_CLKSourceConfig( SysTick_CLKSource_HCLK );
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO|RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC, ENABLE);

	LED_GpioInit();
	delay_init();	
	AD5663_GpioInit();
	LTC2630ISC6_Init();
	AD7792_Init();	
}

void Parameters_Reset(void)
{
	memset(system_status.deviceName,0,sizeof(system_status.deviceName));
	memset(system_status.serialNum,0,sizeof(system_status.serialNum));
	memset(system_status.hardwareVer,0,sizeof(system_status.hardwareVer));
	memset(system_status.softwareVer,0,sizeof(system_status.softwareVer));
	
	system_status.runStatus=0;
	system_status.commStatus=0;
	system_status.calibStatus=0;
	system_status.configStatus=1;    //0  Œ¥≈‰÷√    1 “—≈‰÷√
	system_status.productNum=12345;
	strcpy(system_status.deviceName,"ST-731");
	strcpy(system_status.serialNum,"10");	
	strcpy(system_status.hardwareVer,HW_VERSION);
	strcpy(system_status.softwareVer,SW_VERSION);	
	
	comm_settings.modbusAddr=0x0A;	
	comm_settings.modbusDatabits=8;
	comm_settings.modbusParity=MODBUS_PARITY_EVEN;
	comm_settings.modbusBaud=9600;
	
	measure_settings.sampleCycle=4;
	measure_settings.measureRange=10;
	measure_settings.smoothingFactor=1.0;
	measure_settings.command=0;
	
	calib_settings.calibType=0;
	calib_settings.calibSolution=5;
	calib_settings.calibCommand=0;
	
	filter_settings.filterType=0;
	filter_settings.filterCoefficient_1=0.0;
	filter_settings.filterCoefficient_2=0.0;
	
	sensor_param.slope=1.0;
	sensor_param.intercept=0.0;
	sensor_param.t1=1.0;
	sensor_param.t2=1.0;
	sensor_param.mARange1=0.0;
	sensor_param.mARange2=10.0;
	sensor_param.reserved2=0;
	sensor_param.ledDelayTime=15;
	sensor_param.cLED1=100;
	sensor_param.cLED2=0;
	sensor_param.VGA1=1;
	
	StoreModbusReg();	
}

void LED_TurnOff(void);
void LED_GpioInit(void)
{
	GPIO_InitTypeDef g;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	g.GPIO_Pin=GPIO_Pin_9 | GPIO_Pin_10;
	g.GPIO_Mode=GPIO_Mode_Out_PP;
	g.GPIO_Speed=GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOB,&g);
	
	LED_TurnOff();
}

void LED_TurnOn(void)
{
	/* SW1,SW2: 11 , Select S4 */
	GPIO_SetBits(GPIOB,GPIO_Pin_9);   //LED SW2
	GPIO_SetBits(GPIOB,GPIO_Pin_10);  //LED SW1
	
	write_to_LTC2630ISC6(0X30,sensor_param.cLED1);
}

void LED_TurnOff(void)
{
	GPIO_ResetBits(GPIOB,GPIO_Pin_9);
	GPIO_ResetBits(GPIOB,GPIO_Pin_10);
}

