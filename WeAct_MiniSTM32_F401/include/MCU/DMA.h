#include "types.h"

#define DMA1_BASE	(0x40026000UL)
#define DMA2_BASE	(0x40026400UL)

typedef struct {

	_IO uint32_t CR;		/*Stream x configuration register*/
	_IO uint32_t NDTR;		/*Stream x number of data register*/
	_IO uint32_t PAR;		/*Stream x peripheral address register*/
	_IO uint32_t M0AR;		/*Stream x memory 0 address register*/
	_IO uint32_t M1AR;		/*Stream x memory 1 address register*/
	_IO uint32_t FCR;		/*Stream x FIFO control register*/	/*Not zero on reset*/	

} STREAM;

typedef struct {

	_I uint32_t LISR;
	_I uint32_t HISR;
	_O uint32_t LIFCR;
	_O uint32_t HIFCR;
	_IO STREAM  Sx[8];

} DMA_Type;


#define DMA1	((DMA_Type*)DMA1_BASE)
#define DMA2	((DMA_Type*)DMA2_BASE)

/*----------------------LISR----------------------*/

/*
 * Stream x FIFO error interrupt flag (x=3..0)
 * This bit is set by hardware. It is cleared by software writing 1 to the corresponding bit in the DMA_LIFCR register.
 * 	0: No FIFO Error event on stream x
 * 	1: A FIFO Error event occurred on stream x
 */
#define DMA_LISR_FEIF0_POS	(0U)
#define DMA_LISR_FEIF0_MASK	((1UL) << DMA_LISR_FEIF0_POS)

#define DMA_LISR_FEIF1_POS	(6U)
#define DMA_LISR_FEIF1_MASK	((1UL) << DMA_LISR_FEIF1_POS)

#define DMA_LISR_FEIF2_POS	(16U)
#define DMA_LISR_FEIF2_MASK	((1UL) << DMA_LISR_FEIF2_POS)

#define DMA_LISR_FEIF3_POS	(22U)
#define DMA_LISR_FEIF3_MASK	((1UL) << DMA_LISR_FEIF3_POS)

/*
 * ENStream x direct mode error interrupt flag (x=3..0)
 * This bit is set by hardware. It is cleared by software writing 1 to the corresponding bit in the DMA_LIFCR register.
 * 	0: No Direct Mode Error on stream x
 * 	1: A Direct Mode Error occurred on stream x
 */
#define DMA_LISR_DMEIF0_POS	(2U)
#define DMA_LISR_DMEIF0_MASK	((1UL) << DMA_LISR_DMEIF0_POS)

#define DMA_LISR_DMEIF1_POS	(8U)
#define DMA_LISR_DMEIF1_MASK	((1UL) << DMA_LISR_DMEIF1_POS)

#define DMA_LISR_DMEIF2_POS	(18U)
#define DMA_LISR_DMEIF2_MASK	((1UL) << DMA_LISR_DMEIF2_POS)

#define DMA_LISR_DMEIF3_POS	(24U)
#define DMA_LISR_DMEIF3_MASK	((1UL) << DMA_LISR_DMEIF3_POS)

/*
 * Stream x transfer error interrupt flag (x=3..0)
 * This bit is set by hardware. It is cleared by software writing 1 to the corresponding bit in the DMA_LIFCR register.
 * 	0: No transfer error on stream x
 * 	1: A transfer error occurred on stream x
 */
#define DMA_LISR_TEIF0_POS	(3U)
#define DMA_LISR_TEIF0_MASK	((1UL) << DMA_LISR_TEIF0_POS)

#define DMA_LISR_TEIF1_POS	(9U)
#define DMA_LISR_TEIF1_MASK	((1UL) << DMA_LISR_TEIF1_POS)

#define DMA_LISR_TEIF2_POS	(19U)
#define DMA_LISR_TEIF2_MASK	((1UL) << DMA_LISR_TEIF2_POS)

#define DMA_LISR_TEIF3_POS	(25U)
#define DMA_LISR_TEIF3_MASK	((1UL) << DMA_LISR_TEIF3_POS)

/*
 * Stream x half transfer interrupt flag (x=3..0)
 * This bit is set by hardware. It is cleared by software writing 1 to the corresponding bit in the DMA_LIFCR register.
 * 	0: No half transfer event on stream x
 * 	1: A half transfer event occurred on stream x
 */
#define DMA_LISR_HTIF0_POS	(4U)
#define DMA_LISR_HTIF0_MASK	((1UL) << DMA_LISR_HTIF0_POS)

