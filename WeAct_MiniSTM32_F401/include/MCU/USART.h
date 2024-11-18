#include "types.h"

//USART2 is in the APB 1 domain
#define USART2_BASE	(0x40004400UL)

//USART1 and USART6 are in the APB 2 domain
#define USART1_BASE	(0x40011000UL)
#define USART6_BASE	(0x40011400UL)

typedef struct {

	_IO uint16_t SR;

		_I uint16_t __UNUSUED_0;

	_IO uint16_t DR;

		_I uint16_t __UNUSUED_1;

	_IO uint16_t BRR;

		_I uint16_t __UNUSUED_2;

	_IO uint16_t CR1;

		_I uint16_t __UNUSUED_3;

	_IO uint16_t CR2;

		_I uint16_t __UNUSUED_4;

	_IO uint16_t CR3;

		_I uint16_t __UNUSUED_5;

	_IO uint16_t GTPR;

		_I uint16_t __UNUSUED_6;

} USART_Type;

#define USART1	((USART_Type*)USART1_BASE)
#define USART6	((USART_Type*)USART6_BASE)
#define USART2	((USART_Type*)USART2_BASE)


/*----------------------SR----------------------*/
/*
 * Parity error
 * This bit is set by hardware when a parity error occurs in receiver mode.
 * It is cleared by a software sequence (a read from the status register followed by a read or write access to the USART_DR data register).
 * The software must wait for the RXNE flag to be set before clearing the PE bit.
 * An interrupt is generated if PEIE = 1 in the USART_CR1 register.
 * 
 * 	0: No parity error
 * 	1: Parity error
 */
#define USART_SR_PE_POS			(0U)
#define USART_SR_PE_MASK		((1UL) << USART_SR_PE_POS)

/*
 * Framing error
 * This bit is set by hardware when a de-synchronization, excessive noise or a break character is detected.
 * It is cleared by a software sequence (an read to the USART_SR register followed by a read to the USART_DR register).
 * 	0: No Framing error is detected
 * 	1: Framing error or break character is detected
 * 
 * Note:
 * 	This bit does not generate interrupt as it appears at the same time as the RXNE bit which itself generates an interrupt.
 * 	If the word currently being transferred causes both frame error and overrun error, it will be transferred and only the ORE bit will be set.
 * 
 * 	An interrupt is generated on FE flag in case of Multi Buffer communication if the EIE bit is set.
 */
#define USART_SR_FE_POS			(1U)
#define USART_SR_FE_MASK		((1UL) << USART_SR_FE_POS)

/*
 * Noise detected flag
 * This bit is set by hardware when noise is detected on a received frame.
 * It is cleared by a software sequence (an read to the USART_SR register followed by a read to the USART_DR register).
 * 	0: No noise is detected
 * 	1: Noise is detected
 * 
 * Note:
 * 	This bit does not generate interrupt as it appears at the same time as the RXNE bit which itself generates an interrupting interrupt is generated on NF flag in case of Multi Buffer communication if the EIE bit is set.
 * 
 * Note:
 * 	When the line is noise-free, the NF flag can be disabled by programming the ONEBIT bit to 1 to increase the USART tolerance to deviations (Refer to USART receiver tolerance to clock deviation).
*/

#define USART_SR_NF_POS			(2U)
#define USART_SR_NF_MASK		((1UL) << USART_SR_NF_POS)


/*
 * Overrun error
 * This bit is set by hardware when the word currently being received in the shift register is ready to be transferred into the RDR register while RXNE=1.
 * An interrupt is generated if RXNEIE=1 in the USART_CR1 register.
 * It is cleared by a software sequence (an read to the USART_SR register followed by a read to the USART_DR register).
 * 	0: No Overrun error
 * 	1: Overrun error is detected
 * 
 * Note:
 * 	When this bit is set, the RDR register content will not be lost but the shift register will be overwritten. An interrupt is generated on ORE flag in case of Multi Buffer communication if the EIE bit is set.
 */
#define USART_SR_ORE_POS		(3U)
#define USART_SR_ORE_MASK		((1UL) << USART_SR_ORE_POS)

