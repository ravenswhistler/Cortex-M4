#ifndef RAV_API
#define RAV_API

#include "Systick.h"
#include "NVIC.h"
#include "ITM.h"
#include "SCB.h"

#include "TIMx.h"
#include "RCC.h"
#include "GPIO.h"
#include "MPU.h"
#include "DMA.h"
#include "USART.h"

static inline uint32_t get_bit_val( volatile uint32_t *reg, uint32_t bit_pos, uint32_t bitmask)
{
	return ((uint32_t)((uint32_t)(*reg & bitmask) >> bit_pos));
}




/*----------------------NVIC----------------------*/

#define SET_NVIC_ISER()		(NVIC->ISER[0] |= 0xFFFFFFFFUL); \
				(NVIC->ISER[1] |= 0xFFFFFFFFUL); \
				(NVIC->ISER[2] |= 0xFFFFFFFFUL); \
				(NVIC->ISER[3] |= 0xFFFFFFFFUL); \
				(NVIC->ISER[4] |= 0xFFFFFFFFUL); \
				(NVIC->ISER[5] |= 0xFFFFFFFFUL); \
				(NVIC->ISER[6] |= 0xFFFFFFFFUL); \
				(NVIC->ISER[7] |= 0xFFFFFFFFUL)

#define SET_NVIC_ICER()		(NVIC->ICER[0] |= 0xFFFFFFFFUL); \
				(NVIC->ICER[1] |= 0xFFFFFFFFUL); \
				(NVIC->ICER[2] |= 0xFFFFFFFFUL); \
				(NVIC->ICER[3] |= 0xFFFFFFFFUL); \
				(NVIC->ICER[4] |= 0xFFFFFFFFUL); \
				(NVIC->ICER[5] |= 0xFFFFFFFFUL); \
				(NVIC->ICER[6] |= 0xFFFFFFFFUL); \
				(NVIC->ICER[7] |= 0xFFFFFFFFUL)

void Enable_System_Interrutps(void);
void Enable_External_Interrupts(void);
void Disable_System_Interrupts(void);  
void Disable_External_Interrupts(void);

void Enable_IRQ(IRQN_Type irq);
uint32_t Is_IRQ_Enabled(IRQN_Type irq);
void Disable_IRQ(IRQN_Type irq);
uint32_t Is_IRQ_Disabled(IRQN_Type irq);

void Set_IRQn_Priority(IRQN_Type irq, uint32_t p);
uint32_t Get_IRQn_Priority(IRQN_Type irq);

/*++++++++++++++++++++++++++++++++++++++++++++++++*/


/*----------------------FLASH----------------------*/

void FLASH_Init(void);

/*+++++++++++++++++++++++++++++++++++++++++++++++++*/



/*----------------------SCB----------------------*/

typedef enum {

	NO_SUB_PRIO		= 0,
	ONE_BIT_SUB_PRIO	= 4,
	TWO_BIT_SUB_PRIO	= 5,
	THREE_BIT_SUB_PRIO	= 6,
	NO_GRP_PRIO		= 7,
	FOUR_BIT_SUB_PRIO	= 7

} SCB_PRIO_GRP;

#define SCB_AIRCR_KEY			(0x5FAUL)
#define UNLOCK_SCB_AIRCR()		(SCB->AIRCR |= (SCB_AIRCR_KEY << SCB_AIRCR_VECTKEY_POS))

#define SET_SCB_PRIORITY_GROUPING(x)	(SCB->AIRCR |= x << SCB_AIRCR_PRIGROUP_POS)
#define GET_SCB_PRIORITY_GROUPING()	(SCB->AIRCR & SCB_AIRCR_PRIGROUP_MASK)
#define IS_SCB_PRIORITY_GROUPING(x)	(GET_SCB_PRIORITY_GROUPING == (x << SCB_AIRCR_PRIGROUP_POS))

#define SET_SCB_VTABLE_OFFSET(x)	(SCB->VTOR |= (x & 0x1FFE00UL << SCB_VTOR_TABLEOFF_POS)
#define GET_SCB_VTABLE_OFFSET(x)	(SCB->VTOR & SCB_VTOR_TABLEOFF_MASK)
#define IS_SCB_VTABLE_OFFSET(x)		(GET_SCB_VTABLE_OFFSET == (x & 0x1FFE00UL << SCB_VTOR_TABLEOFF_POS))

#define SET_SCB_VTABLE_IN_FLASH()	(SCB->VTOR &= ~SCB_VTOR_TBLBASE_MASK)
#define SET_SCB_VTABLE_IN_SRAM()	(SCB->VTOR |= SCB_VTOR_TBLBASE_MASK)

#define IS_SCB_VTABLE_IN_FLASH()	((SCB->VTOR & SCB_VTOR_TBLBASEMASK) == (0UL << SCB_VTOR_TBLBASE_POS))
#define IS_SCB_VTABLE_IN_SRAM()		((SCB->VTOR & SCB_VTOR_TBLBASEMASK) == SCB_VTOR_TBLBASE_MASK)

#define SET_SCB_SYSTICK_PRIO(x)		(SCB->SHPR3 |= (x & 0xFUL) << 28U)

/*+++++++++++++++++++++++++++++++++++++++++++++++*/

/*---------------------------RCC---------------------------*/

#define HSIFRQ		(16*MHz)
#define HSEFRQ		(25*MHz)
#define SYSCLK_MAX_FRQ 	(84*MHz)
#define PLLMAXFRQ	SYSCLK_MAX_FRQ

#define HSI 0UL
#define HSE 1UL
#define PLL 2UL

#define SYSTEM_CLOCK		(RCC->CFGR & RCC_CFGR_SWS_MASK)

#define HSI_CLOCK		(HSI << RCC_CFGR_SWS_POS)
#define HSE_CLOCK		(HSE << RCC_CFGR_SWS_POS)
#define PLL_CLOCK		(PLL << RCC_CFGR_SWS_POS)

#define HSI_RDY			((RCC->CR & RCC_CR_HSIRDY_MASK) == RCC_CR_HSIRDY_MASK)
#define HSI_NOT_RDY		((RCC->CR & RCC_CR_HSIRDY_MASK) != RCC_CR_HSIRDY_MASK)

#define HSE_RDY			((RCC->CR & RCC_CR_HSERDY_MASK) == RCC_CR_HSERDY_MASK)
#define HSE_NOT_RDY		((RCC->CR & RCC_CR_HSERDY_MASK) != RCC_CR_HSERDY_MASK)

#define PLL_RDY			((RCC->CR & RCC_CR_PLLRDY_MASK) == RCC_CR_PLLRDY_MASK)
#define PLL_LOCKED		PLL_RDY
#define PLL_NOT_RDY		((RCC->CR & RCC_CR_PLLRDY_MASK) != RCC_CR_PLLRDY_MASK)
#define PLL_UNLOCKED		PLL_NOT_RDY


#define ENABLE_HSI()		RCC->CR |= RCC_CR_HSION_MASK
#define DISABLE_HSI()		RCC->CR &= ~RCC_CR_HSION_MASK

#define ENABLE_HSE()		RCC->CR |= RCC_CR_HSEON_MASK
#define DISABLE_HSE()		RCC->CR &= ~RCC_CR_HSEON_MASK

#define ENABLE_PLL()		RCC->CR |= RCC_CR_PLLON_MASK
#define DISABLE_PLL()		RCC->CR &= ~RCC_CR_PLLON_MASK
#define DISABLE_PLLI2S()	RCC->CR &= ~RCC_CR_PLLI2SON_MASK

#define SET_HSI_SYSCLK()	RCC->CFGR &= ~RCC_CFGR_SW_MASK
#define SET_HSE_SYSCLK()	RCC->CFGR |= HSE << RCC_CFGR_SW_POS
#define SET_PLL_SYSCLK()	RCC->CFGR |= PLL << RCC_CFGR_SW_POS

#define SET_HSI_PLLSRC()	RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLSRC_MASK
#define SET_HSE_PLLSRC()	RCC->PLLCFGR |= RCC_PLLCFGR_PLLSRC_MASK

#define CLEAR_PLLCFGR()		RCC->PLLCFGR = 0

#define SET_PLL_MNPQ(m,n,p,q)	RCC->PLLCFGR |= ((m << RCC_PLLCFGR_PLLM_POS) | \
						(n << RCC_PLLCFGR_PLLN_POS) | \
						(p << RCC_PLLCFGR_PLLP_POS) | \
						(q << RCC_PLLCFGR_PLLQ_POS))

#define GET_PLLSRC()		((RCC->PLLCFGR & RCC_PLLCFGR_PLLSRC_MASK) == RCC_PLLCFGR_PLLSRC_MASK)

#define PLLM			((uint32_t)(RCC->PLLCFGR & RCC_PLLCFGR_PLLM_MASK))
#define PLLN			((uint32_t)((RCC->PLLCFGR & RCC_PLLCFGR_PLLN_MASK) >> (RCC_PLLCFGR_PLLN_POS)))

#define PLLP			(2U + 2*((uint32_t)((RCC->PLLCFGR & RCC_PLLCFGR_PLLP_MASK) >> (RCC_PLLCFGR_PLLP_POS))))

#define PLLQ			((uint32_t)((RCC->PLLCFGR & RCC_PLLCFGR_PLLQ_MASK) >> RCC_PLLCFGR_PLLQ_POS))

#define GET_PLLOUT(PLLSRC)	((PLLSRC/PLLM)*(PLLN/PLLP))

#define MAXOUT_SYSTEM()		RCC->CFGR |= ((0UL << RCC_CFGR_HPRE_POS) | (4UL << RCC_CFGR_PPRE1_POS) | (0UL << RCC_CFGR_PPRE2_POS));

