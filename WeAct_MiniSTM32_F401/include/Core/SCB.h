#ifndef SCB_HEADER
#define SCB_HEADER

#include "types.h"

#define 	SCnSCB_BASE	0xE000E004U

typedef struct {
	_I uint32_t ICTR;
	_IO uint32_t ACTLR;		//Auxiliary control register
} SCnSCB;


/*---------ICTR's MASKs----------*/
//The total number of interrupt lines supported by an implementation, defined in groups of 32. That is, the total number of interrupt lines is up to (32*(INTLINESNUM+1)). However, the absolute maximum number of interrupts is 496, corresponding to the INTLINESNUM value 0b1111.
//INTLINESNUM indicates which registers in the NVIC register map are implemented

#define SCnSCB_ICTR_INTLINESNUM_POS	(0U)
#define SCnSCB_ICTR_INTLINESNUM_MASK	(0x7UL << SCnSCB_ICTR_INTLINESNUM_POS)

/*---------ACTLR's MASKs----------*/
//Disables interrupt of multi-cycle instructions. When set to 1, disables interruption of load multiple and store multiple instructions. This increases the interrupt latency of the processor
//because any LDM or STM must complete before the processor can stack the current state and enter the interrupt handler.
//	0: Enable interruption latency of the processor (load/store and multiply/divide operations).
//	1: Disable interruptions latency.
#define ACTLR_DISMCYCINT_POS	(0U)
#define ACTLR_DISMCYCINT_MASK	(1UL << ACTLR_DISMCYCINT_MASK)

//This bit only affects write buffers implemented in the Cortex-M4 processor. Disables write buffer use during default memory map accesses: This causes all BusFaults to
//be precise BusFaults but decreases performance because any store to memory must complete before the processor can execute the next instruction.
//	0: Enable write buffer use
//	1: Disable write buffer use: Stores to memory is completed before next instruction.
#define ACTLR_DISDEFWBUF_POS	(1U)
#define ACTLR_DISDEFWBUF_MASK	(1UL << ACTLR_DISDEFWBUF_MASK)

//Disables folding of IT instructions:
//	0: Enables IT instructions folding.
//	1: Disables IT instructions folding.
//
//In some situations, the processor can start executing the first instruction in an IT block while it is still executing the IT instruction. This behavior is called IT folding, and improves
//performance, However, IT folding can cause jitter in looping. If a task must avoid jitter, set the DISFOLD bit to 1 before executing the task, to disable IT folding.
#define ACTLR_DISFOLD_POS	(2U)
#define ACTLR_DISFOLD_MASK	(1UL << ACTLR_DISFOLD_MASK)

//Disables automatic update of CONTROL.FPCA.
//The value of this bit should be written as zero or preserved (SBZP).
#define ACTLR_DISFPCA_POS	(8U)
#define ACTLR_DISFPCA_MASK	(1UL << ACTLR_DISFPCA_MASK)

//Disables floating point instructions completing out of order with respect to integer instructions.
#define ACTLR_DISOOFP_POS	(9U)
#define ACTLR_DISOOFP_MASK	(1UL << ACTLR_DISOOFP_MASK)


#define 	SCB_BASE	(0xE000ED00U)
#define SCB ((SCB_Type*)SCB_BASE)

typedef struct {

	_I uint32_t CPUID;
	_IO uint32_t ICSR;		//Interrupt control and state register
	_IO uint32_t VTOR;		//Vector table offset register
	_IO uint32_t AIRCR;		//Application interrupt and reset control register
	_IO uint32_t SCR;		//System control register
	_IO uint32_t CCR;		//Configuration and control register
				
					//System handler priority registers
	_IO uint32_t SHPR1;		//PRI_4: Priority of system handler 4, memory management fault
		       			//PRI_5: Priority of system handler 5, bus fault
		       			//PRI_6: Priority of system handler 6, usage fault
		       	
	_IO uint32_t SHPR2;		//PRI_11: Priority of system handler 11, SVCall

	_IO uint32_t SHPR3;		//PRI_14: Priority of system handler 14, PendSV
					//PRI_15: Priority of system handler 15, SysTick exception

	_IO uint32_t SHCSR;		//System handler control and state register
	_IO uint32_t CFSR;		//Configurable fault status register (UFSR+BFSR+MMFSR)
	_IO uint32_t HFSR;		//Hard fault status register
	_IO uint32_t DFSR;		//TODO
	_IO uint32_t MMFAR;		//Memory management fault address register
	_IO uint32_t BFAR;		//Bus fault address register
	_IO uint32_t AFSR;		//Auxiliary fault status register

} SCB_Type;



