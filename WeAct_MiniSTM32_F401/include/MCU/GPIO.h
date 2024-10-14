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

    	_IO uint16_t BSRRL;		//Port bit set register
    	_IO uint16_t BSRRH;		//Port bit reset register

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
#define GPIO_MODER_MASK(x)	(0x3UL << GPIO_MODER_POS(x))

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
#define GPIO_OSPEEDR_MASK(x)	(0x3UL << GPIO_OSPEEDR_POS(x))

//These bits are written by software to configure the I/O pull-up or pull-down
//	00: No pull-up, pull-down
//	01: Pull-up
//	10: Pull-down
//	11: Reserved
#define GPIO_PUPDR_POS(x)	(2UL*(x%16UL))
#define GPIO_PUPDR_MASK(x)	(0x3UL << GPIO_PUPDR_POS(x))

//These bits are read-only and can be accessed in word mode only. They contain the input value of the corresponding I/O port.
#define GPIO_IDR_POS		(0UL)
#define GPIO_IDR_MASK		(0xFFFFUL << GPIO_IDR_POS)

//These bits can be read and written by software.
//Note: For atomic bit set/reset, the ODR bits can be individually set and reset by writing to the GPIOx_BSRR register (x = A..E and H).

#define GPIO_ODR_POS(x)		(1UL*(x%16UL))
#define GPIO_ODR_MASK(x)	(0x3UL << GPIO_ODR_POS(x))