#define	MAXOUT_AHB()		RCC->CFGR |= (0UL << RCC_CFGR_HPRE_POS)
#define MAXOUT_APB1()		RCC->CFGR |= (0UL << RCC_CFGR_PPRE1_POS)
#define BISECT_APB1()		RCC->CFGR |= (4UL << RCC_CFGR_PPRE1_POS)
#define	MAXOUT_APB2()		RCC->CFGR |= (0UL << RCC_CFGR_PPRE2_POS)

#define SET_PPRE1(x)		RCC->CFGR |= (x << RCC_CFGR_PPRE1_POS)

void __set_system_freq(uint32_t frq);
void __maxout_system_domains(void);

/*---------------------------SYSTICK---------------------------*/

#define	RESET_STK()		STK->CTRL = 0

#define ENABLE_SYSTICK()	STK->CTRL |= STK_CTRL_ENABLE_MASK
#define DISABLE_SYSTICK()	STK->CTRL &= ~STK_CTRL_ENABLE_MASK

#define	CLEAR_STK_VAL()		STK-VAL = 0

#define IS_CALIB_VAL_EXACT()	((STK->CALIB & STK_CALIB_SKEW_MASK) == STK_CALIB_SKEW_MASK)

#define FAKE_TENMS		(STK->CALIB & STK_CALIB_TENMS_MASK)
#define ONEMS			FAKE_TENMS
#define REAL_TENMS		10*ONEMS

#define SET_STK_RELOAD(x)	STK->LOAD = x

#define SET_STK_CLKSRC_AHBdiv8()	STK->CTRL &= ~STK_CTRL_CLKSOURCE_MASK
#define SET_STK_CLKSRC_HCLK()		STK->CTRL |= STK_CTRL_CLKSOURCE_MASK

#define ENABLE_STK_TICKINT()		STK->CTRL |= STK_CTRL_TICINT_MASK
#define DISABLE_STK_TICKINT()		STK->CTRL &= ~STK_CTRL_TICINT_MASK

/*---------------------------MPU---------------------------*/

#define ENABLE_MPU()	MPU->CTRL |= MPU_CTRL_ENABLE_MASK
#define DISABLE_MPU()	MPU->CTRL &= ~MPU_CTRL_ENABLE_MASK

/*---------------------------GPIO---------------------------*/

#define RESET_AHB_PORT_A()	RCC->AHB1RSTR |= RCC_AHB1RSTR_GPIOAEN_MASK
#define RESET_AHB_PORT_B()	RCC->AHB1RSTR |= RCC_AHB1RSTR_GPIOBEN_MASK
#define RESET_AHB_PORT_C()	RCC->AHB1RSTR |= RCC_AHB1RSTR_GPIOCEN_MASK

#define ENABLE_AHB_PORT_A()	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN_MASK
#define ENABLE_AHB_PORT_B()	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN_MASK
#define ENABLE_AHB_PORT_C()	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN_MASK

#define DISABLE_AHB_PORT_A()	RCC->AHB1ENR &= ~RCC_AHB1ENR_GPIOAEN_MASK
#define DISABLE_AHB_PORT_B()	RCC->AHB1ENR &= ~RCC_AHB1ENR_GPIOBEN_MASK
#define DISABLE_AHB_PORT_C()	RCC->AHB1ENR &= ~RCC_AHB1ENR_GPIOCEN_MASK

typedef enum {
	GPIO_PIN_INPUT_MODE	= 0UL,
	GPIO_PIN_OUTPUT_MODE	= 1UL,
	GPIO_PIN_ALTFUNC_MODE	= 2UL,
	GPIO_PIN_ANALOG_MODE	= 3UL
} GPIO_PORT_PIN_MODE;

#define CLEAR_PORT_A_MODER()	GPIOA->MODER = 0
#define CLEAR_PORT_B_MODER() 	GPIOB->MODER = 0
#define CLEAR_PORT_C_MODER() 	GPIOC->MODER = 0

typedef enum {

	GPIO_PORT_A_PIN0 = 0,
	GPIO_PORT_A_PIN1 = 1,
	GPIO_PORT_A_PIN2 = 2,
	GPIO_PORT_A_PIN3 = 3,
	GPIO_PORT_A_PIN4 = 4,
	GPIO_PORT_A_PIN5 = 5,
	GPIO_PORT_A_PIN6 = 6,
	GPIO_PORT_A_PIN7 = 7,
	GPIO_PORT_A_PIN8 = 8,
	GPIO_PORT_A_PIN9 = 9,
	GPIO_PORT_A_PIN10 = 10,
	GPIO_PORT_A_PIN11 = 11,
	GPIO_PORT_A_PIN12 = 12,
	GPIO_PORT_A_PIN13 = 13,
	GPIO_PORT_A_PIN14 = 14,
	GPIO_PORT_A_PIN15 = 15,

	GPIO_PORT_B_PIN0 = 0,
	GPIO_PORT_B_PIN1 = 1,
	GPIO_PORT_B_PIN2 = 2,
	GPIO_PORT_B_PIN3 = 3,
	GPIO_PORT_B_PIN4 = 4,
	GPIO_PORT_B_PIN5 = 5,
	GPIO_PORT_B_PIN6 = 6,
	GPIO_PORT_B_PIN7 = 7,
	GPIO_PORT_B_PIN8 = 8,
	GPIO_PORT_B_PIN9 = 9,
	GPIO_PORT_B_PIN10 = 10,
	GPIO_PORT_B_PIN11 = 11,
	GPIO_PORT_B_PIN12 = 12,
	GPIO_PORT_B_PIN13 = 13,
	GPIO_PORT_B_PIN14 = 14,
	GPIO_PORT_B_PIN15 = 15,

	GPIO_PORT_C_PIN0 = 0,
	GPIO_PORT_C_PIN1 = 1,
	GPIO_PORT_C_PIN2 = 2,
	GPIO_PORT_C_PIN3 = 3,
	GPIO_PORT_C_PIN4 = 4,
	GPIO_PORT_C_PIN5 = 5,
	GPIO_PORT_C_PIN6 = 6,
	GPIO_PORT_C_PIN7 = 7,
	GPIO_PORT_C_PIN8 = 8,
	GPIO_PORT_C_PIN9 = 9,
	GPIO_PORT_C_PIN10 = 10,
	GPIO_PORT_C_PIN11 = 11,
	GPIO_PORT_C_PIN12 = 12,
	GPIO_PORT_C_PIN13 = 13,
	GPIO_PORT_C_PIN14 = 14,
	GPIO_PORT_C_PIN15 = 15

} GPIO_PORT_PIN;

#define SET_PORT_A_PINx_MODE(x,y)	(GPIOA->MODER &= ~GPIO_MODER_MASK(x)); (GPIOA->MODER |= (y << GPIO_MODER_POS(x)))
#define SET_PORT_B_PINx_MODE(x,y)	(GPIOB->MODER &= ~GPIO_MODER_MASK(x)); (GPIOB->MODER |= (y << GPIO_MODER_POS(x)))
#define SET_PORT_C_PINx_MODE(x,y)	(GPIOC->MODER &= ~GPIO_MODER_MASK(x)); (GPIOC->MODER |= (y << GPIO_MODER_POS(x)))

#define AF(x)	(x%16)
#define PORT_B_PIN13_TIM1_CH1N	AF(1)

