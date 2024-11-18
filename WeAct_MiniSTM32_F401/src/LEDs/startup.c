#include "MPU.h"
#include "SCB.h"
#include "Systick.h"
#include "TIMx.h"

#include "API.h"

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
	Disable_System_Interrupts();
	Disable_External_Interrupts();

	DISABLE_MPU();

	//FPU Disabled after reset
	//Disable_FPUT();
	
	FLASH_Init();

	//Use PLL as SYSCLK
	__set_system_freq(84*MHz);

	//Minimum prescaling values for all buses
	//84MHz AHB domain
	//42MHz Low speed APB1
	//84MHz High speed APB2
	__maxout_system_domains();


	//Enable A, B, and C GPIO ports clock
	ENABLE_AHB_PORT_A();
	ENABLE_AHB_PORT_B();
	ENABLE_AHB_PORT_C();

	//Copy the data at the end of text section to RAM where it should be accessed
	for(uint8_t *t_pos = &__etext__, *d_pos = &__sdata__; d_pos < &__edata__; d_pos++, t_pos++)
	{
		*d_pos = *t_pos;
	}

	//Init the bss section to zero
	for(uint8_t *b_pos = &__sbss__; b_pos < &__ebss__; b_pos++)
	{
		*b_pos = 0UL;
	}

	//Do a lot of stuff here
	
	Enable_System_Interrutps();
	Enable_External_Interrupts();

	main();

}
