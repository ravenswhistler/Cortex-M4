#ifndef NVIC_HEADER
#define NVIC_HEADER

typedef enum {

/////////////////////////////////////////	15 system exceptions:

	NMI			 = -14,	
	HARDFAULT		 = -13,
	MEMMANAGE                = -12,
	BUSFAULT                 = -11,
	USAGEFAULT               = -10,
	SVCALL                   = -5,
	DEBUG_MONITOR            = -4,		/*What's the priority register for that interrupt?*/
	PENDSV                   = -2,
	SYSTICK                  = -1,

/////////////////////////////////////////	56 perihperal/external exceptions:

	WWDG                     = 0,
	EXTI16_PVD             	 = 1,
	EXTI21_TAMP_STAMP        = 2,
	EXTI22_RTC_WKUP          = 3,
	FLASH                    = 4,
	RCC                      = 5,
	EXTI0                    = 6,
	EXTI1                    = 7,
	EXTI2                    = 8,
	EXTI3                    = 9,
	EXTI4                    = 10,
	DMA1_STREAM0             = 11,
	DMA1_STREAM1             = 12,
	DMA1_STREAM2             = 13,
	DMA1_STREAM3             = 14,
	DMA1_STREAM4             = 15,
	DMA1_STREAM5             = 16,
	DMA1_STREAM6             = 17,
	ADC                      = 18,
	EXTI9_5                  = 19,
	TIM1_BRK_TIM9            = 20,
	TIM1_UP_TIM10            = 21,
	TIM1_TRIG_COM_TIM11      = 22,
	TIM1_CC                  = 23,
	TIM2                     = 24,
	TIM3                     = 25,
	TIM4                     = 26,
	I2C1_EV                  = 27,
	I2C1_ER                  = 28,
	I2C2_EV                  = 29,
	I2C2_ER                  = 30,
	SPI1                     = 31,
	SPI2                     = 32,
	USART1                   = 33,
	USART2                   = 34,
	EXTI15_10                = 35,
	EXTI17_RTC_ALARM         = 36,
	EXTI18_OTG_FS_WKUP       = 37,
	DMA1_STREAM7             = 38,
	SDIO                     = 39,
	TIM5                     = 40,
	SPI3                     = 41,
	DMA2_STREAM0             = 42,
	DMA2_STREAM1             = 43,
	DMA2_STREAM2             = 44,
	DMA2_STREAM3             = 45,
	DMA2_STREAM4             = 46,
	OTG_FS                   = 47,
	DMA2_STREAM5             = 48,
	DMA2_STREAM6             = 49,
	DMA2_STREAM7             = 50,
	USART6                   = 51,
	I2C3_EV                  = 52,
	I2C3_ER                  = 53,
	FPU                      = 54,
	SPI4			 = 55

} IRQN_Type;

//---------------------------------------

//Each interrupt has an Interrupt Number ranging from 0 up to 256
//Each interrupt has 6 Control bits
//Each Control bit has 8 Registers
//
//
//			1. Enable and disable an interrupt. Writing an enable bit to 1 can enable the corresponding interrupt. Writing an enable bit to 0 does not turn off the corresponding interrupt. Write a disable bit to 1 can disable the interrupt. Writing a disable bit to 0 has no impacts on the related interrupt. Separating enable bits and disable bits allows us to disable an interrupt conveniently with out affecting the other interrupts.

//			2. Pend and clear an interrupt. If an interrupt occurs, the corresponding pending bit is set if the microcontroller cannot process this interrupt immediately. Writing the clear pendi     ng bit to 1 removes the corresponding interrupt from the pending list.
//
//				When an interrupt is disabled but its pending bit has already been set, this interrupt instance remains active, and it is serviced before it is disabled.
//
//                      3. Trigger an interrupt. Setting an active bit by software or hardware activates the related interrupt, and the microcontroller starts the corresponding interrupt handler. If software writes a trigger bit of the software trigger interrupt register (STIR) to 1, the related interrupt is also activated. Most system exceptions can only be activated by hardware.

#define		NVIC_BASE	(0xE000E100UL)
#define		NVIC		((NVIC_Type*)NVIC_BASE)

typedef struct {			/*Base = 0xE000E100*/

//--------Interrupt Controller Type Register (ICTR)--------//

	//ENABLE bit
	//SET ENABLE
	_IO uint32_t	ISER[8U];		/*offset = 0x000	32B	0xE100 -> 0xE11F */
       		 
		uint32_t UNUSED_0[24U];

	//DISABLE bit
	//CLEAR ENABLE (DISABLE)
	_IO uint32_t	ICER[8U];		/*offset = 0x080	32B	0xE180 -> 0xE19F*/
	
		uint32_t UNUSED_1[24U];

	//PENDING bit
	//SET PENDING
	_IO uint32_t	ISPR[8U];		/*offset = 0x100	32B	0xE200 -> 0xE21F*/
        
		uint32_t UNUSED_2[24U];

	//Un-PENDING bit
	//CLEAR PENDING (Un-Pending)
	_IO uint32_t	ICPR[8U];		/*offset = 0x180	32B	0xE280 -> 0xE29f*/
        
		uint32_t UNUSED_3[24U];

	//ACTIVE BIT
	_IO uint32_t IABR[8U];			/*offset = 0x200	32B	0xE300 -> 0xE31F*/

		uint32_t UNUSED_4[56U];
        
	_IO uint8_t IPR[240U];			/*offset = 0x300	60B	0xE400 -> 0xE4EF*/

		uint32_t UNUSED_5[644U];

	//Software-Trigger bit
	_O uint32_t STIR;				/*offset = 0xE00	8B*/

//---------------------------------------------------------//

} NVIC_Type;

#endif
