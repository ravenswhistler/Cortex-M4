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

extern void __set_system_freq(uint32_t frq);
extern void __maxout_system_domains(void);

__attribute__((interrupt, naked, noreturn)) void RESET(void)
{
	//Disable all interrupts
	Disable_Priority_IRQs();
	Disable_NonMaskable_IRQs();

	Disable_MPU();
	//FPU Disabled from reset
	
	//Use PLL as SYSCLK
	__set_system_freq(84000000UL);
	//Minimum prescaling values for all buses
	//84MHz AHB domain
	//42MHz Low speed APB1
	//84MHz High speed APB2
	__maxout_system_domains();

	//Enable A, B, and C GPIO ports clock
	RCC->AHB1ENR |= (RCC_AHB1ENR_GPIOAEN_MASK | RCC_AHB1ENR_GPIOBEN_MASK | RCC_AHB1ENR_GPIOCEN_MASK);

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