#define DMA_LISR_HTIF1_POS	(10U)
#define DMA_LISR_HTIF1_MASK	((1UL) << DMA_LISR_HTIF1_POS)

#define DMA_LISR_HTIF2_POS	(20U)
#define DMA_LISR_HTIF2_MASK	((1UL) << DMA_LISR_HTIF2_POS)

#define DMA_LISR_HTIF3_POS	(26U)
#define DMA_LISR_HTIF3_MASK	((1UL) << DMA_LISR_HTIF3_POS)

/*
 * Stream x transfer complete interrupt flag (x = 3..0)
 * This bit is set by hardware. It is cleared by software writing 1 to the corresponding bit in the DMA_LIFCR register.
 * 	0: No transfer complete event on stream x
 * 	1: A transfer complete event occurred on stream x
 */
#define DMA_LISR_TCIF0_POS	(5U)
#define DMA_LISR_TCIF0_MASK	((1UL) << DMA_LISR_TCIF0_POS)

#define DMA_LISR_TCIF1_POS	(11U)
#define DMA_LISR_TCIF1_MASK	((1UL) << DMA_LISR_TCIF1_POS)

#define DMA_LISR_TCIF2_POS	(21U)
#define DMA_LISR_TCIF2_MASK	((1UL) << DMA_LISR_TCIF2_POS)

#define DMA_LISR_TCIF3_POS	(27U)
#define DMA_LISR_TCIF3_MASK	((1UL) << DMA_LISR_TCIF3_POS)

/*++++++++++++++++++++++++++++++++++++++++++++++*/

/*----------------------HISR----------------------*/

/*
 * Stream x FIFO error interrupt flag (x=7..4)
 * This bit is set by hardware. It is cleared by software writing 1 to the corresponding bit in the DMA_HIFCR register.
 * 	0: No FIFO Error event on stream x
 * 	1: A FIFO Error event occurred on stream x
 */
#define DMA_HISR_FEIF4_POS	(0U)
#define DMA_HISR_FEIF4_MASK	((1UL) << DMA_HISR_FEIF4_POS)

#define DMA_HISR_FEIF5_POS	(6U)
#define DMA_HISR_FEIF5_MASK	((1UL) << DMA_HISR_FEIF5_POS)

#define DMA_HISR_FEIF6_POS	(16U)
#define DMA_HISR_FEIF6_MASK	((1UL) << DMA_HISR_FEIF6_POS)

#define DMA_HISR_FEIF7_POS	(22U)
#define DMA_HISR_FEIF7_MASK	((1UL) << DMA_HISR_FEIF7_POS)

/*
 * ENStream x direct mode error interrupt flag (x=7..4)
 * This bit is set by hardware. It is cleared by software writing 1 to the corresponding bit in the DMA_HIFCR register.
 * 	0: No Direct Mode Error on stream x
 * 	1: A Direct Mode Error occurred on stream x
 */
#define DMA_HISR_DMEIF4_POS	(2U)
#define DMA_HISR_DMEIF4_MASK	((1UL) << DMA_HISR_DMEIF4_POS)

#define DMA_HISR_DMEIF5_POS	(8U)
#define DMA_HISR_DMEIF5_MASK	((1UL) << DMA_HISR_DMEIF5_POS)

#define DMA_HISR_DMEIF6_POS	(18U)
#define DMA_HISR_DMEIF6_MASK	((1UL) << DMA_HISR_DMEIF6_POS)

#define DMA_HISR_DMEIF7_POS	(24U)
#define DMA_HISR_DMEIF7_MASK	((1UL) << DMA_HISR_DMEIF7_POS)

/*
 * Stream x transfer error interrupt flag (x=7..4)
 * This bit is set by hardware. It is cleared by software writing 1 to the corresponding bit in the DMA_HIFCR register.
 * 	0: No transfer error on stream x
 * 	1: A transfer error occurred on stream x
 */
#define DMA_HISR_TEIF4_POS	(3U)
#define DMA_HISR_TEIF4_MASK	((1UL) << DMA_HISR_TEIF4_POS)

#define DMA_HISR_TEIF5_POS	(9U)
#define DMA_HISR_TEIF5_MASK	((1UL) << DMA_HISR_TEIF5_POS)

#define DMA_HISR_TEIF6_POS	(19U)
#define DMA_HISR_TEIF6_MASK	((1UL) << DMA_HISR_TEIF6_POS)

