#ifndef NVIC_HEADER
#define NVIC_HEADER

#include "types.h"

typedef enum {

/////////////////////////////////////////	15 system exceptions:

	NMI_IRQn			= -14,	
	HARDFAULT_IRQn			= -13,
	MEMMANAGE_IRQn     		= -12,
	BUSFAULT_IRQn      		= -11,
	USAGEFAULT_IRQn    		= -10,
	SVCALL_IRQn        		= -5,
	DEBUG_MONITOR_IRQn 		= -4,
	PENDSV_IRQn        		= -2,
	SYSTICK_IRQn       		= -1,

/////////////////////////////////////////	56 perihperal/external exceptions:

	WWDG_IRQn              		= 0 ,	      /* 0x0040 */
	EXTI16_PVD_IRQn        		= 1 ,         /* 0x0044 */
	EXTI21_TAMP_STAMP_IRQn 		= 2 ,         /* 0x0048 */
	EXTI22_RTC_WKUP_IRQn   		= 3 ,         /* 0x004C */
	FLASH_IRQn             		= 4 ,         /* 0x0050 */
	RCC_IRQn               		= 5 ,         /* 0x0054 */
	EXTI0_IRQn             		= 6 ,         /* 0x0058 */
	EXTI1_IRQn             		= 7 ,         /* 0x005C */
	EXTI2_IRQn             		= 8 ,         /* 0x0060 */
	EXTI3_IRQn             		= 9 ,         /* 0x0064 */
	EXTI4_IRQn             		= 10,         /* 0x0068 */
	DMA1_STREAM0_IRQn      		= 11,         /* 0x006C */
	DMA1_STREAM1_IRQn      		= 12,         /* 0x0070 */
	DMA1_STREAM2_IRQn      		= 13,         /* 0x0074 */
	DMA1_STREAM3_IRQn      		= 14,         /* 0x0078 */
	DMA1_STREAM4_IRQn      		= 15,         /* 0x007C */
	DMA1_STREAM5_IRQn      		= 16,         /* 0x0080 */
	DMA1_STREAM6_IRQn      		= 17,         /* 0x0084 */
	ADC_IRQn               		= 18,         /* 0x0088 */

	EXTI9_5_IRQn           		= 23,         /* 0x009C */
	TIM1_BRK_TIM9_IRQn     		= 24,         /* 0x00A0 */
	TIM1_UP_TIM10_IRQn     		= 25,         /* 0x00A4 */
	TIM1_TRIG_COM_TIM11_IRQ		= 26,         /* 0x00A8 */
	TIM1_CC_IRQn           		= 27,         /* 0x00AC */
	TIM2_IRQn              		= 28,         /* 0x00B0 */
	TIM3_IRQn              		= 29,         /* 0x00B4 */
	TIM4_IRQn              		= 30,         /* 0x00B8 */
	I2C1_EV_IRQn           		= 31,         /* 0x00BC */
	I2C1_ER_IRQn           		= 32,         /* 0x00C0 */
	I2C2_EV_IRQn           		= 33,         /* 0x00C4 */
	I2C2_ER_IRQn           		= 34,         /* 0x00C8 */
	SPI1_IRQn              		= 35,         /* 0x00CC */
	SPI2_IRQn              		= 36,         /* 0x00D0 */
	USART1_IRQn            		= 37,         /* 0x00D4 */
	USART2_IRQn            		= 38,         /* 0x00D8 */

	EXTI15_10_IRQn         		= 40,         /* 0x00E0 */
	EXTI17_RTC_ALARM_IRQn  		= 41,         /* 0x00E4 */
	EXTI18_OTG_FS_WKUP_IRQn		= 42,         /* 0x00E8 */
	DMA1_STREAM7_IRQn      		= 47,         /* 0x00FC */
	SDIO_IRQn              		= 49,         /* 0x0104 */
	TIM5_IRQn              		= 50,         /* 0x0108 */
	SPI3_IRQn              		= 51,         /* 0x012C */

	DMA2_STREAM0_IRQn      		= 56,         /* 0x0120 */
	DMA2_STREAM1_IRQn      		= 57,         /* 0x0124 */
	DMA2_STREAM2_IRQn      		= 58,         /* 0x0128 */
	DMA2_STREAM3_IRQn      		= 59,         /* 0x012C */
	DMA2_STREAM4_IRQn      		= 60,         /* 0x0130 */
	OTG_FS_IRQn            		= 67,         /* 0x014C */
	DMA2_STREAM5_IRQn      		= 68,         /* 0x0150 */
	DMA2_STREAM6_IRQn      		= 69,         /* 0x0154 */
	DMA2_STREAM7_IRQn      		= 70,         /* 0x0158 */
	USART6_IRQn            		= 71,         /* 0x015C */
	I2C3_EV_IRQn           		= 72,         /* 0x0160 */
	I2C3_ER_IRQn           		= 73,         /* 0x0164 */
	FPU_IRQn               		= 81,         /* 0x0184 */
	SPI4_IRQn		  	= 84	      /* 0x0190 */
} IRQN_Type;

//---------------------------------------

//	Each interrupt has an Interrupt Number ranging from 0 up to 256
//	Each interrupt has 6 Control bits
//	Each Control bit has 8 Registers
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

typedef struct {

//--------Interrupt Controller Type Register (ICTR)--------//

	//ENABLE bit
	//SET ENABLE
	_IO uint32_t	ISER[8U];		
       		 
		_I uint32_t UNUSED_0[24U];

	//DISABLE bit
	//CLEAR ENABLE (DISABLE)
	_IO uint32_t	ICER[8U];		
	
		_I uint32_t UNUSED_1[24U];

	//PENDING bit
	//SET PENDING
	_IO uint32_t	ISPR[8U];		
        
		_I uint32_t UNUSED_2[24U];

	//Un-PENDING bit
	//CLEAR PENDING (Un-Pending)
	_IO uint32_t	ICPR[8U];		
        
		_I uint32_t UNUSED_3[24U];

	//ACTIVE BIT
	_I uint32_t IABR[8U];			

		_I uint32_t UNUSED_4[56U];
        
	_IO uint8_t IPR[240U];			

		_I uint32_t UNUSED_5[644U];

	//Software-Trigger bit
	_O uint32_t STIR;			

//---------------------------------------------------------//

} NVIC_Type;

#endif
