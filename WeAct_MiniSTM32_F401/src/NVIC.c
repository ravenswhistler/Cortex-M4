#include "types.h"
#include "NVIC.h"

#define WORD_OFFSET(isr)	(((uint32_t)isr) >> 5U)
#define BIT_OFFSET(isr)		(((uint32_t)isr) & 0x1FU)
#define BIT_MASK(isr)		(1UL << BIT_OFFSET(isr))
#define IS_BIT_SET(isr)		BIT_MASK(isr)

//Wraaping this insrtuction in a function might be an idea but it will stay so untli it's a problem 
//The "bx lr" unstruction means return from a funciton call
__attribute__((naked)) void Enable_System_Interrutps(void)	{ asm inline("CPSIE f\n\tbx lr\n\t"); }
__attribute__((naked)) void Enable_External_Interrupts(void)	{ asm inline("CPSIE i\n\tbx lr\n\t"); }

__attribute__((naked)) void Disable_System_Interrupts(void)	{ asm inline("CPSID f\n\tbx lr\n\t"); }
__attribute__((naked)) void Disable_External_Interrupts(void)	{ asm inline("CPSID i\n\tbx lr\n\t"); }


//System ISR contro bits reside in the Core SCB a territory that needs more attention along the Road
//TODO: static inline void Enable_System_IRQ(IRQN_Type irq);
//TODO: static inline void Disable_System_IRQ(IRQN_Type irq);

void Set_Priority(IRQN_Type irq, uint32_t p);
void Get_Priority(IRQN_Type irq);


/*
 * If a pending interrupt is enabled, the NVIC activates the interrupt based on its priority.
 * If an interrupt is not enabled, asserting its interrupt signal changes the interrupt state to pending,
   but the NVIC never activates the interrupt, regardless of its priority.
*/
void Enable_IRQ(IRQN_Type irq)
{
	NVIC->ISER[WORD_OFFSET(irq)] |= BIT_MASK(irq);
}

inline uint32_t Is_IRQ_Enabled(IRQN_Type irq)
{
	return ((NVIC->ISER[WORD_OFFSET(irq)] & BIT_MASK(irq)) == IS_BIT_SET(irq)) ? true : (false);
}

inline void Disable_IRQ(IRQN_Type irq)
{
	NVIC->ICER[WORD_OFFSET(irq)] |= BIT_MASK(irq);
}

inline uint32_t Is_IRQ_Disabled(IRQN_Type irq)
{
	return ((NVIC->ICER[WORD_OFFSET(irq)] & BIT_MASK(irq)) == IS_BIT_SET(irq)) ? true : (false);
}


/*
 * Writing 1 to the ISPR bit corresponding to an interrupt that is pending has no effect.
 * Writing 1 to the ISPR bit corresponding to a disabled interrupt sets the state of that interrupt to pending.
*/
inline void Pend_IRQ(IRQN_Type irq)
{
	NVIC->ISPR[WORD_OFFSET(irq)] |= BIT_MASK(irq);
}


inline uint32_t Is_IRQ_Pending(IRQN_Type irq)
{
	return ((NVIC->ISPR[WORD_OFFSET(irq)] & BIT_MASK(irq)) == IS_BIT_SET(irq)) ? true : (false);
}

inline void UnPend_IRQ(IRQN_Type irq)
{
	NVIC->ICPR[WORD_OFFSET(irq)] |= BIT_MASK(irq);
}

#define Clear_Pend_IRQ(irq) UnPend_IRQ(irq)

inline void Trigger_IRQ(IRQN_Type irq)
{
	NVIC->STIR = ((((uint32_t)irq) % 240U) & (0x1FFU));
}

#define Tigger_SGI(irq) Trigger_IRQ(irq)

uint32_t Is_IRQ_Active(IRQN_Type irq)
{
	return ((NVIC->IABR[WORD_OFFSET(irq)] & BIT_MASK(irq)) == IS_BIT_SET(irq)) ? true : (false);
}
