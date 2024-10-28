#ifndef FLASH_HEADER
#define FLASH_HEADER

#include "types.h"

typedef struct {

	_IO uint32_t ACR;
	_IO uint32_t KEYR;
	_IO uint32_t OTPKEYR;
	_IO uint32_t SR;
	_IO uint32_t CR;
	_IO uint32_t OPTCR;

} FLASH_Type;

#define FLASH_BASE	(0x40023C00U)

#define FLASH		((FLASH_Type*)FLASH_BASE)

/*------------Access Control Register------------*/
//The Flash access control register is used to enable/disable the acceleration features and control the Flash memory access time according to CPU frequency.
//
//LATENCY: Latency
//	These bits represent the ratio of the CPU clock period to the Flash memory access time.
//	
//	0000: Zero wait state
//	0001: One wait state
//	0010: Two wait states
//	-
//	-
//	-
//	1110: Fourteen wait states
//	1111: Fifteen wait states
//
#define FLASH_ACR_LATENCY_POS	(0U)
#define FLASH_ACR_LATENCY_MASK	(0xFUL << FLASH_ACR_LATENCY_POS)

//PRFTEN: Prefetch enable
//	0: Prefetch is disabled
//	1: Prefetch is enabled
#define FLASH_ACR_PRFTEN_POS	(8U)
#define FLASH_ACR_PRFTEN_MASK	(1UL << FLASH_ACR_PRFTEN_POS)

//ICEN: Instruction cache enable
//	0: Instruction cache is disabled
//	1: Instruction cache is enabled
#define FLASH_ACR_ICEN_POS	(9U)
#define FLASH_ACR_ICEN_MASK	(1UL << FLASH_ACR_ICEN_POS)

//DCEN: Data cache enable
//	0: Data cache is disabled
//	1: Data cache is enabled
#define FLASH_ACR_DCEN_POS	(10U)
#define FLASH_ACR_DCEN_MASK	(1UL << FLASH_ACR_DCEN_POS)

//ICRST: Instruction cache reset
//	0: Instruction cache is not reset
//	1: Instruction cache is reset
//
//This bit can be written only when the I cache is disabled.
#define FLASH_ACR_ICRST_POS	(11U)
#define FLASH_ACR_ICRST_MASK	(1UL << FLASH_ACR_ICRST_POS)

//DCRST: Data cache reset
//	0: Data cache is not reset
//	1: Data cache is reset
//
//This bit can be written only when the D cache is disabled.
#define FLASH_ACR_DCRST_POS	(12U)
#define FLASH_ACR_DCRST_MASK	(1UL << FLASH_ACR_DCRST_POS)

/*-----------------------------------------------*/

#endif