#define DMA_HISR_TEIF7_POS	(25U)
#define DMA_HISR_TEIF7_MASK	((1UL) << DMA_HISR_TEIF7_POS)

/*
 * Stream x half transfer interrupt flag (x=7..4)
 * This bit is set by hardware. It is cleared by software writing 1 to the corresponding bit in the DMA_HIFCR register.
 * 	0: No half transfer event on stream x
 * 	1: A half transfer event occurred on stream x
 */
#define DMA_HISR_HTIF4_POS	(4U)
#define DMA_HISR_HTIF4_MASK	((1UL) << DMA_HISR_HTIF4_POS)

#define DMA_HISR_HTIF5_POS	(10U)
#define DMA_HISR_HTIF5_MASK	((1UL) << DMA_HISR_HTIF5_POS)

#define DMA_HISR_HTIF6_POS	(20U)
#define DMA_HISR_HTIF6_MASK	((1UL) << DMA_HISR_HTIF6_POS)

#define DMA_HISR_HTIF7_POS	(26U)
#define DMA_HISR_HTIF7_MASK	((1UL) << DMA_HISR_HTIF7_POS)

/*
 * Stream x transfer complete interrupt flag (x = 7..4)
 * This bit is set by hardware. It is cleared by software writing 1 to the corresponding bit in the DMA_HIFCR register.
 * 	0: No transfer complete event on stream x
 * 	1: A transfer complete event occurred on stream x
 */
#define DMA_HISR_TCIF4_POS	(5U)
#define DMA_HISR_TCIF4_MASK	((1UL) << DMA_HISR_TCIF4_POS)

#define DMA_HISR_TCIF5_POS	(11U)
#define DMA_HISR_TCIF5_MASK	((1UL) << DMA_HISR_TCIF5_POS)

#define DMA_HISR_TCIF6_POS	(21U)
#define DMA_HISR_TCIF6_MASK	((1UL) << DMA_HISR_TCIF6_POS)

#define DMA_HISR_TCIF7_POS	(27U)
#define DMA_HISR_TCIF7_MASK	((1UL) << DMA_HISR_TCIF7_POS)

/*++++++++++++++++++++++++++++++++++++++++++++++*/

/*----------------------LIFCR----------------------*/

/*
 * Stream x clear FIFO error interrupt flag (x = 3..0)
 * Writing 1 to this bit clears the corresponding CFEIFx flag in the DMA_LISR register
 */
#define DMA_LIFCR_CFEIF0_POS	(0U)
#define DMA_LIFCR_CFEIF0_MASK	((1UL) << DMA_LIFCR_CFEIF0_POS)

#define DMA_LIFCR_CFEIF1_POS	(6U)
#define DMA_LIFCR_CFEIF1_MASK	((1UL) << DMA_LIFCR_CFEIF1_POS)

#define DMA_LIFCR_CFEIF2_POS	(16U)
#define DMA_LIFCR_CFEIF2_MASK	((1UL) << DMA_LIFCR_CFEIF2_POS)

#define DMA_LIFCR_CFEIF3_POS	(22U)
#define DMA_LIFCR_CFEIF3_MASK	((1UL) << DMA_LIFCR_CFEIF3_POS)

/*
 * Stream x clear direct mode error interrupt flag (x = 3..0)
 * Writing 1 to this bit clears the corresponding DMEIFx flag in the DMA_LISR register
 */
#define DMA_LIFCR_CDMEIF0_POS	(2U)
#define DMA_LIFCR_CDMEIF0_MASK	((1UL) << DMA_LIFCR_CDMEIF0_POS)

#define DMA_LIFCR_CDMEIF1_POS	(8U)
#define DMA_LIFCR_CDMEIF1_MASK	((1UL) << DMA_LIFCR_CDMEIF1_POS)

#define DMA_LIFCR_CDMEIF2_POS	(18U)
#define DMA_LIFCR_CDMEIF2_MASK	((1UL) << DMA_LIFCR_CDMEIF2_POS)

#define DMA_LIFCR_CDMEIF3_POS	(24U)
#define DMA_LIFCR_CDMEIF3_MASK	((1UL) << DMA_LIFCR_CDMEIF3_POS)

/*
 * Stream x clear transfer error interrupt flag (x = 3..0)
 * Writing 1 to this bit clears the corresponding TEIFx flag in the DMA_LISR register
 */
#define DMA_LIFCR_CTEIF0_POS	(3U)
#define DMA_LIFCR_CTEIF0_MASK	((1UL) << DMA_LIFCR_CTEIF0_POS)