/*---------CPUID's MASKs----------*/

#define		SCB_CPUID_REVISION_POS 		(0U)
#define		SCB_CPUID_REVISION_MASK		(0xFUL << SCB_CPUID_REVISION_POS)

#define		SCB_CPUID_PARTNO_POS		(4U)
#define		SCB_CPUID_PARTNO_MASK		(0xFFFUL << SCB_CPUID_PARTNO_POS)

#define		SCB_CPUID_IMPLEMENTER_POS	(24U)
#define		SCB_CPUID_IMPLEMENTER_MASK	(0xFFUL << SCB_CPUID_IMPLEMENTER_POS)


/*---------ICSR's MASKs----------*/

//Active vector. Contains the active exception number:
//	0: Thread mode
//	Other values: The exception number of the currently active exception.
//Note: Subtract 16 from this value to obtain CMSIS IRQ number required to index into the Interrupt Clear-Enable, Set-Enable, Clear-Pending, Set-Pending, or Priority Register
#define		SCB_ICSR_VECTACTIVE_POS		(0UL)			
#define		SCB_ICSR_VECTACTIVE_MASK	(0x1FFUL)

//Return to base level. Indicates whether there are preempted active exceptions:
//	0: There are preempted active exceptions to execute
//	1: There are no active exceptions, or the currently-executing exception is the only active exception.
#define		SCB_ICSR_RETOBASE_POS		(11U)
#define		SCB_ICSR_RETOBASE_MASK		(0x1UL << SCB_ICSR_RETOBASE_POS)

//Pending vector. Indicates the exception number of the highest priority pending enabled exception.
//	0: No pending exceptions
//	Other values: The exception number of the highest priority pending enabled exception.
//The value indicated by this field includes the effect of the BASEPRI and FAULTMASK
//registers, but not any effect of the PRIMASK register.
#define		SCB_ICSR_VECTPENDING_POS	(12U)	
#define		SCB_ICSR_VECTPENDING_MASK	(0x7F << SCB_ICSR_VECTPENDING_POS)

//Interrupt pending flag, excluding NMI and Faults.
//	0: Interrupt not pending
//	1: Interrupt pending
#define		SCB_ICSR_ISRPENDING_POS		(22U)
#define		SCB_ICSR_ISRPENDING_MASK	(0x1UL << SCB_ICSR_ISRPENDING_POS)

//SysTick exception clear-pending bit. Write-only. On a read, value is unknown.
//	0: No effect
//	1: Removes the pending state from the SysTick exception.
#define		SCB_ICSR_PENDSTCLR_POS		(25U)
#define		SCB_ICSR_PENDSTCLR_MASK		(0x1U << SCB_ICSR_PENDSTCLR_POS)

//SysTick exception set-pending bit.
//	Write:
//	0: No effect
//	1: Change SysTick exception state to pending
//
//	Read:
//	0: SysTick exception is not pending
//	1: SysTick exception is pending
#define		SCB_ICSR_PENDSTSET_POS		(26U)
#define		SCB_ICSR_PENDSTSET_MASK		(0x1UL) << SCB_ICSR_PENDSTSET_POS

//PendSV clear-pending bit. This bit is write-only. On a read, value is unknown.
//	0: No effect
//	1: Removes the pending state from the PendSV exception.
#define		SCB_ICSR_PENDSVCLR_POS		(27U)
#define		SCB_ICSR_PENDSVCLR_MASK		(0x1UL << SCB_ICSR_PENDSVCLR_POS)

//PendSV set-pending bit.
//	Write:
//	0: No effect
//	1: Change PendSV exception state to pending.
//	
//	Read:
//	0: PendSV exception is not pending
//	1: PendSV exception is pending
//
//Writing 1 to this bit is the only way to set the PendSV exception state to pending.
#define		SCB_ICSR_PENDSVSET_POS		(28U)
#define		SCB_ICSR_PENDSVSET_MASK		(0x1UL << SCB_ICSR_PENDSVSET_POS)

//NMI set-pending bit.
//	Write:
//	0: No effect
//	1: Change NMI exception state to pending.
//
//	Read:
//	0: NMI exception is not pending
//	1: NMI exception is pending
#define		SCB_ICSR_NMIPENDSET_POS		(31U)
#define		SCB_ICSR_NMIPENDSET_MASK	(0x1UL << SCB_ICSR_NMIPENDSET_POS)


