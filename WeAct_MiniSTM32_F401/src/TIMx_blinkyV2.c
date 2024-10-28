#include "Systick.h"
#include "TIMx.h"
#include "API.h"

#define PSCVAL	84		//TIM1 CNT runs at 1MHz
#define ARRVAL	500		//OCxREF toggled every 1mSec (1KHz) {PWMperiod = 2*ARR -> if ARR/2 == 500 then the PWMperiod is 1mSEC when PSC(clk) == 1MHz}
#define PERIOD	ARRVAL		
#define RES	500		//Usually i would choose something like 1% or 0.1% to modify the duty cycle but since ARR is relatively small a +/- 5 would result in faster rate of change and make the LED behave quicker than what's comfortable to the observer's
#define STEP (PERIOD/RES)	//A STEP represents the Unit fraction of (increase/decrease) that corresponds to representable integer value. usually equals 1.
				//The smaller the period and the bigger the ARR value, the finer the tuning of the respective signal's duty cycle.
				//Thi this example i chose to preload once every compare match and update once every overflow) which makes the led shine at max and dim out in a time period equals to [1000*(2*ARR/CLK(psc)) = 1] sec

static volatile uint32_t time = 0;

void Systick_Callback(void)
{
	if(time > 0) time--;
}

void wait(uint32_t t)
{
	time = t;
	while(time != 0);
}

void TIM1_Compare_Callback(void)
{
	static volatile uint32_t DIR = 1;
	//static volatile uint32_t ticks = 0;

	if(TIM1->CCR1 == RES*STEP) { DIR = 0; }
	if(TIM1->CCR1 == 0)	   { DIR = 1; }

	//To mmake the led to reach global maxima and global minima in roughly 2 sec (which is also roughly 2000 mseconds( = 2000 PWM cycles)) uncomment the next line
	//if((ticks++ % 2) == 0)
	//This makes the led to swing between shinning out at max and turn off in exactly one second
	if(1)
	{
		if(DIR)
		{
			TIM1->CCR1 += STEP;
		}
		else
		{
			TIM1->CCR1 -= STEP;
		}
	}
	return;
}

void TIM1_Update_Callback()
{
	static volatile uint32_t LOCK = 0;
	if(LOCK == 0) { ENABLE_SYSTICK(); LOCK++; }
	return;
}

void main()
{

	/*-------GPIO Port C STK Init configuration-------*/

	/**/	RESET_STK();
	/**/	while(!IS_CALIB_VAL_EXACT()) { }
	/**/	SET_STK_RELOAD(84*1000);
	/**/	SET_STK_CLKSRC_HCLK();
	/**/	ENABLE_STK_TICKINT();

	/**/	SET_PORT_C_PINx_MODE(13, OUTPUT_MODE);
	/**/	SET_PORT_C_PINx_OUTPUT_TYPE(13, OPEN_DRAIN_OTYPE);
	/**/	SET_PORT_C_PINx_O_SPEED(13, LOW);
	/**/	SET_PORT_C_PINx_PUSH_PULL(13, NO_PULL_PUSH);

	/*-------GPIO Port B TIM1 Init configuration-------*/

	/**/	//At reset Port B isn't zeroed out
	/**/	CLEAR_PORT_B_MODER();
	/**/
	/**/	SET_PORT_B_PINx_MODE(13, ALTFUNC_MODE);
	/**/	
	/**/	SET_PORT_B_PINx_ALTFUNC(13, PORT_B_PIN13_TIM1_CH1N);
	/**/	
	/**/	SET_PORT_B_PINx_OUTPUT_TYPE(13, PUSH_PULL_OTYPE);
	/**/
	/**/	SET_PORT_B_PINx_PUSH_PULL(13, NO_PULL_PUSH);
        /**/	
	/**/	SET_PORT_B_PINx_O_SPEED(13, LOW);
	/**/
	/**/	ENABLE_APB2_TIM1();

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

		TIM1->CCR1 = PERIOD - 10;

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
		//Center-aligned mode (set compare/capture flag at each match between CNT and CCR1 in ONLY while up counting)
		TIM1->CR1 |= 2UL << TIMx_CR1_CMS_POS;

		//Generate UEV from multiple sources
		TIM1->CR1 &= ~TIMx_CR1_URS_MASK;

		//Trigger a UEV and reinitialize and update the regissters imediately.
		TIM1->EGR |= TIMx_EGR_UG_MASK;

		//This line of 5 No ops and the clearing of TIM1->SR will be explained in details later in a seperate note
		NOP(); NOP(); NOP(); NOP(); NOP();

		//Clear status register to ensure no interrupt be generated when enabled
		TIM1->SR = 0;

		//Always Generate UEV
		TIM1->CR1 &= ~TIMx_CR1_UDIS_MASK;

		//Enable interrupt on UEV
		TIM1->DIER |= TIMx_DIER_UIE_MASK;

		//Enable interrupt on matching compare
		TIM1->DIER |= TIMx_DIER_CCxIE_MASK;

		/*-------TIM1 Timer Channel unit configs-------*/

			//Zero dead-time insertion
			TIM1->BDTR &= ~TIMx_BDTR_BKE_MASK;

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

		//Automatic output enable
		TIM1->BDTR |= TIMx_BDTR_AOE_MASK;

		//Enable OC/OCN when setting their respective Enable bits
		TIM1->BDTR |= TIMx_BDTR_MOE_MASK;



	//7. Enable the counter
	
		//Enable TIM1 Capture/Compare Interrupt
		Enable_IRQ(TIM1_CC_IRQn);
		Enable_IRQ(TIM1_UP_TIM10_IRQn);

		//Enable Timer
		TIM1->CR1 |= TIMx_CR1_CEN_MASK;


	while(1)
	{
		TOGGLE_PORT_C_PINx_O_DATA(13);
		//The timer is running at 1MHz, meanwhile Systick runs at 84MHz, the timer ticks every 1 milli-second while systick ticks every 1 microsecond
		//It takes 1000 ticks for timer 1 to span 1 second
		//It takes 84000 ticks for systick 1 to span 1 second
		//The reload value for both equal the total amount of ticks it takes to span 1 second (with that amount halvedin Center-aligned mode for TIM1)
		//TO prove the calculations correct, use 1 second worth of ARR as Systick delay
		wait(2*ARRVAL);
	}

}
