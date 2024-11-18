#include "API.h"

#define CALLBACKS 		\
	X(TIM1_Update) 		\
	X(TIM1_Compare)		\
	X(Systick)		\
	X(DMA2_Stream0)

#define X(callback)	__attribute__((weak)) void callback##_Callback(void) { while(1); }
	CALLBACKS
#undef X

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

__attribute__((interrupt)) void DMA2_Stream0(void)
{
	DMA2_Stream0_Callback();
	return;
}