#define SET_PORT_A_PINx_ALTFUNC(x,y) \
	((x > 7 ) ? (GPIOA->AFRH |= ( y << GPIO_AFRH_POS(x))) : \
	 (GPIOA->AFRL |= ( y << GPIO_AFRL_POS(x)))

#define SET_PORT_B_PINx_ALTFUNC(x,y) \
	((x > 7 ) ? (GPIOB->AFRH |= ( y << GPIO_AFRH_POS(x))) : \
	 (GPIOB->AFRL |= ( y << GPIO_AFRL_POS(x)))

#define SET_PORT_C_PINx_ALTFUNC(x,y) \
	((x > 7 ) ? (GPIOC->AFRH |= ( y << GPIO_AFRH_POS(x))) : \
	 (GPIOC->AFRL |= ( y << GPIO_AFRL_POS(x)))

typedef enum {
	GPIO_PORT_PUSH_PULL_TYPE 	= 0UL,
	GPIO_PORT_OPEN_DRAIN_TYPE	= 1UL
} GPIO_PORT_OUTPUT_TYPE;

#define SET_PORT_A_PINx_OUTPUT_TYPE(x, y)	(GPIOA->OTYPER &= ~GPIO_OTYPER_MASK(x)); (GPIOA->OTYPER |= (y << GPIO_OTYPER_POS(x))
#define SET_PORT_B_PINx_OUTPUT_TYPE(x, y)	(GPIOB->OTYPER &= ~GPIO_OTYPER_MASK(x)); (GPIOB->OTYPER |= (y << GPIO_OTYPER_POS(x))
#define SET_PORT_C_PINx_OUTPUT_TYPE(x, y)	(GPIOC->OTYPER &= ~GPIO_OTYPER_MASK(x)); (GPIOC->OTYPER |= (y << GPIO_OTYPER_POS(x))

typedef enum {
	GPIO_PORT_LOW_SPEED		= 0UL,
	GPIO_PORT_MEDIUM_SPEED		= 1UL,
	GPIO_PORT_HIGH_SPEED		= 2UL,
	GPIO_PORT_VERY_HIGH_SPEED	= 3UL
} GPIO_PORT_SPEED;
#define SET_PORT_A_PINx_O_SPEED(x,y)	(GPIOA->OSPEEDR &= ~GPIO_OSPEEDR_MASK(x)); (GPIOA->OSPEEDR |= (y << GPIO_OSPEEDR_POS(x)))
#define SET_PORT_B_PINx_O_SPEED(x,y)	(GPIOB->OSPEEDR &= ~GPIO_OSPEEDR_MASK(x)); (GPIOB->OSPEEDR |= (y << GPIO_OSPEEDR_POS(x)))
#define SET_PORT_C_PINx_O_SPEED(x,y)	(GPIOC->OSPEEDR &= ~GPIO_OSPEEDR_MASK(x)); (GPIOC->OSPEEDR |= (y << GPIO_OSPEEDR_POS(x)))

typedef enum {
	GPIO_IO_NO_PULL_UP_OR_DOWN	= 0UL,
	GPIO_IO_PULL_UP			= 1UL,
	GPIO_IO_PULL_DOWN		= 2UL
} GPIO_PUP_PDOWN;

#define SET_PORT_A_PINx_PUSH_PULL(x,y)	(GPIOA->PUPDR &= ~GPIO_PUPDR_MASK(x)); (GPIOA->PUPDR |= (y << GPIO_PUPDR_POS(x)))
#define SET_PORT_B_PINx_PUSH_PULL(x,y)	(GPIOB->PUPDR &= ~GPIO_PUPDR_MASK(x)); (GPIOB->PUPDR |= (y << GPIO_PUPDR_POS(x)))
#define SET_PORT_C_PINx_PUSH_PULL(x,y)	(GPIOC->PUPDR &= ~GPIO_PUPDR_MASK(x)); (GPIOC->PUPDR |= (y << GPIO_PUPDR_POS(x)))

#define IS_PORT_z_PINx_OPEN_DRAIN(z, x) (n->OTYPER & (uint16_t)GPIO_OTYPER_MASK(x)) == (uint16_t)(GPIO_PORT_OPEN_DRAIN_TYPE << GPIO_OTYPER_POS(x))

#define ENABLE_PORT_A_PINx_O_DATA(x)	(IS_PORT_z_PINx_OPEN_DRAIN(GPIOA, x)) ? (GPIOA->ODR &= ~GPIO_ODR_MASK(x)) : (GPIOA->ODR |= GPIO_ODR_MASK(x))
#define ENABLE_PORT_B_PINx_O_DATA(x)	(IS_PORT_z_PINx_OPEN_DRAIN(GPIOB, x)) ? (GPIOB->ODR &= ~GPIO_ODR_MASK(x)) : (GPIOB->ODR |= GPIO_ODR_MASK(x))
#define ENABLE_PORT_C_PINx_O_DATA(x)	(IS_PORT_z_PINx_OPEN_DRAIN(GPIOC, x)) ? (GPIOC->ODR &= ~GPIO_ODR_MASK(x)) : (GPIOC->ODR |= GPIO_ODR_MASK(x))

#define DISABLE_PORT_A_PINx_O_DATA(x)	(IS_PORT_z_PINx_OPEN_DRAIN(GPIOA, x)) ? (GPIOA->ODR |= GPIO_ODR_MASK(x)) : (GPIOA->ODR &= ~GPIO_ODR_MASK(x))
#define DISABLE_PORT_B_PINx_O_DATA(x)   (IS_PORT_z_PINx_OPEN_DRAIN(GPIOB, x)) ? (GPIOB->ODR |= GPIO_ODR_MASK(x)) : (GPIOB->ODR &= ~GPIO_ODR_MASK(x))
#define DISABLE_PORT_C_PINx_O_DATA(x)   (IS_PORT_z_PINx_OPEN_DRAIN(GPIOC, x)) ? (GPIOC->ODR |= GPIO_ODR_MASK(x)) : (GPIOC->ODR &= ~GPIO_ODR_MASK(x))

#define TOGGLE_PORT_A_PINx_O_DATA(x)	(GPIOA->ODR ^= GPIO_ODR_MASK(x))
#define TOGGLE_PORT_B_PINx_O_DATA(x)    (GPIOB->ODR ^= GPIO_ODR_MASK(x))
#define TOGGLE_PORT_C_PINx_O_DATA(x)    (GPIOC->ODR ^= GPIO_ODR_MASK(x))

#define RESET_APB2_TIM1()	RCC->APB2RSTR |= RCC_APB2RSTR_TIM1RST_MASK;
#define ENABLE_APB2_TIM1()	RCC->APB2ENR |= RCC_APB2ENR_TIM1EN_MASK;
#define DISABLE_APB2_TIM1()	RCC->APB2ENR &= ~RCC_APB2ENR_TIM1EN_MASK;


void LED_Config(GPIO_Type *GPIO, GPIO_PORT_PIN pin, uint32_t ENABLE);

void DIM_LED(GPIO_Type *GPIO, GPIO_PORT_PIN pin);
void SHINE_LED(GPIO_Type *GPIO, GPIO_PORT_PIN pin);
void TOGGLE_LED(GPIO_Type *GPIO, GPIO_PORT_PIN  pin);

/*++++++++++++++++++++++++++++++++++++++++++++++*/

/*----------------------DMA----------------------*/

#define ENABLE_DMA1_CLK()	(RCC->AHB1ENR |= RCC_AHB1ENR_DMA1EN_MASK)
#define ENABLE_DMA2_CLK()	(RCC->AHB1ENR |= RCC_AHB1ENR_DMA2EN_MASK)

#define DISABLE_DMA1_CLK()	(RCC->AHB1ENR &= ~RCC_AHB1ENR_DMA1EN_MASK)
#define DISABLE_DMA2_CLK()	(RCC->AHB1ENR &= ~RCC_AHB1ENR_DMA2EN_MASK)

typedef enum {
	DMA_S0 = 0,
	DMA_S1 = 1,
	DMA_S2 = 2,
	DMA_S3 = 3,
	DMA_S4 = 4,
	DMA_S5 = 5,
	DMA_S6 = 6,
	DMA_S7 = 7
} DMA_STREAMx;

typedef enum {

/*------DMA1 Stream 0 Request Channels------*/
	DMA1_S0_CH0_SPI3_RX = 0,
	DMA1_S0_CH1_I2C1_RX = 1,
	DMA1_S0_CH2_TIM4_CH1 = 2,
	DMA1_S0_CH3_I2S3_EXT_RX = 3,
	DMA1_S0_CH4 = 4,
	DMA1_S0_CH5 = 5,
	DMA1_S0_CH6_TIM5_CH3 = 6,
	DMA1_S0_CH6_TIM5_UP = 6,
	DMA1_S0_CH7 = 7,

/*------DMA1 Stream 1 Request Channels------*/
	DMA1_S1_CH0 = 0,
	DMA1_S1_CH1_I2C3_RX = 1,
	DMA1_S1_CH2 = 2,
	DMA1_S1_CH3_TIM2_UP = 3,
	DMA1_S1_CH3_TIM2_CH3 = 3,
	DMA1_S1_CH4 = 4,
	DMA1_S1_CH5 = 5,
	DMA1_S1_CH6_TIM5_CH4 = 6,
	DMA1_S1_CH6_TIM5_TRIG = 6,
	DMA1_S1_CH7 = 7,

/*------DMA1 Stream 2 Request Channels------*/
	DMA1_S2_CH0_SPI3_RX = 0,
	DMA1_S2_CH1 = 1,
	DMA1_S2_CH2_I2S3_EXT_RX = 2,
	DMA1_S2_CH3_I2C3_RX = 3,
	DMA1_S2_CH4 = 4,
	DMA1_S2_CH5_TIM3_CH4 = 5,
	DMA1_S2_CH5_TIM3_UP = 5,
	DMA1_S2_CH6_TIM5_CH1 = 6,
	DMA1_S2_CH7_I2C2_RX = 7,

/*------DMA1 Stream 3 Request Channels------*/
	DMA1_S3_CH0_SPI2_RX = 0,
	DMA1_S3_CH1 = 1,
	DMA1_S3_CH2_TIM4_CH2 = 2,
	DMA1_S3_CH3_I2S2_EXT_RX = 3,
	DMA1_S3_CH4 = 4,
	DMA1_S3_CH5 = 5,
	DMA1_S3_CH6_TIM5_CH4 = 6,
	DMA1_S3_CH6_TIM5_TRIG = 6,
	DMA1_S3_CH7_I2C2_RX = 7,

/*------DMA1 Stream 4 Request Channels------*/
	DMA1_S4_CH0_SPI2_TX = 0,
	DMA1_S4_CH1 = 1,
	DMA1_S4_CH2_I2S2_EXT_TX = 2,
	DMA1_S4_CH3_I2C3_TX = 3,
	DMA1_S4_CH4 = 4,
	DMA1_S4_CH5_TIM3_CH1 = 5,
	DMA1_S4_CH5_TIM1_TRIG = 5,
	DMA1_S4_CH6_TIM5_CH2 = 6,
	DMA1_S4_CH7 = 7,

/*------DMA1 Stream 5 Request Channels------*/
	DMA1_S5_CH0_SPI3_TX = 0,
	DMA1_S5_CH1_I2C1_RX = 1,
	DMA1_S5_CH2_I2S3_EXT_TX = 2,
	DMA1_S5_CH3_TIM2_CH1 = 3,
	DMA1_S5_CH4_USART2_RX = 4,
	DMA1_S5_CH5_TIM3_CH2 = 5,
	DMA1_S5_CH6_I2C3_TX = 6,
	DMA1_S5_CH7 = 7,

/*------DMA1 Stream 6 Request Channels------*/
	DMA1_S6_CH0 = 0,
	DMA1_S6_CH1_I2C1_TX = 1,
	DMA1_S6_CH2_TIM4_UP = 2,
	DMA1_S6_CH3_TIM2_CH2 = 3,
	DMA1_S6_CH3_TIM2_CH4 = 3,
	DMA1_S6_CH4_USART2_TX = 4,
	DMA1_S6_CH5 = 5,
	DMA1_S6_CH6_TIM5_UP = 6,
	DMA1_S6_CH7 = 7,

/*------DMA1 Stream 7 Request Channels------*/
	DMA1_S7_CH0_SPI3_TX = 0,
	DMA1_S7_CH1_I2C1_TX = 1,
	DMA1_S7_CH2_TIM4_CH3 = 2,
	DMA1_S7_CH3_TIM2_UP = 3,
	DMA1_S7_CH3_TIM2_CH4 = 3,
	DMA1_S7_CH4 = 4,
	DMA1_S7_CH5_TIM3_CH3 = 5,
	DMA1_S7_CH6 = 6,
	DMA1_S7_CH7_I2C2_TX = 7,

/*------DMA2 Stream 0 Request Channels------*/
	DMA2_S0_CH0_ADC1 = 0,
	DMA2_S0_CH1 = 1,
	DMA2_S0_CH2 = 2,
	DMA2_S0_CH3_SPI1_RX = 3,
	DMA2_S0_CH4_SPI4_RX = 4,
	DMA2_S0_CH5 = 5,
	DMA2_S0_CH6_TIM1_TRIG = 6,
	DMA2_S0_CH7 = 7,

/*------DMA2 Stream 1 Request Channels------*/
	DMA2_S1_CH0 = 0,
	DMA2_S1_CH1 = 1,
	DMA2_S1_CH2 = 2,
	DMA2_S1_CH3 = 3,
	DMA2_S1_CH4_SPI4_TX = 4,
	DMA2_S1_CH5_USART6_RX = 5,
	DMA2_S1_CH6_TIM1_CH1 = 6,
	DMA2_S1_CH7 = 7,

/*------DMA2 Stream 2 Request Channels------*/
	DMA2_S2_CH0 = 0,
	DMA2_S2_CH1 = 1,
	DMA2_S2_CH2 = 2,
	DMA2_S2_CH3_SPI1_RX = 3,
	DMA2_S2_CH4_USART1_RX = 4,
	DMA2_S2_CH5_USART6_RX = 5,
	DMA2_S2_CH6_TIM1_CH2 = 6,
	DMA2_S2_CH7 = 7,

/*------DMA2 Stream 3 Request Channels------*/
	DMA2_S3_CH0 = 0,
	DMA2_S3_CH1 = 1,
	DMA2_S3_CH2 = 2,
	DMA2_S3_CH3_SPI1_TX = 3,
	DMA2_S3_CH4_SDIO = 4,
	DMA2_S3_CH5_SPI4_RX = 5,
	DMA2_S3_CH6_TIM1_CH1 = 6,
	DMA2_S3_CH7 = 7,

/*------DMA2 Stream 4 Request Channels------*/
	DMA2_S4_CH0_ADC1 = 0,
	DMA2_S4_CH1 = 1,
	DMA2_S4_CH2 = 2,
	DMA2_S4_CH3 = 3,
	DMA2_S4_CH4 = 4,
	DMA2_S4_CH5_SPI4_TX = 5,
	DMA2_S4_CH6_TIM1_CH4 = 6,
	DMA2_S4_CH6_TIM1_TRIG = 6,
	DMA2_S4_CH6_TIM1_COM = 6,
	DMA2_S4_CH7 = 7,

/*------DMA2 Stream 5 Request Channels------*/
	DMA2_S5_CH0 = 0,
	DMA2_S5_CH1 = 1,
	DMA2_S5_CH2 = 2,
	DMA2_S5_CH3_SPI1_TX = 3,
	DMA2_S5_CH4_USART1_RX = 4,
	DMA2_S5_CH5 = 5,
	DMA2_S5_CH6_TIM1_UP = 6,
	DMA2_S5_CH7 = 7,

/*------DMA2 Stream 6 Request Channels------*/
	DMA2_S6_CH0_TIM1_CH1 = 0,
	DMA2_S6_CH0_TIM1_CH2 = 0,
	DMA2_S6_CH0_TIM1_CH3 = 0,
	DMA2_S6_CH1 = 1,
	DMA2_S6_CH2 = 2,
	DMA2_S6_CH4_SDIO = 4,
	DMA2_S6_CH5_USART6_TX = 5,
	DMA2_S6_CH6_TIM1_CH3 = 6,
	DMA2_S6_CH7 = 7,

/*------DMA2 Stream 7 Request Channels------*/
	DMA2_S7_CH0 = 0,
	DMA2_S7_CH1 = 1,
	DMA2_S7_CH2 = 2,
	DMA2_S7_CH3 = 3,
	DMA2_S7_CH4_USART1_TX = 4,
	DMA2_S7_CH5_USART6_TX = 5,
	DMA2_S7_CH6 = 6,
	DMA2_S7_CH7 = 7

} DMA_STREAM_CHANNEL;


#define IS_DMAn_S0_FIFO_ERR(n)		((n->LISR & DMA_LISR_FEIF0_MASK) == DMA_LISR_FEIF0_MASK)
#define IS_DMAn_S1_FIFO_ERR(n)		((n->LISR & DMA_LISR_FEIF1_MASK) == DMA_LISR_FEIF1_MASK)
#define IS_DMAn_S2_FIFO_ERR(n)		((n->LISR & DMA_LISR_FEIF2_MASK) == DMA_LISR_FEIF2_MASK)
#define IS_DMAn_S3_FIFO_ERR(n)		((n->LISR & DMA_LISR_FEIF3_MASK) == DMA_LISR_FEIF3_MASK)
#define IS_DMAn_S4_FIFO_ERR(n)		((n->HISR & DMA_HISR_FEIF4_MASK) == DMA_HISR_FEIF4_MASK)
#define IS_DMAn_S5_FIFO_ERR(n)		((n->HISR & DMA_HISR_FEIF5_MASK) == DMA_HISR_FEIF5_MASK)
#define IS_DMAn_S6_FIFO_ERR(n)		((n->HISR & DMA_HISR_FEIF6_MASK) == DMA_HISR_FEIF6_MASK)
#define IS_DMAn_S7_FIFO_ERR(n)		((n->HISR & DMA_HISR_FEIF7_MASK) == DMA_HISR_FEIF7_MASK)

#define IS_DMAn_S0_DIR_ERR(n)		((n->LISR & DMA_LISR_DMEIF0_MASK) == DMA_LISR_DMEIF0_MASK)
#define IS_DMAn_S1_DIR_ERR(n)		((n->LISR & DMA_LISR_DMEIF1_MASK) == DMA_LISR_DMEIF1_MASK)
#define IS_DMAn_S2_DIR_ERR(n)		((n->LISR & DMA_LISR_DMEIF2_MASK) == DMA_LISR_DMEIF2_MASK)
#define IS_DMAn_S3_DIR_ERR(n)		((n->LISR & DMA_LISR_DMEIF3_MASK) == DMA_LISR_DMEIF3_MASK)
#define IS_DMAn_S4_DIR_ERR(n)		((n->HISR & DMA_HISR_DMEIF4_MASK) == DMA_HISR_DMEIF4_MASK)
#define IS_DMAn_S5_DIR_ERR(n)		((n->HISR & DMA_HISR_DMEIF5_MASK) == DMA_HISR_DMEIF5_MASK)
#define IS_DMAn_S6_DIR_ERR(n)		((n->HISR & DMA_HISR_DMEIF6_MASK) == DMA_HISR_DMEIF6_MASK)
#define IS_DMAn_S7_DIR_ERR(n)		((n->HISR & DMA_HISR_DMEIF7_MASK) == DMA_HISR_DMEIF7_MASK)

#define IS_DMAn_S0_TRNSF_ERR(n)		((n->LISR & DMA_LISR_TEIF0_MASK) == DMA_LISR_TEIF0_MASK)
#define IS_DMAn_S1_TRNSF_ERR(n)		((n->LISR & DMA_LISR_TEIF1_MASK) == DMA_LISR_TEIF1_MASK)
#define IS_DMAn_S2_TRNSF_ERR(n)		((n->LISR & DMA_LISR_TEIF2_MASK) == DMA_LISR_TEIF2_MASK)
#define IS_DMAn_S3_TRNSF_ERR(n)		((n->LISR & DMA_LISR_TEIF3_MASK) == DMA_LISR_TEIF3_MASK)
#define IS_DMAn_S4_TRNSF_ERR(n)		((n->HISR & DMA_HISR_TEIF4_MASK) == DMA_HISR_TEIF4_MASK)
#define IS_DMAn_S5_TRNSF_ERR(n)		((n->HISR & DMA_HISR_TEIF5_MASK) == DMA_HISR_TEIF5_MASK)
#define IS_DMAn_S6_TRNSF_ERR(n)		((n->HISR & DMA_HISR_TEIF6_MASK) == DMA_HISR_TEIF6_MASK)
#define IS_DMAn_S7_TRNSF_ERR(n)		((n->HISR & DMA_HISR_TEIF7_MASK) == DMA_HISR_TEIF7_MASK)

#define IS_DMAn_S0_TRNSF_HLF(n)		((n->LISR & DMA_LISR_HTIF0_MASK) == DMA_LISR_HTIF0_MASK)
#define IS_DMAn_S1_TRNSF_HLF(n)		((n->LISR & DMA_LISR_HTIF1_MASK) == DMA_LISR_HTIF1_MASK)
#define IS_DMAn_S2_TRNSF_HLF(n)		((n->LISR & DMA_LISR_HTIF2_MASK) == DMA_LISR_HTIF2_MASK)
#define IS_DMAn_S3_TRNSF_HLF(n)		((n->LISR & DMA_LISR_HTIF3_MASK) == DMA_LISR_HTIF3_MASK)
#define IS_DMAn_S4_TRNSF_HLF(n)		((n->HISR & DMA_HISR_HTIF4_MASK) == DMA_HISR_HTIF4_MASK)
#define IS_DMAn_S5_TRNSF_HLF(n)		((n->HISR & DMA_HISR_HTIF5_MASK) == DMA_HISR_HTIF5_MASK)
#define IS_DMAn_S6_TRNSF_HLF(n)		((n->HISR & DMA_HISR_HTIF6_MASK) == DMA_HISR_HTIF6_MASK)
#define IS_DMAn_S7_TRNSF_HLF(n)		((n->HISR & DMA_HISR_HTIF7_MASK) == DMA_HISR_HTIF7_MASK)

#define IS_DMAn_S0_TRNSF_CMPLT(n)		((n->LISR & DMA_LISR_TCIF0_MASK) == DMA_LISR_TCIF0_MASK)
#define IS_DMAn_S1_TRNSF_CMPLT(n)		((n->LISR & DMA_LISR_TCIF1_MASK) == DMA_LISR_TCIF1_MASK)
#define IS_DMAn_S2_TRNSF_CMPLT(n)		((n->LISR & DMA_LISR_TCIF2_MASK) == DMA_LISR_TCIF2_MASK)
#define IS_DMAn_S3_TRNSF_CMPLT(n)		((n->LISR & DMA_LISR_TCIF3_MASK) == DMA_LISR_TCIF3_MASK)
#define IS_DMAn_S4_TRNSF_CMPLT(n)		((n->HISR & DMA_HISR_TCIF4_MASK) == DMA_HISR_TCIF4_MASK)
#define IS_DMAn_S5_TRNSF_CMPLT(n)		((n->HISR & DMA_HISR_TCIF5_MASK) == DMA_HISR_TCIF5_MASK)
#define IS_DMAn_S6_TRNSF_CMPLT(n)		((n->HISR & DMA_HISR_TCIF6_MASK) == DMA_HISR_TCIF6_MASK)
#define IS_DMAn_S7_TRNSF_CMPLT(n)		((n->HISR & DMA_HISR_TCIF7_MASK) == DMA_HISR_TCIF7_MASK)

#define CLEAR_DMAn_S0_FIFO_ERR(n)		(n->LIFCR |= DMA_LIFCR_CFEIF0_MASK)
#define CLEAR_DMAn_S1_FIFO_ERR(n)		(n->LIFCR |= DMA_LIFCR_CFEIF1_MASK)
#define CLEAR_DMAn_S2_FIFO_ERR(n)		(n->LIFCR |= DMA_LIFCR_CFEIF2_MASK)
#define CLEAR_DMAn_S3_FIFO_ERR(n)		(n->LIFCR |= DMA_LIFCR_CFEIF3_MASK)
#define CLEAR_DMAn_S4_FIFO_ERR(n)		(n->HIFCR |= DMA_HIFCR_CFEIF4_MASK)
#define CLEAR_DMAn_S5_FIFO_ERR(n)		(n->HIFCR |= DMA_HIFCR_CFEIF5_MASK)
#define CLEAR_DMAn_S6_FIFO_ERR(n)		(n->HIFCR |= DMA_HIFCR_CFEIF6_MASK)
#define CLEAR_DMAn_S7_FIFO_ERR(n)		(n->HIFCR |= DMA_HIFCR_CFEIF7_MASK)

#define CLEAR_DMAn_S0_DIR_ERR(n)		(n->LIFCR |= DMA_LIFCR_CDMEIF0_MASK)
#define CLEAR_DMAn_S1_DIR_ERR(n)		(n->LIFCR |= DMA_LIFCR_CDMEIF1_MASK)
#define CLEAR_DMAn_S2_DIR_ERR(n)		(n->LIFCR |= DMA_LIFCR_CDMEIF2_MASK)
#define CLEAR_DMAn_S3_DIR_ERR(n)		(n->LIFCR |= DMA_LIFCR_CDMEIF3_MASK)
#define CLEAR_DMAn_S4_DIR_ERR(n)		(n->HIFCR |= DMA_HIFCR_CDMEIF4_MASK)
#define CLEAR_DMAn_S5_DIR_ERR(n)		(n->HIFCR |= DMA_HIFCR_CDMEIF5_MASK)
#define CLEAR_DMAn_S6_DIR_ERR(n)		(n->HIFCR |= DMA_HIFCR_CDMEIF6_MASK)
#define CLEAR_DMAn_S7_DIR_ERR(n)		(n->HIFCR |= DMA_HIFCR_CDMEIF7_MASK)

#define CLEAR_DMAn_S0_TRNSF_ERR(n)		(n->LIFCR |= DMA_LIFCR_CTEIF0_MASK)
#define CLEAR_DMAn_S1_TRNSF_ERR(n)		(n->LIFCR |= DMA_LIFCR_CTEIF1_MASK)
#define CLEAR_DMAn_S2_TRNSF_ERR(n)		(n->LIFCR |= DMA_LIFCR_CTEIF2_MASK)
#define CLEAR_DMAn_S3_TRNSF_ERR(n)		(n->LIFCR |= DMA_LIFCR_CTEIF3_MASK)
#define CLEAR_DMAn_S4_TRNSF_ERR(n)		(n->HIFCR |= DMA_HIFCR_CTEIF4_MASK)
#define CLEAR_DMAn_S5_TRNSF_ERR(n)		(n->HIFCR |= DMA_HIFCR_CTEIF5_MASK)
#define CLEAR_DMAn_S6_TRNSF_ERR(n)		(n->HIFCR |= DMA_HIFCR_CTEIF6_MASK)
#define CLEAR_DMAn_S7_TRNSF_ERR(n)		(n->HIFCR |= DMA_HIFCR_CTEIF7_MASK)

#define CLEAR_DMAn_S0_TRNSF_HLF(n)		(n->LIFCR |= DMA_LIFCR_CHTIF0_MASK)
#define CLEAR_DMAn_S1_TRNSF_HLF(n)		(n->LIFCR |= DMA_LIFCR_CHTIF1_MASK)
#define CLEAR_DMAn_S2_TRNSF_HLF(n)		(n->LIFCR |= DMA_LIFCR_CHTIF2_MASK)
#define CLEAR_DMAn_S3_TRNSF_HLF(n)		(n->LIFCR |= DMA_LIFCR_CHTIF3_MASK)
#define CLEAR_DMAn_S4_TRNSF_HLF(n)		(n->HIFCR |= DMA_HIFCR_CHTIF4_MASK)
#define CLEAR_DMAn_S5_TRNSF_HLF(n)		(n->HIFCR |= DMA_HIFCR_CHTIF5_MASK)
#define CLEAR_DMAn_S6_TRNSF_HLF(n)		(n->HIFCR |= DMA_HIFCR_CHTIF6_MASK)
#define CLEAR_DMAn_S7_TRNSF_HLF(n)		(n->HIFCR |= DMA_HIFCR_CHTIF7_MASK)

#define CLEAR_DMAn_S0_TRNSF_CMPLT(n)		(n->LIFCR |= DMA_LIFCR_CTCIF0_MASK)
#define CLEAR_DMAn_S1_TRNSF_CMPLT(n)		(n->LIFCR |= DMA_LIFCR_CTCIF1_MASK)
#define CLEAR_DMAn_S2_TRNSF_CMPLT(n)		(n->LIFCR |= DMA_LIFCR_CTCIF2_MASK)
#define CLEAR_DMAn_S3_TRNSF_CMPLT(n)		(n->LIFCR |= DMA_LIFCR_CTCIF3_MASK)
#define CLEAR_DMAn_S4_TRNSF_CMPLT(n)		(n->HIFCR |= DMA_HIFCR_CTCIF4_MASK)
#define CLEAR_DMAn_S5_TRNSF_CMPLT(n)		(n->HIFCR |= DMA_HIFCR_CTCIF5_MASK)
#define CLEAR_DMAn_S6_TRNSF_CMPLT(n)		(n->HIFCR |= DMA_HIFCR_CTCIF6_MASK)
#define CLEAR_DMAn_S7_TRNSF_CMPLT(n)		(n->HIFCR |= DMA_HIFCR_CTCIF7_MASK)

#define ENABLE_DMAn_Sx(n, z)			(n->Sx[z].CR |= DMA_Sx_EN_MASK)
#define DISABLE_DMAn_Sx(n, z)			(n->Sx[z].CR &= ~DMA_Sx_EN_MASK)
#define IS_DMAn_Sx_ENABLED(n, z)		((n->Sx[z].CR & DMA_Sx_EN_MASK) == DMA_Sx_EN_MASK)

#define ENABLE_DMAn_Sx_DIR_ERR_INT(n, z)		(n->Sx[z].CR |= DMA_Sx_DMEIE_MASK)
#define DISABLE_DMAn_Sx_DIR_ERR_INT(n, z)		(n->Sx[z].CR &= ~DMA_Sx_DMEIE_MASK)
#define IS_DMAn_Sx_DIR_ERR_INT_ENABLED(n, z)	((n->Sx[z].CR & DMA_Sx_DMEIE_MASK) == DMA_Sx_DMEIE_MASK)

#define ENABLE_DMAn_Sx_TRNSF_ERR_INT(n, z)		(n->Sx[z].CR |= DMA_Sx_TEIE_MASK)
#define DISABLE_DMAn_Sx_TRNSF_ERR_INT(n, z)	(n->Sx[z].CR &= ~DMA_Sx_TEIE_MASK)
#define IS_DMAn_Sx_TRNSF_ERR_INT_ENABLED(n, z)	((n->Sx[z].CR & DMA_Sx_TEIE_MASK) == DMA_Sx_TEIE_MASK)

#define ENABLE_DMAn_Sx_TRNSF_HLF_INT(n, z)		(n->Sx[z].CR |= DMA_Sx_HTIE_MASK)
#define DISABLE_DMAn_Sx_TRNSF_HLF_INT(n, z)	(n->Sx[z].CR &= ~DMA_Sx_HTIE_MASK)
#define IS_DMAn_Sx_TRNSF_HLF_INT_ENABLED(n, z)	((n->Sx[z].CR & DMA_Sx_HTIE_MASK) == DMA_Sx_HTIE_MASK)

#define ENABLE_DMAn_Sx_TRNSF_CMPLT_INT(n, z)	(n->Sx[z].CR |= DMA_Sx_TCIE_MASK)
#define DISABLE_DMAn_Sx_TRNSF_CMPLT_INT(n, z)	(n->Sx[z].CR &= ~DMA_Sx_TCIE_MASK)
#define IS_DMAn_Sx_TRNSF_CMPLT_INT_ENABLED(n, z)	((n->Sx[z].CR & DMA_Sx_TCIE_MASK) == DMA_Sx_TCIE_MASK)

typedef enum {
	DMA_FLCNTRL	= 0UL,
	PERIPH_FLCNTRL	= 1UL
} DMA_FLOW_CONTROLER;

#define SET_DMAn_Sx_FLOW_CNTRL(n, z, y)		(n->Sx[z].CR |= (y%2 << DMA_Sx_PFCTRL_POS))
#define GET_DMAn_Sx_FLOW_CNTRL(n, z)		((n->Sx[z].CR & DMA_Sx_PFCTRL_MASK) >> DMA_Sx_PFCTRL_POS)

typedef enum {
	DMA_PRPH_TO_MEM = 0UL,
	DMA_MEM_TO_PRPH = 1UL,		
	DMA_MEM_TO_MEM = 2UL		
} DMA_DIRx;

#define SET_DMAn_Sx_DIR(n, z, y)			(n->Sx[z].CR |= (y%3 << DMA_Sx_DIR_POS))
#define GET_DMAn_Sx_DIR(n, z)			(n->Sx[z].CR & DMA_Sx_DIR_MASK)

#define ENABLE_DMAn_Sx_CIRC(n, z)			(n->Sx[z].CR |= DMA_Sx_CIRC_MASK)
#define DISABLE_DMAn_Sx_CIRC(n, z)			(n->Sx[z].CR &= ~DMA_Sx_CIRC_MASK)
#define IS_DMAn_Sx_CIRC_ENABLED(n, z)		((n->Sx[z].CR & DMA_Sx_CIRC_MASK) == DMA_Sx_CIRC_MASK)

#define ENABLE_DMAn_Sx_P_INCRMNT(n, z)		(n->Sx[z].CR |= DMA_Sx_PINC_MASK)
#define DISABLE_DMAn_Sx_P_INCRMNT(n, z)		(n->Sx[z].CR &= ~DMA_Sx_PINC_MASK)

#define ENABLE_DMAn_Sx_M_INCRMNT(n, z)		(n->Sx[z].CR |= DMA_Sx_MINC_MASK)
#define DISABLE_DMAn_Sx_M_INCRMNT(n, z)		(n->Sx[z].CR &= ~DMA_Sx_MINC_MASK)

typedef enum {
	DMA_BYTE	= 0UL,
	DMA_HWORD	= 1UL,
	DMA_WORD	= 2UL
} DMA_DATA_SIZE;

#define SET_DMAn_Sx_PSIZE(n, z, y)			(n->Sx[z].CR |= (y%3 << DMA_Sx_PSIZE_POS))
#define GET_DMAn_Sx_PSIZE(n, z)			(n->Sx[z].CR & DMA_Sx_PSIZE_MASK)

#define SET_DMAn_Sx_MSIZE(n, z, y)			(n->Sx[z].CR |= (y%3 << DMA_Sx_PSIZE_POS))
#define GET_DMAn_Sx_MSIZE(n, z)			(n->Sx[z].CR & DMA_Sx_PSIZE_MASK)

#define DMA_INC_PSIZE_OFFSET	(0UL)		
#define DMA_INC_WORD_OFFSET	(1UL)		

#define SET_DMAn_Sx_P_INC_FFSET(n, z, y)		(n->Sx[z].CR |= (y << DMA_Sx_PINCOS_POS))
#define GET_DMAn_Sx_P_INC_OFFSET(n, z)		(n->Sx[z].CR & DMA_Sx_PINCOS_MASK)

typedef enum {
	DMA_LOW_STRM_PRI = 0UL,		
	DMA_MED_STRM_PRI = 1UL,		
	DMA_HGH_STRM_PRI = 2UL,		
	DMA_VHI_STRM_PRI = 3UL		
} DMA_STREAM_PRI;

#define SET_DMAn_Sx_PRI(n, z, y)			(n->Sx[z].CR |= (y << DMA_Sx_PL_POS))
#define GET_DMAn_Sx_PRI(n, z)			(n->Sx[z].CR & DMA_Sx_PL_MASK)

#define ENABLE_DMAn_Sx_DBLBUF(n, z)		(n->Sx[z].CR |= DMA_Sx_DBM_MASK)
#define DISABLE_DMAn_Sx_DBLBUF(n, z)		(n->Sx[z].CR &= ~DMA_Sx_DBM_MASK)

#define DMA_CRNT_TRGT_MEM_0	(0UL)
#define DMA_CRNT_TRGT_MEM_0	(0UL)
#define DMA_CRNT_TRGT_MEM_1	(1UL)
#define DMA_CRNT_TRGT_MEM_1	(1UL)

#define SET_DMAn_Sx_CRNT_TRGT(n, z, y)		(n->Sx[z].CR |= (y%2 << DMA_Sx_CT_POS))
#define GET_DMAn_Sx_CRNT_TRGT(n, z)		(n->Sx[z].CR & DMA_Sx_CT_MASK)

typedef enum {
	DMA_BURST_SINGLE_TRNSF	= 0UL,			
	DMA_BURST_INC_4_TRNSF 	= 1UL,		
	DMA_BURST_INC_8_TRNSF 	= 2UL,		
	DMA_BURST_INC_16_TRNSF	= 3UL		
} DMA_TRANSACTION;

#define SET_DMAn_Sx_P_BURST(n, z, y)		(n->Sx[z].CR |= (y%4 << DMA_Sx_PBURST_POS))
#define GET_DMAn_Sx_P_BURST(n, z)			(n->Sx[z].CR & DMA_Sx_PBURST_MASK)

#define SET_DMAn_Sx_M_BURST(n, z, y)		(n->Sx[z].CR |= (y%4 << DMA_Sx_MBURST_POS))
#define GET_DMAn_Sx_M_BURST(n, z)			(n->Sx[z].CR & DMA_Sx_MBURST_MASK)

#define SET_DMAn_Sx_CHANNEL(n, z, y)		(n->Sx[z].CR |= (y%8 << DMA_Sx_CHSEL_POS))
#define GET_DMAn_Sx_CHANNEL(n, z)			(n->Sx[z].CR & DMA_Sx_CHSEL_MASK)

#define SET_DMAn_Sx_NDT(n, z, y)		(n->Sx[z].NDTR = (y))
#define GET_DMAn_Sx_NDT(n, z)			(n->Sx[z].NDTR & DMA_Sx_NDT_MASK)

#define SET_DMAn_Sx_PERIPHERAL_ADD(n, z, y)	(n->Sx[z].PAR |= (y << DMA_PAR_PAR_POS))

#define GET_DMAn_Sx_PERIPHERAL_ADD(n, z)		(n->Sx[z].PAR & DMA_PAR_PAR_MASK)

#define SET_DMAn_Sx_MMEM0_ADD(n, z, y)		(n->Sx[z].M0AR |= (y << DMA_M0AR_M0A_POS))
#define GET_DMAn_Sx_MEM0_ADD(n, z)			(n->Sx[z].M0AR & DMA_M0AR_M0A_MASK)

#define SET_DMAn_Sx_MMEM1_ADD(n, z, y)		(n->Sx[z].M1AR |= (y << DMA_M1AR_M1A_POS))
#define GET_DMAn_Sx_MEM1_ADD(n, z)			(n->Sx[z].M1AR & DMA_M1AR_M1A_MASK)

typedef enum {
	DMA_FIFO_1QRTR	= 0UL,
	DMA_FIFO_HALF	= 1UL,
	DMA_FIFO_3QRTR	= 2UL,
	DMA_FIFO_FULL	= 3UL		
} DMA_FIFO_THRSHLD;

#define SET_DMAn_Sx_FIFO_THRSHLD(n, z, y) 		(n->Sx[z].FCR |= (y << DMA_FCR_FTH_POS))
#define GET_DMAn_Sx_FIFO_THRSHLD(n, z)    		(n->Sx[z].FCR & (DMA_FCR_FTH_MASK))

#define ENABLE_DMAn_Sx_DIR_MODE(n, z)     		(n->Sx[z].FCR &= ~DMA_FCR_DMDIS_MASK)
#define DISABLE_DMAn_Sx_DIR_MODE(n, z)    		(n->Sx[z].FCR |= DMA_FCR_DMDIS_MASK)
#define ENABLE_DMAn_Sx_FIFO_MODE(n, z)			DISABLE_DMAn_Sx_DIR_MODE(n, z)
#define DISABLE_DMAn_Sx_FIFO_MODE(n, z)			ENABLE_DMAn_Sx_DIR_MODE(n, z)

#define DMA_FIFO_STATUS_ZERO_1QRTR	(0UL)
#define DMA_FIFO_STATUS_QRTR_HALF	(1UL)
#define DMA_FIFO_STATUS_HALF_3QRTR	(2UL)
#define DMA_FIFO_STATUS_3QRTR_FULL	(3UL)
#define DMA_FIFO_STATUS_EMPTY		(4UL)
#define DMA_FIFO_STATUS_FULL		(5UL)

#define GET_DMAn_Sx_FIFO_STATUS(n, z)		(n->Sx[z].FCR & DMA_FCR_FS_MASK)

#define ENABLE_DMAn_Sx_FIFO_ERR_INT(n, z) 		(n->Sx[z].FCR |= DMA_FCR_FS_MASK)
#define DISABLE_DMAn_Sx_FIFO_ERR_INT(n, z)		(n->Sx[z].FCR &= ~DMA_FCR_FS_MASK)


uint32_t Get_DMA_Data_Count(DMA_Type *dma, DMA_STREAMx stream);

void DMA_Mem_To_Mem(DMA_STREAMx stream, 		\
		    uint32_t src, 			\
		    uint32_t dest, 			\
		    uint32_t count, 			\
		    DMA_STREAM_CHANNEL channel, 	\
		    DMA_STREAM_PRI priority, 		\
		    DMA_FIFO_THRSHLD fifo_threshold, 	\
		    DMA_DATA_SIZE data_sz);

void DMA_Transfer(DMA_Type *dma,			\
		  DMA_STREAMx stream, 			\
		  uint32_t src, 			\
		  uint32_t dest, 			\
		  uint32_t count, 			\
		  DMA_STREAM_CHANNEL channel, 		\
		  DMA_STREAM_PRI priority, 		\
		  uint32_t direct_mode, 		\
		  DMA_FIFO_THRSHLD fifo_threshold, 	\
		  DMA_DIRx direction, 			\
		  DMA_FLOW_CONTROLER flow_controller, 	\
		  DMA_DATA_SIZE data_sz, 		\
		  uint32_t pincrement, 			\
		  uint32_t mincrement );

/*++++++++++++++++++++++++++++++++++++++++++++++*/

/*----------------------USART----------------------*/

#define USART_1 1
#define USART_2 2
#define USART_6 6

#define IS_USARTz_PARITY_ERR(z)			((USARTz->SR & USART_SR_PE_MASK) == USART_SR_PE_MASK)
/*
 * It is cleared by a software sequence (a read from the status register followed by a read or write access to the USART_DR data register).
 * The software must wait for the RXNE flag to be set before clearing the PE bit.
*/
#define CLEAR_USARTz_PARITY_ERR(z)		while(!(IS_USARTz_DATA_READ_RDY(z))); (void)(USARTz->SR & USART_SR_PE_MASK); (void)(USARTz->DR & USART_DR_DR_MASK)

#define IS_USARTz_FRAME_ERR(z) 			((USARTz->SR & USART_SR_FE_MASK) == USART_SR_FE_MASK)
/*
 * It is cleared by a software sequence (an read to the USART_SR register followed by a read to the USART_DR register).
 */
#define CLEAR_USARTz_FRAME_ERR(z)	 	(void)(USARTz->SR & USART_SR_FE_MASK); (void)(USARTz->DR & USART_DR_DR_MASK)

#define IS_USARTz_NOISE_DTCTD(z) 		((USARTz->SR & USART_SR_NF_MASK) == USART_SR_NF_MASK)
/*
 * It is cleared by a software sequence (an read to the USART_SR register followed by a read to the USART_DR register).
 */
#define CLEAR_USARTz_NOISE_DTCTD(z) 		(void)(USARTz->SR & USART_SR_NF_MASK); (void)(USARTz->DR & USART_DR_DR_MASK)

#define IS_USARTz_OVRRN_ERR(z) 			((USARTz->SR & USART_SR_ORE_MASK) == USART_SR_ORE_MASK)

/*
 * It is cleared by a software sequence (an read to the USART_SR register followed by a read to the USART_DR register).
 */
#define CLEAR_USARTz_OVRRN_ERR(z) 		(void)(USARTz->SR & USART_SR_ORE_MASK); (void)(USARTz->DR & USART_DR_DR_MASK)

#define IS_USARTz_IDLE_DTCTD(z)			((USARTz->SR & USART_SR_IDLE_MASK) == USART_SR_IDLE_MASK)

 /*
  * It is cleared by a software sequence (an read to the USART_SR register followed by a read to the USART_DR register).
  */
#define CLEAR_USARTz_IDLE_DTCTD(z)		(void)(USARTz->SR & USART_SR_IDLE_MASK); (void)(USARTz->DR & USART_DR_DR_MASK)

#define IS_USARTz_DATA_READ_RDY(z)		((USARTz->SR & USART_SR_RXNE_MASK) == USART_SR_RXNE_MASK)
/*
 * It is cleared by a read to the USART_DR register.
 * The RXNE flag can also be cleared by writing a zero to it. This clearing sequence is recommended only for multibuffer communication.
 */
#define CLEAR_USARTz_RXNE(z)			(void)(USARTz->DR & USART_DR_DR_MASK)
#define CLEAR_USARTz_MULTIBUF_RXNE(z)		(USARTz->SR = ~USART_SR_RXNE_MASK)

#define IS_USARTz_TRNSM_CMPLT(z)		((USARTz->SR & USART_SR_TC_MASK) == USART_SR_TC_MASK)
/*
 * It is cleared by a software sequence (a read from the USART_SR register followed by a write to the USART_DR register).
 * The TC bit can also be cleared by writing a '0' to it. This clearing sequence is recommended only for multibuffer communication.
 */
#define CLEAR_USARTz_TRNSM_CMPLT(z)		(USARTz->DR = USARTz->DR)
#define CLEAR_USARTz_MULTIBUF_TRNSM_CMPLT(z)	(USARTz->SR &= ~USART_SR_TC_MASK)

#define IS_USARTz_DATA_TRNSMT_DATA_EMPTY(z)	((USARTz->SR & USART_SR_TXE_MASK) == USART_SR_TXE_MASK)
/*
 * It is cleared by a write to the USART_DR register.
 */
#define CLEAR_USARTz_TRNSMT_DATA_EMPTY(z)	(USARTz->DR = USARTz->DR)

#define IS_USARTz_LIN_BRK_DTCTD(z)		((USARTz->SR & USART_SR_LBD_MASK) == USART_SR_LBD_MASK)
/*
 * It is cleared by software (by writing it to 0). An interrupt is generated if LBDIE = 1 in the USART_CR2 register.
 */
#define CLEAR_USARTz_LIN_BRK_DTCTD(z)		(USARTz->SR = ~USART_SR_LBD_MASK)

#define IS_USARTz_CTS_CHNGD(z)			((USARTz->SR & USART_SR_CTS_MASK) == USART_SR_CTS_MASK)
/*
 * It is cleared by software (by writing it to 0). An interrupt is generated if CTSIE=1 in the USART_CR3 register.
 */
#define CLEAR_USARTz_CTS_CHNGD(z)		(USARTz->SR = ~(USART_SR_CTS_MASK))


#define GET_USARTz_DATA(z)			(USARTz->DR)
#define CLEAR_USARTz_DATA(z)			(USARTz->DR = 0)

#define SET_USARTz_DIV_FRACTION(z, y)		(USARTz->BRR |= (y << USART_BRR_Div_FRACTION_POS))
#define GET_USARTz_DIV_FRACTION(z)		(USARTz->BRR & USART_BRR_Div_FRACTION_MASK)

#define SET_USARTz_DIV_MANTISSA(z, y)		(USARTz->BRR |= (y << USART_BRR_Div_MANTISSA_POS))
#define GET_USARTz_DIV_MANTISSA(z)		(USARTz->BRR & USART_BRR_Div_MANTISSA_MASK)


#define SET_USARTz_SND_BRK(z)			(USARTz->CR1 |= USART_CR1_SBK_MASK)
#define CLEAR_USARTz_SND_BRK(z)			(USARTz->CR1 &= ~USART_CR1_SBK_MASK)
#define GET_USARTz_SND_BRK(z)			(USARTz->CR1 & USART_CR1_SBK_MASK)

#define SET_USARTz_RCVR_WKP(z)			(USARTz->CR1 |= USART_CR1_RWU_MASK)
#define CLEAR_USARTz_RCVR_WKP(z)		(USARTz->CR1 &= ~USART_CR1_RWU_MASK)
#define GET_USARTz_RCVR_WKP(z)			(USARTz->CR1 & USART_CR1_RWU_MASK)

#define ENABLE_USARTz_RCVR(z)			(USARTz->CR1 |= USART_CR1_RE_MASK)
#define DISABLE_USARTz_RCVR(z)			(USARTz->CR1 &= ~USART_CR1_RE_MASK)

#define ENABLE_USARTz_TRNSMTR(z)		(USARTz->CR1 |= USART_CR1_TE_MASK)
#define DISABLE_USARTz_TRNSMTR(z)		(USARTz->CR1 &= ~USART_CR1_TE_MASK)

#define ENABLE_USARTz_IDLE_INT(z)		(USARTz->CR1 |= USART_CR1_IDLEIE_MASK)
#define DISABLE_USARTz_IDLE_INT(z)		(USARTz->CR1 &= ~USART_CR1_IDLEIE_MASK)

#define ENABLE_USARTz_DATA_READ_RDY_INT(z)	(USARTz->CR1 |= USART_CR1_RXNEIE_MASK)
#define ENABLE_USARTz_RXNE_INT(z)		ENABLE_USARTz_DATA_READ_RDY_INT(z)
#define DISABLE_USARTz_DATA_READ_RDY_INT(z)	(USARTz->CR1 &= ~USART_CR1_RXNEIE_MASK)
#define DISABLE_USARTz_RXNE_INT(z)		DISABLE_USARTz_DATA_READ_RDY_INT(z)

#define ENABLE_USARTz_DATA_TRNSM_CMPLT_INT(z)	(USARTz->CR1 |= USART_CR1_TCIE_MASK)
#define DISABLE_USARTz_DATA_TRNSM_CMPLT_INT(z)	(USARTz->CR1 &= ~USART_CR1_TCIE_MASK)

#define ENABLE_USARTz_TRNSMT_DATA_EMPTY_INT(z)	(USARTz->CR1 |= USART_CR1_TXEIE_MASK)
#define DISABLE_USARTz_TRNSMT_DATA_EMPTY_INT(z)	(USARTz->CR1 &= ~USART_CR1_TXEIE_MASK)

#define ENABLE_USARTz_PARITY_ERR_INT(z)		(USARTz->CR1 |= USART_CR1_PEIE_MASK)
#define DISABLE_USARTz_PARITY_ERR_INT(z)	(USARTz->CR1 &= ~USART_CR1_PEIE_MASK)

#define USART_ODD_PARITY			(1UL)
#define USART_EVEN_PARITY			(0UL)
#define SET_USARTz_PARITY(z, y)			(USARTz->CR1 |= (y << USART_CR1_PS_POS))
#define GET_USARTz_PARITY(z)			(USARTz->CR1 & USART_CR1_PS_MASK)

#define ENABLE_USARTz_PARITY_CNTRL(z)		(USARTz->CR1 |= USART_CR1_PCE_MASK)
#define DISABLE_USARTz_PARITY_CNTRL(z)		(USARTz->CR1 &= ~USART_CR1_PCE_MASK)

#define USART_WKP_IDLE_MTHD			(0UL)
#define USART_WKP_ADDMRK_MTHD			(1UL)
#define SET_USARTz_WKP_METHOD(z, y)		(USARTz->CR1 |= (y << USART_CR1_WAKE_POS))
#define GET_USARTz_WKP_METHOD(z)		(USARTz->CR1 & USART_CR1_WAKE_MASK)

#define USART_WORD_LEN_8			(0UL)
#define USART_WORD_LEN_9			(1UL)
#define SET_USARTz_WORD_LEN(z, y)		(USARTz->CR1 |= (y << USART_CR1_M_POS))
#define GET_USARTz_WORD_LEN(z)			(USARTz->CR1 & USART_CR1_M_MASK)

#define ENABLE_USARTz(z)			(USARTz->CR1 |= USART_CR1_UE_MASK)
#define DISABLE_USARTz(z)			(USARTz->CR1 &= ~USART_CR1_UE_MASK)

#define USART_OVER_SAMPLE_16			(0UL)
#define USART_OVER_SAMPLE_8			(1UL)
#define SET_USARTz_OVER_SMPL_8(z)		(USARTz->CR1 |= USART_CR1_OVER8_MASK)
#define SET_USARTz_OVER_SMPL_16(z)		(USARTz->CR1 &= ~USART_CR1_OVER8_MASK)
#define GET_USARTz_OVER_SMPL(z)			(USARTz->CR1 & USART_CR1_OVER8_MASK)

#define SET_USARTz_NODE_ADD(z, y)		(USARTz->CR2 |= (y << USART_CR2_ADD_POS))
#define GET_USARTz_NODE_ADD(z)			(USARTz->CR2 & (USART_CR2_ADD_MASKQq))

#define SET_USARTz_LIN_BRK_10BIT_LEN(z)		(USARTz->CR2 &= ~USART_CR2_LBDL_MASK)
#define SET_USARTz_LIN_BRK_11BIT_LEN(z)		(USARTz->CR2 |= USART_CR2_LBDL_MASK)

#define ENABLE_USARTz_LIN_BRK_DTCT_INT(z)	(USARTz->CR2 |= USART_CR2_LBDIE_MASK)
#define DISABLE_USARTz_LIN_BRK_DTC_INT(z)	(USARTz->CR2 &= ~USART_CR2_LBDIE_MASK)

#define ENABLE_USARTz_LST_BIT_CLK_PULS(z)	(USARTz->CR2 |= USART_CR2_LBCL_MASK)
#define DISABLE_USARTz_LST_BIT_CLK_PULS(z)	(USARTz->CR2 &= ~USART_CR2_LBCL_MASK)

#define SET_USARTz_FRST_DATA_CPTR_FRST_CLK_TRNST(z)	(USARTz->CR2 &= ~USART_CR2_CPHA_MASK)
#define SET_USARTz_FRST_DATA_CPTR_SCND_CLK_TRNST(z)	(USARTz->CR2 |= USART_CR2_CPHA_MASK)

#define SET_USARTz_CLK_POLARITY_LOW(z)		(USARTz->CR2 &= ~USART_CR2_CPOL_MASK)
#define SET_USARTz_CLK_POLARITY_HIGH(z)		(USARTz->CR2 |= USART_CR2_CPOL_MASK)

#define ENABLE_USARTz_CK_PIN(z)			(USARTz->CR2 |= USART_CR2_CLKEN_MASK)
#define DISABLE_USARTz_CK_PIN(z)		(USARTz->CR2 &= ~USART_CR2_CLKEN_MASK)

#define USART_STOP_BITS_1			(0UL)
#define USART_STOP_BITS_HLF			(1UL)
#define USART_STOP_BITS_2			(2UL)
#define USART_STOP_BITS_1_HLF			(3UL)
#define SET_USARTz_STOP_BITS(z, y)		(USARTz->CR2 |= (y << USART_CR2_STOP_POS))
#define GET_USARTz_STOP_BITS(z)			(USARTz->CR2 & USART_CR2_STOP_MASK)

#define ENABLE_USARTz_LIN_MODE(z)		(USARTz->CR2 |= USART_CR2_LINEN_MASK)
#define DISABLE_USARTz_LIN_MODE(z)		(USARTz->CR2 &= ~USART_CR2_LINEN_MASK)
#define IS_USARTz_LIN_MODE_ENABLED(z)		((USARTz->CR2 & USART_CR2_LINEN_MASK) == USART_CR2_LINEN_MASK)

#define ENABLE_USARTz_ERR_INT(z)		(USARTz->CR3 |= USART_CR3_EIE_MASK)
#define DISABLE_USARTz_ERR_INT(z)		(USARTz->CR3 &= ~USART_CR3_EIE_MASK)
#define IS_USARTz_ERR_INT_ENABLED(z)		((USARTz->CR3 & USART_CR3_EIE_MASK) == USART_CR3_EIE_MASK)

#define ENABLE_USARTz_IRDA_MODE(z)		(USARTz->CR3 |= USART_CR3_IREN_MASK)
#define DISABLE_USARTz_IRDA_MODE(z)		(USARTz->CR3 &= ~USART_CR3_IREN_MASK)
#define IS_USARTz_IRDA_MODE_ENABLED(z)		((USARTz->CR3 & USART_CR3_IREN_MASK) == USART_CR3_IREN_MASK)

#define SET_USARTz_IRDA_NORMAL_PWR(z)		(USARTz->CR3 &= ~USART_CR3_IRLP_MASK)
#define SET_USARTz_IRDA_LOW_PWR(z)		(USARTz->CR3 |= USART_CR3_IRLP_MASK)

#define SET_USARTz_HLF_DPLX(z)			(USARTz->CR3 |= USART_CR3_HDSEL_MASK)
#define CLEAR_USARTz_HLF_DPLX(z)		(USARTz->CR3 &= ~USART_CR3_HDSEL_MASK)

#define ENABLE_USARTz_NACK_TRNSM(z)		(USARTz->CR3 |= USART_CR3_NACK_MASK)
#define DISABLE_USARTz_NACK_TRNASM(z)		(USARTz->CR3 &= ~USART_CR3_NACK_MASK)

#define ENABLE_USARTz_SMRTCRD_MODE(z)		(USARTz->CR3 |= USART_CR3_SCEN_MASK)
#define DISABLE_USARTz_SMRTCRD_MODE(z)		(USARTz->CR3 &= ~USART_CR3_SCEN_MASK)

#define ENABLE_USARTz_DMA_RECPTION(z)		(USARTz->CR3 |= USART_CR3_DMAR_MASK)
#define DISABLE_USARTz_DMA_RECEPTION(z)		(USARTz->CR3 &= ~USART_CR3_DMAR_MASK)

#define ENABLE_USARTz_DMA_TRANSMISSION(z)	(USARTz->CR3 |= USART_CR3_DMAT_MASK)
#define DISABLE_USARTz_DMA_TRANSMISSION(z)	(USARTz->CR3 &= ~USART_CR3_DMAT_MASK)

#define ENABLE_USARTz_RTS_INT(z)		(USARTz->CR3 |= USART_CR3_RTSE_MASK)
#define DISABLE_USARTz_RTS_INT(z)		(USARTz->CR3 &= ~USART_CR3_RTSE_MASK)

#define ENABLE_USARTz_CTS_MODE(z)		(USARTz->CR3 |= USART_CR3_CTSE_MASK)
#define DISABLE_USARTz_CTS_MODE(z)		(USARTz->CR3 &= ~USART_CR3_CTSE_MASK)

#define ENABLE_USARTz_CTS_INT(z)		(USARTz->CR3 |= USART_CR3_CTSIE_MASK)
#define DISABLE_USARTz_CTS_INT(z)		(USARTz->CR3 &= ~USART_CR3_CTSIE_MASK)

#define USART_SMPL_3BIT_MTHD			(0UL)
#define USART_SMPL_1BIT_MTHD			(1UL)
#define SET_USARTz_SMPL_MTHD(z, y)		(USARTz->CR3 |= (y << USART_CR3_ONEBIT_POS))
#define GET_USARTz_SMPL_MTHD(z)			(USARTz->CR3 & USART_CR3_ONEBIT_MASK)

#define USART_PSC_IRDA_NRML_MODE_VAL	(1UL)
#define USART_PSC_IRDA_LOW_MODE_VAL(x)	(((x == 0) ? 0x1UL : (x)) % 0xFFFFUL)
#define USART_PSC_SMRTCRD_MODE_VAL(x)	(((x == 0) ? 0x1UL : (x >> 2)) % 0xFFUL)
#define SET_USARTz_PSC(z, y)	(USARTz->GTPR |= (y << USART_GTPR_PSC_POS))
#define GET_USARTz_PSC(z)	(USARTz->GTPR & USART_GTPR_PSC_MASK)
#define IS_USARTz_PSC(z, y)	((USARTz->GTPR & USART_GTPR_PSC_MASK) == (y << USART_GTPR_PSC_POS))

#define SET_USARTz_GAURD_TIME_VAL(z, y)	(USARTz->GTPR |= (y << USART_GTPR_GT_POS))
#define GET_USART_GAURD_TIME_VAL(z)	(USARTz->GTPR & USART_GTPR_GT_MASK)
#define IS_USARTz_GAURD_TIME_VAL(z, y)	((USARTz->GTPR & USART_GTPR_GT_MASK) == (y << USART_GTPR_GT_POS))

/*++++++++++++++++++++++++++++++++++++++++++++++*/
#endif //RAV_API
