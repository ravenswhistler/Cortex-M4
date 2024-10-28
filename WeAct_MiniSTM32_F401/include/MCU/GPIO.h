#include "types.h"

#define 	GPIO_A_BASE	(0x40020000UL)
#define 	GPIO_B_BASE	(0x40020400UL)
#define 	GPIO_C_BASE	(0x40020800UL)

#define		GPIOA	((GPIO_Type*)GPIO_A_BASE)
#define		GPIOB	((GPIO_Type*)GPIO_B_BASE)
#define		GPIOC	((GPIO_Type*)GPIO_C_BASE)

typedef struct {
	_IO uint32_t MODER;		//Port mode register
    	_IO uint16_t OTYPER;		//Port output type register
 		
		uint16_t __UNUSED_0;
    	
	_IO uint32_t OSPEEDR;		//Port output speed register
 	_IO uint32_t PUPDR;		//Port pull-up/pull-down register
 	_I  uint16_t IDR;		//Port input data register
         	
		uint16_t __UNUSED_1;

    	_IO uint16_t ODR;		//Port output data register

		uint16_t __UNUSED_2;

    	_I uint16_t BSR;		//Port bit set register
    	_I uint16_t BRR;		//Port bit reset register

 	_IO uint32_t LCKR;		//Port configuration lock register

    	_IO uint32_t AFRL;		//Alternate function low register
    	_IO uint32_t AFRH;		//Alternate function high register

} GPIO_Type;

//These bits are written by software to configure the I/O direction mode.
//	00: Input (reset state)
//	01: General purpose output mode
//	10: Alternate function mode
//	11: Analog mode
#define GPIO_MODER_POS(x)	(2UL*(x%16UL))
#define GPIO_MODER_MASK(x)	(3UL << GPIO_MODER_POS(x))

//These bits are written by software to configure the output type of the I/O port.
//	0: Output push-pull (reset state)
//	1: Output open-drain
#define GPIO_OTYPER_POS(x)	(1UL*(x%16UL))
#define GPIO_OTYPER_MASK(x)	(1UL << GPIO_OTYPER_POS(x))

//These bits are written by software to configure the I/O output speed.
//	00: Low speed
//	01: Medium speed
//	10: High speed
//	11: Very high speed
#define GPIO_OSPEEDR_POS(x)	(2UL*(x%16UL))
#define GPIO_OSPEEDR_MASK(x)	(3UL << GPIO_OSPEEDR_POS(x))

//These bits are written by software to configure the I/O pull-up or pull-down
//	00: No pull-up, pull-down
//	01: Pull-up
//	10: Pull-down
//	11: Reserved
#define GPIO_PUPDR_POS(x)	(2UL*(x%16UL))
#define GPIO_PUPDR_MASK(x)	(3UL << GPIO_PUPDR_POS(x))

//These bits are read-only and can be accessed in word mode only. They contain the input value of the corresponding I/O port.
#define GPIO_IDR_POS		(0UL)
#define GPIO_IDR_MASK		(0xFFFFUL << GPIO_IDR_POS)

//These bits can be read and written by software.
//Note: For atomic bit set/reset, the ODR bits can be individually set and reset by writing to the GPIOx_BSRR register (x = A..E and H).
#define GPIO_ODR_POS(x)		(1UL*(x%16UL))
#define GPIO_ODR_MASK(x)	(1UL << GPIO_ODR_POS(x))


//Note: If both BSx and BRx are set, BSx has priority.

//These bits are write-only and can be accessed in word, half-word or byte mode. A read to these bits returns the value 0x0000.
//	0: No action on the corresponding ODRx bit
//	1: Resets the corresponding ODRx bit
#define GPIO_BSR_POS(x)			(1UL*(x%16UL))
#define GPIO_BSR_MASK(x)		(3UL << GPIO_BSR_POS(x))
//
//These bits are write-only and can be accessed in word, half-word or byte mode. A read to these bits returns the value 0x0000.
//	0: No action on the corresponding ODRx bit
//	1: Sets the corresponding ODRx bit
#define GPIO_BRR_POS(x)			(1UL*(x%16UL))
#define GPIO_BRR_MASK(x)		(3UL << GPIO_BRR_POS(x))

//This register is used to lock the configuration of the port bits when a correct write sequence is applied to bit 16 (LCKK).
//The value of bits [15:0] is used to lock the configuration of the GPIO.
//
//During the write sequence, the value of LCKR[15:0] must not change.
//When the LOCK sequence has been applied on a port bit, the value of this port bit can no longer be modified until the next MCU or peripheral reset.
//
//A specific write sequence is used to write to the GPIOx_LCKR register.
//Only word access (32-bit long) is allowed during this write sequence.
//
//Each lock bit freezes a specific configuration register (control and alternate function registers).

//These bits are read/write but can only be written when the LCKK bit is ‘0.
//	0: Port configuration not locked
//	1: Port configuration locked
#define GPIO_LCKR_LCK_POS(x)		(1UL*(x%16UL))
#define GPIO_LCKR_LCK_MASK(x)		(1UL << GPIO_LCKR_LCK_POS(x))

//This bit can be read any time. It can only be modified using the lock key write sequence.
//	0: Port configuration lock key not active
//	1: Port configuration lock key active. The GPIOx_LCKR register is locked until an MCU reset or a peripheral reset occurs.
//
//	LOCK key write sequence:
//		WR LCKR[16] = ‘1’ + LCKR[15:0]
//		WR LCKR[16] = ‘0’ + LCKR[15:0]
//		WR LCKR[16] = ‘1’ + LCKR[15:0]
//		RD LCKR
//		RD LCKR[16] = ‘1’ (this read operation is optional but it confirms that the lock is active)
//
//Note: During the LOCK key write sequence, the value of LCK[15:0] must not change.
//      Any error in the lock sequence aborts the lock.
//      After the first lock sequence on any bit of the port, any read access on the LCKK bit will return ‘1’ until the next CPU reset.
#define GPIO_LCKR_LCKK_POS		(16UL)
#define GPIO_LCKR_LCKK_MASK		(1UL << GPIO_LCKR_LCK_POS)

//Alternate function selection for port x bit y (0...7)
//These bits are written by software to configure alternate function I/Os AFRLy selection:
//	0000: AF0		1000: AF8
//	0001: AF1               1001: AF9
//	0010: AF2               1010: AF10
//	0011: AF3               1011: AF11
//	0100: AF4               1100: AF12
//	0101: AF5               1101: AF13
//	0110: AF6               1110: AF14
//	0111: AF7               1111: AF15
#define GPIO_AFRL_POS(x)		(4UL*x%7UL))
#define GPIO_AFRL_MASK(x)		(0xFUL << GPIO_AFRL_POS(x))

//Alternate function selection for port x bit y (y = 8..15)
#define GPIO_AFRH_POS(x)		(4UL* ((x%8UL)%15UL) )
#define GPIO_AFRH_MASK(x)		(0xFUL << GPIO_AFRH_POS(x))

