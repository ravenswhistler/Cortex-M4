#ifndef RCC_HEADER
#define RCC_HEADER

#include "types.h"

#define RCC_BASE	(0x40023800U)
#define RCC		((RCC_Type*)RCC_BASE)

typedef struct {
	
	_IO uint32_t CR;				//clock control register
   	_IO uint32_t PLLCFGR;			//PLL configuration register
	_IO uint32_t CFGR;				//Clock configuration register
	_IO uint32_t CIR;				//Clock interrupt register
    	_IO uint32_t AHB1RSTR;			//AHB1 peripheral reset register
	_IO uint32_t AHB2RSTR;			//AHB2 peripheral reset register
		uint32_t 	__UNUSED__0;
		uint32_t 	__UNUSED__1;
	_IO uint32_t APB1RSTR;			//APB1 peripheral reset register
	_IO uint32_t APB2RSTR;			//APB2 peripheral reset register
		uint32_t 	__UNUSED__2;
		uint32_t 	__UNUSED__3;
	_IO uint32_t AHB1ENR;			//AHB1 peripheral clock enable register
	_IO uint32_t AHB2ENR;			//AHB2 peripheral clock enable register
		uint32_t 	__UNUSED__4;
		uint32_t 	__UNUSED__5;
	_IO uint32_t APB1ENR;			//APB1 peripheral clock enable register
	_IO uint32_t APB2ENR;			//APB2 peripheral clock enable register
		uint32_t 	__UNUSED__6;
		uint32_t 	__UNUSED__7;
	_IO uint32_t AHB1LPENR;			//AHB1 peripheral clock enable in low power mode register
	_IO uint32_t AHB2LPENR;			//AHB2 peripheral clock enable in low power mode register
		uint32_t 	__UNUSED__8;
		uint32_t 	__UNUSED__9;
	_IO uint32_t APB1LPENR;			//APB1 peripheral clock enabled in low power mode register
	_IO uint32_t APB2LPENR;			//APB2 peripheral clock enabled in low power mode register
		uint32_t 	__UNUSED__10;
		uint32_t 	__UNUSED__11;
	_IO uint32_t BDCR;				//Backup domain control register
	_IO uint32_t CSR;				//Clock control & status register
		uint32_t 	__UNUSED__12;
		uint32_t 	__UNUSED__13;
	_IO uint32_t SSCGR;			//Spread spectrum clock generation register
	_IO uint32_t PLLI2SCFGR;			//PLLI2S configuration register
		uint32_t 	__UNUSED__14;
	_IO uint32_t DCKCFGR;			//Dedicated Clocks Configuration Register
	
} RCC_Type;


/*---------CR's MASKs----------*/

//Internal high-speed clock enable
//Set and cleared by software.
//Set by hardware to force the HSI oscillator ON when leaving the Stop or Standby mode or in case of a failure of the HSE oscillator used directly or indirectly as the system clock. This bit cannot be cleared if the HSI is used directly or indirectly as the system clock.
//	0: HSI oscillator OFF
//	1: HSI oscillator ON
#define RCC_CR_HSION_POS	(0U)
#define RCC_CR_HSION_MASK	(1UL << RCC_CR_HSION_POS)

//Internal high-speed clock ready flag
//Set by hardware to indicate that the HSI oscillator is stable. After the HSION bit is cleared, HSIRDY goes low after 6 HSI clock cycles.
//	0: HSI oscillator not ready
//	1: HSI oscillator ready
#define RCC_CR_HSIRDY_POS	(1U)
#define RCC_CR_HSIRDY_MASK	(1UL << RCC_CR_HSIRDY_POS)

//Internal high-speed clock trimming
//These bits provide an additional user-programmable trimming value that is added to the HSICAL[7:0] bits. It can be programmed to adjust to variations in voltage and temperature that influence the frequency of the internal HSI RC.
#define RCC_CR_HSITRIM_POS	(4U)
#define RCC_CR_HSITRIM_MASK	(0x1FUL << RCC_CR_HSITRIM_POS)

//internal high-speed clock calibration These bits are initialized automatically at startup.
#define RCC_CR_HSICAL_POS	(8U)
#define RCC_CR_HSICAL_MASK	(0xFFUL << RCC_CR_HSICAL_POS)

//HSE clock enable
//Set and cleared by software.
//Cleared by hardware to stop the HSE oscillator when entering Stop or Standby mode. This bit cannot be reset if the HSE oscillator is used directly or indirectly as the system clock.
//	0: HSE oscillator OFF
//	1: HSE oscillator ON
#define RCC_CR_HSEON_POS	(16U)
#define RCC_CR_HSEON_MASK	(1UL << RCC_CR_HSEON_POS)

//HSE clock ready flag
//Set by hardware to indicate that the HSE oscillator is stable. After the HSEON bit is cleared, HSERDY goes low after 6 HSE oscillator clock cycles.
//	0: HSE oscillator not ready
//	1: HSE oscillator ready
#define RCC_CR_HSERDY_POS	(17U)
#define RCC_CR_HSERDY_MASK	(1UL << RCC_CR_HSERDY_POS)

//HSE clock bypass
//Set and cleared by software to bypass the oscillator with an external clock. The external clock must be enabled with the HSEON bit, to be used by the device.
//The HSEBYP bit can be written only if the HSE oscillator is disabled.
//	0: HSE oscillator not bypassed
//	1: HSE oscillator bypassed with an external clock
#define RCC_CR_HSEBYP_POS	(18U)
#define RCC_CR_HSEBYP_MASK	(1UL << RCC_CR_HSEBYP_POS)

//Clock security system enable
//Set and cleared by software to enable the clock security system. When CSSON is set, the clock detector is enabled by hardware when the HSE oscillator is ready, and disabled by hardware if an oscillator failure is detected.
//	0: Clock security system OFF (Clock detector OFF)
//	1: Clock security system ON (Clock detector ON if HSE oscillator is stable, OFF if not)
#define RCC_CR_CSSON_POS	(19U)
#define RCC_CR_CSSON_MASK	(1UL << RCC_CR_CSSON_POS)

//Main PLL (PLL) enable
//Set and cleared by software to enable PLL.
//Cleared by hardware when entering Stop or Standby mode. This bit cannot be reset if PLL clock is used as the system clock.
//	0: PLL OFF
//	1: PLL ON
#define RCC_CR_PLLON_POS	(24U)
#define RCC_CR_PLLON_MASK	(1UL << RCC_CR_PLLON_POS)

//Main PLL (PLL) clock ready flag
//Set by hardware to indicate that PLL is locked.
//	0: PLL unlocked
//	1: PLL locked
#define RCC_CR_PLLRDY_POS	(25U)
#define RCC_CR_PLLRDY_MASK	(1UL << RCC_CR_PLLRDY_POS)

//PLLI2S enable
//Set and cleared by software to enable PLLI2S.
//Cleared by hardware when entering Stop or Standby mode.
//	0: PLLI2S OFF
//	1: PLLI2S ON
#define RCC_CR_PLLI2SON_POS	(26U)
#define RCC_CR_PLLI2SON_MASK	(1UL << RCC_CR_PLLI2SON_POS)

//PLLI2S clock ready flag
//Set by hardware to indicate that the PLLI2S is locked.
//	0: PLLI2S unlocked
//	1: PLLI2S locked
#define RCC_CR_PLLI2SRDY_POS	(27U)
#define RCC_CR_PLLI2SRDY_MASK	(1UL << RCC_CR_PLLI2SRDY_POS)


/*---------PLLCFGR's MASKs----------*/

