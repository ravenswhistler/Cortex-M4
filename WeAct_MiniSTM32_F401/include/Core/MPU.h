#ifndef MPU_HEADER
#define MPU_HEADER

#include "types.h"

#define MPU_BASE (0xE000ED90)
#define MPU	((MPU_Type*)MPU_BASE)

typedef struct {

	uint32_t TYPER;		//MPU type register: indicates whether the MPU is present, and if so, how many regions it supports.
	uint32_t CTRL;		//MPU Control register: Enables the MPU, Enables the default memory map background region, Enables use of the MPU when in the hard fault, Non-maskable Interrupt (NMI), and FAULTMASK escalated handlers
	uint32_t RNR;		//MPU region number register: The MPU_RNR register selects which memory region is referenced by the MPU_RBAR and MPU_RASR registers.
	uint32_t RBAR;		//MPU region base address register: The MPU_RBAR register defines the base address of the MPU region selected by the MPU_RNR register, and can update the value of the MPU_RNR register.
	uint32_t RASR;		//MPU region attribute and size register: defines the region size and memory attributes of the MPU region specified by the MPU_RNR, and enables that region and any subregions.
	uint32_t RBAR_A1;
	uint32_t RASR_A1;
	uint32_t RBAR_A2;
	uint32_t RASR_A2;
	uint32_t RBAR_A3;
	uint32_t RASR_A3;
} MPU_Type;

/*---------TYPER's MASKs----------*/
//Separate flag. This bit indicates support for unified or separate instruction and data memory maps:
//	0 = Unified
//	1 = Separate
#define		MPU_TYPER_SEPARATE_POS	(0U)
#define		MPU_TYPER_SEPARATE_MASK	(1UL << MPU_TYPER_SEPARATE_POS)

//Number of MPU data regions. These bits indicates the number of supported MPU data regions.
//	0x08: Eight MPU regions
//	0x00: MPU not present
#define		MPU_TYPER_DREGION_POS	(8U)
#define		MPU_TYPER_DREGION_MASK	(0xFFUL << MPU_TYPER_DREGION_POS)

//Number of MPU instruction regions. These bits indicates the number of supported MPU instruction regions. Always contains 0x00.
//The MPU memory map is unified and is described by the DREGION field.
#define		MPU_TYPER_IREGION_POS	(16U)
#define		MPU_TYPER_IREGION_MASK	(0xFFUL << MPU_TYPER_IREGION_POS)

/*---------CTRL's MASKs----------*/
//When ENABLE and PRIVDEFENA are both set to 1:
//	- For privileged accesses, the default memory map is as described in Section 2.2: Memory model on page 28. Any access by privileged software that does not address an enabled memory region behaves as defined by the default memory map.
//	- Any access by unprivileged software that does not address an enabled memory region causes a memory management fault.

//XN and Strongly-ordered rules always apply to the System Control Space regardless of the value of the ENABLE bit.

//When the ENABLE bit is set to 1, at least one region of the memory map must be enabled for the system to function unless the PRIVDEFENA bit is set to 1. If the PRIVDEFENA bit is set to 1 and no regions are enabled, then only privileged software can operate.

//When the ENABLE bit is set to 0, the system uses the default memory map. This has the same memory attributes as if the MPU is not implemented, see Table 13: Memory access behavior on page 30. The default memory map applies to accesses from both privileged and unprivileged software.

//When the MPU is enabled, accesses to the System Control Space and vector table are always permitted. Other areas are accessible based on regions and whether PRIVDEFENA is set to 1.

//Unless HFNMIENA is set to 1, the MPU is not enabled when the processor is executing the handler for an exception with priority –1 or –2. These priorities are only possible when handling a hard fault or NMI exception, or when FAULTMASK is enabled. Setting the HFNMIENA bit to 1 enables the MPU when operating with these two priorities.


//Enables the MPU
//	0: MPU disabled
//	1: MPU enabled
#define		MPU_CTRL_ENABLE_POS	(0U)
#define		MPU_CTRL_ENABLE_MASK	(1UL << MPU_CTRL_ENABLE_POS)

//Enables the operation of MPU during hard fault, NMI, and FAULTMASK handlers. When the MPU is enabled:
//	0: MPU is disabled during hard fault, NMI, and FAULTMASK handlers, regardless of the value of the ENABLE bit
//	1: The MPU is enabled during hard fault, NMI, and FAULTMASK handlers.
//Note: When the MPU is disabled, if this bit is set to 1 the behavior is unpredictable.
#define		MPU_CTRL_HFNMIENA_POS	(1U)
#define		MPU_CTRL_HFNMIENA_MASK	(1UL << MPU_CTRL_HFNMIENA_POS)

