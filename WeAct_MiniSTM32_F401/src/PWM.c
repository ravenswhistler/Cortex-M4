#include "types.h"
#include "GPIO.h"
#include "Systick.h"
#include "RCC.h"
#include "TIMx.h"
#include "NVIC.h"

#define PSCVAL	84		//TIM1 CNT runs at 1MHz
#define ARRVAL	500		//OCxREF toggled every 1mSec (1KHz) {PWMperiod = 2*ARR -> if ARR/2 == 500 then the PWMperiod is 1mSEC when PSC(clk) == 1MHz}
#define PERIOD	500		//alias to ARRVAL
#define RES	500
#define STEP (PERIOD/RES)	//A STEP represents the Unit fraction of (increase/decrease) that corresponds to representable integer value. usually equals 1.
				//The smaller the period and the bigger the ARR value, the finer the tuning of the respective signal. Because you can change the duty cycle(active portion of the PWMperiod) twice (but in this example i choose once every overflow) in a time period equals to (2*ARR/CLK(psc))sec within [0, ARR] range. 

static volatile uint32_t LOCKED = 0;

void main()
{


	//while(get_bit_val(&RCC->CFGR, RCC_CFGR_SWS_POS, RCC_CFGR_SWS_MASK) == 0) { while(1) { } }
	/*-------GPIO Port B TIM1 Init configuration-------*/

	/**/	//Clear and Set Moder to output mode
	/**/	GPIOC->MODER &= ~GPIO_MODER_MASK(13U);
	/**/	//General Purpose Output
	/**/	GPIOC->MODER |= (1UL << GPIO_MODER_POS(13U));
	/**/
        /**/	//Clear and Set Moder to output mode
	/**/	GPIOB->MODER &= ~GPIO_MODER_MASK(13U);
	/**/	//Alternate FUnction Mode
	/**/	GPIOB->MODER |= (2UL << GPIO_MODER_POS(13U));
        /**/	
	/**/	//PB13 TIM1_CH1N
	/**/	GPIOB->AFRH |= 1 << GPIO_AFRH_POS(13UL);
        /**/	
	/**/	//Push Pull Mode
	/**/	GPIOC->OTYPER &= ~GPIO_OTYPER_MASK(13U);
	/**/	//No Puul No Push
	/**/	GPIOC->PUPDR &=  ~GPIO_PUPDR_MASK(13U);
	/**/
	/**/	//Low Speed
	/**/	GPIOC->OSPEEDR &=  ~GPIO_OSPEEDR_MASK(13U);
        /**/	
	/**/	//APB2 clock Enable for TIM1 
	/**/	RCC->APB2ENR |= RCC_APB2ENR_TIM1EN_MASK;

	/*-------------------------------------------------*/

	//Unlock TIM1
	TIM1->BDTR &= ~TIMx_BDTR_LOCK_MASK;
	
	/*-------TIM1 Master-Slave unit configs-------*/

	//CLK_INT directly fed to the Prescaler
	TIM1->SMCR &= ~TIMx_SMCR_SMS_MASK;

	/*--------------------------------------------*/

	//Following Application note 4013
	//To configure the timer PWM mode:

	//1. Configure the output pin:
	//	a) Select the output mode by writing CCS bits in CCMRx register.
	
			//Main Channel Output Mode
			TIM1->CCMR1 &= ~TIMx_CCMRx_CC1S_MASK;

	//	b) Select the polarity by writing the CCxP bit in CCER register.
	//
			//Active high polarity
			TIM1->CCER &= ~TIMx_CCER_CC1NP_MASK;

	//2. Select the PWM mode (PWM1 or PWM2) by writing OCxM bits in CCMRx register.
	
			//Sub-Output level
			//Output Channel mode: PWM mode 2 (True-HIGH)
			//OC1REF is true when CNT > CC1 
			TIM1->CCMR1 |= TIMx_CCMRx_OC1M_MASK;

			//Fast Disable
			TIM1->CCMR1 &= ~TIMx_CCMRx_OC1FE_MASK;

			//OC1REF isn't affected by any ETRF input
			TIM1->CCMR1 &= ~TIMx_CCMRx_OC1CE_MASK;

	//3. Program the period and the duty cycle respectively in ARR and CCRx registers.
	
		/*-------TIM1 Time Base unit configs-------*/

		TIM1->RCR = 0;

		TIM1->PSC = PSCVAL - 1;
	
		TIM1->ARR = ARRVAL - 1;

		TIM1->CCR1 = 0;

		/*--------------------------------------------*/
	
	//4. Set the preload bit in CCMRx register and the ARPE bit in the CR1 register.
	
		//Preload enable
		TIM1->CCMR1 |= TIMx_CCMRx_OC1PE_MASK;

		//Preload ARR
		TIM1->CR1 |= TIMx_CR1_ARPE_MASK;

		//Clock divison is 1
		TIM1->CR1 &= ~TIMx_CR1_CKDE_MASK;

	//5. Select the counting mode:
	//	a) PWM edge-aligned mode: the counter must be configured up-counting or down-counting
	//	b) PWM center aligned mode: the counter mode must be center aligned counting mode (CMS bits different from '00').
	//
		//Center-aligned mode (make interrupt at each matching between CNT and CCR1 in up counting)
		TIM1->CR1 |= 3UL << TIMx_CR1_CMS_POS;


		//Trigger a UEV and reinitialize and update the regissters imediately.
		TIM1->EGR |= TIMx_EGR_UG_MASK;


		/*-------TIM1 Timer Channel unit configs-------*/

			//Zero dead-time insertion
			//TIM1->BDTR &= ~TIMx_BDTR_BKE_MASK;

			//Off-state idle mode disable
			TIM1->BDTR &= ~TIMx_BDTR_OSSI_MASK;

			//Off-state idle mode disable
			TIM1->BDTR &= ~TIMx_BDTR_OSSR_MASK;

			//Break inputs disabled
			TIM1->BDTR &= ~TIMx_BDTR_BKE_MASK;

		/*--------------------------------------------*/


	//6. Enable the capture compare.
	
		//Don't preload control bits
		TIM1->CR2 &= ~TIMx_CR2_CCPC_MASK;

		//OC1 Disable
		TIM1->CCER &= ~TIMx_CCER_CC1E_MASK;

		//OC1N Enable
		TIM1->CCER |= TIMx_CCER_CC1NE_MASK;
		
		//Generate UEV on overflows/underflows only
		TIM1->CR1 |= TIMx_CR1_URS_MASK;

		//Always Generate UEV
		TIM1->CR1 &= ~TIMx_CR1_UDIS_MASK;

		//Enable interrupt on UEV
		TIM1->DIER |= TIMx_DIER_UIE_MASK;

		//Automatic output enable
		TIM1->BDTR |= TIMx_BDTR_AOE_MASK;

		//Enable OC/OCN when setting their respective Enable bits
		TIM1->BDTR |= TIMx_BDTR_MOE_MASK;

		//Enable interrupt on matching compare
		TIM1->DIER |= TIMx_DIER_CCxIE_MASK;


	//7. Enable the counter
	
		//Enable Timer
		TIM1->CR1 |= TIMx_CR1_CEN_MASK;

	uint32_t t = 0;
	while(1)
	{
		while(TIM1->CCR1 != RES*STEP)
		{
			t = TIM1->SR;
			t &= TIMx_SR_UIF_MASK;
			if(t == 1UL) {
				LOCKED++;
				if(LOCKED == 2) { TIM1->CCR1 += STEP; LOCKED = 0; }
				TIM1->SR = ~TIMx_SR_UIF_MASK;
			}
		}

		while(TIM1->CCR1 != 0)
		{
			t = TIM1->SR;
			t &= TIMx_SR_UIF_MASK;
			if(t == 1UL) {
				LOCKED++;
				if(LOCKED == 2) { TIM1->CCR1 -= STEP; LOCKED = 0; }
				TIM1->SR = ~TIMx_SR_UIF_MASK;
			}
		}
	}
}