/*---------VTOR's MASKs----------*/

//Vector table base offset field.
//It contains bits [29:9] of the offset of the table base from memory address 0x00000000. When setting TBLOFF, you must align the offset to the number of exception entries in the vector
//table. The minimum alignment is 128 words. Table alignment requirements mean that bits[8:0] of the table offset are always zero.
//
//Bit 29 determines whether the vector table is in the code or SRAM memory region.
//	0: Code
//	1: SRAM
//
//Note: Bit 29 is sometimes called the TBLBASE bit.
#define		SCB_VTOR_TABLEOFF_POS		(9U)
#define		SCB_VTOR_TABLEOFF_MASK		(0x1FFFFFUL << SCB_VTOR_TABLEOFF_MASK)

#define		SCB_VTOR_TBLBASE_POS		(29U)
#define		SCB_VTOR_TBLBASEMASK		(0x1UL << SCB_VTOR_TBLBASE_MASK)


/*---------AIRCR's MASKs----------*/

//To write to this register, you must write 0x5FA to the VECTKEY field, otherwise the processor ignores the write.

#define		SCB_AIRCR_VECTRESET_POS		(0U)
#define		SCB_AIRCR_VECTRESET_MASK	(1UL << SCB_AIRCR_VECTRESET_POS)

#define		SCB_AIRCR_VECTCLRACTIVE_POS	(1U)
#define		SCB_AIRCR_VECTCLRACTIVE_MASK	(1UL << SCB_AIRCR_VECTCLRACTIVE_POS)

//System reset request
//This is intended to force a large system reset of all major components except for debug.
//This bit reads as 0.
//	0: No system reset request
//	1: Asserts a signal to the outer system that requests a reset.
#define		SCB_AIRCR_SYSRESETREQ_POS	(2U)
#define		SCB_AIRCR_SYSRESETREQ_MASK	(1UL << SCB_AIRCR_SYSRESETREQ_POS)

//Interrupt priority grouping field This field determines the split of group priority from subpriorit
#define		SCB_AIRCR_PRIGROUP_POS		(8U)
#define		SCB_AIRCR_PRIGROUP_MASK		(7UL << SCB_AIRCR_PRIGROUP_POS)

#define		SCB_AIRCR_ENDIANESS_POS		(15U)
#define		SCB_AIRCR_ENDIANESS_MASK	(1UL << SCB_AIRCR_ENDIANESS_POS)

//Register key
//Reads as 0xFA05
//On writes, write 0x5FA to VECTKEY, otherwise the write is ignored.
#define		SCB_AIRCR_VECTKEY_POS		(16U)
#define		SCB_AIRCR_VECTKEY_MASK		(0xFFFFUL << SCB_AIRCR_VECTKEY_POS)

#define		AIRCR_KEY			(0x5FA)
/*---------SCR's MASKs----------*/
//The SCR controls features of entry to and exit from low power state.

//Configures sleep-on-exit when returning from Handler mode to Thread mode. Setting this bit to 1 enables an interrupt-driven application to avoid returning to an empty main application.
//	0: Do not sleep when returning to Thread mode.
//	1: Enter sleep, or deep sleep, on return from an interrupt service routine.
#define		SCB_SCR_SLEEPONNEXIT_POS	(1U)
#define		SCB_SCR_SLEEPONNEXIT_MASK	(0x1UL << SCB_SCR_SLEEPONNEXIT_POS)

//Controls whether the processor uses sleep or deep sleep as its low power mode:
//	0: Sleep
//	1: Deep sleep.
#define		SCB_SCR_SLEEPDEEP_POS		(2U)
#define		SCB_SCR_SLEEPDEEP_MASK		(0x1UL << SCB_SCR_SLEPDEEP_POS)

//Send Event on Pending bit
//When an event or interrupt enters pending state, the event signal wakes up the processor from WFE. If the processor is not waiting for an event, the event is registered and affects the next WFE.
//The processor also wakes up on execution of an SEV instruction or an external event
//	0: Only enabled interrupts or events can wakeup the processor, disabled interrupts are excluded
//	1: Enabled events and all interrupts, including disabled interrupts, can wakeup the processor.
#define		SCB_SCR_SEVONPEND_POS		(4U)
#define		SCB_SCR_SEVONPEND_MASK		(0x1UL << SCB_SCR_SEVONPEND_POS)