#define DMA_LIFCR_CTEIF1_POS	(9U)
#define DMA_LIFCR_CTEIF1_MASK	((1UL) << DMA_LIFCR_CTEIF1_POS)

#define DMA_LIFCR_CTEIF2_POS	(19U)
#define DMA_LIFCR_CTEIF2_MASK	((1UL) << DMA_LIFCR_CTEIF2_POS)

#define DMA_LIFCR_CTEIF3_POS	(25U)
#define DMA_LIFCR_CTEIF3_MASK	((1UL) << DMA_LIFCR_CTEIF3_POS)

/*
 * Stream x clear half transfer interrupt flag (x = 3..0)
 * Writing 1 to this bit clears the corresponding HTIFx flag in the DMA_LISR register
 */
#define DMA_LIFCR_CHTIF0_POS	(4U)
#define DMA_LIFCR_CHTIF0_MASK	((1UL) << DMA_LIFCR_CHTIF0_POS)

#define DMA_LIFCR_CHTIF1_POS	(10U)
#define DMA_LIFCR_CHTIF1_MASK	((1UL) << DMA_LIFCR_CHTIF1_POS)

#define DMA_LIFCR_CHTIF2_POS	(20U)
#define DMA_LIFCR_CHTIF2_MASK	((1UL) << DMA_LIFCR_CHTIF2_POS)

#define DMA_LIFCR_CHTIF3_POS	(26U)
#define DMA_LIFCR_CHTIF3_MASK	((1UL) << DMA_LIFCR_CHTIF3_POS)

/*
 * Stream x clear transfer complete interrupt flag (x = 3..0)
 * Writing 1 to this bit clears the corresponding TCIFx flag in the DMA_LISR register
 */
#define DMA_LIFCR_CTCIF0_POS	(5U)
#define DMA_LIFCR_CTCIF0_MASK	((1UL) << DMA_LIFCR_CTCIF0_POS)

#define DMA_LIFCR_CTCIF1_POS	(11U)
#define DMA_LIFCR_CTCIF1_MASK	((1UL) << DMA_LIFCR_CTCIF1_POS)

#define DMA_LIFCR_CTCIF2_POS	(21U)
#define DMA_LIFCR_CTCIF2_MASK	((1UL) << DMA_LIFCR_CTCIF2_POS)

#define DMA_LIFCR_CTCIF3_POS	(27U)
#define DMA_LIFCR_CTCIF3_MASK	((1UL) << DMA_LIFCR_CTCIF3_POS)

/*++++++++++++++++++++++++++++++++++++++++++++++*/

/*----------------------HIFCR----------------------*/

/*
 * Stream x clear FIFO error interrupt flag (x = 7..4)
 * Writing 1 to this bit clears the corresponding CFEIFx flag in the DMA_HISR register
 */
#define DMA_HIFCR_CFEIF4_POS	(0U)
#define DMA_HIFCR_CFEIF4_MASK	((1UL) << DMA_HIFCR_CFEIF4_POS)

#define DMA_HIFCR_CFEIF5_POS	(6U)
#define DMA_HIFCR_CFEIF5_MASK	((1UL) << DMA_HIFCR_CFEIF5_POS)

#define DMA_HIFCR_CFEIF6_POS	(16U)
#define DMA_HIFCR_CFEIF6_MASK	((1UL) << DMA_HIFCR_CFEIF6_POS)

#define DMA_HIFCR_CFEIF7_POS	(22U)
#define DMA_HIFCR_CFEIF7_MASK	((1UL) << DMA_HIFCR_CFEIF7_POS)

/*
 * Stream x clear direct mode error interrupt flag (x = 7..4)
 * Writing 1 to this bit clears the corresponding DMEIFx flag in the DMA_HISR register
 */
#define DMA_HIFCR_CDMEIF4_POS	(2U)
#define DMA_HIFCR_CDMEIF4_MASK	((1UL) << DMA_HIFCR_CDMEIF4_POS)

#define DMA_HIFCR_CDMEIF5_POS	(8U)
#define DMA_HIFCR_CDMEIF5_MASK	((1UL) << DMA_HIFCR_CDMEIF5_POS)

#define DMA_HIFCR_CDMEIF6_POS	(18U)
#define DMA_HIFCR_CDMEIF6_MASK	((1UL) << DMA_HIFCR_CDMEIF6_POS)

#define DMA_HIFCR_CDMEIF7_POS	(24U)
#define DMA_HIFCR_CDMEIF7_MASK	((1UL) << DMA_HIFCR_CDMEIF7_POS)