//This register is used to configure the PLL clock outputs according to the formulas:
//	- f(VCO clock) = f(PLL clock input) × (PLLN / PLLM)
//	- f(PLL general clock output) = f(VCO clock) / PLLP
//	- f(USB OTG FS, SDIO, RNG clock output) = f(VCO clock) / PLLQ

//Division factor for the main PLL (PLL) and audio PLL (PLLI2S) input clock Set and cleared by software to divide the PLL and PLLI2S input clock before the VCO. These bits can be written only when the PLL and PLLI2S are disabled.
//Caution: The software has to set these bits correctly to ensure that the VCO input frequency ranges from 1 to 2 MHz. It is recommended to select a frequency of 2 MHz to limit PLL jitter.
//VCO input frequency = PLL input clock frequency / PLLM with 2 ≤ PLLM ≤ 63
//	000000: PLLM = 0, wrong configuration
//	000001: PLLM = 1, wrong configuration
//	000010: PLLM = 2
//	000011: PLLM = 3
//	000100: PLLM = 4
//	...
//	111110: PLLM = 62
//	111111: PLLM = 63
#define RCC_PLLCFGR_PLLM_POS	(0U)
#define RCC_PLLCFGR_PLLM_MASK	(0x3FUL << RCC_PLLCFGR_PLLM_POS)

//Main PLL (PLL) multiplication factor for VCO Set and cleared by software to control the multiplication factor of the VCO. These bits can be written only when PLL is disabled. Only half-word and word accesses are allowed to write these bits.
//Caution: The software has to set these bits correctly to ensure that the VCO output frequency is between 192 and 432 MHz.
//
//	VCO output frequency = VCO input frequency × PLLN with 192 ≤PLLN ≤432
//	000000000: PLLN = 0, wrong configuration
//	000000001: PLLN = 1, wrong configuration
//	...
//	...
//	110110000: PLLN = 432
//	110110001: PLLN = 433, wrong configuration
//	...
//	111111111: PLLN = 511, wrong configuration
#define RCC_PLLCFGR_PLLN_POS	(6U)
#define RCC_PLLCFGR_PLLN_MASK	(0x1FFUL << RCC_PLLCFGR_PLLN_POS)

//Main PLL (PLL) division factor for main system clock Set and cleared by software to control the frequency of the general PLL output clock. These bits can be written only if PLL is disabled.
//Caution: The software has to set these bits correctly not to exceed 84 MHz on this domain.
//	PLL output clock frequency = VCO frequency / PLLP with PLLP = 2, 4, 6, or 8
//	00: PLLP = 2
//	01: PLLP = 4
//	10: PLLP = 6
//	11: PLLP = 8
#define RCC_PLLCFGR_PLLP_POS	(16U)
#define RCC_PLLCFGR_PLLP_MASK	(0x3UL << RCC_PLLCFGR_PLLP_POS)

//Main PLL(PLL) and audio PLL (PLLI2S) entry clock source
//Set and cleared by software to select PLL and PLLI2S clock source. This bit can be written only when PLL and PLLI2S are disabled.
//	0: HSI clock selected as PLL and PLLI2S clock entry
//	1: HSE oscillator clock selected as PLL and PLLI2S clock entry
#define RCC_PLLCFGR_PLLSRC_POS	(22U)
#define RCC_PLLCFGR_PLLSRC_MASK	(1UL << RCC_PLLCFGR_PLLSRC_POS)

//Main PLL (PLL) division factor for USB OTG FS, SDIO and random number generator clocks
//Set and cleared by software to control the frequency of USB OTG FS clock, the random number generator clock and the SDIO clock. These bits should be written only if PLL is disabled.
//Caution: The USB OTG FS requires a 48 MHz clock to work correctly. The SDIO and the random number generator need a frequency lower than or equal to 48 MHz to work correctly.
//
//	USB OTG FS clock frequency = VCO frequency / PLLQ with 2 ≤ PLLQ ≤ 15
//	
//	0000: PLLQ = 0, wrong configuration
//	0001: PLLQ = 1, wrong configuration
//	0010: PLLQ = 2
//	0011: PLLQ = 3
//	0100: PLLQ = 4
//	...
//	1111: PLLQ = 15
#define RCC_PLLCFGR_PLLQ_POS	(24U)
#define RCC_PLLCFGR_PLLQ_MASK	(0xFUL << RCC_PLLCFGR_PLLQ_POS)


/*---------CFGR's MASKs----------*/

//System clock switch
//Set and cleared by software to select the system clock source.
//
//Set by hardware to force the HSI selection when leaving the Stop or Standby mode or in case of failure of the HSE oscillator used directly or indirectly as the system clock.
//
//	00: HSI oscillator selected as system clock
//	01: HSE oscillator selected as system clock
//	10: PLL selected as system clock
//	11: not allowed
#define RCC_CFGR_SW_POS		(0U)
#define RCC_CFGR_SW_MASK	(0x3UL << RCC_CFGR_SW_POS)

//System clock switch status
//Set and cleared by hardware to indicate which clock source is used as the system clock.
//
//	00: HSI oscillator used as the system clock
//	01: HSE oscillator used as the system clock
//	10: PLL used as the system clock
//	11: not applicable
#define RCC_CFGR_SWS_POS	(2U)
#define RCC_CFGR_SWS_MASK	(0x3UL << RCC_CFGR_SWS_POS)

//AHB prescaler
//Set and cleared by software to control AHB clock division factor.
//Caution: The clocks are divided with the new prescaler factor from 1 to 16 AHB cycles after HPRE write.
//	0xxx: system clock not divided
//	1000: system clock divided by 2
//	1001: system clock divided by 4
//	1010: system clock divided by 8
//	1011: system clock divided by 16
//	1100: system clock divided by 64
//	1101: system clock divided by 128
//	1110: system clock divided by 256
//	1111: system clock divided by 512
#define RCC_CFGR_HPRE_POS	(4U)
#define RCC_CFGR_HPRE_MASK	(0xFUL << RCC_CFGR_HPRE_POS)

//APB Low speed prescaler (APB1)
//Set and cleared by software to control APB low-speed clock division factor.
//Caution: The software has to set these bits correctly not to exceed 42 MHz on this domain. The clocks are divided with the new prescaler factor from 1 to 16 AHB cycles after PPRE1 write.
//	0xx: AHB clock not divided
//	100: AHB clock divided by 2
//	101: AHB clock divided by 4
//	110: AHB clock divided by 8
//	111: AHB clock divided by 16
#define RCC_CFGR_PPRE1_POS	(10U)
#define RCC_CFGR_PPRE1_MASK	(0x7UL << RCC_CFGR_PPRE1_POS)

//APB high-speed prescaler (APB2)
//Set and cleared by software to control APB high-speed clock division factor.
//Caution: The software has to set these bits correctly not to exceed 84 MHz on this domain. The clocks are divided with the new prescaler factor from 1 to 16 AHB cycles after PPRE2 write.
//	0xx: AHB clock not divided
//	100: AHB clock divided by 2
//	101: AHB clock divided by 4
//	110: AHB clock divided by 8
//	111: AHB clock divided by 16
#define RCC_CFGR_PPRE2_POS	(13U)
#define RCC_CFGR_PPRE2_MASK	(0x7UL << RCC_CFGR_PPRE2_POS)

//HSE division factor for RTC clock
//Set and cleared by software to divide the HSE clock input clock to generate a 1 MHz clock for RTC.
//Caution: The software has to set these bits correctly to ensure that the clock supplied to the RTC is 1 MHz. These bits must be configured if needed before selecting the RTC clock source.
//	00000: no clock
//	00001: no clock
//	00010: HSE/2
//	00011: HSE/3
//	00100: HSE/4
//	...
//	11110: HSE/30
//	11111: HSE/31
#define RCC_CFGR_RTCPRE_POS	(16U)
#define RCC_CFGR_RTCPRE_MASK	(0x1FUL << RCC_CFGR_RTCPRE_POS)

