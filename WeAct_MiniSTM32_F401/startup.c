#include "MPU.h"
#include "SCB.h"
#include "NVIC.h"
#include "Systick.h"
#include "RCC.h"

#define Enable_Priority_IRQs()		asm inline("CPSIE i\n\t")
#define Disable_Priority_IRQs()		asm inline("CPSID i\n\t")

#define Enable_NonMaskable_IRQs()	asm inline("CPSIE f\n\t")
#define Disable_NonMaskable_IRQs()	asm inline("CPSID f\n\t")

#define Enable_MPU()	MPU->CTRL |= MPU_CTRL_ENABLE_MASK
#define Disable_MPU()	MPU->CTRL &= ~MPU_CTRL_ENABLE_MASK

extern uint32_t __stack_top__;
extern uint32_t __stack_size__;


extern uint32_t __etext__;
extern uint32_t __sdata__;	// load address = __etext__ but virtual access address is beginning of RAM (check .map and .list file for confirmation)
extern uint32_t __edata__;

extern uint32_t __sbss__;
extern uint32_t __ebss__;

extern void main(void);

__attribute__((interrupt, naked, noreturn)) void RESET(void)
{
	//Disable all interrupts
	Disable_Priority_IRQs();
	Disable_NonMaskable_IRQs();

	Disable_MPU();
	//FPU Disabled from reset
	
	//Use PLL as SYSCLK
	//After reset the HSI is tha main clock source (see RM0368 Rev 5 6.2.6)
	
	//Check if System clock switch selects PLL as system clock
	if((RCC->CFGR & RCC_CFGR_SWS_MASK) == 0x2UL << RCC_CFGR_SWS_POS)
	{
		//Enable HSI
		RCC->CR |= RCC_CR_HSION_MASK;
		//Wait until HSI is ready
		while((RCC->CR & RCC_CR_HSIRDY_MASK) == 0UL);
		
		//Set HSI as system clock
		RCC->CFGR &= ~RCC_CFGR_SW_MASK;

	}

	//Disable PLL
	RCC->CR &= ~RCC_CR_PLLON_MASK;

	//Wait until it's dead
	while((RCC->CR & RCC_CR_PLLRDY_MASK) == RCC_CR_PLLRDY_MASK);

	//HSI as Main PLL Input
	RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLSRC_MASK;

	//Configure PLL's VCO to 2MHz (HSI is 16MHz)
	RCC->PLLCFGR |= (0x8UL << RCC_PLLCFGR_PLLM_POS) | \

	/*Set PLL's N (VCO Multiplication Factor) to 168 MHz = 0xA8UL*/ \
			(0xA8UL << RCC_PLLCFGR_PLLN_POS) | \
	
	/*Set PLL's P to 2*/ \
			(0x2UL << RCC_PLLCFGR_PLLP_POS);

	//Now the Main PLL output equals to 84MHz
	//Turn on the princess back again
	RCC->CR |= RCC_CR_PLLON_MASK;
	
	//Select PLL as system clock
	RCC->CFGR |= (0x2UL << RCC_CFGR_SW_MASK);

	//Minimum prescaling values for all buses
	//84MHz AHB domain
		//42MHz Low speed APB1
			//84MHz High speed APB2
	RCC->CFGR |= ((0UL << RCC_CFGR_HPRE_POS) | (2UL << RCC_CFGR_PPRE1_POS) | (0UL << RCC_CFGR_PPRE2_POS));
	
	//Enable A, B, and C GPIO ports clock
	RCC->AHB1ENR |= (RCC_AHB1ENR_GPIOAEN_MASK | RCC_AHB1ENR_GPIOBEN_MASK | RCC_AHB1ENR_GPIOCEN_MASK);
	//Set CLKSOURCE of Systick to AHB's so it's fed 84MHz
	//STK->CTRL 

	//Copy the data at the end of text section to RAM where it should be accessed
	for(uint32_t *t_pos = &__etext__, *d_pos = &__sdata__; d_pos < &__edata__; d_pos++, t_pos++)
	{
		*d_pos = *t_pos;
	}

	//Init the bss section to zero
	for(uint32_t *b_pos = &__sbss__; b_pos < &__ebss__; b_pos++)
	{
		*b_pos = 0UL;
	}

	//Do a lot of stuff here
	
	Enable_NonMaskable_IRQs();
	Enable_Priority_IRQs();

	main();
}