/*---------CCR's MASKs----------*/

//Configures how the processor enters Thread mode.
//	0: Processor can enter Thread mode only when no exception is active.
//	1: Processor can enter Thread mode from any level under the control of an EXC_RETURN value
#define		SCB_CCR_NONBASETHRDENA_POS	(0U)					//Configures how the processor enters Thread mode.
#define		SCB_CCR_NONBASETHRDENA_MASK	(0x1UL << SCB_CCR_NONBASETHRDENA_POS)

//Enables unprivileged software access to the STIR
//	0: Disable
//	1: Enable.
#define		SCB_CCR_USERSETMPEND_POS	(1U)
#define		SCB_CCR_USERSETMPEND_MASK	(0x1UL << SCB_CCR_USERSETMPEND_POS)	

//Enables unaligned access traps:
//	0: Do not trap unaligned halfword and word accesses
//	1: Trap unaligned halfword and word accesses.
//If this bit is set to 1, an unaligned access generates a usage fault.
//Unaligned LDM, STM, LDRD, and STRD instructions always fault irrespective of whether UNALIGN_TRP is set to 1.
#define		SCB_CCR_UNALIGN_TRP_POS		(3U)
#define		SCB_CCR_UNALIGN_TRP_MASK	(0x1UL << SCB_CCR_UNALIGN_TRP_POS)

//Enables faulting or halting when the processor executes an SDIV or UDIV instruction with a divisor of 0:
//	0: Do not trap divide by 0
//	1: Trap divide by 0.
//When this bit is set to 0, a divide by zero returns a quotient of 0.
#define		SCB_CCR_DIV_0_TRP_POS	(4U)
#define		SCB_CCR_DIV_0_TRP_MASK	(0x1UL << SCB_CCR_DIV_0_TRP_POS)

//Enables handlers with priority -1 or -2 to ignore data bus faults caused by load and store instructions. This applies to the hard fault, NMI, and FAULTMASK escalated handlers.
//Set this bit to 1 only when the handler and its data are in absolutely safe memory.
//The normal use of this bit is to probe system devices and bridges to detect control path problems and fix them.
//	0: Data bus faults caused by load and store instructions cause a lock-up
//	1: Handlers running at priority -1 and -2 ignore data bus faults caused by load and store instructions
#define		SCB_CCR_BFHFNMIGN_POS	(8U)
#define		SCB_CCR_BFHFNMIGN_MASK	(0x1UL << SCB_CCR_BFHFNMIGN_POS)

//Configures stack alignment on exception entry. On exception entry, the processor uses bit 9 of the stacked PSR to indicate the stack alignment.
//On return from the exception it uses this stacked bit to restore the correct stack alignment.
//	0: 4-byte aligned
//	1: 8-byte aligned
#define		SCB_CCR_STKALIGN_POS	(9U)
#define		SCB_CCR_STKALIGN_MASK	(0x1UL << SCB_CCR_STKALIGN_POS)


/*---------SHCSR's MASKs----------*/
//The SHCSR enables the system handlers, and indicates:
//	- The pending status of the bus fault, memory management fault, and SVC exceptions
//	- The active status of the system handlers.
//
//If you disable a system handler and the corresponding fault occurs, the processor treats the fault as a hard fault.


	/*---------READ-ONLY ACTIVE BITS----------*/
#define		SCB_SHCSR_MEMFAULTACT_POS	(0U)
#define		SCB_SHCSR_MEMFAULTACT_MASK	(0x1UL << SCB_SHCSR_MEMFAULTACT_POS)

#define		SCB_SHCSR_BUSFAULTACT_POS	(1U)
#define		SCB_SHCSR_BUSFAULTACT_MASK	(0x1UL << SCB_SHCSR_BUSFAULTACT_POS)

#define		SCB_SHCSR_USGFAULTACT_POS	(3U)
#define		SCB_SHCSR_USGFAULTACT_MASK	(0x1UL << SCB_SHCSR_USGFAULTACT_POS)

#define		SCB_SHCSR_SVCALLACT_POS		(7U)
#define		SCB_SHCSR_SVCALLACT_MASK	(0x1UL << SCB_SHCSR_SVCALLACT_POS)

#define		SCB_SHCSR_MONITORACT_POS	(8U)
#define		SCB_SHCSR_MONITORACT_MASK	(0x1UL << SCB_SHCSR_MONITORACT_POS)