//Microcontroller clock output 1
//Set and cleared by software. Clock source selection may generate glitches on MCO1. It is highly recommended to configure these bits only after reset before enabling the external oscillators and PLL.
//
//	00: HSI clock selected
//	01: LSE oscillator selected
//	10: HSE oscillator clock selected
//	11: PLL clock selected
#define RCC_CFGR_MCO1_POS	(21U)
#define RCC_CFGR_MCO1_MASK	(0x3UL << RCC_CFGR_MCO1_POS)

//I2S clock selection
//Set and cleared by software. This bit allows to select the I2S clock source between the PLLI2S clock and the external clock. It is highly recommended to change this bit only after reset and before enabling the I2S module.
//	0: PLLI2S clock used as I2S clock source
//	1: External clock mapped on the I2S_CKIN pin used as I2S clock source
#define RCC_CFGR_I2SSRC_POS	(23U)
#define RCC_CFGR_I2SSRC_MASK	(1UL << RCC_CFGR_I2SSRC_POS)

//MCO1 prescaler
//Set and cleared by software to configure the prescaler of the MCO1. Modification of this prescaler may generate glitches on MCO1. It is highly recommended to change this prescaler only after reset before enabling the external oscillators and the PLL.
//	100: division by 2
//	101: division by 3
//	110: division by 4
//	111: division by 5
#define RCC_CFGR_MCO1PRE_POS	(24U)
#define RCC_CFGR_MCO1PRE_MASK	(0x7UL << RCC_CFGR_MCO1PRE_POS)

//MCO2 prescaler
//Set and cleared by software to configure the prescaler of the MCO2. Modification of this prescaler may generate glitches on MCO2. It is highly recommended to change this prescaler only after reset before enabling the external oscillators and the PLLs.
//
//	0xx: no division
//	100: division by 2
//	101: division by 3
//	110: division by 4
//	111: division by 5
#define RCC_CFGR_MCO2PRE_POS	(27U)
#define RCC_CFGR_MCO2PRE_MASK	(0x7UL << RCC_CFGR_MCO2PRE_POS)

//Microcontroller clock output 2
//Set and cleared by software. Clock source selection may generate glitches on MCO2. It is highly recommended to configure these bits only after reset before enabling the external oscillators and the PLLs.
//
//	00: System clock (SYSCLK) selected
//	01: PLLI2S clock selected
//	10: HSE oscillator clock selected
//	11: PLL clock selected
#define RCC_CFGR_MCO2_POS	(30U)
#define RCC_CFGR_MCO2_MASK	(0x3UL << RCC_CFGR_MCO2_POS)


/*---------CIR's MASKs----------*/

//LSI ready interrupt flag
//Set by hardware when the internal low speed clock becomes stable and LSIRDYDIE is set.
//Cleared by software setting the LSIRDYC bit.
//	0: No clock ready interrupt caused by the LSI oscillator
//	1: Clock ready interrupt caused by the LSI oscillator
#define RCC_CIR_LSIRDYF_POS	(0U)
#define RCC_CIR_LSIRDYF_MASK	(1UL << RCC_CIR_LSIRDYF_POS)

//LSE ready interrupt flag
//Set by hardware when the External Low Speed clock becomes stable and LSERDYDIE is set.
//Cleared by software setting the LSERDYC bit.
//	0: No clock ready interrupt caused by the LSE oscillator
//	1: Clock ready interrupt caused by the LSE oscillator
#define RCC_CIR_LSERDYF_POS	(1U)
#define RCC_CIR_LSERDYF_MASK	(1UL << RCC_CIR_LSERDYF_POS)

//HSI ready interrupt flag
//Set by hardware when the Internal High Speed clock becomes stable and HSIRDYDIE is set.
//Cleared by software setting the HSIRDYC bit.
//	0: No clock ready interrupt caused by the HSI oscillator
//	1: Clock ready interrupt caused by the HSI oscillator
#define RCC_CIR_HSIRDYF_POS	(2U)
#define RCC_CIR_HSIRDYF_MASK	(1UL << RCC_CIR_HSIRDYF_POS)

//HSE ready interrupt flag
//Set by hardware when External High Speed clock becomes stable and HSERDYDIE is set. Cleared by software setting the HSERDYC bit.
//	0: No clock ready interrupt caused by the HSE oscillator
//	1: Clock ready interrupt caused by the HSE oscillator
#define RCC_CIR_HSERDYF_POS	(3U)
#define RCC_CIR_HSERDYF_MASK	(1UL << RCC_CIR_HSERDYF_POS)

//Main PLL (PLL) ready interrupt flag
//Set by hardware when PLL locks and PLLRDYDIE is set.
//Cleared by software setting the PLLRDYC bit.
//	0: No clock ready interrupt caused by PLL lock
//	1: Clock ready interrupt caused by PLL lock
#define RCC_CIR_PLLRDYF_POS	(4U)
#define RCC_CIR_PLLRDYF_MASK	(1UL << RCC_CIR_PLLRDYF_POS)

//PLLI2S ready interrupt flag
//Set by hardware when the PLLI2S locks and PLLI2SRDYDIE is set.
//Cleared by software setting the PLLRI2SDYC bit.
//	0: No clock ready interrupt caused by PLLI2S lock
//	1: Clock ready interrupt caused by PLLI2S lock
#define RCC_CIR_PLLI2SRDYF_POS	(5U)
#define RCC_CIR_PLLI2SRDYF_MASK	(1UL << RCC_CIR_PLLI2SRDYF_POS)

//Clock security system interrupt flag
//Set by hardware when a failure is detected in the HSE oscillator.
//Cleared by software setting the CSSC bit.
//	0: No clock security interrupt caused by HSE clock failure
//	1: Clock security interrupt caused by HSE clock failure
#define RCC_CIR_CSSF_POS	(7U)
#define RCC_CIR_CSSF_MASK	(1UL << RCC_CIR_CSSF_POS)

//LSI ready interrupt enable
//Set and cleared by software to enable/disable interrupt caused by LSI oscillator stabilization.
//	0: LSI ready interrupt disabled
//	1: LSI ready interrupt enabled
#define RCC_CIR_LSIRDYIE_POS	(8U)
#define RCC_CIR_LSIRDYIE_MASK	(1UL << RCC_CIR_LSIRDYIE_POS)

//LSE ready interrupt enable
//Set and cleared by software to enable/disable interrupt caused by the LSE oscillator stabilization.
//	0: LSE ready interrupt disabled
//	1: LSE ready interrupt enabled
#define RCC_CIR_LSERDYIE_POS	(9U)
#define RCC_CIR_LSERDYIE_MASK	(1UL << RCC_CIR_LSERDYIE_POS)

//HSI ready interrupt enable
//Set and cleared by software to enable/disable interrupt caused by the HSI oscillator stabilization.
//	0: HSI ready interrupt disabled
//	1: HSI ready interrupt enabled
#define RCC_CIR_HSIRDYIE_POS	(10U)
#define RCC_CIR_HSIRDYIE_MASK	(1UL << RCC_CIR_HSIRDYIE_POS)

//HSE ready interrupt enable
//Set and cleared by software to enable/disable interrupt caused by the HSE oscillator stabilization.
//	0: HSE ready interrupt disabled
//	1: HSE ready interrupt enabled
#define RCC_CIR_HSERDYIE_POS	(11U)
#define RCC_CIR_HSERDYIE_MASK	(1UL << RCC_CIR_HSERDYIE_POS)