/*
 * IDLE line detected
 * This bit is set by hardware when an Idle Line is detected. An interrupt is generated if the IDLEIE=1 in the USART_CR1 register.
 * It is cleared by a software sequence (an read to the USART_SR register followed by a read to the USART_DR register).
 * 	0: No Idle Line is detected
 * 	1: Idle Line is detected
 * 
 * Note:
 * 	The IDLE bit will not be set again until the RXNE bit has been set itself (i.e. a new idle line occurs).
 */
#define USART_SR_IDLE_POS		(4U)
#define USART_SR_IDLE_MASK		((1UL) << USART_SR_IDLE_POS)

/*
 * Read data register not empty
 * This bit is set by hardware when the content of the RDR shift register has been transferred to the USART_DR register.
 * An interrupt is generated if RXNEIE=1 in the USART_CR1 register.
 * It is cleared by a read to the USART_DR register.
 * The RXNE flag can also be cleared by writing a zero to it. This clearing sequence is recommended only for multibuffer communication.
 * 	0: Data is not received
 * 	1: Received data is ready to be read.
 */
#define USART_SR_RXNE_POS		(5U)
#define USART_SR_RXNE_MASK		((1UL) << USART_SR_RXNE_POS)

/*
 * Transmission complete
 * This bit is set by hardware if the transmission of a frame containing data is complete and if TXE is set.
 * An interrupt is generated if TCIE=1 in the USART_CR1 register.
 * It is cleared by a software sequence (a read from the USART_SR register followed by a write to the USART_DR register).
 * The TC bit can also be cleared by writing a '0' to it. This clearing sequence is recommended only for multibuffer communication.
 * 	0: Transmission is not complete
 * 	1: Transmission is complete
 */
#define USART_SR_TC_POS			(6U)
#define USART_SR_TC_MASK		((1UL) << USART_SR_TC_POS)

/*
 * Transmit data register empty
 * This bit is set by hardware when the content of the TDR register has been transferred into the shift register.
 * An interrupt is generated if the TXEIE bit=1 in the USART_CR1 register.
 * It is cleared by a write to the USART_DR register.
 * 	0: Data is not transferred to the shift register
 * 	1: Data is transferred to the shift register)
 * 
 * Note:
 * 	This bit is used during single buffer transmission.
 */
#define USART_SR_TXE_POS		(7U)
#define USART_SR_TXE_MASK		((1UL) << USART_SR_TXE_POS)

/*
 * LIN break detection flag
 * This bit is set by hardware when the LIN break is detected.
 * It is cleared by software (by writing it to 0). An interrupt is generated if LBDIE = 1 in the USART_CR2 register.
 * 	0: LIN Break not detected
 * 	1: LIN break detected
 * Note:
 * 	An interrupt is generated when LBD=1 if LBDIE=1
 */
#define USART_SR_LBD_POS		(8U)
#define USART_SR_LBD_MASK		((1UL) << USART_SR_LBD_POS)

/*
 * CTS flag
 * This bit is set by hardware when the CTS input toggles, if the CTSE bit is set.
 * It is cleared by software (by writing it to 0). An interrupt is generated if CTSIE=1 in the USART_CR3 register.
 * 	0: No change occurred on the CTS status line
 * 	1: A change occurred on the CTS status line
 */
#define USART_SR_CTS_POS		(9U)
#define USART_SR_CTS_MASK		((1UL) << USART_SR_CTS_POS)

/*++++++++++++++++++++++++++++++++++++++++++++++*/

/*----------------------DR----------------------*/

/*
 * Data value
 * Contains the Received or Transmitted data character, depending on whether it is read from or written to.
 * 
 * The Data register performs a double function (read and write) since it is composed of two registers, one for transmission (TDR) and one for reception (RDR)
 * 
 * 	The TDR register provides the parallel interface between the internal bus and the output shift register.
 * 
 * 	The RDR register provides the parallel interface between the input shift register and the internal bus.
 * 
 * When transmitting with the parity enabled (PCE bit set to 1 in the USART_CR1 register), the value written in the MSB (bit 7 or bit 8 depending on the data length) has no effect because it is replaced by the parity.
 * 
 * When receiving with the parity enabled, the value read in the MSB bit is the received parity bit.
 */
