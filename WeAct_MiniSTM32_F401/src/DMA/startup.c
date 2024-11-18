#include "API.h"

extern uint32_t __stack_top__;
extern uint32_t __stack_size__;

extern uint32_t __etext__;
extern uint32_t __sdata__;	// load address = __etext__ but virtual access address is beginning of RAM (check .map and .list file for confirmation)
extern uint32_t __edata__;
extern uint32_t __data_size__;
extern uint32_t __bss_size__;

extern uint32_t __sbss__;
extern uint32_t __ebss__;

extern void main(void);

__attribute__((interrupt, naked, noreturn)) void RESET(void)
{
	//Disable all interrupts
	Disable_System_Interrupts();
	Disable_External_Interrupts();

	//Disable_MPU();
	DISABLE_MPU();

	//FPU Disabled after reset
	//Disable_FPU();
	
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

	RESET_STK();
	while(!IS_CALIB_VAL_EXACT()) { }
	SET_STK_RELOAD(REAL_TENMS);
	SET_STK_CLKSRC_AHBdiv8();
	ENABLE_STK_TICKINT();

	LED_Config(GPIOC, GPIO_PORT_C_PIN13, 0);

	LED_Config(GPIOB, GPIO_PORT_B_PIN0, 0);
	LED_Config(GPIOB, GPIO_PORT_B_PIN1, 0);
	LED_Config(GPIOB, GPIO_PORT_B_PIN2, 0);

	LED_Config(GPIOB, GPIO_PORT_B_PIN4, 0);
	
	LED_Config(GPIOB, GPIO_PORT_B_PIN6, 0);
	LED_Config(GPIOB, GPIO_PORT_B_PIN7, 0);
	LED_Config(GPIOB, GPIO_PORT_B_PIN8, 0);
	LED_Config(GPIOB, GPIO_PORT_B_PIN9, 0);
	LED_Config(GPIOB, GPIO_PORT_B_PIN10, 0);

	LED_Config(GPIOB, GPIO_PORT_B_PIN12, 0);

	SET_NVIC_ICER();

	Enable_System_Interrutps();
	Enable_External_Interrupts();


	UNLOCK_SCB_AIRCR();
	SET_SCB_PRIORITY_GROUPING(NO_SUB_PRIO);

	SET_SCB_SYSTICK_PRIO(1);
	Set_IRQn_Priority(DMA2_STREAM0_IRQn, 2);
	ENABLE_SYSTICK();
	Enable_IRQ(DMA2_STREAM0_IRQn);


	//reserve space for excessive arguments
	asm inline("sub sp, #16\n\t");

	//Copy data section from flash to ram
	DMA_Mem_To_Mem(DMA_S0, (uint32_t)&__etext__, (uint32_t)&__sdata__, ((uint32_t)&__data_size__) >> 2, DMA2_S0_CH7, DMA_VHI_STRM_PRI, DMA_FIFO_FULL, DMA_WORD);

	//Init the bss section to zero
	for(uint32_t *b_pos = &__sbss__; b_pos < &__ebss__; b_pos++)
	{
		*b_pos = 0UL;
	}


	main();

}
