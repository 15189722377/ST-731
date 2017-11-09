#include "delay.h"

int main(void)
{
	int test=0;
	
	SysTick_CLKSourceConfig( SysTick_CLKSource_HCLK );
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO|RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC, ENABLE);
		
	delay_init();
	
	while(test<10)
	{
		delay_ms(1000);
		test++;
	}
	test=test;
}