#define USART_DR_DR_POS			(0U)
#define USART_DR_DR_MASK		((0x1FFUL) << USART_DR_DR_POS)

/*++++++++++++++++++++++++++++++++++++++++++++++*/

/*----------------------BRR----------------------*/
/* Register specific note: The baud counters stop counting if the TE or RE bits are disabled respectively. */

/*
 * fraction of USARTDIV
 * These 4 bits define the fraction of the USART Divider (USARTDIV).
 * When OVER8=1, the DIV_Fraction3 bit is not considered and must be kept cleared.
 */
#define USART_BRR_Div_FRACTION_POS		(0U)
#define USART_BRR_Div_FRACTION_MASK		((0xFUL) << USART_BRR_Div_FRACTION_POS)

/*
 * mantissa of USARTDIV
 * These 12 bits define the mantissa of the USART Divider (USARTDIV)
 */
#define USART_BRR_Div_MANTISSA_POS		(4U)
#define USART_BRR_Div_MANTISSA_MASK		((0xFFFUL) << USART_BRR_Div_MANTISSA_POS)

/*++++++++++++++++++++++++++++++++++++++++++++++*/

/*----------------------CR1----------------------*/

/*
 * Send break
 * This bit set is used to send break characters. It can be set and cleared by software.
 * It should be set by software, and will be reset by hardware during the stop bit of break.
 * 	0: No break character is transmitted
 * 	1: Break character will be transmitted
 */
#define USART_CR1_SBK_POS		(0U)
#define USART_CR1_SBK_MASK		((1UL) << USART_CR1_SBK_POS)

/*
 * Receiver wakeup
 * This bit determines if the USART is in mute mode or not.
 * It is set and cleared by software and can be cleared by hardware when a wakeup sequence is recognized.
 * 	0: Receiver in active mode
 * 	1: Receiver in mute mode
 * 
 * Note:
 * 	Before selecting Mute mode (by setting the RWU bit) the USART must first receive a data byte, otherwise it cannot function in Mute mode with wakeup by Idle line detection.
 * 
 *          In Address Mark Detection wakeup configuration (WAKE bit=1) the RWU bit cannot be modified by software while the RXNE bit is set.
 */
#define USART_CR1_RWU_POS		(1U)
#define USART_CR1_RWU_MASK		((1UL) << USART_CR1_RWU_POS)

/*
 * Receiver enable
 * This bit enables the receiver. It is set and cleared by software.
 * 	0: Receiver is disabled
 * 	1: Receiver is enabled and begins searching for a start bit
 */
#define USART_CR1_RE_POS		(2U)
#define USART_CR1_RE_MASK		((1UL) << USART_CR1_RE_POS)

/*
 * Transmitter enable
 * This bit enables the transmitter. It is set and cleared by software.
 * 	0: Transmitter is disabled
 * 	1: Transmitter is enabled
 * 
 * Note:
 * 	During transmission, a “0” pulse on the TE bit (“0” followed by “1”) sends a preamble (idle line) after the current word, except in smartcard mode.
 * 
 * 	When TE is set, there is a 1 bit-time delay before the transmission starts.
 */
#define USART_CR1_TE_POS		(3U)
#define USART_CR1_TE_MASK		((1UL) << USART_CR1_TE_POS)

/*
 * IDLE interrupt enable
 * This bit is set and cleared by software.
 * 	0: Interrupt is inhibited
 * 	1: An USART interrupt is generated whenever IDLE=1 in the USART_SR register
 */
#define USART_CR1_IDLEIE_POS		(4U)
#define USART_CR1_IDLEIE_MASK		((1UL) << USART_CR1_IDLEIE_POS)

/*
 * RXNE interrupt enable
 * This bit is set and cleared by software.
 * 	0: Interrupt is inhibited
 * 	1: An USART interrupt is generated whenever ORE=1 or RXNE=1 in the USART_SR register
 */
#define USART_CR1_RXNEIE_POS		(5U)
#define USART_CR1_RXNEIE_MASK		((1UL) << USART_CR1_RXNEIE_POS)

