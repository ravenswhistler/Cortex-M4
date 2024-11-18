#include "FLASH.h"

void FLASH_Init(void)
{
	FLASH->ACR |= (2UL << FLASH_ACR_LATENCY_POS);

	FLASH->ACR |= (FLASH_ACR_PRFTEN_MASK | FLASH_ACR_ICEN_MASK | FLASH_ACR_DCEN_MASK);

	while(((uint32_t)(FLASH->ACR & FLASH_ACR_LATENCY_MASK)) != ((uint32_t)2UL));

	return;
}
