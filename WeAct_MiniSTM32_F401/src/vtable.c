#include "types.h"

extern	uint32_t __stack_top__;
extern void RESET(void);


//---------------System interrupts--------------//

#define IRQs																	\
	X(NMI)				/*Non maskable interrupt, Clock Security System*/							\
	X(HardFault)			/*All class of fault*/											\
	X(MemManage)			/*Memory management*/											\
	X(BusFault)			/*Pre-fetch fault, memory access fault*/								\
	X(UsageFault)			/*Undefined instruction or illegal state*/								\
	X(SVCall)			/*System Service call via SWI instruction*/								\
	X(Debug_Monitor)		/*Monitor Debug Monitor*/										\
	X(PendSV)			/*Pendable request for system service*/									\
	X(Systick)			/*System tick timer*/											\
																		\
/*-------------Non System interrupts------------*/												\
																		\
	X(WWDG)				/*WWDG Window Watchdog interrupt*/									\
	X(EXTI16_PVD)                   /*EXTI Line 16 interrupt / PVD through EXTI line detection interrupt*/					\
	X(EXTI21_TAMP_STAMP)            /*EXTI Line 21 interrupt / Tamper and TimeStamp interrupts through the EXTI line*/ 			\
	X(EXTI22_RTC_WKUP)              /*EXTI Line 22 interrupt / RTC Wakeup interrupt through the EXTI line*/ 				\
	X(FLASH)                        /*FLASH Flash global interrupt 0x0000 0050 5 12 settable RCC RCC global interrupt*/ 			\
	X(_RCC)                         /*FLASH Flash global interrupt 0x0000 0050 5 12 settable RCC RCC global interrupt*/ 			\
	X(EXTI0)                        /*EXTI0 EXTI Line0 interrupt*/										\
	X(EXTI1)                        /*EXTI1 EXTI Line1 interrupt*/										\
	X(EXTI2)                        /*EXTI2 EXTI Line2 interrupt*/										\
	X(EXTI3)                        /*EXTI3 EXTI Line3 interrupt*/										\
	X(EXTI4)                        /*EXTI4 EXTI Line4 interrupt*/										\
	X(DMA1_Stream0)                 /*DMA1_Stream0 DMA1 Stream0 global interrupt*/								\
	X(DMA1_Stream1)                 /*DMA1_Stream1 DMA1 Stream1 global interrupt*/								\
	X(DMA1_Stream2)                 /*DMA1_Stream2 DMA1 Stream2 global interrupt*/								\
	X(DMA1_Stream3)                 /*DMA1_Stream3*/											\
	X(DMA1_Stream4)                 /*DMA1_Stream4 DMA1 Stream4 global interrupt*/ 								\
	X(DMA1_Stream5)                 /*DMA1_Stream5 DMA1 Stream5 global interrupt*/ 								\
	X(DMA1_Stream6)                 /*DMA1_Stream6 DMA1 Stream6 global interrupt*/ 								\
	X(ADC)                          /*ADC ADC1 global interrupts*/ 										\
	X(EXTI9_5)                      /*EXTI9_5 EXTI Line[9:5] interrupts*/ 									\
	X(TIM1_BRK_TIM9)                /*TIM1_BRK_TIM9 TIM1 Break interrupt and TIM9 global interrupt*/ 					\
	X(TIM1_UP_TIM10)                /*TIM1_UP_TIM10 TIM1 Update interrupt and TIM10 global interrupt*/ 					\
	X(TIM1_TRG_COM_TIM11)           /*TIM1_TRG_COM_TIM11 TIM1 Trigger and Commutation interrupts and TIM11 global interrupt*/ 		\
	X(TIM1_CC)                      /*TIM1_CC TIM1 Capture Compare interrupt*/	 							\
	X(TIM2)                         /*TIM2 TIM2 global interrupt*/ 										\
	X(_TIM3)                        /*TIM3 TIM3 global interrupt*/ 										\
	X(TIM4)                         /*TIM4 TIM4 global interrupt*/ 										\
	X(I2C1_EV)                      /*I2C1_EV I2C1 event interrupt*/									\
	X(I2C1_ER)                      /*I2C1_ER I2C1 error interrupt*/									\
	X(I2C2_EV)                      /*I2C2_EV I2C2 event interrupt*/									\
	X(I2C2_ER)                      /*I2C2_ER I2C2 error interrupt*/									\
	X(SPI1)                         /*SPI1 SPI1 global interrupt*/										\
	X(SPI2)                         /*SPI2 SPI2 global interrupt*/										\
	X(USART1)                       /*USART1 USART1 global interrupt*/									\
	X(USART2)                       /*USART2 USART2 global interrupt*/									\
	X(EXTI15_10)                    /*EXTI15_10 EXTI Line[15:10] interrupts*/								\
	X(EXTI17_RTC_Alarm)		/*EXTI17 / RTC_Alarm EXTI Line 17 interrupt / RTC Alarms (A and B) through EXTI line interrupt*/ 	\
	X(EXTI18_OTG_FS_WKUP)           /*EXTI18 / OTG_FS_WKUP EXTI Line 18 interrupt / USB On-The-Go FS Wakeup through EXTI line interrupt*/ 	\
	X(DMA1_Stream7)                 /*DMA1_Stream7 DMA1 Stream7 global interrupt*/								\
	X(SDIO)                         /*SDIO SDIO global interrupt*/										\
	X(TIM5)                         /*TIM5 TIM5 global interrupt*/										\
	X(SPI3)                         /*SPI3 SPI3 global interrupt*/										\
	X(DMA2_Stream0)                 /*DMA2_Stream0 DMA2 Stream0 global interrupt*/								\
	X(DMA2_Stream1)                 /*DMA2_Stream1 DMA2 Stream1 global interrupt*/								\
	X(DMA2_Stream2)                 /*DMA2_Stream2 DMA2 Stream2 global interrupt*/								\
	X(DMA2_Stream3)                 /*DMA2_Stream3 DMA2 Stream3 global interrupt*/								\
	X(DMA2_Stream4)                 /*DMA2_Stream4 DMA2 Stream4 global interrupt*/								\
	X(OTG_FS)                       /*OTG_FS USB On The Go FS global interrupt*/								\
	X(DMA2_Stream5)                 /*DMA2_Stream5 DMA2 Stream5 global interrupt*/								\
	X(DMA2_Stream6)                 /*DMA2_Stream6 DMA2 Stream6 global interrupt*/								\
	X(DMA2_Stream7)                 /*DMA2_Stream7 DMA2 Stream7 global interrupt*/								\
	X(USART6)                       /*USART6 USART6 global interrupt*/									\
	X(I2C3_EV)                      /*I2C3_EV I2C3 event interrupt*/ 									\
	X(I2C3_ER)                      /*I2C3_ER I2C3 error interrupt*/ 									\
	X(FPU)                          /*FPU FPU global interrupt*/ 										\
	X(SPI4)                         /*SPI4 SPI 4 global interrupt*/