/*
 * Stream x clear transfer error interrupt flag (x = 7..4)
 * Writing 1 to this bit clears the corresponding TEIFx flag in the DMA_HISR register
 */
#define DMA_HIFCR_CTEIF4_POS	(3U)
#define DMA_HIFCR_CTEIF4_MASK	((1UL) << DMA_HIFCR_CTEIF4_POS)

#define DMA_HIFCR_CTEIF5_POS	(9U)
#define DMA_HIFCR_CTEIF5_MASK	((1UL) << DMA_HIFCR_CTEIF5_POS)

#define DMA_HIFCR_CTEIF6_POS	(19U)
#define DMA_HIFCR_CTEIF6_MASK	((1UL) << DMA_HIFCR_CTEIF6_POS)

#define DMA_HIFCR_CTEIF7_POS	(25U)
#define DMA_HIFCR_CTEIF7_MASK	((1UL) << DMA_HIFCR_CTEIF7_POS)

/*
 * Stream x clear half transfer interrupt flag (x = 7..4)
 * Writing 1 to this bit clears the corresponding HTIFx flag in the DMA_HISR register
 */
#define DMA_HIFCR_CHTIF4_POS	(4U)
#define DMA_HIFCR_CHTIF4_MASK	((1UL) << DMA_HIFCR_CHTIF4_POS)

#define DMA_HIFCR_CHTIF5_POS	(10U)
#define DMA_HIFCR_CHTIF5_MASK	((1UL) << DMA_HIFCR_CHTIF5_POS)

#define DMA_HIFCR_CHTIF6_POS	(20U)
#define DMA_HIFCR_CHTIF6_MASK	((1UL) << DMA_HIFCR_CHTIF6_POS)

#define DMA_HIFCR_CHTIF7_POS	(26U)
#define DMA_HIFCR_CHTIF7_MASK	((1UL) << DMA_HIFCR_CHTIF7_POS)

/*
 * Stream x clear transfer complete interrupt flag (x = 7..4)
 * Writing 1 to this bit clears the corresponding TCIFx flag in the DMA_HISR register
 */
#define DMA_HIFCR_CTCIF4_POS	(5U)
#define DMA_HIFCR_CTCIF4_MASK	((1UL) << DMA_HIFCR_CTCIF4_POS)

#define DMA_HIFCR_CTCIF5_POS	(11U)
#define DMA_HIFCR_CTCIF5_MASK	((1UL) << DMA_HIFCR_CTCIF5_POS)

#define DMA_HIFCR_CTCIF6_POS	(21U)
#define DMA_HIFCR_CTCIF6_MASK	((1UL) << DMA_HIFCR_CTCIF6_POS)

#define DMA_HIFCR_CTCIF7_POS	(27U)
#define DMA_HIFCR_CTCIF7_MASK	((1UL) << DMA_HIFCR_CTCIF7_POS)

/*++++++++++++++++++++++++++++++++++++++++++++++*/

/*----------------------Streams Registers----------------------*/

/*----------------------CR Register----------------------*/
/*
 * Stream enable / flag stream ready when read low
 * This bit is set and cleared by software.
 * 	0: Stream disabled
 * 	1: Stream enabled
 * 
 *  This bit may be cleared by hardware:
 * 	– on a DMA end of transfer (stream ready to be configured)
 * 	– if a transfer error occurs on the AHB master buses
 * 	– when the FIFO threshold on memory AHB port is not compatible with the size of the burst
 * 
 * When this bit is read as 0, the software is allowed to program the Configuration and FIFO bits registers.
 * It is forbidden to write these registers when the EN bit is read as 1.
 * 
 * Note:
 * 	Before setting EN bit to '1' to start a new transfer, the event flags corresponding to the stream in DMA_LISR or DMA_HISR register must be cleared.
 */
#define DMA_Sx_EN_POS		(0U)
#define DMA_Sx_EN_MASK		((1UL) << DMA_Sx_EN_POS)

/*
 * Direct mode error interrupt enable
 * This bit is set and cleared by software.
 * 	0: DME interrupt disabled
 * 	1: DME interrupt enabled
 */
#define DMA_Sx_DMEIE_POS	(1U)
#define DMA_Sx_DMEIE_MASK	((1UL) << DMA_Sx_DMEIE_POS)

/*
 * Transfer error interrupt enable
 * This bit is set and cleared by software.
 * 	0: TE interrupt disabled
 * 	1: TE interrupt enabled
 */