//Main PLL (PLL) ready interrupt enable
//Set and cleared by software to enable/disable interrupt caused by PLL lock.
//	0: PLL lock interrupt disabled
//	1: PLL lock interrupt enabled
#define RCC_CIR_PLLRDYIE_POS	(12U)
#define RCC_CIR_PLLRDYIE_MASK	(1UL << RCC_CIR_PLLRDYIE_POS)

//PLLI2S ready interrupt enable
//Set and cleared by software to enable/disable interrupt caused by PLLI2S lock.
//	0: PLLI2S lock interrupt disabled
//	1: PLLI2S lock interrupt enabled
#define RCC_CIR_PLLI2SRDYIE_POS		(13U)
#define RCC_CIR_PLLI2SRDYIE_MASK	(1UL << RCC_CIR_PLLI2SRDYIE_POS)

//LSI ready interrupt clear
//This bit is set by software to clear the LSIRDYF flag.
//	0: No effect
//	1: LSIRDYF cleared
#define RCC_CIR_LSIRDYC_POS	(16U)
#define RCC_CIR_LSIRDYC_MASK	(1UL << RCC_CIR_LSIRDYC_POS)

//LSE ready interrupt clear
//This bit is set by software to clear the LSERDYF flag.
//	0: No effect
//	1: LSERDYF cleared
#define RCC_CIR_LSERDYC_POS	(17U)
#define RCC_CIR_LSERDYC_MASK	(1UL << RCC_CIR_LSERDYC_POS)

//HSI ready interrupt clear
//This bit is set software to clear the HSIRDYF flag.
//	0: No effect
//	1: HSIRDYF cleared
#define RCC_CIR_HSIRDYC_POS	(18U)
#define RCC_CIR_HSIRDYC_MASK	(1UL << RCC_CIR_HSIRDYC_POS)

//HSE ready interrupt clear
//This bit is set by software to clear the HSERDYF flag.
//	0: No effect
//	1: HSERDYF cleared
#define RCC_CIR_HSERDYC_POS	(19U)
#define RCC_CIR_HSERDYC_MASK	(1UL << RCC_CIR_HSERDYC_POS)

//Main PLL(PLL) ready interrupt clear
//This bit is set by software to clear the PLLRDYF flag.
//	0: No effect
//	1: PLLRDYF cleared
#define RCC_CIR_PLLRDYC_POS	(20U)
#define RCC_CIR_PLLRDYC_MASK	(1UL << RCC_CIR_PLLRDYC_POS)

//PLLI2S ready interrupt clear
//This bit is set by software to clear the PLLI2SRDYF flag.
//	0: No effect
//	1: PLLI2SRDYF cleared
#define RCC_CIR_PLLI2SRDYC_POS	(21U)
#define RCC_CIR_PLLI2SRDYC_MASK	(1UL << RCC_CIR_PLLI2SRDYC_POS)

//Clock security system interrupt clear
//This bit is set by software to clear the CSSF flag.
//	0: No effect
//	1: Clear CSSF flag
#define RCC_CIR_CSSC_POS	(23U)
#define RCC_CIR_CSSC_MASK	(1UL << RCC_CIR_CSSC_POS)

/*---------AHB1RSTR's MASKs----------*/

//IO port A reset
//Set and cleared by software.
//	0: does not reset IO port A
//	1: resets IO port A
#define RCC_AHB1RSTR_GPIOARST_POS	(0U)
#define RCC_AHB1RSTR_GPIOARST_MASK	(1UL << RCC_AHB1RSTR_GPIOARST_POS)

#define RCC_AHB1RSTR_GPIOBRST_POS	(1U)
#define RCC_AHB1RSTR_GPIOBRST_MASK	(1UL << RCC_AHB1RSTR_GPIOBRST_POS)

#define RCC_AHB1RSTR_GPIOCRST_POS	(2U)
#define RCC_AHB1RSTR_GPIOCRST_MASK	(1UL << RCC_AHB1RSTR_GPIOCRST_POS)

#define RCC_AHB1RSTR_GPIODRST_POS	(3U)
#define RCC_AHB1RSTR_GPIODRST_MASK	(1UL << RCC_AHB1RSTR_GPIODRST_POS)

#define RCC_AHB1RSTR_GPIOERST_POS	(4U)
#define RCC_AHB1RSTR_GPIOERST_MASK	(1UL << RCC_AHB1RSTR_GPIOERST_POS)

#define RCC_AHB1RSTR_GPIOHRST_POS	(7U)
#define RCC_AHB1RSTR_GPIOHRST_MASK	(1UL << RCC_AHB1RSTR_GPIOHRST_POS)

//CRC reset
//Set and cleared by software.
//	0: does not reset CRC
//	1: resets CRC
#define RCC_AHB1RSTR_CRCRST_POS		(12U)
#define RCC_AHB1RSTR_CRCRST_MASK	(1UL << RCC_AHB1RSTR_CRCRST_POS)

//DMA1 reset
//Set and cleared by software.
//	0: does not reset DMA1
//	1: resets DMA1
#define RCC_AHB1RSTR_DMA1RST_POS	(21U)
#define RCC_AHB1RSTR_DMA1RST_MASK	(1UL << RCC_AHB1RSTR_DMA1RST_POS)

#define RCC_AHB1RSTR_DMA2_POS		(22U)
#define RCC_AHB1RSTR_DMA2_MASK		(1UL << RCC_AHB1RSTR_DMA2_POS)


/*---------AHB2RSTR's MASKs----------*/

#define RCC_AHB2RSTR_OTGFSRST_POS	(7U)
#define RCC_AHB2RSTR_OTGFSRST_MASK	(1UL << RCC_AHB2RSTR_OTGFSRST_POS)

/*---------APB1RSTR's MASKs----------*/

//TIM2 reset
//Set and cleared by software.
//	0: does not reset TIM2
//	1: resets TIM2
#define RCC_APB1RSTR_TIM2RST_POS	(0U)
#define RCC_APB1RSTR_TIM2RST_MASK	(1UL << RCC_APB1RSTR_TIM2RST_POS)

#define RCC_APB1RSTR_TIM3RST_POS	(1U)
#define RCC_APB1RSTR_TIM3RST_MASK	(1UL << RCC_APB1RSTR_TIM3RST_POS)

#define RCC_APB1RSTR_TIM4RST_POS	(2U)
#define RCC_APB1RSTR_TIM4RST_MASK	(1UL << RCC_APB1RSTR_TIM4RST_POS)

#define RCC_APB1RSTR_TIM5RST_POS	(3U)
#define RCC_APB1RSTR_TIM5RST_MASK	(1UL << RCC_APB1RSTR_TIM5RST_POS)

//Window watchdog reset
//Set and cleared by software.
//	0: does not reset the window watchdog
//	1: resets the window watchdog
#define RCC_APB1RSTR_WWDGRST_POS	(11U)
#define RCC_APB1RSTR_WWDGRST_MASK	(1UL << RCC_APB1RSTR_WWDGRST_POS)

//SPI2 reset
//Set and cleared by software.
//	0: does not reset SPI2
//	1: resets SPI2
#define RCC_APB1RSTR_SPI2RST_POS	(14U)
#define RCC_APB1RSTR_SPI2RST_MASK	(1UL << RCC_APB1RSTR_SPI2RST_POS)

#define RCC_APB1RSTR_SPI3RST_POS	(15U)
#define RCC_APB1RSTR_SPI3RST_MASK	(1UL << RCC_APB1RSTR_SPI3RST_POS)

