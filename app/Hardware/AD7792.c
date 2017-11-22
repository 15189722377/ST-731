#include "AD7792.h"
#include "delay.h"
#include "app.h"

unsigned char DataRead[3];

static void AD7792_GpioInit(void)
{
	GPIO_InitTypeDef g;
	
	g.GPIO_Mode=GPIO_Mode_Out_PP;
	g.GPIO_Speed=GPIO_Speed_50MHz;
	
	g.GPIO_Pin=GPIO_Pin_4;    //AD7792_CLK
	GPIO_Init(GPIOA,&g);
	
	g.GPIO_Pin=GPIO_Pin_5;    //AD7792_MOSI   
	GPIO_Init(GPIOA,&g);
  
	g.GPIO_Pin=GPIO_Pin_10;   //AD7792_CS		
	GPIO_Init(GPIOA,&g);	
	GPIO_Init(GPIOA,&g);
	
	g.GPIO_Mode=GPIO_Mode_IPU;
	g.GPIO_Pin=GPIO_Pin_6;    //AD7792_MISO	 
	GPIO_Init(GPIOA,&g);
}

void Delay(unsigned int Time)
{
	while(Time)
	{
		Time--;
	}
}

void WriteToReg(unsigned char ByteData);
void Write2bytes(u16 data);
void ReadFromReg(unsigned char nByte);
void AD7792_Init(void)
{
	int ResetTime;
	
	AD7792_GpioInit();
	/* Set up UART */
	
	/* PRECONFIGURE...*/
	ResetTime=32;
	CLK_1;
 	AD7792_CS_0;		  //to keep DIN=1 for 32 sclock to reset the part
 	MOSI_1;
 	while(ResetTime--)
	{
		Delay(10);
		CLK_0;
		Delay(10);
 		CLK_1;
	}
 	AD7792_CS_1;	
	
	WriteToReg(0x00|(1<<3));//write mode register,  1:mode register
	Write2bytes(0x400a);	// idle mode, 120ms refresh rate
	
  /*  AIN1+, AIN1-,  calib  */
	WriteToReg(0x00|(2<<3));//write configuration register,  1:configuration register
	Write2bytes(0x1000);	// uni-polar, 1-times gain, enable input buffer, channel:AIN1(+)-AIN1(-)

	WriteToReg(0x00|(5<<3));//write IO register,  1:IO register
	WriteToReg(0x00);		//disable internal excitation current source
	
	WriteToReg(0x00|(1<<3));//write mode register,  1:mode register
	Write2bytes(0x800a);	// internal zero scale calibration
	delay_ms(240);     //it takes two convert period to calib. convert period=2/fADC=2/16.7=119.76ms
	
	WriteToReg(0x00|(1<<3));//write mode register,  1:mode register
	Write2bytes(0xa00a);	// internal full scale calibration
	delay_ms(240);     //it takes two convert period to calib. convert period=2/fADC=2/16.7=119.76ms
	
	/*  AIN2+, AIN2-,   calib  */
	WriteToReg(0x00|(2<<3));//write configuration register,  1:configuration register
	Write2bytes(0x1001);	// uni-polar, 1-times gain, enable input buffer, channel:AIN2(+)-AIN2(-)
	
	WriteToReg(0x00|(1<<3));//write mode register,  1:mode register
	Write2bytes(0x800a);	// internal zero scale calibration
	delay_ms(240);
	
	WriteToReg(0x00|(1<<3));//write mode register,  1:mode register
	Write2bytes(0xa00a);	// internal full scale calibration
	delay_ms(240);	

	WriteToReg(0x00|(1<<3));//write mode register,  1:mode register
	Write2bytes(0x000a);	// start contiguous conversion
	delay_ms(240);      //first conversion occurs after 2/fADC, conversion period is 2/fADC
}    

void WriteToReg(unsigned char ByteData) // write ByteData to the register
{
	unsigned char temp=0x80;
	int i;	
	
	AD7792_CS_0;
	
	for(i=0;i<8;i++)
	{
 		if((temp & ByteData)==0)
		{		
       MOSI_0;
		}	
 		else
		{
			 MOSI_1;
    }
		CLK_0;
		Delay(10);
	  CLK_1;
		Delay(10);
 		temp=temp>>1;
	}
	AD7792_CS_1;
}

void delayLoop(unsigned int Time)
{
		Time*=3;
		while(Time--)
		{
			__nop();
		}
}

