#include "API.h"

static inline void Tune_MNPQ(uint32_t PLLOUT, uint32_t *M, uint32_t *N, uint32_t *P, uint32_t *Q)
{
	//TODO
	(void)PLLOUT;
	(void)M;
	(void)N;
	(void)P;
	(void)Q;
}

static void PLL_Tune(uint32_t clk, uint32_t PLLOUT)
{
	if(PLLOUT == PLLMAXFRQ) 
	{
		if(clk == HSI)
		{
			/*
			 * Divide 16Mhz by 16 to have 1 MHz as the PLLVCO input
			 * Multiply the VCO input by 336 you get 336MHz VCO output
			 * Divide VCO output by 4 to have 84MHz
			 * Divide VCO out by 8 for USB OTG to have 42MHz for them
			 */
			SET_PLL_MNPQ(16UL, 336UL, 1UL, 8UL);
		}
		else if (clk == HSE)
		{
			/*
			 * Divide 25Mhz by 25 to have 1 MHz as the PLLVCO input
			 * Multiply the VCO input by 336 you get 336MHz VCO output
			 * Divide VCO output by 4 to have 84MHz
			 * Divide VCO out by 8 for USB OTG to have 42MHz for them
			 */
			SET_PLL_MNPQ(25UL, 336UL, 1UL, 8UL);
		}
		else
		{
			PLL_Tune(((GET_PLLSRC()) ? HSE : (HSI)), PLLOUT);
		}
	}
	else
	{
		//TODO
		uint32_t M = 0, N = 0, P = 0, Q = 0;
		Tune_MNPQ(PLLOUT, &M, &N, &P, &Q);
		SET_PLL_MNPQ(M, N, P, Q);
	}

}

uint32_t Get_System_Speed(void)
{
	if	(SYSTEM_CLOCK == HSI_CLOCK) { return HSIFRQ; }
	else if (SYSTEM_CLOCK == HSE_CLOCK) { return HSEFRQ; }
	else { return GET_PLLOUT(((GET_PLLSRC()) ? HSEFRQ : (HSIFRQ))); }
}


void __tune_system_domains(uint32_t AHB, uint32_t APB1, uint32_t APB2)
{
	//TODO
	(void) AHB;
	(void) APB1;
	(void) APB2;
}

void __maxout_system_domains(void)
{
	uint32_t sysclk = Get_System_Speed();

	if(sysclk == SYSCLK_MAX_FRQ)
	{
		MAXOUT_SYSTEM();
	}
	else
	{

		MAXOUT_AHB();
		if(sysclk <= SYSCLK_MAX_FRQ/2) { MAXOUT_APB1(); }
		else
		{
			uint32_t div = 0;
			uint32_t frq = sysclk;
			do {
				//Divide the system clock by 2^div until it's equal or less than the maximum allowable frequency in the LOW SPEED Peripheal Domain
				//Div has to be 2^n where n is within [1,4] range 
				frq = frq >> div++;
				if(div > 4) { break; } //TODO: ERROR (This is unlikely but we can't leave our six exposed, people might die)
			} while(frq > SYSCLK_MAX_FRQ/2);

			SET_PPRE1((
				   (--div == 1) ? 4UL : \
				   (div	  == 2)	? 5UL : \
				   (div   == 3)	? 6UL : \
				   7UL \
				   ));
		}
		MAXOUT_APB2();
	}
}

static void sysclk(uint32_t clk, uint32_t PLLOUT)
{

	//TODO: Check if the requested frequency is within allowable range definied by the configured wait states and vlotage range in the FLASH interface 

	switch(clk)
	{
		case HSI:
			{
				if(SYSTEM_CLOCK != HSI_CLOCK)
				{
					ENABLE_HSI();
					while(HSI_NOT_RDY);
					SET_HSI_SYSCLK();
				}
				break;
			}

		case HSE:
			{
				if(SYSTEM_CLOCK != HSE_CLOCK)
				{
					ENABLE_HSE();
					while(HSE_NOT_RDY);
					SET_HSE_SYSCLK();
				}
				break;
			}

		case PLL:
			{
				if(SYSTEM_CLOCK != PLL_CLOCK)
				{
					DISABLE_PLL();

					DISABLE_PLLI2S();

					while(PLL_LOCKED);
					
					//PLLCFGR and CR registers in RCC are not zeroed out after reset
					CLEAR_PLLCFGR();

 					ENABLE_HSE();

					SET_HSE_PLLSRC();

					PLL_Tune(HSE, PLLOUT);

					ENABLE_PLL();

					while(PLL_UNLOCKED);

					SET_PLL_SYSCLK();

					while(SYSTEM_CLOCK != PLL_CLOCK);
				}
				break;

			}
		default:
			{
				break;
			}
	}
}

void __set_system_freq(uint32_t frq)
{
	
	if(frq == PLLMAXFRQ)
	{
		sysclk(PLL, frq);
	}
	else if(frq == HSIFRQ)
	{
		sysclk(HSI, 0U);
	}
	else if(frq == HSEFRQ)
	{
		sysclk(HSE, 0U);
	}
	else
	{
		//TODO:
		//	if (frq > HSEFRQ)
		//	{
		//		//TODO
		//	}
		//	else if(HSEFRQ > frq && frq > HSIFRQ) 
		//	{
		//		//TODO
		//	}
		//	else
		//	{
		//		//TODO
		//	}
	}

	//Halt if the requested frequency isn't what was configured
	while(frq != Get_System_Speed());
}