//USART2 reset
//Set and cleared by software.
//	0: does not reset USART2
//	1: resets USART2
#define RCC_APB1RSTR_USART2RST_POS	(17U)
#define RCC_APB1RSTR_USART2RST_MASK	(1UL << RCC_APB1RSTR_USART2RST_POS)

//I2C1 reset
//Set and cleared by software.
//	0: does not reset I2C1
//	1: resets I2C1
#define RCC_APB1RSTR_I2C1RST_POS	(21U)
#define RCC_APB1RSTR_I2C1RST_MASK	(1UL << RCC_APB1RSTR_I2C1RST_POS)

#define RCC_APB1RSTR_I2C2RST_POS	(22U)
#define RCC_APB1RSTR_I2C2RST_MASK	(1UL << RCC_APB1RSTR_I2C2RST_POS)

#define RCC_APB1RSTR_I2C3RST_POS	(23U)
#define RCC_APB1RSTR_I2C3RST_MASK	(1UL << RCC_APB1RSTR_I2C3RST_POS)

//Power interface reset
//Set and cleared by software.
//	0: does not reset the power interface
//	1: resets the power interface
#define RCC_APB1RSTR_PWRRST_POS		(28U)
#define RCC_APB1RSTR_PWRRST_MASK	(1UL << RCC_APB1RSTR_PWRRST_POS)


/*---------APB2RSTR's MASKs----------*/

#define RCC_APB2RSTR_TIM1RST_POS	(0U)
#define RCC_APB2RSTR_TIM1RST_MASK	(1UL << RCC_APB2RSTR_TIM1RST_POS)


#define RCC_APB2RSTR_USART1RST_POS	(4U)
#define RCC_APB2RSTR_USART1RST_MASK	(1UL << RCC_APB1RSTR_USART1RST_POS)


#define RCC_APB2RSTR_USART6RST_POS	(5U)
#define RCC_APB2RSTR_USART6RST_MASK	(1UL << RCC_APB2RSTR_USART6RST_POS)

#define RCC_APB2RSTR_ADC1RST_POS	(8U)
#define RCC_APB2RSTR_ADC1RST_MASK	(1UL << RCC_APB2RSTR_ADC1RST_POS)

#define RCC_APB2RSTR_SDIORST_POS	(11U)
#define RCC_APB2RSTR_SDIORST_MASK	(1UL << RCC_APB2RSTR_SDIORST_POS)

#define RCC_APB2RSTR_SPI1RST_POS	(12U)
#define RCC_APB2RSTR_SPI1RST_MASK	(1UL << RCC_APB2RSTR_SPI1RST_POS)

#define RCC_APB2RSTR_SPI4RST_POS	(13U)
#define RCC_APB2RSTR_SPI4RST_MASK	(1UL << RCC_APB2RSTR_SPI4RST_POS)

#define RCC_APB2RSTR_SYSCFGRST_POS	(14U)
#define RCC_APB2RSTR_SYSCFGRST_MASK	(1UL << RCC_APB2RSTR_SYSCFGRST_POS)

#define RCC_APB2RSTR_TIM9RST_POS	(16U)
#define RCC_APB2RSTR_TIM9RST_MASK	(1UL << RCC_APB2RSTR_TIM9RST_POS)

#define RCC_APB2RSTR_TIM10RST_POS	(17U)
#define RCC_APB2RSTR_TIM10RST_MASK	(1UL << RCC_APB2RSTR_TIM10RST_POS)

#define RCC_APB2RSTR_TIM11RST_POS	(18U)
#define RCC_APB2RSTR_TIM11RST_MASK	(1UL << RCC_APB2RSTR_TIM11RST_POS)


/*---------AHB1ENR's MASKs----------*/

#define RCC_AHB1ENR_GPIOAEN_POS		(0U)
#define RCC_AHB1ENR_GPIOAEN_MASK	(1UL << RCC_AHB1ENR_GPIOAEN_POS)

#define RCC_AHB1ENR_GPIOBEN_POS		(1U)
#define RCC_AHB1ENR_GPIOBEN_MASK	(1UL << RCC_AHB1ENR_GPIOBEN_POS)

#define RCC_AHB1ENR_GPIOCEN_POS		(2U)
#define RCC_AHB1ENR_GPIOCEN_MASK	(1UL << RCC_AHB1ENR_GPIOCEN_POS)

#define RCC_AHB1ENR_GPIODEN_POS		(3U)
#define RCC_AHB1ENR_GPIODEN_MASK	(1UL << RCC_AHB1ENR_GPIODEN_POS)

#define RCC_AHB1ENR_GPIOEEN_POS		(4U)
#define RCC_AHB1ENR_GPIOEEN_MASK	(1UL << RCC_AHB1ENR_GPIOEEN_POS)

#define RCC_AHB1ENR_GPIOHEN_POS		(7U)
#define RCC_AHB1ENR_GPIOHEN_MASK	(1UL << RCC_AHB1ENR_GPIOHEN_POS)

#define RCC_AHB1ENR_CRCEN_POS		(12U)
#define RCC_AHB1ENR_CRCEN_MASK		(1UL << RCC_AHB1ENR_CRCEN_POS)

#define RCC_AHB1ENR_DMA1EN_POS		(21U)
#define RCC_AHB1ENR_DMA1EN_MASK		(1UL << RCC_AHB1ENR_DMA1EN_POS)

#define RCC_AHB1ENR_DMA2EN_POS		(22U)
#define RCC_AHB1ENR_DMA2EN_MASK		(1UL << RCC_AHB1ENR_DMA2EN_POS)


/*---------AHB2ENR's MASKs----------*/

//USB OTG FS clock enable
//Set and cleared by software.
//	0: USB OTG FS clock disabled
//	1: USB OTG FS clock enabled
#define RCC_AHB2ENR_OTGFSEN_POS		(7U)
#define RCC_AHB2ENR_OTGFSEN_MASK	(1UL << RCC_AHB2ENR_OTGFSEN_POS)

/*---------APB1ENR's MASKs----------*/

#define RCC_APB1ENR_TIM2EN_POS		(0U)
#define RCC_APB1ENR_TIM2EN_MASK		(1UL << RCC_APB1ENR_TIM2EN_POS)

#define RCC_APB1ENR_TIM3EN_POS		(1U)
#define RCC_APB1ENR_TIM3EN_MASK		(1UL << RCC_APB1ENR_TIM3EN_POS)

#define RCC_APB1ENR_TIM4EN_POS		(2U)
#define RCC_APB1ENR_TIM4EN_MASK		(1UL << RCC_APB1ENR_TIM4EN_POS)

#define RCC_APB1ENR_TIM5EN_POS		(3U)
#define RCC_APB1ENR_TIM5EN_MASK		(1UL << RCC_APB1ENR_TIM5EN_POS)

#define RCC_APB1ENR_WWDGEN_POS		(11U)
#define RCC_APB1ENR_WWDGEN_MASK		(1UL << RCC_APB1ENR_WWDGEN_POS)

#define RCC_APB1ENR_SPI2EN_POS		(14U)
#define RCC_APB1ENR_SPI2EN_MASK		(1UL << RCC_APB1ENR_SPI2EN_POS)

#define RCC_APB1ENR_SPI3EN_POS		(15U)
#define RCC_APB1ENR_SPI3EN_MASK		(1UL << RCC_APB1ENR_SPI3EN_POS)

#define RCC_APB1ENR_USART2EN_POS	(17U)
#define RCC_APB1ENR_USART2EN_MASK	(1UL << RCC_APB1ENR_USART2EN_POS)