/*
 * Transmission complete interrupt enable
 * This bit is set and cleared by software.
 * 	0: Interrupt is inhibited
 * 	1: An USART interrupt is generated whenever TC=1 in the USART_SR register
 */
#define USART_CR1_TCIE_POS		(6U)
#define USART_CR1_TCIE_MASK		((1UL) << USART_CR1_TCIE_POS)

/*
 * TXE interrupt enable
 * This bit is set and cleared by software.
 * 	0: Interrupt is inhibited
 * 	1: An USART interrupt is generated whenever TXE=1 in the USART_SR register
 */
#define USART_CR1_TXEIE_POS		(7U)
#define USART_CR1_TXEIE_MASK		((1UL) << USART_CR1_TXEIE_POS)

/*
 * PE interrupt enable
 * This bit is set and cleared by software.
 * 	0: Interrupt is inhibited
 * 	1: An USART interrupt is generated whenever PE=1 in the USART_SR register
 */
#define USART_CR1_PEIE_POS		(8U)
#define USART_CR1_PEIE_MASK		((1UL) << USART_CR1_PEIE_POS)

/*
 * Parity selection
 * This bit selects the odd or even parity when the parity generation/detection is enabled (PCE bit set).
 * It is set and cleared by software. The parity will be selected after the current byte.
 * 	0: Even parity
 * 	1: Odd parit
 */
#define USART_CR1_PS_POS		(9U)
#define USART_CR1_PS_MASK		((1UL) << USART_CR1_PS_POS)

/*
 * Parity control enable
 * This bit selects the hardware parity control (generation and detection).
 * When the parity control is enabled, the computed parity is inserted at the MSB position (9th bit if M=1; 8th bit if M=0) and parity is checked on the received data.
 * This bit is set and cleared by software. Once it is set, PCE is active after the current byte (in reception and in transmission).
 * 	0: Parity control disabled
 * 	1: Parity control enabled
 */
#define USART_CR1_PCE_POS		(10U)
#define USART_CR1_PCE_MASK		((1UL) << USART_CR1_PCE_POS)

/*
 * Wakeup method
 * This bit determines the USART wakeup method, it is set or cleared by software.
 * 	0: Idle Line
 * 	1: Address Mark
 */
#define USART_CR1_WAKE_POS		(11U)
#define USART_CR1_WAKE_MASK		((1UL) << USART_CR1_WAKE_POS)

/*
 * Word length
 * This bit determines the word length. It is set or cleared by software.
 * 	0: 1 Start bit, 8 Data bits, n Stop bit
 * 	1: 1 Start bit, 9 Data bits, n Stop bit
 * 
 * Note:
 * 	The M bit must not be modified during a data transfer (both transmission and reception)
 */
#define USART_CR1_M_POS			(12U)
#define USART_CR1_M_MASK		((1UL) << USART_CR1_M_POS)

/*
 * USART enable
 * When this bit is cleared, the USART prescalers and outputs are stopped and the end of the current byte transfer in order to reduce power consumption.
 * This bit is set and cleared by software.
 * 	0: USART prescaler and outputs disabled
 * 	1: USART enabled
 */
#define USART_CR1_UE_POS		(13U)
#define USART_CR1_UE_MASK		((1UL) << USART_CR1_UE_POS)

/*
 * Oversampling mode
 * 	0: oversampling by 16
 * 	1: oversampling by 8
 * 
 * Note:
 * 	Oversampling by 8 is not available in the Smartcard, IrDA and LIN modes: when SCEN=1,IREN=1 or LINEN=1 then OVER8 is forced to ‘0 by hardware.
 */
#define USART_CR1_OVER8_POS		(15U)
#define USART_CR1_OVER8_MASK		((1UL) << USART_CR1_OVER8_POS)

/*++++++++++++++++++++++++++++++++++++++++++++++*/

/*----------------------CR2----------------------*/

/*
 * Address of the USART node
 * This bit-field gives the address of the USART node.
 * This is used in multiprocessor communication during mute mode, for wake up with address mark detection.
 */
#define USART_CR2_ADD_POS		(0U)
#define USART_CR2_ADD_MASK		((0xFUL) << USART_CR2_ADD_POS)

