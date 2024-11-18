#include "API.h"

volatile uint32_t time = 0;

void Systick_Callback(void) {

	if(time > 0) time--;
	return;
}

//__attribute__((interrupt)) void Systick(void)
//{
//	Systick_Callback();
//	return;
//}


void Delay(uint32_t D)
{
	time = D;
	while(time != 0);
}

void main()
{
	RESET_STK();

	while(!IS_CALIB_VAL_EXACT()) { }

	SET_STK_RELOAD(REAL_TENMS);

	SET_STK_CLKSRC_AHBdiv8();

	ENABLE_STK_TICKINT();

	CLEAR_PORT_C_MODER();

	SET_PORT_C_PINx_MODE(13, 1);

	SET_PORT_C_PINx_OUTPUT_TYPE(13, OPEN_DRAIN_OTYPE);

	SET_PORT_C_PINx_O_SPEED(13, LOW);

	SET_PORT_C_PINx_PUSH_PULL(13, NO_PULL_PUSH);

	ENABLE_SYSTICK();

	while(1) {

		TOGGLE_PORT_C_PINx_O_DATA(13);
		Delay(100);
	}

	
}