void Write2bytes(u16 data)
{
	int i=0;

	AD7792_CS_0;
	for(i=0; i<16; i++)
	{
		if(data&0x8000)
		{
			MOSI_1;
		}
		else
		{
			MOSI_0;
		}

		data<<=1;
		CLK_0;
		delayLoop(10);
		CLK_1;
		delayLoop(10);
	}
	AD7792_CS_1;
}

void ReadFromReg(unsigned char nByte) // nByte is the number of bytes which need to be read
{
	int i,j;
  unsigned char temp=0;
	
 	MOSI_1;
 	AD7792_CS_0;

	for(i=0; i<nByte; i++)
	{
		for(j=0; j<8; j++)
	  {
			CLK_0;
			if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6)==0)  //PA6, MISO
			{				
				temp=temp<<1;
			}
			else
			{
				temp=temp<<1;
				temp=temp+0x01;
			}
			Delay(10);
			CLK_1;
			Delay(10);
		}
			DataRead[i]=temp;
			temp=0;
	}
  AD7792_CS_1;
}

PDChannal PD_Channal;
u16 AD_GetPD(PDChannal PD_Channal)
{
	u8 count;
	u32 temp;
	u16 tempMax=0;
	u16 tempMin=65535;
	u32 tempAverage=0;
	
	/* select PD */
	switch (PD_Channal)
	{
		case PD_measure:
		{
			WriteToReg(0x00|(2<<3));//write configuration register,  1:configuration register
			Write2bytes(0x1000);	// uni-polar, 1-times gain, enable input buffer, channel:AIN1(+)-AIN1(-)
      delay_ms(240);			
			break;
		}
//		case PD_main:
//		{
//			WriteToReg(0x00|(2<<3));//write configuration register,  1:configuration register
//			Write2bytes(0x1212);	// uni-polar, 4-times gain, enable input buffer, channel:AIN3(+)-AIN3(-)			
//			break;
//		}
//		case PD_background:
//		{
//			WriteToReg(0x00|(2<<3));//write configuration register,  1:configuration register
//			Write2bytes(0x1212);	// uni-polar, 4-times gain, enable input buffer, channel:AIN3(+)-AIN3(-)			
//			break;
//		}
		case PD_ref:
		{
			WriteToReg(0x00|(2<<3));//write configuration register,  1:configuration register
			Write2bytes(0x1001);	// uni-polar, 1-times gain, enable input buffer, channel:AIN2(+)-AIN2(-)	
      delay_ms(240);			
			break;
		}
		default: break;
	}
	
//	WriteToReg(0x00|(1<<3));//write mode register,  1:mode register
//	Write2bytes(0x000a);	// start contiguous conversion
//	delay_ms(40);
	
	/* start to read from ADC register*/
	for (count=0; count<40; count++)
	{
		temp = 0;

		__disable_irq();
		
		WriteToReg(0x40);//write to Communication register.The next step is to read from Status register.
		ReadFromReg(1);//¶ÁÈ¡×´Ì¬¼Ä´æÆ÷	
		
		while((DataRead[0]&0x10)!=0x00)   //????????????????????????????????????????????
		{
			WriteToReg(0x40);//write to Communication register.The next step is to read from Status register.
		  ReadFromReg(1);//¶ÁÈ¡×´Ì¬¼Ä´æÆ÷	
		}

		WriteToReg(0x58);//write to Communication register.The next step is to read from Data register.
		ReadFromReg(2);//¶ÁÈ¡½á¹û¼Ä´æÆ÷
		
		__enable_irq();

		temp=DataRead[0];
		temp<<=8;
		temp+=DataRead[1];
     
    filter_settings.ad7792[count]=temp;
		
		if (temp > tempMax)
			tempMax = temp;
		if (temp < tempMin)
			tempMin = temp;

		tempAverage += temp;
	}

	tempAverage -= (tempMax+tempMin);
	tempAverage /= 38;
	temp = (u16)tempAverage;
	
	return temp;
	
	/* save PD value in modbus register*/
//	switch (PD_Channal)
//	{
//		case PD_measure:
//		{
//			sensor_param.pdEnd=temp;
//			break;
//		}
//		case PD_main:
//		{
//			sensor_param.PD1=temp;		
//			break;
//		}
//		case PD_background:
//		{
//			sensor_param.PD2=temp;
//			break;
//		}
//		case PD_ref:
//		{
//			sensor_param.PD3=temp;		
//			break;
//		}
//		default: break;
//	}	
}