/*
 * lin break detection length
 * This bit is for selection between 11 bit or 10 bit break detection.
 * 	0: 10-bit break detection
 * 	1: 11-bit break detection
 */
#define USART_CR2_LBDL_POS		(5U)
#define USART_CR2_LBDL_MASK		((1UL) << USART_CR2_LBDL_POS)

/*
 * LIN break detection interrupt enable
 * Break interrupt mask (break detection using break delimiter).
 * 	0: Interrupt is inhibited
 * 	1: An interrupt is generated whenever LBD=1 in the USART_SR register
 */
#define USART_CR2_LBDIE_POS		(6U)
#define USART_CR2_LBDIE_MASK		((1UL) << USART_CR2_LBDIE_POS)

/*
 * Last bit clock pulse
 * This bit allows the user to select whether the clock pulse associated with the last data bit transmitted (MSB) has to be output on the CK pin in synchronous mode.
 * 	0: The clock pulse of the last data bit is not output to the CK pin
 * 	1: The clock pulse of the last data bit is output to the CK pin
 * NOTE:
 * 	The last bit is the 8th or 9th data bit transmitted depending on the 8 or 9 bit format selected by the M bit in the USART_CR1 register.
 */
#define USART_CR2_LBCL_POS		(8U)
#define USART_CR2_LBCL_MASK		((1UL) << USART_CR2_LBCL_POS)

/*
 * Clock phase
 * This bit allows the user to select the phase of the clock output on the CK pin in synchronous mode.
 * It works in conjunction with the CPOL bit to produce the desired clock/data relationship
 * 	0: The first clock transition is the first data capture edge
 * 	1: The second clock transition is the first data capture edge
 */
#define USART_CR2_CPHA_POS		(9U)
#define USART_CR2_CPHA_MASK		((1UL) << USART_CR2_CPHA_POS)

/*
 * Clock polarity
 * This bit allows the user to select the polarity of the clock output on the CK pin in synchronous mode.
 * It works in conjunction with the CPHA bit to produce the desired clock/data relationship
 * 	0: Steady low value on CK pin outside transmission window.
 * 	1: Steady high value on CK pin outside transmission window.
 */
#define USART_CR2_CPOL_POS		(10U)
#define USART_CR2_CPOL_MASK		((1UL) << USART_CR2_CPOL_POS)

/*
 * Clock enable
 * 	This bit allows the user to enable the CK pin.
 * 	0: CK pin disabled
 * 	1: CK pin enabled
 */
#define USART_CR2_CLKEN_POS		(11U)
#define USART_CR2_CLKEN_MASK		((1UL) << USART_CR2_CLKEN_POS)

/*
 * STOP bits
 * These bits are used for programming the stop bits.
 * 	00: 1 Stop bit
 * 	01: 0.5 Stop bit
 * 	10: 2 Stop bits
 * 	11: 1.5 Stop bit
 */
#define USART_CR2_STOP_POS		(12U)
#define USART_CR2_STOP_MASK		((3UL) << USART_CR2_STOP_POS)

/*++++++++++++++++++++++++++++++++++++++++++++++*/

/*----------------------CR3----------------------*/

/*
 * Error interrupt enable
 * Error Interrupt Enable Bit is required to enable interrupt generation in case of a framing error, overrun error or noise flag (FE=1 or ORE=1 or NF=1 in the USART_SR register) in case of Multi Buffer Communication (DMAR=1 in the USART_CR3 register).
 * 
 * 	0: Interrupt is inhibited
 * 	1: An interrupt is generated whenever DMAR=1 in the USART_CR3 register and FE=1 or ORE=1 or NF=1 in the USART_SR register.
 */
#define USART_CR3_EIE_POS		(0U)
#define USART_CR3_EIE_MASK		((1UL) << USART_CR3_EIE_POS)

/*
 * IrDA mode enable
 * This bit is set and cleared by software.
 * 	0: IrDA disabled
 * 	1: IrDA enabled
 */
#define USART_CR3_IREN_POS		(1U)
#define USART_CR3_IREN_MASK		((1UL) << USART_CR3_IREN_POS)

/*
 * IrDA low-power
 * This bit is used for selecting between normal and low-power IrDA modes
 * 	0: Normal mode
 * 	1: Low-power mode
 */