#define		SCB_SHCSR_PENDSVACT_POS		(10U)
#define		SCB_SHCSR_PENDSVACT_MASK	(0x1UL << SCB_SHCSR_PENDSVACT_POS)

#define		SCB_SHCSR_SYSTICKACT_POS	(11U)
#define		SCB_SHCSR_SYSTICKACT_MASK	(0x1UL << SCB_SHCSR_SYSTICKACT_POS)


	/*---------READ-WRITE PENDING BITS----------*/
//Pending bits, read as 1 if the exception is pending, or as 0 if it is not pending. You can write to these bits to change the pending status of the exceptions.
//
#define		SCB_SHCSR_USGFAULTPENDED_POS	(12U)
#define		SCB_SHCSR_USGFAULTPENDED_MASK	(0x1UL << SCB_SHCSR_USGFAULTPENDED_POS)

#define		SCB_SHCSR_MEMFAULTPENDED_POS	(13U)
#define		SCB_SHCSR_MEMFAULTPENDED_MASK	(0x1UL << SCB_SHCSR_MEMFAULTPENDED_POS)

#define		SCB_SHCSR_BUSFAULTPENDED_POS	(14U)
#define		SCB_SHCSR_BUSFAULTPENDED_MASK	(0x1UL << SCB_SHCSR_BUSFAULTPENDED_POS)

#define		SCB_SHCSR_SVCALLPENDED_POS	(15U)
#define		SCB_SHCSR_SVCALLPENDED_MASK	(0x1UL << SCB_SHCSR_SVCALLPENDED_POS)


	/*---------READ-WRITE ENABLE BITS----------*/
//Active bits, read as 1 if the exception is active, or as 0 if it is not active. You can write to these bits to change the active status of the exceptions, but see the Caution in this section.

#define		SCB_SHCSR_MEMFAULTENA_POS	(16U)
#define		SCB_SHCSR_MEMFAULTENA_MASK	(0x1UL << SCB_SHCSR_MEMFAULTENA_POS)

#define		SCB_SHCSR_BUSFAULTENA_POS	(17U)
#define		SCB_SHCSR_BUSFAULTENA_MASK	(0x1UL << SCB_SHCSR_BUSFAULTENA_POS)

#define		SCB_SHCSR_USGFAULTENA_POS	(18U)
#define		SCB_SHCSR_USGFAULTENA_MASK	(0x1UL << SCB_SHCSR_USGFAULTENA_POS)


/*---------CFSR's MASKs----------*/
//The CFSR is byte accessible. You can access the CFSR or its subregisters as follows:
//	- Access the complete CFSR with a word access to 0xE000ED28
//	- Access the MMFSR with a byte access to 0xE000ED28
//	- Access the MMFSR and BFSR with a halfword access to 0xE000ED28
//	- Access the BFSR with a byte access to 0xE000ED29
//	- Access the UFSR with a halfword access to 0xE000ED2A.
//The CFSR indicates the cause of a memory management fault, bus fault, or usage fault.


	/*---------MMFSR's MASKs----------*/

//Instruction access violation flag. This fault occurs on any access to an XN region, even the MPU is disabled or not present.
//When this bit is 1, the PC value stacked for the exception return points to the faulting instruction. The processor has not written a fault address to the MMAR.
//	0: No instruction access violation fault
//	1: The processor attempted an instruction fetch from a location that does not permit execution
#define		SCB_CFSR_MMFSR_IACCVIOL_POS	(0U)
#define		SCB_CFSR_MMFSR_IACCVIOL_MASK	(0x1UL << SCB_CFSR_MMFSR_IACCVIOL_POS)

//Data access violation flag. When this bit is 1, the PC value stacked for the exception return points to the faulting instruction. The processor has loaded the MMAR with the address of the attempted access.
//	0: No data access violation fault
//	1: The processor attempted a load or store at a location that does not permit the operation.
#define		SCB_CFSR_MMFSR_DACCVIOL_POS	(1U)
#define		SCB_CFSR_MMFSR_DACCVIOL_MASK	(0x1UL << SCB_CFSR_MMFSR_DACCVIOL_POS)