#define DMA_Sx_TEIE_POS		(2U)
#define DMA_Sx_TEIE_MASK	((1UL) << DMA_Sx_TEIE_POS)

/*
 * Half transfer interrupt enable
 * This bit is set and cleared by software.
 * 	0: HT interrupt disabled
 * 	1: HT interrupt enabled
 */
#define DMA_Sx_HTIE_POS		(3U)
#define DMA_Sx_HTIE_MASK	((1UL) << DMA_Sx_HTIE_POS)

/*
 * Transfer complete interrupt enable
 * This bit is set and cleared by software.
 * 	0: TC interrupt disabled
 * 	1: TC interrupt enabled
 */
#define DMA_Sx_TCIE_POS		(4U)
#define DMA_Sx_TCIE_MASK	((1UL) << DMA_Sx_TCIE_POS)

/*
 * Peripheral flow controller
 * This bit is set and cleared by software.
 * 	0: The DMA is the flow controller
 * 	1: The peripheral is the flow controller
 * This bit is protected and can be written only if EN is ‘0’.
 * When the memory-to-memory mode is selected (bits DIR[1:0]=10), then this bit is automatically forced to 0 by hardware.
 */
#define DMA_Sx_PFCTRL_POS	(5U)
#define DMA_Sx_PFCTRL_MASK	((1UL) << DMA_Sx_PFCTRL_POS)

/*
 * Data transfer direction
 * These bits are set and cleared by software.
 * 	00: Peripheral-to-memory
 * 	01: Memory-to-peripheral
 * 	10: Memory-to-memory
 * 	11: reserved
 * These bits are protected and can be written only if EN is ‘0’.
 */
#define DMA_Sx_DIR_POS		(6U)
#define DMA_Sx_DIR_MASK		((3UL) << DMA_Sx_DIR_POS)

/*
 * Circular mode
 * This bit is set and cleared by software and can be cleared by hardware.
 * 	0: Circular mode disabled
 * 	1: Circular mode enabled
 * 
 * When the peripheral is the flow controller (bit PFCTRL=1) and the stream is enabled (bit EN=1), then this bit is automatically forced by hardware to 0.
 * 
 * It is automatically forced by hardware to 1 if the DBM bit is set, as soon as the stream is
 * enabled (bit EN ='1').
 */
#define DMA_Sx_CIRC_POS		(8U)
#define DMA_Sx_CIRC_MASK	((1UL) << DMA_Sx_CIRC_POS)

/*
 * Peripheral increment mode
 * This bit is set and cleared by software.
 * 	0: Peripheral address pointer is fixed
 * 	1: Peripheral address pointer is incremented after each data transfer (increment is done according to PSIZE)
 * This bit is protected and can be written only if EN is ‘0’.
 */
#define DMA_Sx_PINC_POS		(9U)
#define DMA_Sx_PINC_MASK	((1UL) << DMA_Sx_PINC_POS)

/*
 * Memory increment mode
 * This bit is set and cleared by software.
 * 	0: Memory address pointer is fixed
 * 	1: Memory address pointer is incremented after each data transfer (increment is done according to MSIZE)
 * This bit is protected and can be written only if EN is ‘0’.
 */
#define DMA_Sx_MINC_POS		(10U)
#define DMA_Sx_MINC_MASK	((1UL) << DMA_Sx_MINC_POS)

/*
 * Peripheral data size
 * These bits are set and cleared by software.
 * 	00: Byte (8-bit)
 * 	01: Half-word (16-bit)
 * 	10: Word (32-bit)
 * 	11: reserved
 * 
 * These bits are protected and can be written only if EN is ‘0’
 */
#define DMA_Sx_PSIZE_POS	(11U)
#define DMA_Sx_PSIZE_MASK	((3UL) << DMA_Sx_PSIZE_POS)

/*
 * Memory data size
 * These bits are set and cleared by software.
 * 	00: byte (8-bit)
 * 	01: half-word (16-bit)
 * 	10: word (32-bit)
 * 	11: reserved
 * 
 * These bits are protected and can be written only if EN is ‘0’.
 * In direct mode, MSIZE is forced by hardware to the same value as PSIZE as soon as bit EN = '1'.
 */
#define DMA_Sx_MSIZE_POS	(13U)
#define DMA_Sx_MSIZE_MASK	((3UL) << DMA_Sx_MSIZE_POS)

