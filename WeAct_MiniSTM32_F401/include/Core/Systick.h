#ifndef SYSTICK_HEADER
#define SYSTICK_HEADER

#include "types.h"
//The processor has a 24-bit system timer, SysTick, that counts down from the reload value to zero, reloads (wraps to) the value in the STK_LOAD register on the next clock edge, then counts down on subsequent clocks.
//When the processor is halted for debugging the counter does not decrement.

#define SysTick_BASE		(0xE000E010UL)
#define STK			((SysTick_Type*)SysTick_BASE)

typedef struct {

	_IO	uint32_t	CTRL;		//SysTick control and status register
	_IO 	uint32_t	LOAD;		//SysTick reload value register
	_IO 	uint32_t	VAL;		//SysTick current value register
	_I	uint32_t	CALIB;		//SysTick calibration value registe

} SysTick_Type;

//inline void STK_Enable();
//inline void STK_Disable();
//inline void STK_Set_Interrupting(uint32_t TICINT) { STK->CTRL |= };
//inline void STK_Set_CLKSRC();
//
//inline uint32_t STK_Get_Val();
//inline uint32_t STK_Get_Reload();
//inline uint32_t STK_Get_Zero();


//Enables the counter. When ENABLE is set to 1, the counter loads the RELOAD value from the LOAD register and then counts down. On reaching 0, it sets the COUNTFLAG to 1 and optionally asserts the SysTick depending on the value of TICKINT. It then loads the RELOAD value again, and begins counting.
//	0: Counter disabled
//	1: Counter enabled
#define		STK_CTRL_ENABLE_POS	(0U)
#define		STK_CTRL_ENABLE_MASK	(1UL << STK_CTRL_ENABLE_POS)

//SysTick exception request enable
//	0: Counting down to zero does not assert the SysTick exception request
//	1: Counting down to zero to asserts the SysTick exception request.
//Note: Software can use COUNTFLAG to determine if SysTick has ever counted to zero. Bit 0
#define		STK_CTRL_TICINT_POS	(1U)
#define		STK_CTRL_TICINT_MASK	(1UL << STK_CTRL_TICINT_POS)

//Clock source selection Selects the clock source.
//	0: AHB/8
//	1: Processor clock (AHB)
#define		STK_CTRL_CLKSOURCE_POS	(2U)
#define		STK_CTRL_CLKSOURCE_MASK	(1UL << STK_CTRL_CLKSOURCE_POS)

//Returns 1 if timer counted to 0 since last time this was read.
#define		STK_CTRL_COUNTFLAG_POS	(16U)
#define		STK_CTRL_COUNTFLAG_MASK	(1UL << STK_CTRL_COUNTFLAG_POS)

//The LOAD register specifies the start value to load into the STK_VAL register when the counter is enabled and when it reaches 0.
//Calculating the RELOAD value
//The RELOAD value can be any value in the range 0x00000001-0x00FFFFFF. A start value of 0 is possible, but has no effect because the SysTick exception request and COUNTFLAG are activated when counting from 1 to 0.
//The RELOAD value is calculated according to its use:
//To generate a multi-shot timer with a period of N processor clock cycles, use a RELOAD value of N-1. For example, if the SysTick interrupt is required every 100 clock pulses, set RELOAD to 99.
//To deliver a single SysTick interrupt after a delay of N processor clock cycles, use a RELOAD of value N. For example, if a SysTick interrupt is required after 100 clock pulses, set RELOAD to 99.
#define		STK_LOAD_RELOAD_POS	(0U)
#define		STK_LOAD_RELOAD_MASK	(0xFFFFFFUL << STK_LOAD_RELOAD_POS)


//Current counter value
//The VAL register contains the current value of the SysTick counter.
//Reads return the current value of the SysTick counter.
//A write of any value clears the field to 0, and also clears the COUNTFLAG bit in the STK_CTRL register to 0.
#define		STK_VAL_CURRENT_POS	(0U)
#define		STK_VAL_CURRENT_MASK	(0xFFFFFFUL << STK_VAL_CURRENT_POS)


//Calibration value. Indicates the calibration value when the SysTick counter runs on HCLK max/8 as external clock. The value is product dependent, please refer to the Product Reference Manual, SysTick Calibration Value section. When HCLK is programmed at the maximum frequency, the SysTick period is 1ms.
//If calibration information is not known, calculate the calibration value required from the frequency of the processor clock or external clock.
#define		STK_CALIB_TENMS_POS	(0U)
#define		STK_CALIB_TENMS_MASK	(0xFFFFFFUL << STK_CALIB_TENMS_POS)

//SKEW flag: Indicates whether the TENMS value is exact. Reads as one. Calibration value for the 1 ms inexact timing is not known because TENMS is not known. This can affect the suitability of SysTick as a software real time clock.
#define		STK_CALIB_SKEW_POS	(30U)
#define		STK_CALIB_SKEW_MASK	(0x1UL << STK_CALIB_SKEW_POS)

//NOREF flag. Reads as zero. Indicates that a separate reference clock is provided. The frequency of this clock is HCLK/8.
#define		STK_CALIB_NOREF_POS	(31U)
#define		STK_CALIB_NOREF_MASK	(0x1UL << STK_CALIB_NOREF_POS)

#endif
