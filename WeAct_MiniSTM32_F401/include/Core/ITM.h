#ifndef ITM_HEADER
#define ITM_HEADER

#include "types.h"

#define	ITM_BASE	(0xE0000000UL)
#define DBG_BASE	(0xE000EDF0UL)

typedef struct {

	_IO uint32_t DHCSR;	//Debug Halting Control and Status Register
	_IO uint32_t DCRSR;	//Debug Core Register Selector Register
	_IO uint32_t DCRDR;	//Debug Core Register Data Register
	_IO uint32_t DEMCR;	//Debug Exception and Monitor Control Register

} DBG_Type;

#define DBG	((DBG_Type*)DBG_BASE)

#define ENABLE_DBG_DWT()	(DBG->DEMCR |= 1U << 24U)
#define ENABLE_DBG_ITM()	(DBG->DEMCR |= 1U << 24U)


typedef struct {

	_IO uint32_t STIM[32];		//Stimulus Port Registers 0-31
		_I uint32_t __UNUSED_0[864];
	_IO uint32_t TER;		//Trace Enable Register
		_I uint32_t __UNUSED_1[15];
	_IO uint32_t TPR;		//Trace Privilege Register
		_I uint32_t __UNUSED_2[15];
	_IO uint32_t TCR;		//Trace Control Register


} ITM_Type;

#define ITM	((ITM_Type*)ITM_BASE)

#define ITM_LOCK	((uint32_t*)0xE0000FB0UL)
#define ITM_KEY		(0xC5ACCE55UL)
#define UNLOCK_ITM()	(*ITM_LOCK) = ITM_KEY

#define ENABLE_ITM()	(ITM->TCR |= 1UL)

#define ENABLE_ITM_UNPRIV_STIM0_7_PORTS()	(ITM->TPR |= 1UL )
#define ENABLE_ITM_UNPRIV_STIM8_15_PORTS()	(ITM->TPR |= 1UL << 1U )
#define ENABLE_ITM_UNPRIV_STIM16_23_PORTS()	(ITM->TPR |= 1UL << 2U )
#define ENABLE_ITM_UNPRIV_STIM31_24_PORTS()	(ITM->TPR |= 1UL << 3U )

#define ENABLE_ITM_STIMx_PORT(x)	(ITM->TER |= 1UL << x )
#define DIABLE_ITM_STIMx_PORT(x)	(ITM->TER &= ~(0UL << x) )

#define WRITE_ITM_STIMx_PORT(x, y)	(ITM->STIM[x%32] = ((uint32_t)y))


#endif //ITM_HEADER
