#include "../DEFINES.h"

#define 	FPU_BASE	(0xE000EF30UL)
#define 	FPU		((FPU_Type*)FPU_BASE)

typedef struct {

		UWORD __UNUSED_0;
	_IO UWORD FPCCR;	//Floating-point context control register
	_IO UWORD FPCAR;	//Floating-point context address register
	_IO UWORD FPDSCR;	//Floating-point default status control register
	_I UWORD MVFR0;		//Media and FP Feature Register 0
	_I UWORD MVFR1;		//Media and FP Feature Register 1
	_I UWORD MVFR2;		//Media and FP Feature Register 2
} FPU_Type;


/*---------FPCCR's MASKs----------*/
//The FPCCR register sets or returns FPU control data.

//	0: Lazy state preservation is not active.
//	1: Lazy state preservation is active. floating-point stack frame is allocated but saving state to it is deferred.
#define FPU_FPCCR_LSPACT_POS	(0U)
#define FPU_FPCCR_LSPACT_MASK	(1UL << FPU_FPCCR_LSPACT_MASK)

//	0: Privilege level was not user when the floating-point stack frame was allocated.
//	1: Privilege level was user when the floating-point stack frame was allocated. Bit 1 LSPACT:
#define FPU_FPCCR_USER_POS	(1U)
#define FPU_FPCCR_USER_MASK	(1UL << FPU_FPCCR_USER_MASK)

//	0: Mode was not Thread Mode when the floating-point stack frame was allocated.
//	1: Mode was Thread Mode when the floating-point stack frame was allocated.
#define FPU_FPCCR_THREAD_POS	(3U)
#define FPU_FPCCR_THREAD_MASK	(1UL << FPU_FPCCR_THREAD_MASK)

//	0: Priority did not permit setting the HardFault handler to the pending state when the floating- point stack frame was allocated.
//	1: Priority permitted setting the HardFault handler to the pending state when the floating-point stack frame was allocated.
#define FPU_FPCCR_HFRDY_POS	(4U)
#define FPU_FPCCR_HFRDY_MASK	(1UL << FPU_FPCCR_HFRDY_MASK)

//	0: MemManage is disabled or priority did not permit setting the MemManage handler to the pending state when the floating-point stack frame was allocated.
//	1: MemManage is enabled and priority permitted setting the MemManage handler to the pending state when the floating-point stack frame was allocated.
#define FPU_FPCCR_MMRDY_POS	(5U)
#define FPU_FPCCR_MMRDY_MASK	(1UL << FPU_FPCCR_MMRDY_MASK)

//	0: BusFault is disabled or priority did not permit setting the BusFault handler to the pending state when the floating-point stack frame was allocated.
//	1: BusFault is enabled and priority permitted setting the BusFault handler to the pending state when the floating-point stack frame was allocated.
#define FPU_FPCCR_BFRDY_POS	(6U)
#define FPU_FPCCR_BFRDY_MASK	(1UL << FPU_FPCCR_BFRDY_MASK)

//	0: DebugMonitor is disabled or priority did not permit setting MON_PEND when the floating- point stack frame was allocated.
//	1: DebugMonitor is enabled and priority permits setting MON_PEND when the floating-point stack frame was allocated.
#define FPU_FPCCR_MONRDY_POS	(8U)
#define FPU_FPCCR_MONRDY_MASK	(1UL << FPU_FPCCR_MONRDY_MASK)

//	0: Disable automatic lazy state preservation for floating-point context.
//	1: Enable automatic lazy state preservation for floating-point context.
#define FPU_FPCCR_LSPEN_POS	(30U)
#define FPU_FPCCR_LSPEN_MASK	(1UL << FPU_FPCCR_LSPEN_MASK)

//Enables CONTROL<2> setting on execution of a floating-point instruction. This results in automatic hardware state preservation and restoration, for floating-point context, on exception entry and exit.
//	0: Disable CONTROL<2> setting on execution of a floating-point instruction.
//	1: Enable CONTROL<2> setting on execution of a floating-point instruction.
#define FPU_FPCCR_ASPEN_POS	(31U)
#define FPU_FPCCR_ASPEN_MASK	(1UL << FPU_FPCCR_ASPEN_MASK)


/*---------FPCAR's MASKs----------*/
//The FPCAR register holds the location of the unpopulated floating-point register space allocated on an exception stack frame.

#define FPU_FPPCAR_ADDRESS_POS		(0U)
#define FPU_FPPCAR_ADDRESS_MASK		(1UL << FPU_FPPCAR_ADDRESS_MASK)

/*---------FPDSCR's MASKs----------*/
//The FPDSCR register holds the default values for the floating-point status control data.

#define FPU_FPDSCR_RMode_POS		(22U)
#define FPU_FPDSCR_RMode_MASK		(0x3UL << FPU_FPDSCR_RMode_MASK)

#define FPU_FPDSCR_FZ_POS		(24U)
#define FPU_FPDSCR_FZ_MASK		(1UL << FPU_FPDSCR_FZ_MASK)

#define FPU_FPDSCR_DN_POS		(25U)
#define FPU_FPDSCR_DN_MASK		(1UL << FPU_FPDSCR_DN_MASK)

#define FPU_FPDSCR_AHP_POS		(26U)
#define FPU_FPDSCR_AHP_MASK		(1UL << FPU_FPDSCR_AHP_MASK)

