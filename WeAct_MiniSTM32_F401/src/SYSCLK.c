#include "API.h"

static void PLL_Init(void);

static inline void PLL_MaxOut(CLK clk)
{
	if(clk == HSI)
	{
		//Configure PLL's VCO to 1MHz (HSI is 16MHz)
		//Set PLL's N (VCO Multiplication Factor) to 336 MHz = 0x150UL
		//Set PLL's P to 2
		SET_PLL_MNP(16UL, 336UL, 2UL);
	}
	else if (clk = HSE)
	{
		//Configure PLL's VCO to 1MHz (HSE is 25MHz) Set M = 25
		//Set PLL's N (VCO Multiplication Factor) Set N = 336 MHz
		//Set PLL's P to 2
		SET_PLL_MNP(25UL, 336UL, 2UL);
	}
	else
	{
		//Call PLL_Init();
	}
}

static inline uint32_t Get_System_Speed(void)
{
	if	(IS_HSI_SYSCLK()) { return HSIFRQ; }
	else if (IS_HSE_SYSCLK()) { return HSEFRQ; }
	else 			  { return GET_PLLOUT( (GET_PLLSRC() ? HSEFRQ : (HSIFRQ)) ); }

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
			uint32_t div = 1;
			uint32_t frq = sysclk;
			do {
				frq >> div++;
			}
			while(frq >= SYSCLK_MAX_FRQ/2);
			SET_PPRE1(--div);
			
		}
		MAXOUT_APB2();
	}
}

static void sysclk(CLK clk)
{
	switch(clk)
	{

		case HSI:
			{
				if(!IS_HSI_SYSCLK())
				{
					//Enable HSI
					ENABLE_HSI();

					//Wait until HSI is ready
					while(!IS_HSI_RDY());

					//Set HSI as system clock
					SET_HSI_SYSCLK();
				}
				break;
			}
		case HSE:
			{
				if(!IS_HSE_SYSCLK())
				{
					//Enable HSE
					ENABLE_HSE();

					//Wait until HSE is ready
					while(!IS_HSE_RDY());

					//Set HSE as system clock
					SET_HSE_SYSCLK();
				}
				break;
			}
		case PLL:
			{
				if(!IS_PLL_SYSCLK())
				{
					PLL_Init();
					SET_PLL_SYSCLK();
				}
				break;
			}
		default:
			{
				break;
			}
	}
}

static inline void PLL_Init(void)
{
	//After reset the HSI is tha main clock source (see RM0368 Rev 5 6.2.6)
	
	//Check if PLL is System clock and switch to HSI if true

	sysclk(HSI);

	//Disable PLL
	DISABLE_PLL();

	//Wait until it's dead
	while(IS_PLL_RDY());

	//HSI as Main PLL Input
	SET_HSI_PLLSRC();

	//Max out main PLL OUT to 84MHz
	PLL_MaxOut(HSI);

	//Now the Main PLL output equals to 84MHz

	//Turn on the princess back again
	ENABLE_PLL();
}

void __set_system_freq(uint32_t frq)
{
	
	if(frq == PLLMAXFRQ || frq == HSIFRQ || frq == HSEFRQ)
	{
		if(frq == PLLMAXFRQ)
		{
			sysclk(PLL);
		}
		else if(frq == HSIFRQ)
		{
			sysclk(HSI);
		}
		else
		{
			sysclk(HSE);
		}
	}
	else
	{
		if (frq > HSEFRQ)
		{
			//TODO
		}
		else if(HSEFRQ > frq && frq > HSIFRQ) 
		{
			//TODO
		}
		else
		{
			//TODO
		}
	}
}