#define RCC_APB1ENR_I2C1EN_POS		(21U)
#define RCC_APB1ENR_I2C1EN_MASK		(1UL << RCC_APB1ENR_I2C1EN_POS)

#define RCC_APB1ENR_I2C2EN_POS		(22U)
#define RCC_APB1ENR_I2C2EN_MASK		(1UL << RCC_APB1ENR_I2C2EN_POS)

#define RCC_APB1ENR_I2C3EN_POS		(23U)
#define RCC_APB1ENR_I2C3EN_MASK		(1UL << RCC_APB1ENR_I2C3EN_POS)

#define RCC_APB1ENR_PWREN_POS		(28U)
#define RCC_APB1ENR_PWREN_MASK		(1UL << RCC_APB1ENR_PWREN_POS)


/*---------APB2ENR's MASKs----------*/

#define RCC_APB2ENR_TIM1EN_POS		(0U)
#define RCC_APB2ENR_TIM1EN_MASK		(1UL << RCC_APB2ENR_TIM1EN_POS)

#define RCC_APB2ENR_USART1EN_POS	(4U)
#define RCC_APB2ENR_USART1EN_MASK	(1UL << RCC_APB2ENR_USART1EN_POS)

#define RCC_APB2ENR_USART6EN_POS	(5U)
#define RCC_APB2ENR_USART6EN_MASK	(1UL << RCC_APB2ENR_USART6EN_POS)

#define RCC_APB2ENR_ADC1EN_POS		(8U)
#define RCC_APB2ENR_ADC1EN_MASK		(1UL << RCC_APB2ENR_ADC1EN_POS)

#define RCC_APB2ENR_SDIOEN_POS		(11U)
#define RCC_APB2ENR_SDIOEN_MASK		(1UL << RCC_APB2ENR_SDIOEN_POS)

#define RCC_APB2ENR_SPI1EN_POS		(12U)
#define RCC_APB2ENR_SPI1EN_MASK		(1UL << RCC_APB2ENR_SPI1EN_POS)

#define RCC_APB2ENR_SPI4EN_POS		(13U)
#define RCC_APB2ENR_SPI4EN_MASK		(1UL << RCC_APB2ENR_SPI4EN_POS)

#define RCC_APB2ENR_SYSCFGEN_POS	(14U)
#define RCC_APB2ENR_SYSCFGEN_MASK	(1UL << RCC_APB2ENR_SYSCFGEN_POS)

#define RCC_APB2ENR_TIM9EN_POS		(16U)
#define RCC_APB2ENR_TIM9EN_MASK		(1UL << RCC_APB2ENR_TIM9EN_POS)

#define RCC_APB2ENR_TIM10EN_POS		(17U)
#define RCC_APB2ENR_TIM10EN_MASK	(1UL << RCC_APB2ENR_TIM10EN_POS)

#define RCC_APB2ENR_TIM11EN_POS		(18U)
#define RCC_APB2ENR_TIM11EN_MASK	(1UL << RCC_APB2ENR_TIM11EN_POS)


/*---------AHB1LPENR's MASKs----------*/

//IO port A clock enable during sleep mode
//Set and cleared by software.
//	0: IO port A clock disabled during Sleep mode
//	1: IO port A clock enabled during Sleep mode
#define RCC_AHB1LPENR_GPIOALPEN_POS		(0U)
#define RCC_AHB1LPENR_GPIOALPEN_MASK		(1UL << RCC_AHB1LPENR_GPIOALPEN_POS)

#define RCC_AHB1LPENR_GPIOBLPEN_POS		(1U)
#define RCC_AHB1LPENR_GPIOBLPEN_MASK		(1UL << RCC_AHB1LPENR_GPIOBLPEN_POS)

#define RCC_AHB1LPENR_GPIOCLPEN_POS		(2U)
#define RCC_AHB1LPENR_GPIOCLPEN_MASK		(1UL << RCC_AHB1LPENR_GPIOCLPEN_POS)

#define RCC_AHB1LPENR_GPIODLPEN_POS		(3U)
#define RCC_AHB1LPENR_GPIODLPEN_MASK		(1UL << RCC_AHB1LPENR_GPIODLPEN_POS)

#define RCC_AHB1LPENR_GPIOELPEN_POS		(4U)
#define RCC_AHB1LPENR_GPIOELPEN_MASK		(1UL << RCC_AHB1LPENR_GPIOELPEN_POS)

#define RCC_AHB1LPENR_GPIOHLPEN_POS		(7U)
#define RCC_AHB1LPENR_GPIOHLPEN_MASK		(1UL << RCC_AHB1LPENR_GPIOHLPEN_POS)

#define RCC_AHB1LPENR_CRCLPEN_POS		(12U)
#define RCC_AHB1LPENR_CRCLPEN_MASK		(1UL << RCC_AHB1LPENR_CRCLPEN_POS)

#define RCC_AHB1LPENR_DMA1LPEN_POS		(21U)
#define RCC_AHB1LPENR_DMA1LPEN_MASK		(1UL << RCC_AHB1LPENR_DMA1LPEN_POS)

#define RCC_AHB1LPENR_DMA2LPEN_POS		(22U)
#define RCC_AHB1LPENR_DMA2LPEN_MASK		(1UL << RCC_AHB1LPENR_DMA2LPEN_POS)


/*---------AHB2LPENR's MASKs----------*/

//USB OTG FS clock enable during Sleep mode
//Set and cleared by software.
//	0: USB OTG FS clock disabled during Sleep mode
//	1: USB OTG FS clock enabled during Sleep mode
#define RCC_AHB2LPENR_OTGFSLPEN_POS		(7U)
#define RCC_AHB2LPENR_OTGFSLPEN_MASK		(1UL << RCC_AHB2LPENR_OTGFSLPEN_POS)



/*---------APB1LPENR's MASKs----------*/

//TIM2 clock enable during Sleep mode
//Set and cleared by software.
//	0: TIM2 clock disabled during Sleep mode
//	1: TIM2 clock enabled during Sleep mode
#define RCC_APB1LPENR_TIM2LPEN_POS		(0U)
#define RCC_APB1LPENR_TIM2LPEN_MASK		(1UL << RCC_APB1LPENR_TIM2LPEN_POS)

#define RCC_APB1LPENR_TIM3LPEN_POS		(1U)
#define RCC_APB1LPENR_TIM3LPEN_MASK		(1UL << RCC_APB1LPENR_TIM3LPEN_POS)

#define RCC_APB1LPENR_TIM4LPEN_POS		(2U)
#define RCC_APB1LPENR_TIM4LPEN_MASK		(1UL << RCC_APB1LPENR_TIM4LPEN_POS)

#define RCC_APB1LPENR_TIM5LPEN_POS		(3U)
#define RCC_APB1LPENR_TIM5LPEN_MASK		(1UL << RCC_APB1LPENR_TIM5LPEN_POS)

#define RCC_APB1LPENR_WWDGLPEN_POS		(11U)
#define RCC_APB1LPENR_WWDGLPEN_MASK		(1UL << RCC_APB1LPENR_WWDGLPEN_POS)

#define RCC_APB1LPENR_SPI2LPEN_POS		(14U)
#define RCC_APB1LPENR_SPI2LPEN_MASK		(1UL << RCC_APB1LPENR_SPI2LPEN_POS)

#define RCC_APB1LPENR_SPI3LPEN_POS		(15U)
#define RCC_APB1LPENR_SPI3LPEN_MASK		(1UL << RCC_APB1LPENR_SPI3LPEN_POS)

#define RCC_APB1LPENR_USART2LPEN_POS		(17U)
#define RCC_APB1LPENR_USART2LPEN_MASK		(1UL << RCC_APB1LPENR_USART2LPEN_POS)