/*
 * Peripheral increment offset size
 * This bit is set and cleared by software
 * 	0: The offset size for the peripheral address calculation is linked to the PSIZE
 * 	1: The offset size for the peripheral address calculation is fixed to 4 (32-bit alignment).
 * 
 * This bit has no meaning if bit PINC = '0'.
 * This bit is protected and can be written only if EN = '0'.
 * This bit is forced low by hardware when the stream is enabled (bit EN = '1') if the direct mode is selected or if PBURST are different from “00”.
 */
#define DMA_Sx_PINCOS_POS	(15U)
#define DMA_Sx_PINCOS_MASK	((1UL) << DMA_Sx_PINCOS_POS)

/*
 * Priority level
 * These bits are set and cleared by software.
 * 	00: Low
 * 	01: Medium
 * 	10: High
 * 	11: Very high
 * 
 * These bits are protected and can be written only if EN is ‘0’.
 */
#define DMA_Sx_PL_POS		(16U)
#define DMA_Sx_PL_MASK		((3UL) << DMA_Sx_PL_POS)

/*
 * Double buffer mode
 * This bits is set and cleared by software.
 * 	0: No buffer switching at the end of transfer
 * 	1: Memory target switched at the end of the DMA transfer
 * 
 * This bit is protected and can be written only if EN is ‘0’.
 */
#define DMA_Sx_DBM_POS		(18U)
#define DMA_Sx_DBM_MASK		((1UL) << DMA_Sx_DBM_POS)

/*
 * Current target (only in double buffer mode)
 * This bits is set and cleared by hardware. It can also be written by software.
 * 	0: The current target memory is Memory 0 (addressed by the DMA_SxM0AR pointer)
 * 	1: The current target memory is Memory 1 (addressed by the DMA_SxM1AR pointer)
 * 
 * This bit can be written only if EN is ‘0’ to indicate the target memory area of the first transfer.
 * Once the stream is enabled, this bit operates as a status flag indicating which memory area is the current target.
 */
#define DMA_Sx_CT_POS		(19U)
#define DMA_Sx_CT_MASK		((1UL) << DMA_Sx_CT_POS)

/*
 * Peripheral burst transfer configuration
 * These bits are set and cleared by software.
 * 	00: single transfer
 * 	01: INCR4 (incremental burst of 4 beats)
 * 	10: INCR8 (incremental burst of 8 beats)
 * 	11: INCR16 (incremental burst of 16 beats)
 * These bits are protected and can be written only if EN is ‘0’
 * In direct mode, these bits are forced to 0x0 by hardware.
 */
#define DMA_Sx_PBURST_POS	(21U)
#define DMA_Sx_PBURST_MASK	((3UL) << DMA_Sx_PBURST_POS)

/*
 * Memory burst transfer configuration
 * These bits are set and cleared by software.
 * 	00: single transfer
 * 	01: INCR4 (incremental burst of 4 beats)
 * 	10: INCR8 (incremental burst of 8 beats)
 * 	11: INCR16 (incremental burst of 16 beats)
 * These bits are protected and can be written only if EN is ‘0’
 * In direct mode, these bits are forced to 0x0 by hardware as soon as bit EN= '1'.
 */
#define DMA_Sx_MBURST_POS	(23U)
#define DMA_Sx_MBURST_MASK	((3UL) << DMA_Sx_MBURST_POS)

/*
 * Channel selection
 * These bits are set and cleared by software.
 * 	000: channel 0 selected
 * 	001: channel 1 selected
 * 	010: channel 2 selected
 * 	011: channel 3 selected
 * 	100: channel 4 selected
 * 	101: channel 5 selected
 * 	110: channel 6 selected
 * 	111: channel 7 selected
 * 
 * These bits are protected and can be written only if EN is ‘0’
 */
#define DMA_Sx_CHSEL_POS	(25U)
#define DMA_Sx_CHSEL_MASK	((7UL) << DMA_Sx_CHSEL_POS)

/*++++++++++++++++++++++++++++++++++++++++++++++*/

/*----------------------NDTR----------------------*/

/*
 * Number of data items to transfer
 * Number of data items to be transferred (0 up to 65535). This register can be written only when the stream is disabled.
 * When the stream is enabled, this register is read-only, indicating the remaining data items to be transmitted.
 * This register decrements after each DMA transfer.
 * 
 * Once the transfer has completed, this register can either stay at zero (when the stream is in normal mode) or be reloaded automatically with the previously programmed value in the following cases:
 * 
 *     – when the stream is configured in Circular mode.
 *     – when the stream is enabled again by setting EN bit to '1'
 * 
 * If the value of this register is zero, no transaction can be served even if the stream is enabled.
 */