//Memory manager fault on unstacking for a return from exception. This fault is chained to the handler. This means that when this bit is 1, the original return stack is still present. The processor has not adjusted the SP from the failing return, and has not performed a new save. The processor has not written a fault address to the MMAR.
//	0: No unstacking fault
//	1: Unstack for an exception return has caused one or more access violations.
#define		SCB_CFSR_MMFSR_MUNSTKERR_POS	(3U)
#define		SCB_CFSR_MMFSR_MUNSTKERR_MASK	(0x1UL << SCB_CFSR_MMFSR_MUNSTKERR_POS)

//Memory manager fault on stacking for exception entry. When this bit is 1, the SP is still adjusted but the values in the context area on the stack might be incorrect. The processor has not written a fault address to the MMAR.
//	0: No stacking fault
//	1: Stacking for an exception entry has caused one or more access violations.
#define		SCB_CFSR_MMFSR_MSTKERR_POS	(4U)
#define		SCB_CFSR_MMFSR_MSTKERR_MASK	(0x1UL << SCB_CFSR_MMFSR_MSTKERR_POS)

//	0: No MemManage fault occurred during floating-point lazy state preservation
//	1: A MemManage fault occurred during floating-point lazy state preservation
#define		SCB_CFSR_MMFSR_MLSPERR_POS	(5U)
#define		SCB_CFSR_MMFSR_MLSPERR_MASK	(0x1UL << SCB_CFSR_MMFSR_MLSPERR_POS)

//Memory Management Fault Address Register (MMAR) valid flag. If a memory management fault occurs and is escalated to a hard fault because of priority, the hard fault handler must set this bit to 0. This prevents problems on return to a stacked active memory management fault handler whose MMAR value is overwritten.
//	0: Value in MMAR is not a valid fault address
//	1: MMAR holds a valid fault address.
#define		SCB_CFSR_MMFSR_MMARVALID_POS	(7U)
#define		SCB_CFSR_MMFSR_MMARVALID_MASK	(0x1UL << SCB_CFSR_MMFSR_MMARVALID_POS)


	/*---------BFSR's MASKs----------*/

//Instruction bus error. The processor detects the instruction bus error on prefetching an instruction, but it sets the IBUSERR flag to 1 only if it attempts to issue the faulting instruction.
//When the processor sets this bit is 1, it does not write a fault address to the BFAR.
//	0: No instruction bus error
//	1: Instruction bus error.
#define		SCB_CFSR_BFSR_IBUSERR_POS	(8U)
#define		SCB_CFSR_BFSR_IBUSERR_MASK	(0x1UL << SCB_CFSR_BFSR_IBUSERR_POS)

//Precise data bus error. When the processor sets this bit is 1, it writes the faulting address to the BFAR.
//	0: No precise data bus error
//	1: A data bus error has occurred, and the PC value stacked for the exception return points to the instruction that caused the fault.
#define		SCB_CFSR_BFSR_PRECISERR_POS	(9U)
#define		SCB_CFSR_BFSR_PRECISERR_MASK	(0x1UL << SCB_CFSR_BFSR_PRECISERR_POS)

//Imprecise data bus error. When the processor sets this bit to 1, it does not write a fault address to the BFAR. This is an asynchronous fault. Therefore, if it is detected when the priority of the current process is higher than the bus fault priority, the bus fault becomes pending and becomes active only when the processor returns from all higher priority processes. If a precise fault occurs before the processor enters the handler for the imprecise bus fault, the handler detects both IMPRECISERR set to 1 and one of the precise fault status bits set to 1.
//	0: No imprecise data bus error
//	1: A data bus error has occurred, but the return address in the stack frame is not related to the instruction that caused the error.
#define		SCB_CFSR_BFSR_IMPRECISERR_POS	(10U)
#define		SCB_CFSR_BFSR_IMPRECISERR_MASK	(0x1UL << SCB_CFSR_BFSR_IMPRECISERR_POS)

//Bus fault on unstacking for a return from exception. This fault is chained to the handler. This means that when the processor sets this bit to 1, the original return stack is still present. The processor does not adjust the SP from the failing return, does not performed a new save, and does not write a fault address to the BFAR.
//	0: No unstacking fault
//	1: Unstack for an exception return has caused one or more bus faults.
#define		SCB_CFSR_BFSR_UNSTKERR_POS	(11U)
#define		SCB_CFSR_BFSR_UNSTKERR_MASK	(0x1UL << SCB_CFSR_BFSR_UNSTKERR_POS)