#define RCC_APB1LPENR_I2C1LPEN_POS		(21U)
#define RCC_APB1LPENR_I2C1LPEN_MASK		(1UL << RCC_APB1LPENR_I2C1LPEN_POS)

#define RCC_APB1LPENR_I2C2LPEN_POS		(22U)
#define RCC_APB1LPENR_I2C2LPEN_MASK		(1UL << RCC_APB1LPENR_I2C2LPEN_POS)

#define RCC_APB1LPENR_I2C3LPEN_POS		(23U)
#define RCC_APB1LPENR_I2C3LPEN_MASK		(1UL << RCC_APB1LPENR_I2C3LPEN_POS)

#define RCC_APB1LPENR_PWRLPEN_POS		(28U)
#define RCC_APB1LPENR_PWRLPEN_MASK		(1UL << RCC_APB1LPENR_PWRLPEN_POS)


/*---------APB2LPENR's MASKs----------*/

#define RCC_APB2LPENR_TIM1LPEN_POS		(0U)
#define RCC_APB2LPENR_TIM1LPEN_MASK		(1UL << RCC_APB2LPENR_TIM1LPEN_POS)

#define RCC_APB2LPENR_USART1LPEN_POS		(4U)
#define RCC_APB2LPENR_USART1LPEN_MASK		(1UL << RCC_APB2LPENR_USART1LPEN_POS)

#define RCC_APB2LPENR_USART6LPEN_POS		(5U)
#define RCC_APB2LPENR_USART6LPEN_MASK		(1UL << RCC_APB2LPENR_USART6LPEN_POS)

#define RCC_APB2LPENR_ADC1LPEN_POS		(8U)
#define RCC_APB2LPENR_ADC1LPEN_MASK		(1UL << RCC_APB2LPENR_ADC1LPEN_POS)

#define RCC_APB2LPENR_SDIOLPEN_POS		(11U)
#define RCC_APB2LPENR_SDIOLPEN_MASK		(1UL << RCC_APB2LPENR_SDIOLPEN_POS)

#define RCC_APB2LPENR_SPI1LPEN_POS		(12U)
#define RCC_APB2LPENR_SPI1LPEN_MASK		(1UL << RCC_APB2LPENR_SPI1LPEN_POS)

#define RCC_APB2LPENR_SPI4LPEN_POS		(13U)
#define RCC_APB2LPENR_SPI4LPEN_MASK		(1UL << RCC_APB2LPENR_SPI4LPEN_POS)

#define RCC_APB2LPENR_SYSCFGLPEN_POS		(14U)
#define RCC_APB2LPENR_SYSCFGLPEN_MASK		(1UL << RCC_APB2LPENR_SYSCFGLPEN_POS)

#define RCC_APB2LPENR_TIM9LPEN_POS		(16U)
#define RCC_APB2LPENR_TIM9LPEN_MASK		(1UL << RCC_APB2LPENR_TIM9LPEN_POS)

#define RCC_APB2LPENR_TIM10LPEN_POS		(17U)
#define RCC_APB2LPENR_TIM10LPEN_MASK		(1UL << RCC_APB2LPENR_TIM10LPEN_POS)

#define RCC_APB2LPENR_TIM11LPEN_POS		(18U)
#define RCC_APB2LPENR_TIM11LPEN_MASK		(1UL << RCC_APB2LPENR_TIM11LPEN_POS)


/*---------BDCR's MASKs----------*/
//Access: 0 ≤ wait state ≤ 3, word, half-word and byte access
//Wait states are inserted in case of successive accesses to this register.
//The LSEON, LSEBYP, RTCSEL and RTCEN bits in the RCC Backup domain control register (RCC_BDCR) are in the Backup domain. As a result, after Reset, these bits are write-protected and the DBP bit in the PWR power control register (PWR_CR) has to be set before these can be modified.
//These bits are only reset after a Backup domain Reset. Any internal or external Reset will not have any effect on these bits.

//External low-speed oscillator enable
//Set and cleared by software.
//	0: LSE clock OFF
//	1: LSE clock ON
#define RCC_BDCR_LSEON_POS		(0U)
#define RCC_BDCR_LSEON_MASK		(1UL << RCC_BDCR_LSEON_POS)

//External low-speed oscillator ready
//Set and cleared by hardware to indicate when the external 32 kHz oscillator is stable. After the LSEON bit is cleared, LSERDY goes low after 6 external low-speed oscillator clock cycles.
//	0: LSE clock not ready
//	1: LSE clock ready
#define RCC_BDCR_LSERDY_POS		(1U)
#define RCC_BDCR_LSERDY_MASK		(1UL << RCC_BDCR_LSERDY_POS)

//External low-speed oscillator bypass
//Set and cleared by software to bypass oscillator in debug mode. This bit can be written only when the LSE clock is disabled.
//	0: LSE oscillator not bypassed
//	1: LSE oscillator bypassed
#define RCC_BDCR_LSEBYP_POS		(0U)
#define RCC_BDCR_LSEBYP_MASK		(1UL << RCC_BDCR_LSEBYP_POS)

//RTC clock source selection
//Set by software to select the clock source for the RTC. Once the RTC clock source has been selected, it cannot be changed anymore unless the Backup domain is reset. The BDRST bit can be used to reset them.
//	00: No clock
//	01: LSE oscillator clock used as the RTC clock
//	10: LSI oscillator clock used as the RTC clock
//	11: HSE oscillator clock divided by a programmable prescaler (selection through the
//RTCPRE[4:0] bits in the RCC clock configuration register (RCC_CFGR)) used as the RTC clock

#define RCC_BDCR_RTCSEL_POS		(8U)
#define RCC_BDCR_RTCSEL_MASK		(0x3UL << RCC_BDCR_RTCSEL_POS)

//RTC clock enable
//Set and cleared by software.
//	0: RTC clock disabled
//	1: RTC clock enabled
#define RCC_BDCR_RTCEN_POS		(15U)
#define RCC_BDCR_RTCEN_MASK		(1UL << RCC_BDCR_RTCEN_POS)

//Backup domain software reset
//Set and cleared by software.
//	0: Reset not activated
//	1: Resets the entire Backup domain
#define RCC_BDCR_BDRST_POS		(16U)
#define RCC_BDCR_BDRST_MASK		(1UL << RCC_BDCR_BDRST_POS)


/*---------CSR's MASKs----------*/

//Internal low-speed oscillator enable
//Set and cleared by software.
//	0: LSI RC oscillator OFF
//	1: LSI RC oscillator ON
#define RCC_CSR_LSION_POS		(0U)
#define RCC_CSR_LSION_MASK		(1UL << RCC_CSR_LSION_POS)

//Internal low-speed oscillator ready
//Set and cleared by hardware to indicate when the internal RC 40 kHz oscillator is stable.
//After the LSION bit is cleared, LSIRDY goes low after 3 LSI clock cycles.
//	0: LSI RC oscillator not ready
//	1: LSI RC oscillator ready
#define RCC_CSR_LSIRDY_POS		(1U)
#define RCC_CSR_LSIRDY_MASK		(1UL << RCC_CSR_LSIRDY_POS)

//Remove reset flag
//Set by software to clear the reset flags.
//	0: No effect
//	1: Clear the reset flags
#define RCC_CSR_RMVF_POS		(24U)
#define RCC_CSR_RMVF_MASK		(1UL << RCC_CSR_RMVF_POS)

