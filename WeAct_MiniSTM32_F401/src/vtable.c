#define		default_isr_alias(IRS) \
	__attribute__((interrupt, weak, noreturn)) \
	void IRS(void) { \
		while(1) \
		{		} \
	}

#define	uint32_t unsigned int
extern	uint32_t __stack_top__;

extern void RESET(void);

//---------------System interrupts--------------//
default_isr_alias(NMI)				//Non maskable interrupt, Clock Security System
default_isr_alias(HardFault)			//All class of fault
default_isr_alias(MemManage)			//Memory management
default_isr_alias(BusFault)			//Pre-fetch fault, memory access fault
default_isr_alias(UsageFault)			//Undefined instruction or illegal state
//                                              //
//                                              //
//                                              //
//                                              //
default_isr_alias(SVCall)			//System Service call via SWI instruction
default_isr_alias(Debug_Monitor)		//Monitor Debug Monitor
//                                              //
default_isr_alias(PendSV)			//Pendable request for system service
default_isr_alias(Systick)			//System tick timer
						
//-------------Non System interrupts------------//

default_isr_alias(WWDG)				//WWDG Window Watchdog interrupt
default_isr_alias(EXTI16_PVD)                   //EXTI Line 16 interrupt / PVD through EXTI line detection interrupt
default_isr_alias(EXTI21_TAMP_STAMP)            //EXTI Line 21 interrupt / Tamper and TimeStamp interrupts through the EXTI line
default_isr_alias(EXTI22_RTC_WKUP)              //EXTI Line 22 interrupt / RTC Wakeup interrupt through the EXTI line
default_isr_alias(FLASH)                        //FLASH Flash global interrupt 0x0000 0050 5 12 settable RCC RCC global interrupt
default_isr_alias(EXTI0)                        //EXTI0 EXTI Line0 interrupt
default_isr_alias(EXTI1)                        //EXTI1 EXTI Line1 interrupt
default_isr_alias(EXTI2)                        //EXTI2 EXTI Line2 interrupt
default_isr_alias(EXTI3)                        //EXTI3 EXTI Line3 interrupt
default_isr_alias(EXTI4)                        //EXTI4 EXTI Line4 interrupt
default_isr_alias(DMA1_Stream0)                 //DMA1_Stream0 DMA1 Stream0 global interrupt
default_isr_alias(DMA1_Stream1)                 //DMA1_Stream1 DMA1 Stream1 global interrupt
default_isr_alias(DMA1_Stream2)                 //DMA1_Stream2 DMA1 Stream2 global interrupt
default_isr_alias(DMA1_Stream3)                 //DMA1_Stream3
default_isr_alias(DMA1_Stream4)                 //DMA1_Stream4 DMA1 Stream4 global interrupt
default_isr_alias(DMA1_Stream5)                 //DMA1_Stream5 DMA1 Stream5 global interrupt
default_isr_alias(DMA1_Stream6)                 //DMA1_Stream6 DMA1 Stream6 global interrupt
default_isr_alias(ADC)                          //ADC ADC1 global interrupts
default_isr_alias(EXTI9_5)                      //EXTI9_5 EXTI Line[9:5] interrupts
default_isr_alias(TIM1_BRK_TIM9)                //TIM1_BRK_TIM9 TIM1 Break interrupt and TIM9 global interrupt
default_isr_alias(TIM1_UP_TIM10)                //TIM1_UP_TIM10 TIM1 Update interrupt and TIM10 global interrupt
default_isr_alias(TIM1_TRG_COM_TIM11)           //TIM1_TRG_COM_TIM11 TIM1 Trigger and Commutation interrupts and TIM11 global interrupt
default_isr_alias(TIM1_CC)                      //TIM1_CC TIM1 Capture Compare interrupt
default_isr_alias(TIM2)                         //TIM2 TIM2 global interrupt
default_isr_alias(TIM3)                         //TIM3 TIM3 global interrupt
default_isr_alias(TIM4)                         //TIM4 TIM4 global interrupt
default_isr_alias(I2C1_EV)                      //I2C1_EV I2C1 event interrupt
default_isr_alias(I2C1_ER)                      //I2C1_ER I2C1 error interrupt
default_isr_alias(I2C2_EV)                      //I2C2_EV I2C2 event interrupt
default_isr_alias(I2C2_ER)                      //I2C2_ER I2C2 error interrupt
default_isr_alias(SPI1)                         //SPI1 SPI1 global interrupt
default_isr_alias(SPI2)                         //SPI2 SPI2 global interrupt
default_isr_alias(USART1)                       //USART1 USART1 global interrupt
default_isr_alias(USART2)                       //USART2 USART2 global interrupt
default_isr_alias(EXTI15_10)                    //EXTI15_10 EXTI Line[15:10] interrupts
default_isr_alias(EXTI17)                       //EXTI17 / RTC_Alarm EXTI Line 17 interrupt / RTC Alarms (A and B) through EXTI line interrupt
default_isr_alias(EXTI18)                       //EXTI18 / OTG_FS_WKUP EXTI Line 18 interrupt / USB On-The-Go FS Wakeup through EXTI line interrupt
default_isr_alias(DMA1_Stream7)                 //DMA1_Stream7 DMA1 Stream7 global interrupt
default_isr_alias(SDIO)                         //SDIO SDIO global interrupt
default_isr_alias(TIM5)                         //TIM5 TIM5 global interrupt
default_isr_alias(SPI3)                         //SPI3 SPI3 global interrupt
default_isr_alias(DMA2_Stream0)                 //DMA2_Stream0 DMA2 Stream0 global interrupt
default_isr_alias(DMA2_Stream1)                 //DMA2_Stream1 DMA2 Stream1 global interrupt
default_isr_alias(DMA2_Stream2)                 //DMA2_Stream2 DMA2 Stream2 global interrupt
default_isr_alias(DMA2_Stream3)                 //DMA2_Stream3 DMA2 Stream3 global interrupt
default_isr_alias(DMA2_Stream4)                 //DMA2_Stream4 DMA2 Stream4 global interrupt
default_isr_alias(OTG_FS)                       //OTG_FS USB On The Go FS global interrupt
default_isr_alias(DMA2_Stream5)                 //DMA2_Stream5 DMA2 Stream5 global interrupt
default_isr_alias(DMA2_Stream6)                 //DMA2_Stream6 DMA2 Stream6 global interrupt
default_isr_alias(DMA2_Stream7)                 //DMA2_Stream7 DMA2 Stream7 global interrupt
default_isr_alias(USART6)                       //USART6 USART6 global interrupt
default_isr_alias(I2C3_EV)                      //I2C3_EV I2C3 event interrupt
default_isr_alias(I2C3_ER)                      //I2C3_ER I2C3 error interrupt
default_isr_alias(FPU)                          //FPU FPU global interrupt
default_isr_alias(SPI4)                         //SPI4 SPI 4 global interrupt