//Enable priviliged software access to default memory map.
//  0: If the MPU is enabled, disables use of the default memory map. Any memory access to a location not covered by any enabled region causes a fault.
//  1: If the MPU is enabled, enables use of the default memory map as a background region for privileged software accesses.
//Note: When enabled, the background region acts as if it is region number -1. Any region that is defined and enabled has priority over this default map. If the MPU is disabled, the processor ignores this bit.
#define		MPU_CTRL_PRIVDEFENA_POS		(2U)
#define		MPU_CTRL_PRIVDEFENA_MASK	(1UL << MPU_CTRL_PRIVDEFENA_POS)

/*---------RNR's MASKs----------*/
//These bits indicate the MPU region referenced by the MPU_RBAR and MPU_RASR registers. The MPU supports 8 memory regions, so the permitted values of this field are 0-7.
//Normally, you write the required region number to this register before accessing the MPU_RBAR or MPU_RASR. However you can change the region number by writing to the MPU_RBAR register with the VALID bit set to 1. This write updates the value of the REGION field.
#define		MPU_RNR_REGION_POS	(0U)
#define		MPU_RNR_REGION_MASK	(0xFFUL << MPU_RNR_REGION_POS)

/*---------BRAR's MASKs----------*/
//MPU region field. For the behavior on writes, see the description of the VALID field. On reads, returns the current region number, as specified by the MPU_RNR register.
#define		MPU_RBAR_REGION_POS	(0U)
#define		MPU_RBAR_REGION_MASK	(0xFUL << MPU_RBAR_REGION_POS)
//
//MPU region number valid
//	Write:
//  		0: MPU_RNR register not changed, and the processor:
//       			- Updates the base address for the region specified in the MPU_RNR
//       			- Ignores the value of the REGION field
//  		1: the processor:
//       			- updates the value of the MPU_RNR to the value of the REGION field
//       			- updates the base address for the region specified in the REGION field.
//
//	Read:
//		Always read as zero.
#define		MPU_RBAR_VALID_POS	(4U)
#define		MPU_RBAR_VALID_MASK	(1UL << MPU_RBAR_VALID_POS)

//Region base address field
//The value of N depends on the region size.
//The region size, as specified by the SIZE field in the MPU_RASR, defines the value of N:
//	N = Log2(Region size in bytes),
//
//If the region size is configured to 4 GB, in the MPU_RASR register, there is no valid ADDR field. In this case, the region occupies the complete memory map, and the base address is 0x00000000.
//The base address is aligned to the size of the region. For example, a 64 KB region must be aligned on a multiple of 64 KB, for example, at 0x00010000 or 0x00020000.
//TODO
#define		MPU_RBAR_ADDR_POS
#define		MPU_RBAR_ADDR_MASK

/*---------RASR's MASKs----------*/
//MPU_RASR is accessible using word or halfword accesses:
//	- The most significant halfword holds the region attributes
//	- The least significant halfword holds the region size and the region and subregion enable bits.
#define		MPU_RASR_ENABLE_POS	(0U)
#define		MPU_RASR_ENABLE_MASK	(1UL << MPU_RASR_ENABLE_POS)

//Size of the MPU protection region.
//The minimum permitted value is 3 (b00010).
#define		MPU_RASR_SIZE_POS	(1U)
#define		MPU_RASR_SIZE_MASK	(0x1FUL << MPU_RASR_SIZE_POS)

//Subregion disable bits.
//For each bit in this field:
//	0: corresponding sub-region is enabled
//	1: corresponding sub-region is disabled
//Region sizes of 128 bytes and less do not support subregions. When writing the attributes for such a region, write the SRD field as 0x00.
#define		MPU_RASR_SRD_POS	(6U)
#define		MPU_RASR_SRD_MASK	(0x3UL << MPU_RASR_SRD_POS)

//memory attribute
#define		MPU_RASR_B_POS		(16U)
#define		MPU_RASR_B_MASK		(1UL << MPU_RASR_B_POS)

//memory attribute
#define		MPU_RASR_C_POS		(17U)
#define		MPU_RASR_C_MASK		(1UL << MPU_RASR_S_POS)

//Shareable memory attribute
#define		MPU_RASR_S_POS		(18U)
#define		MPU_RASR_S_MASK		(1UL << MPU_RASR_S_POS)

//TEX: memory attribute
#define		MPU_RASR_TEX_POS	(19U)
#define		MPU_RASR_TEX_MASK	(0x7UL << MPU_RASR_TEX_POS)

//Access permission
#define		MPU_RASR_AP_POS		(24U)
#define		MPU_RASR_AP_MASK	(0x7UL << MPU_RASR_AP_POS)

//XN: Instruction access disable bit:
//	0: Instruction fetches enabled
//	1: Instruction fetches disabled.
#define		MPU_RASR_XN_POS		(28U)
#define		MPU_RASR_XN_MASK	(1UL << MPU_RASR_XN_POS)

#endif //MPU_HEADER