//BOR reset flag
//Cleared by software by writing the RMVF bit.
//Set by hardware when a POR/PDR or BOR reset occurs.
//	0: No POR/PDR or BOR reset occurred
//	1: POR/PDR or BOR reset occurred
#define RCC_CSR_BORRSTF_POS		(25U)
#define RCC_CSR_BORRSTF_MASK		(1UL << RCC_CSR_BORRSTF_POS)

//PIN reset flag
//Set by hardware when a reset from the NRST pin occurs.
//Cleared by writing to the RMVF bit.
//	0: No reset from NRST pin occurred
//	1: Reset from NRST pin occurred
#define RCC_CSR_PINRSTF_POS		(26U)
#define RCC_CSR_PINRSTF_MASK		(1UL << RCC_CSR_PINRSTF_POS)

//POR/PDR reset flag
//Set by hardware when a POR/PDR reset occurs.
//Cleared by writing to the RMVF bit.
//	0: No POR/PDR reset occurred
//	1: POR/PDR reset occurred
#define RCC_CSR_PORRSTF_POS		(27U)
#define RCC_CSR_PORRSTF_MASK		(1UL << RCC_CSR_PORRSTF_POS)

//Software reset flag
//Set by hardware when a software reset occurs.
//Cleared by writing to the RMVF bit.
//	0: No software reset occurred
//	1: Software reset occurred
#define RCC_CSR_SFTRSTF_POS		(28U)
#define RCC_CSR_SFTRSTF_MASK		(1UL << RCC_CSR_SFTRSTF_POS)

//Independent watchdog reset flag
//Set by hardware when an independent watchdog reset from VDD domain occurs.
//Cleared by writing to the RMVF bit.
//0: No watchdog reset occurred
//1: Watchdog reset occurred
#define RCC_CSR_IWDGRSTF_POS		(29U)
#define RCC_CSR_IWDGRSTF_MASK		(1UL << RCC_CSR_IWDGRSTF_POS)

//Window watchdog reset flag
//Set by hardware when a window watchdog reset occurs.
//Cleared by writing to the RMVF bit.
//	0: No window watchdog reset occurred
//	1: Window watchdog reset occurred
#define RCC_CSR_WWDGRSTF_POS		(30U)
#define RCC_CSR_WWDGRSTF_MASK		(1UL << RCC_CSR_WWDGRSTF_POS)

//Low-power reset flag
//Set by hardware when a Low-power management reset occurs.
//Cleared by writing to the RMVF bit.
//	0: No Low-power management reset occurred
//	1: Low-power management reset occurred
#define RCC_CSR_LOWRRSTF_POS		(31U)
#define RCC_CSR_LOWRRSTF_MASK		(1UL << RCC_CSR_LOWRRSTF_POS)


/*---------SSCGR's MASKs----------*/

//The spread spectrum clock generation is available only for the main PLL.
//The RCC_SSCGR register must be written either before the main PLL is enabled or after the main PLL disabled.
//For full details about PLL spread spectrum clock generation (SSCG) characteristics, refer to the “Electrical characteristics” section in your device datasheet.

//Modulation period
//Set and cleared by software. To write before setting CR[24]=PLLON bit.
//Configuration input for modulation profile period.
#define RCC_SSCGR_MODPER_POS		(0U)
#define RCC_SSCGR_MODPER_MASK		(0xF1FFUL << RCC_SSCGR_MODPER_POS)

//Incrementation step
//Set and cleared by software. To write before setting CR[24]=PLLON bit.
//Configuration input for modulation profile amplitude.
#define RCC_SSCGR_INCSTEP_POS		(13U)
#define RCC_SSCGR_INCSTEP_MASK		(0x7FFFUL << RCC_SSCGR_INCSTEP_POS)

//Spread Select
//Set and cleared by software.
//To write before to set CR[24]=PLLON bit.
//	0: Center spread
//	1: Down spread
#define RCC_SSCGR_SPREADSEL_POS		(30U)
#define RCC_SSCGR_SPREADSEL_MASK	(0x1UL << RCC_SSCGR_SPREADSEL_POS)

//Spread spectrum modulation enable
//Set and cleared by software.
//	0: Spread spectrum modulation DISABLE. (To write after clearing CR[24]=PLLON bit)
//	1: Spread spectrum modulation ENABLE. (To write before setting CR[24]=PLLON bit)
#define RCC_SSCGR_SSCGEN_POS		(31U)
#define RCC_SSCGR_SSCGEN_MASK		(0x1UL << RCC_SSCGR_SSCGEN_POS)


/*---------PLLI2SCFGR's MASKs----------*/

//PLLI2S multiplication factor for VCO
//Set and cleared by software to control the multiplication factor of the VCO. These bits can be written only when the PLLI2S is disabled. Only half-word and word accesses are allowed to write these bits.
//Caution: The software has to set these bits correctly to ensure that the VCO output frequency is between 192 and 432 MHz. With VCO input frequency ranges from 1 to 2 MHz (refer to Figure 13 and divider factor M of the RCC PLL configuration register (RCC_PLLCFGR))
//
//	VCO output frequency = VCO input frequency × PLLI2SN with 192 ≤ PLLI2SN ≤ 432
//
//	000000000: PLLI2SN = 0, wrong configuration
//	000000001: PLLI2SN = 1, wrong configuration
//	...
//	011000000: PLLI2SN = 192
//	011000001: PLLI2SN = 193
//	011000010: PLLI2SN = 194
//	...
//	110110000: PLLI2SN = 432
//	110110000: PLLI2SN = 433, wrong configuration
//	...
//	111111111: PLLI2SN = 511, wrong configuration
#define RCC_PLLI2SCFGR_PLLI2SN_POS		(6U)
#define RCC_PLLI2SCFGR_PLLI2SN_MASK		(0x1FFUL << RCC_PLLI2SCFGR_PLLI2SN_POS)

//PLLI2S division factor for I2S clocks
//Set and cleared by software to control the I2S clock frequency. These bits should be written only if the PLLI2S is disabled. The factor must be chosen in accordance with the prescaler values inside the I2S peripherals, to reach 0.3% error when using standard crystals and 0% error with audio crystals.
//Caution: The I2Ss requires a frequency lower than or equal to 192 MHz to work correctly.
//
//	I2S clock frequency = VCO frequency / PLLR with 2 ≤PLLR ≤7
//	000: PLLR = 0, wrong configuration
//	001: PLLR = 1, wrong configuration
//	010: PLLR = 2
//	...
//	111: PLLR = 7
#define RCC_PLLI2SCFGR_PLLI2SR_POS		(28U)
#define RCC_PLLI2SCFGR_PLLI2SR_MASK		(0x7UL << RCC_PLLI2SCFGR_PLLI2SR_POS)

/*---------DCKCFGR's MASKs----------*/

//Timers clocks prescalers selection
//Set and reset by software to control the clock frequency of all the timers connected to APB1 and APB2 domain.
//	0: If the APB prescaler (PPRE1, PPRE2 in the RCC_CFGR register) is configured to a division factor of 1, TIMxCLK = HCKL . Otherwise, the timer clock frequencies are set to twice to the frequency of the APB domain to which the timers are connected: TIMxCLK = 2xPCLKx.
//	1: If the APB prescaler ( PPRE1, PPRE2 in the RCC_CFGR register) is configured to a division factor of 1 or 2, TIMxCLK = HCKL. Otherwise, the timer clock frequencies are set to four times to the frequency of the APB domain to which the timers are connected: TIMxCLK = 4xPCLKx.
#define RCC_DCKCFGR_TIMPRE_POS		(24U)
#define RCC_DCKCFGR_TIMPRE_MASK		(1UL << RCC_DCKCFGR_TIMPRE_POS)

#endif