#define DMA_Sx_NDT_POS		(0U)
#define DMA_Sx_NDT_MASK		((0xFFFFUL) << DMA_Sx_NDT_POS)

/*++++++++++++++++++++++++++++++++++++++++++++++*/

/*----------------------PAR----------------------*/

/*
 * Peripheral address
 * Base address of the peripheral data register from/to which the data will be read/written.
 * These bits are write-protected and can be written only when bit EN = '0' in the DMA_SxCR register.
 */
#define DMA_PAR_PAR_POS		(0U)
#define DMA_PAR_PAR_MASK	((0xFFFFFFFFUL) << DMA_PAR_PAR_POS)

/*++++++++++++++++++++++++++++++++++++++++++++++*/

/*----------------------M0AR----------------------*/

/*
 * Memory 0 address
 * Base address of Memory area 0 from/to which the data will be read/written.
 * These bits are write-protected. They can be written only if:
 * 	– the stream is disabled (bit EN= '0' in the DMA_SxCR register) or
 * 	– the stream is enabled (EN=’1’ in DMA_SxCR register) and bit CT = '1' in the DMA_SxCR register (in Double buffer mode).
 */
#define DMA_M0AR_M0A_POS	(0U)
#define DMA_M0AR_M0A_MASK	((0xFFFFFFFFUL) << DMA_M0AR_M0A_POS)

/*++++++++++++++++++++++++++++++++++++++++++++++*/

/*----------------------M1AR----------------------*/

/*
 * Memory 1 address (used in case of Double buffer mode)
 * Base address of Memory area 1 from/to which the data will be read/written.
 * This register is used only for the Double buffer mode.
 * These bits are write-protected. They can be written only if:
 * 	– the stream is disabled (bit EN= '0' in the DMA_SxCR register) or
 * 	– the stream is enabled (EN=’1’ in DMA_SxCR register) and bit CT = '0' in the DMA_SxCR register.
 */
#define DMA_M1AR_M1A_POS	(0U)
#define DMA_M1AR_M1A_MASK	((0xFFFFFFFFUL) << DMA_M1AR_M1A_POS)

/*++++++++++++++++++++++++++++++++++++++++++++++*/

/*----------------------FCR----------------------*/

/*
 * FIFO threshold selection
 * These bits are set and cleared by software.
 * 
 * 	00: 1/4 full FIFO
 * 	01: 1/2 full FIFO
 * 	10: 3/4 full FIFO
 * 	11: full FIFO
 * 
 * These bits are not used in the direct mode when the DMIS value is zero.
 * These bits are protected and can be written only if EN is ‘0’.
 */
#define DMA_FCR_FTH_POS		(0U)
#define DMA_FCR_FTH_MASK	((3UL) << DMA_FCR_FTH_POS)

/*
 * Direct mode disable
 * This bit is set and cleared by software. It can be set by hardware.
 * 
 * 	0: Direct mode enabled
 * 	1: Direct mode disabled
 * 
 * This bit is protected and can be written only if EN is ‘0’.
 * 
 * This bit is set by hardware if the memory-to-memory mode is selected (DIR bit in DMA_SxCR are “10”)
 * and the EN bit in the DMA_SxCR register is ‘1’ because the direct mode is not allowed in the memory-to-memory configuration.
 */
#define DMA_FCR_DMDIS_POS	(2U)
#define DMA_FCR_DMDIS_MASK	((1UL) << DMA_FCR_DMDIS_POS)

/*
 * FIFO status
 * These bits are read-only.
 * 	000: 0 < fifo_level < 1/4
 * 	001: 1/4 ≤ fifo_level < 1/2
 * 	010: 1/2 ≤ fifo_level < 3/4
 * 	011: 3/4 ≤ fifo_level < full
 * 	100: FIFO is empty
 * 	101: FIFO is full
 * 	others: no meaning
 * 
 * These bits are not relevant in the direct mode (DMDIS bit is zero).
 */
#define DMA_FCR_FS_POS		(3U)
#define DMA_FCR_FS_MASK		((7UL) << DMA_FCR_FS_POS)

/*
 * FIFO error interrupt enable
 * This bit is set and cleared by software.
 * 	0: FE interrupt disabled
 * 	1: FE interrupt enabled
 */
#define DMA_FCR_FEIE_POS	(7U)
#define DMA_FCR_FEIE_MASK	((1UL) << DMA_FCR_FEIE_POS)

/*++++++++++++++++++++++++++++++++++++++++++++++*/