uint32_t vtable[] __attribute__((section(".isr_vector"))) = {
	(uint32_t) &__stack_top__,
	(uint32_t) &RESET,
	(uint32_t) &NMI,
        (uint32_t) &HardFault,
        (uint32_t) &MemManage,
        (uint32_t) &BusFault,
        (uint32_t) &UsageFault,
	(uint32_t) 0UL,				//0x1CUL			
	(uint32_t) 0UL,				//0x20UL
	(uint32_t) 0UL,				//0x24UL
	(uint32_t) 0UL,				//0x28UL
        (uint32_t) &SVCall,
        (uint32_t) &Debug_Monitor,
	(uint32_t) 0UL,				//0x34UL
        (uint32_t) &PendSV,
        (uint32_t) &Systick,
              			
/*----------System interrupts------------*/
                                           
        (uint32_t) &WWDG,
        (uint32_t) &EXTI16_PVD,
        (uint32_t) &EXTI21_TAMP_STAMP,
        (uint32_t) &EXTI22_RTC_WKUP,
        (uint32_t) &FLASH,
        (uint32_t) &EXTI0,
        (uint32_t) &EXTI1,
        (uint32_t) &EXTI2,
        (uint32_t) &EXTI3,
        (uint32_t) &EXTI4,
        (uint32_t) &DMA1_Stream0,
        (uint32_t) &DMA1_Stream1,
        (uint32_t) &DMA1_Stream2,
        (uint32_t) &DMA1_Stream3,
        (uint32_t) &DMA1_Stream4,
        (uint32_t) &DMA1_Stream5,
        (uint32_t) &DMA1_Stream6,
        (uint32_t) &ADC,
        (uint32_t) &EXTI9_5,
        (uint32_t) &TIM1_BRK_TIM9,
        (uint32_t) &TIM1_UP_TIM10,
        (uint32_t) &TIM1_TRG_COM_TIM11,
        (uint32_t) &TIM1_CC,
        (uint32_t) &TIM2,
        (uint32_t) &TIM3,
        (uint32_t) &TIM4,
        (uint32_t) &I2C1_EV,
        (uint32_t) &I2C1_ER,
        (uint32_t) &I2C2_EV,
        (uint32_t) &I2C2_ER,
        (uint32_t) &SPI1,
        (uint32_t) &SPI2,
        (uint32_t) &USART1,
        (uint32_t) &USART2,
        (uint32_t) &EXTI15_10,
        (uint32_t) &EXTI17,
        (uint32_t) &EXTI18,
        (uint32_t) &DMA1_Stream7,
        (uint32_t) &SDIO,
        (uint32_t) &TIM5,
        (uint32_t) &SPI3,
        (uint32_t) &DMA2_Stream0,
        (uint32_t) &DMA2_Stream1,
        (uint32_t) &DMA2_Stream2,
        (uint32_t) &DMA2_Stream3,
        (uint32_t) &DMA2_Stream4,
        (uint32_t) &OTG_FS,
        (uint32_t) &DMA2_Stream5,
        (uint32_t) &DMA2_Stream6,
        (uint32_t) &DMA2_Stream7,
        (uint32_t) &USART6,
        (uint32_t) &I2C3_EV,
        (uint32_t) &I2C3_ER,
        (uint32_t) &FPU,
        (uint32_t) &SPI4
};