#define USART_CR3_IRLP_POS		(2U)
#define USART_CR3_IRLP_MASK		((1UL) << USART_CR3_IRLP_POS)

/*
 * Half-duplex selection
 * Selection of Single-wire Half-duplex mode
 * 	0: Half duplex mode is not selected
 * 	1: Half duplex mode is selected
 */
#define USART_CR3_HDSEL_POS		(3U)
#define USART_CR3_HDSEL_MASK		((1UL) << USART_CR3_HDSEL_POS)

/*
 * Smartcard NACK enable
 * 	0: NACK transmission in case of parity error is disabled
 * 	1: NACK transmission during parity error is enabled
 */
#define USART_CR3_NACK_POS		(4U)
#define USART_CR3_NACK_MASK		((1UL) << USART_CR3_NACK_POS)

/*
 * Smartcard mode enable
 * This bit is used for enabling Smartcard mode.
 * 	0: Smartcard Mode disabled
 * 	1: Smartcard Mode enabled
 */
#define USART_CR3_SCEN_POS		(5U)
#define USART_CR3_SCEN_MASK		((1UL) << USART_CR3_SCEN_POS)

/*
 * DMAR: DMA enable receiver
 * This bit is set/reset by software
 * 	0: DMA mode is disabled for reception
 * 	1: DMA mode is enabled for reception
 */
#define USART_CR3_DMAR_POS		(6U)
#define USART_CR3_DMAR_MASK		((1UL) << USART_CR3_DMAR_POS)

/*
 * DMA enable transmitter
 * This bit is set/reset by software
 * 	1: DMA mode is enabled for transmission.
 * 	0: DMA mode is disabled for transmission.
 */
#define USART_CR3_DMAT_POS		(7U)
#define USART_CR3_DMAT_MASK		((1UL) << USART_CR3_DMAT_POS)

/*
 * RTS enable
 * 	0: RTS hardware flow control disabled
 * 	1: RTS interrupt enabled
 * 
 * Note:
 * 	Data is only requested when there is space in the receive buffer.
 * 	The transmission of data is expected to cease after the current character has been transmitted. The RTS output is asserted (tied to 0) when a data can be received.
 */
#define USART_CR3_RTSE_POS		(8U)
#define USART_CR3_RTSE_MASK		((1UL) << USART_CR3_RTSE_POS)

/*++++++++++++++++++++++++++++++++++++++++++++++*/

/*----------------------GTPR----------------------*/

/*
 * Prescaler value
 * – In IrDA Low-power mode:
 * 
 * 	PSC[7:0] = IrDA Low-Power Baud Rate
 * 		Used for programming the prescaler for dividing the system clock to achieve the low-power frequency:
 *   			The source clock is divided by the value given in the register (8 significant bits):
 *   				00000000: Reserved - do not program this value
 *   				00000001: divides the source clock by 1
 *   				00000010: divides the source clock by 2
 *   				...
 * 
 * – In normal IrDA mode: PSC must be set to 00000001.
 * 
 * – In smartcard mode:
 * 
 * 	PSC[4:0]: Prescaler value Used for programming the prescaler for dividing the system clock to provide the smartcard clock.
 * 			The value given in the register (5 significant bits) is multiplied by 2 to give the division factor of the source clock frequency:
 *   				00000: Reserved - do not program this value
 *   				00001: divides the source clock by 2
 *   				00010: divides the source clock by 4
 *   				00011: divides the source clock by 6
 *   				...
 * Note:
 * 	Bits [7:5] have no effect if Smartcard mode is used.
 */
#define USART_GTPR_PSC_POS		(0U)
#define USART_GTPR_PSC_MASK		((0xFFUL) << USART_GTPR_PSC_POS)

/*
 * Guard time value
 * This bit-field gives the Guard time value in terms of number of baud clocks.
 * Note:
 * 	This is used in Smartcard mode. The Transmission Complete flag is set after this guard time value.
 */
#define USART_GTPR_GT_POS		(8U)
#define USART_GTPR_GT_MASK		((0xFFUL) << USART_GTPR_GT_POS)

/*++++++++++++++++++++++++++++++++++++++++++++++*/