//Bus fault on stacking for exception entry. When the processor sets this bit to 1, the SP is still adjusted but the values in the context area on the stack might be incorrect. The processor does not write a fault address to the BFAR.
//	0: No stacking fault
//	1: Stacking for an exception entry has caused one or more bus faults.
#define		SCB_CFSR_BFSR_STKERR_POS	(12U)
#define		SCB_CFSR_BFSR_STKERR_MASK	(0x1UL << SCB_CFSR_BFSR_STKERR_POS)

//Bus fault on floating-point lazy state preservation.
//	0: No bus fault occurred during floating-point lazy state preservation.
//	1: A bus fault occurred during floating-point lazy state preservation
#define		SCB_CFSR_BFSR_LSPERR_POS	(13U)
#define		SCB_CFSR_BFSR_LSPERR_MASK	(0x1UL << SCB_CFSR_BFSR_LSPERR_POS)

//Bus Fault Address Register (BFAR) valid flag. The processor sets this bit to 1 after a bus fault where the address is known. Other faults can set this bit to 0, such as a memory management fault occurring later.
//If a bus fault occurs and is escalated to a hard fault because of priority, the hard fault handler must set this bit to 0. This prevents problems if returning to a stacked active bus fault handler whose BFAR value is overwritten.
//0: Value in BFAR is not a valid fault address
//1: BFAR holds a valid fault address.
#define		SCB_CFSR_BFSR_BFARVALID_POS	(15U)
#define		SCB_CFSR_BFSR_BFARVALID_MASK	(0x1UL << SCB_CFSR_BFSR_BFARVALID_POS)


	/*---------UFSR's MASKs----------*/

//Undefined instruction usage fault. When this bit is set to 1, the PC value stacked for the exception return points to the undefined instruction.
//An undefined instruction is an instruction that the processor cannot decode.
//	0: No undefined instruction usage fault
//	1: The processor has attempted to execute an undefined instruction.
#define		SCB_CFSR_UFSR_UNDEFINSTR_POS	(16U)
#define		SCB_CFSR_UFSR_UNDEFINSTR_MASK	(0x1UL << SCB_CFSR_UFSR_UNDEFINSTR_POS)

//Invalid state usage fault. When this bit is set to 1, the PC value stacked for the exception return points to the instruction that attempted the illegal use of the EPSR.
//This bit is not set to 1 if an undefined instruction uses the EPSR.
//	0: No invalid state usage fault
//	1: The processor has attempted to execute an instruction that makes illegal use of the EPSR.
#define		SCB_CFSR_UFSR_INVSTATE_POS	(17U)
#define		SCB_CFSR_UFSR_INVSTATE_MASK	(0x1UL << SCB_CFSR_UFSR_INVSTATE_POS)

//Invalid PC load usage fault, caused by an invalid PC load by EXC_RETURN:
//When this bit is set to 1, the PC value stacked for the exception return points to the instruction that tried to perform the illegal load of the PC.
//	0: No invalid PC load usage fault
//	1: The processor has attempted an illegal load of EXC_RETURN to the PC, as a result of an invalid context, or an invalid EXC_RETURN value.
#define		SCB_CFSR_UFSR_INVPC_POS		(18U)
#define		SCB_CFSR_UFSR_INVPC_MASK	(0x1UL << SCB_CFSR_UFSR_INVPC_POS)

//No coprocessor usage fault. The processor does not support coprocessor instructions:
//	0: No usage fault caused by attempting to access a coprocessor
//	1: the processor has attempted to access a coprocessor.
#define		SCB_CFSR_UFSR_NOCP_POS		(19U)
#define		SCB_CFSR_UFSR_NOCP_MASK		(0x1UL << SCB_CFSR_UFSR_NOCP_POS)

//Unaligned access usage fault. Enable trapping of unaligned accesses by setting the UNALIGN_TRP bit in the CCR to 1
//Unaligned LDM, STM, LDRD, and STRD instructions always fault irrespective of the setting of UNALIGN_TRP.
//	0: No unaligned access fault, or unaligned access trapping not enabled
//	1: the processor has made an unaligned memory access.
#define		SCB_CFSR_UFSR_UNALIGNED_POS	(24U)
#define		SCB_CFSR_UFSR_UNALIGNED_MASK	(0x1UL << SCB_CFSR_UFSR_UNALIGNED_POS)