#define		X(IRS)	__attribute__((interrupt, weak)) void IRS(void) {  while(1)  {	}  }
	IRQs
#undef X

uint32_t vtable[] __attribute__((section(".isr_vector"))) = {

	/*----------System interrupts------------*/

	/* 0x000 */	(uint32_t) &__stack_top__,				// Top of stack
	/* 0x004 */	(uint32_t) &RESET,                                      // Reset_Handler
	/* 0x008 */	(uint32_t) &NMI,                                        // NMI_Handler
        /* 0x00C */	(uint32_t) &HardFault,                                  // HardFault_Handler
        /* 0x010 */	(uint32_t) &MemManage,                                  // MemManage_Handler
        /* 0x014 */	(uint32_t) &BusFault,                                   // BusFault_Handler
        /* 0x018 */	(uint32_t) &UsageFault,                                 // UsageFault_Handler

	/* 0x01C */	(uint32_t) 0UL,
	/* 0x020 */	(uint32_t) 0UL,
	/* 0x024 */	(uint32_t) 0UL,
	/* 0x028 */	(uint32_t) 0UL,

        /* 0x02C */	(uint32_t) &SVCall,                                    	// SVC_Handler
        /* 0x030 */	(uint32_t) &Debug_Monitor,                             	// DebugMon_Handler

	/* 0x034 */	(uint32_t) 0UL,

        /* 0x038 */	(uint32_t) &PendSV,                                    	// PendSV_Handler
        /* 0x03C */	(uint32_t) &Systick,                                   	// SysTick_Handler

	/*-------Non System interrupts-----------*/
                                                                
	/* 0x040 */	(uint32_t) &WWDG,                                       /* Window WatchDog              */
	/* 0x044 */	(uint32_t) &EXTI16_PVD,                                 /* PVD through EXTI Line detection */
	/* 0x048 */	(uint32_t) &EXTI21_TAMP_STAMP,                          /* Tamper and TimeStamps through the EXTI line */
	/* 0x04C */	(uint32_t) &EXTI22_RTC_WKUP,                            /* RTC Wakeup through the EXTI line */
	/* 0x050 */	(uint32_t) &FLASH,                                      /* FLASH                        */
	/* 0x054 */	(uint32_t) &_RCC,                                       /* RCC                          */
	/* 0x058 */	(uint32_t) &EXTI0,                                      /* EXTI Line0                   */
	/* 0x05C */	(uint32_t) &EXTI1,                                      /* EXTI Line1                   */
	/* 0x060 */	(uint32_t) &EXTI2,                                      /* EXTI Line2                   */
	/* 0x064 */	(uint32_t) &EXTI3,                                      /* EXTI Line3                   */
	/* 0x068 */	(uint32_t) &EXTI4,                                      /* EXTI Line4                   */
	/* 0x06C */	(uint32_t) &DMA1_Stream0,                               /* DMA1 Stream 0                */
	/* 0x070 */	(uint32_t) &DMA1_Stream1,                               /* DMA1 Stream 1                */
	/* 0x074 */	(uint32_t) &DMA1_Stream2,                               /* DMA1 Stream 2                */
	/* 0x078 */	(uint32_t) &DMA1_Stream3,                               /* DMA1 Stream 3                */
	/* 0x07C */	(uint32_t) &DMA1_Stream4,                               /* DMA1 Stream 4                */
	/* 0x080 */	(uint32_t) &DMA1_Stream5,                               /* DMA1 Stream 5                */
	/* 0x084 */	(uint32_t) &DMA1_Stream6,                               /* DMA1 Stream 6                */
	/* 0x088 */	(uint32_t) &ADC,                                        /* ADC1                         */

	/* 0x08C */	(uint32_t) 0UL,
	/* 0x090 */	(uint32_t) 0UL,
	/* 0x094 */	(uint32_t) 0UL,
	/* 0x098 */	(uint32_t) 0UL,

	/* 0x09C */	(uint32_t) &EXTI9_5,                                    /* External Line[9:5]s          */
	/* 0x0A0 */	(uint32_t) &TIM1_BRK_TIM9,                              /* TIM1 Break and TIM9          */
	/* 0x0A4 */	(uint32_t) &TIM1_UP_TIM10,                              /* TIM1 Update and TIM10        */
	/* 0x0A8 */	(uint32_t) &TIM1_TRG_COM_TIM11,                         /* TIM1 Trigger and Commutation and TIM11 */
	/* 0x0AC */	(uint32_t) &TIM1_CC,                                    /* TIM1 Capture Compare         */
	/* 0x0B0 */	(uint32_t) &TIM2,                                       /* TIM2                         */
	/* 0x0B4 */	(uint32_t) &_TIM3,                                      /* TIM3                         */
	/* 0x0B8 */	(uint32_t) &TIM4,                                       /* TIM4                         */
	/* 0x0BC */	(uint32_t) &I2C1_EV,                                    /* I2C1 Event                   */
	/* 0x0C0 */	(uint32_t) &I2C1_ER,                                    /* I2C1 Error                   */
	/* 0x0C4 */	(uint32_t) &I2C2_EV,                                    /* I2C2 Event                   */
	/* 0x0C8 */	(uint32_t) &I2C2_ER,                                    /* I2C2 Error                   */
	/* 0x0CC */	(uint32_t) &SPI1,                                       /* SPI1                         */
	/* 0x0D0 */	(uint32_t) &SPI2,                                       /* SPI2                         */
	/* 0x0D4 */	(uint32_t) &USART1,                                     /* USART1                       */
	/* 0x0D8 */	(uint32_t) &USART2,                                     /* USART2			*/

	/* 0x0DC */	(uint32_t) 0UL,

	/* 0x0E0 */	(uint32_t) &EXTI15_10,                                  /* External Line[15:10]s        */
	/* 0x0E4 */	(uint32_t) &EXTI17_RTC_Alarm,                           /* RTC Alarm (A and B) through EXTI Line */
	/* 0x0E8 */	(uint32_t) &EXTI18_OTG_FS_WKUP,                         /* USB OTG FS Wakeup through EXTI line */

	/* 0x0EC */	(uint32_t) 0UL,
	/* 0x0F0 */	(uint32_t) 0UL,
	/* 0x0F4 */	(uint32_t) 0UL,
	/* 0x0F8 */	(uint32_t) 0UL,

	/* 0x0FC */	(uint32_t) &DMA1_Stream7,                               /* DMA1 Stream7                 */

	/* 0x010 */	(uint32_t) 0UL,

	/* 0x104 */	(uint32_t) &SDIO,                                       /* SDIO                         */
	/* 0x108 */	(uint32_t) &TIM5,                                       /* TIM5                         */
	/* 0x10C */	(uint32_t) &SPI3,                                       /* SPI3                         */

	/* 0x110 */	(uint32_t) 0UL,
	/* 0x114 */	(uint32_t) 0UL,
	/* 0x118 */	(uint32_t) 0UL,
	/* 0x11C */	(uint32_t) 0UL,

	/* 0x120 */	(uint32_t) &DMA2_Stream0,                               /* DMA2 Stream 0                */
	/* 0x124 */	(uint32_t) &DMA2_Stream1,                               /* DMA2 Stream 1                */
	/* 0x128 */	(uint32_t) &DMA2_Stream2,                               /* DMA2 Stream 2                */
	/* 0x12C */	(uint32_t) &DMA2_Stream3,                               /* DMA2 Stream 3                */
	/* 0x130 */	(uint32_t) &DMA2_Stream4,                               /* DMA2 Stream 4                */

	/* 0x134 */	(uint32_t) 0UL,
	/* 0x138 */	(uint32_t) 0UL,
	/* 0x13C */	(uint32_t) 0UL,
	/* 0x140 */	(uint32_t) 0UL,
	/* 0x144 */	(uint32_t) 0UL,
	/* 0x148 */	(uint32_t) 0UL,

	/* 0x14C */	(uint32_t) &OTG_FS,                                     /* USB OTG FS                   */
	/* 0x150 */	(uint32_t) &DMA2_Stream5,                               /* DMA2 Stream 5                */
	/* 0x154 */	(uint32_t) &DMA2_Stream6,                               /* DMA2 Stream 6                */
	/* 0x158 */	(uint32_t) &DMA2_Stream7,                               /* DMA2 Stream 7                */
	/* 0x15C */	(uint32_t) &USART6,                                     /* USART6                       */
	/* 0x160 */	(uint32_t) &I2C3_EV,                                    /* I2C3 event                   */
	/* 0x164 */	(uint32_t) &I2C3_ER,                                    /* I2C3 error                   */

	/* 0x168 */	(uint32_t) 0UL,
	/* 0x16C */	(uint32_t) 0UL,
	/* 0x170 */	(uint32_t) 0UL,
	/* 0x174 */	(uint32_t) 0UL,
	/* 0x178 */	(uint32_t) 0UL,
	/* 0x17C */	(uint32_t) 0UL,
	/* 0x180 */	(uint32_t) 0UL,

	/* 0x184 */	(uint32_t) &FPU,                                        /* FPU                          */

	/* 0x188 */	(uint32_t) 0UL,
	/* 0x18C */	(uint32_t) 0UL,

	/* 0x190 */	(uint32_t) &SPI4                                        /* SPI4                         */
};                                                              
