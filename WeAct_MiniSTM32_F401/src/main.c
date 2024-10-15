#include "types.h"
#include "GPIO.h"
#include "Systick.h"
#include "RCC.h"

volatile uint32_t time = 0;

__attribute__((interrupt, noreturn)) void Systick(void)
{
	if(time > 0) time--;
}

void Delay(uint32_t D)
{
	time = D;
	while(time != 0);
}
void main()
{
	//Halt if the PLL isn't the system clock
	if(RCC->CFGR & RCC_CFGR_SWS_MASK != 10 << RCC_CFGR_SWS_POS) { while(1) {} }

	//Systick Clear
	STK->CTRL = 0UL;
	
	//Halt if the TENMS isn't accurate
	if(STK->CALIB & STK_CALIB_SKEW_MASK == ~STK_CALIB_SKEW_MASK) { while(1) { } }

	//Make Reload equals to 10ms worth of ticks
	STK->LOAD = (STK->CALIB & STK_CALIB_TENMS_MASK)*10;
	//Clear Current Value						    
	STK->VAL = 0UL;
	//Set CLK source to AHB HCLK 
	STK->CTRL |= (STK_CTRL_TICINT_MASK) | (STK_CTRL_CLKSOURCE_MASK);

	//Clear and Set Moder to output mode
	GPIOC->MODER &= ~GPIO_MODER_MASK(13U);
	GPIOC->MODER |= (1UL << GPIO_MODER_POS(13U));

	//Open-Drain
	GPIOC->OTYPER |= GPIO_OTYPER_MASK(13U);

	//Low Speed
	GPIOC->OSPEEDR &=  ~GPIO_OSPEEDR_MASK(13U);

	//No Puul No Push
	GPIOC->PUPDR &=  ~GPIO_PUPDR_MASK(13U);

	//Enable Systick
	STK->CTRL |= STK_CTRL_ENABLE_MASK;

	while(1) {
		//Toggle LED
		GPIOC->ODR ^= GPIO_ODR_MASK(13U);
		Delay(100);
	}

	
}