//Divide by zero usage fault. When the processor sets this bit to 1, the PC value stacked for the exception return points to the instruction that performed the divide by zero.
//Enable trapping of divide by zero by setting the DIV_0_TRP bit in the CCR to 1
//	0: No divide by zero fault, or divide by zero trapping not enabled
//	1: The processor has executed an SDIV or UDIV instruction with a divisor of 0.
#define		SCB_CFSR_UFSR_DIVBYZERO_POS	(25U)
#define		SCB_CFSR_UFSR_DIVBYZERO_MASK	(0x1UL << SCB_CFSR_UFSR_DIVBYZERO_POS)


/*---------HFSR's MASKs----------*/

//The HFSR gives information about events that activate the hard fault handler. This register is read, write to clear. This means that bits in the register read normally, but writing 1 to any bit clears that bit to 0.

//Vector table hard fault. Indicates a bus fault on a vector table read during exception processing. This error is always handled by the hard fault handler.
//When this bit is set to 1, the PC value stacked for the exception return points to the instruction that was preempted by the exception.
//
//	0: No bus fault on vector table read
//	1: Bus fault on vector table read.
#define		SCB_HFSR_VECTTBL_POS	(1U)
#define		SCB_HFSR_VECTTBL_MASK	(0x1UL << SCB_HFSR_VECTTBL_POS)

//Forced hard fault. Indicates a forced hard fault, generated by escalation of a fault with configurable priority that cannot be handles, either because of priority or because it is disabled.
//When this bit is set to 1, the hard fault handler must read the other fault status registers to find the cause of the fault.
//	0: No forced hard fault
//	1: Forced hard fault.
#define		SCB_HFSR_FORCED_POS	(30U)
#define		SCB_HFSR_FORCED_MASK	(0x1UL << SCB_HFSR_FORCED_POS)

//Reserved for Debug use. When writing to the register you must write 0 to this bit, otherwise behavior is unpredictable.
#define		SCB_HFSR_DEBUG_VT_POS	(31U)
#define		SCB_HFSR_DEBUG_VT_MASK	(0x1UL << SCB_HFSR_DEBUG_VT_POS)


/*---------MMFAR's MASKs----------*/

//Memory management fault address When the MMARVALID bit of the MMFSR is set to 1, this field holds the address of the location that generated the memory management fault.
//When an unaligned access faults, the address is the actual address that faulted. Because a single read or write instruction can be split into multiple aligned accesses, the fault address can be any address in the range of the requested access size.
//Flags in the MMFSR register indicate the cause of the fault, and whether the value in the MMFAR is valid.
#define		SCB_MMFAR_POS		(0U)
#define		SCB_MMAR_MASK		(0xFFFFFFFFUL << SCB_MMAR_POS)


/*---------BFAR's MASKs----------*/

//Bus fault address When the BFARVALID bit of the BFSR is set to 1, this field holds the address of the location that generated the bus fault.
//When an unaligned access faults the address in the BFAR is the one requested by the instruction, even if it is not the address of the fault.
#define		SCB_BFAR_POS		(0U)
#define		SCB_BFAR_MASK		(0xFFFFFFFFUL << SCB_BFAR_POS)

/*---------ASFAR's MASKs----------*/

//Implementation defined. The AFSR contains additional system fault information. The bits map to the AUXFAULT input signals.
//This register is read, write to clear. This means that bits in the register read normally, but writing 1 to any bit clears that bit to 0.
//Each AFSR bit maps directly to an AUXFAULT input of the processor, and a single-cycle HIGH signal on the input sets the corresponding AFSR bit to one. It remains set to 1 until you write 1 to the bit to clear it to zero.
//When an AFSR bit is latched as one, an exception does not occur. Use an interrupt if an exception is required.
#define		SCB_ASFAR_IMPDEF_POS		(0U)
#define		SCB_ASFAR_IMPDEF_MASK		(0xFFFFFFFFUL << SCB_ASFAR_IMPDEF_POS)


/*---------CPACR's MASKs----------*/
//The CPACR register specifies the access privileges for coprocessors.
//[2n+1:2n] for n values 10 and 11. Access privileges for coprocessor n. The possible values of each field are:
//	0b00: Access denied. Any attempted access generates a NOCP UsageFault.
//	0b01: Privileged access only. An unprivileged access generates a NOCP fault.
//	0b10: Reserved. The result of any access is Unpredictable.
//	0b11: Full access.
#define		SCB_CPACR_CPn_POS		(20U)
#define		SCB_CPACR_CPn_MASK		(0xFUL << SCB_CPACR_CPn_POS)
#endif
