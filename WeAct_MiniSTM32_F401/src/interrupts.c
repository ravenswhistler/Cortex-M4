#include "TIMx.h"
#include "RCC.h"
#include "GPIO.h"

extern void TIM1_Compare_Callback(void);
extern void TIM1_Update_Callback(void);
extern void Systick_Callback(void);

__attribute__((interrupt)) void Systick(void)
{
	Systick_Callback();
	return;
}

__attribute__((interrupt)) void TIM1_UP_TIM10(void)
{
	TIM1_Update_Callback();
	TIM1->SR = ~TIMx_SR_UIF_MASK;
	return;
}


__attribute__((interrupt)) void TIM1_CC(void)
{
	TIM1_Compare_Callback();
	TIM1->SR = ~TIMx_SR_CCxIF_MASK(1);
	return;
}
