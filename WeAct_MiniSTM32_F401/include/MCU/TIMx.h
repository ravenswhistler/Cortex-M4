#ifndef TIMx_HEADER
#define TIMx_HEADER
#include "types.h"

//-----------Comman main features between all TIMx-----------//
//
//	- 16-bit (excl. TIM2 and TIM5 are 32-bit) up, down, up/down auto-reload counter. (TIM10 and TIM11 are auto-reload 16-bit only conter.)
//	- 16-bit programmable prescaler allowing dividing (also “on the fly”) the counter clock frequency either by any factor between 1 and 65536. (Can be changed "on the fly" for TIM9 to TIM11)
//	- Up to 4 (TIM9 has 2 channels, TIM10 and TIM11 has 1 channel) independent channels for:
//       	– Input Capture
//      	– Output Compare
//      	– PWM generation (Edge (only for TIM9 To TIM11) and Center-aligned Mode)
//      	– One-pulse mode output
//
//	- Synchronization circuit to control the timer with external signals and to interconnect several timers together. (excl. TIM10 and TIM11)
//	- Interrupt/DMA(DMA excl. TIM9 to TIM11) generation on the following events:
//      	– Update: counter overflow/underflow, counter initialization (by software(SW only TIM10 and TIM11) or internal(SW or internal only for TIM9)/external trigger)
//      	– Trigger event (counter start, stop, initialization or count by internal/external(external excl. TIM9) trigger) (excl. TIM10 and TIM11)
//      	– Input capture
//      	– Output compare
//      	– Break input (Only TIM1)
//
//	- Supports incremental (quadrature) encoder and hall-sensor circuitry for positioning purposes (incl. TIM1 to TIM5 only)
//	- Trigger input for external clock or cycle-by-cycle current management (incl. TIM1 to TIM5 only)
//

//-----------TIM1 specific features-----------//
//	- Complementary outputs with programmable dead-time
//	- Repetition counter to update the timer registers only after a given number of cycles of the counter.
//	- Break input to put the timer’s output signals in reset state or in a known state.

//APB1:
#define TIM2_BASE	(0x40000000U)
#define TIM3_BASE	(0x40000400U)
#define TIM4_BASE	(0x40000800U)
#define TIM5_BASE	(0x40000C00U)

//APB2:
#define TIM1_BASE	(0x40010000U)

#define TIM9_BASE	(0x40014000U)

#define TIM10_BASE	(0x40014400U)
#define TIM11_BASE	(0x40014800U)

typedef struct {

	_IO uint32_t CR1;
	_IO uint32_t CR2;
	_IO uint32_t SMCR;
	_IO uint32_t DIER;
	_IO uint32_t SR;
	_IO uint32_t EGR;
	_IO uint32_t CCMR1;		//Output Compare OR Input Capture Mode
	_IO uint32_t CCMR2;		//Output Compare OR Input Capture Mode
	_IO uint32_t CCER;
	_IO uint16_t CNT;
	_IO uint16_t __UNUSED_0;
	_IO uint16_t PSC;
	_IO uint16_t __UNUSED_1;
	_IO uint16_t ARR;
	_IO uint16_t __UNUSED_2;
	_IO uint8_t  RCR;
	_IO uint8_t  __UNUSED_3;
	_IO uint16_t __UNUSED_4;
	_IO uint16_t CCR1;
	_IO uint16_t __UNUSED_5;
	_IO uint16_t CCR2;
	_IO uint16_t __UNUSED_6;
	_IO uint16_t CCR3;
	_IO uint16_t __UNUSED_7;
	_IO uint16_t CCR4;
	_IO uint16_t __UNUSED_8;
	_IO uint16_t BDTR;
	_IO uint16_t __UNUSED_9;
	_IO uint32_t DCR;
	_IO uint32_t DMAR;
} TIM1_Type;

#define	TIM1	((TIM1_Type*)TIM1_BASE)


#if 0
typedef struct {

	_IO uint32_t CR1;
#if defined (TIM9_t) || defined (TIM10_t)|| defined (TIM11_t)
	_I uint32_t __UNUSED_0;
#else
	_IO uint32_t CR2;
#endif
	_IO uint32_t SMCR;
	_IO uint32_t DIER;
	_IO uint32_t SR;
	_IO uint32_t EGR;
	_IO uint32_t CCMR1;		//Output Compare OR Input Capture Mode
#if defined (TIM19_t) || defined (TIM10_t)|| defined (TIM11_t)
	_I uint32_t __UNUSED_1;
#else
	_IO uint32_t CCMR2;		//Output Compare OR Input Capture Mode
#endif
	_IO uint32_t CCER;
#if defined (TIM2_t) || defined (TIM5_t)
	_IO uint32_t CNT;
#else
	_IO uint16_t CNT;
	_I uint16_t __UNUSED_2;
#endif
	_IO uint32_t PSC;
	_IO uint32_t ARR;
#if defined (TIM1_t)
	_IO uint32_t RCR;
#else
	_IO uint32_t __UNUSED_3;
#endif
	_IO uint32_t CCR1;
#if defined (TIM10_t) || defined (TIM11_t)
	_I uint32_t __UNUSED_4[6];
#else
	_IO uint32_t CCR2;
#if defined (TIM9_t)
	_I uint32_t __UNUSED_5[5];
#else
		_IO uint32_t CCR3;
		_IO uint32_t CCR4;
#if defined (TIM1_t)
			_IO uint32_t BDTR;
#else
			_I uint32_t __UNUSED_6;
#endif
		_IO uint32_t DCR;
		_IO uint32_t DMAR;
#endif
#endif
#if defined (TIM2_t) || defined (TIM5_t) || defined (TIM10_t) || defined (TIM11_t)
		_IO uint32_t OR;
#endif
} TIMx_Type;

#endif

#if 0
//#define TIM1_t
//	#define	TIM1	((TIMx_Type*)TIM1_BASE)
//#undef TIM1_t

#define TIM2_t
	#define	TIM2	((TIMx_Type*)TIM2_BASE)
#undef TIM2_t

#define TIM3_t
	#define	TIM3	((TIMx_Type*)TIM3_BASE)
#undef TIM3_t

#define TIM4_t
	#define	TIM4	((TIMx_Type*)TIM4_BASE)
#undef TIM4_t

#define TIM5_t
	#define	TIM5	((TIMx_Type*)TIM5_BASE)
#undef TIM5_t

#define TIM9_t
	#define	TIM9	((TIMx_Type*)TIM9_BASE)
#undef TIM9_t

#define TIM10_t
	#define	TIM10	((TIMx_Type*)TIM10_BASE)
#undef TIM10_t

#define TIM11_t
	#define	TIM11	((TIMx_Type*)TIM11_BASE)
#undef TIM11_t

#endif

//ANY THING BELOW THIS LINE SHOUDN'T BE ACCESSED EITHER FOR READ OR WRITE BY ANY THING LESS THAN WORD-WIDE 32-BIT ACCESS
//
/*-------------------Control Reg 1-------------------*/

//CEN: Counter enable
//	0: Counter disabled
//	1: Counter enabled
//Note:
//	External clock, gated mode and encoder mode can work only if the CEN bit has been previously set by software.
//	However trigger mode can set the CEN bit automatically by hardware.
#define	TIMx_CR1_CEN_POS		(0U)
#define	TIMx_CR1_CEN_MASK		(1U << TIMx_CR1_CEN_POS)

//UDIS: Update disable
//	This bit is set and cleared by software to enable/disable UEV event generation.
//	0: UEV enabled. The Update (UEV) event is generated by one of the following events:
//		– Counter overflow/underflow
//		– Setting the UG bit
//		– Update generation through the slave mode controller
//	Buffered registers are then loaded with their preload values.
//
//	1: UEV disabled. The Update event is not generated, shadow registers keep their value (ARR, PSC, CCRx).
//	However the counter and the prescaler are reinitialized if the UG bit is set or if a hardware reset is received from the slave mode controller.
#define	TIMx_CR1_UDIS_POS		(1U)
#define	TIMx_CR1_UDIS_MASK		(1U << TIMx_CR1_UDIS_POS)

//URS: Update request source
//	This bit is set and cleared by software to select the UEV event sources.
//	0: Any of the following events generate an update interrupt or DMA request if enabled. These events can be:
//		– Counter overflow/underflow
//		– Setting the UG bit
//		– Update generation through the slave mode controller
//	
//	1: Only counter overflow/underflow generates an update interrupt or DMA request if enabled
#define	TIMx_CR1_URS_POS		(2U)
#define	TIMx_CR1_URS_MASK		(1U << TIMx_CR1_URS_POS)

//OPM: One pulse mode
//	0: Counter is not stopped at update event
//	1: Counter stops counting at the next update event (clearing the bit CEN)
#define	TIMx_CR1_OPM_POS		(3U)
#define	TIMx_CR1_OPM_MASK		(1U << TIMx_CR1_OPM_POS)

//DIR: Direction
//	0: Counter used as upcounter
//	1: Counter used as downcounter
//
//Note:
//	This bit is read only when the timer is configured in Center-aligned mode or Encoder mode.
#define	TIMx_CR1_DIR_POS		(4U)
#define	TIMx_CR1_DIR_MASK		(1U << TIMx_CR1_DIR_POS)

//CMS[1:0]: Center-aligned mode selection
//	00: Edge-aligned mode. The counter counts up or down depending on the direction bit (DIR).
//	
//	01: Center-aligned mode 1. The counter counts up and down alternatively.
//		Output compare interrupt flags of channels configured in output (CCxS=00 in TIMx_CCMRx register) are set only when the counter is counting down.
//	
//	10: Center-aligned mode 2. The counter counts up and down alternatively.
//		Output compare interrupt flags of channels configured in output (CCxS=00 in TIMx_CCMRx register) are set only when the counter is counting up.
//	
//	11: Center-aligned mode 3. The counter counts up and down alternatively.
//		Output compare interrupt flags of channels configured in output (CCxS=00 in TIMx_CCMRx register) are set both when the counter is counting up or down.
//
//Note:
//	It is not allowed to switch from edge-aligned mode to center-aligned mode as long as the counter is enabled (CEN=1)
#define	TIMx_CR1_CMS_POS		(5U)
#define	TIMx_CR1_CMS_MASK		(3U << TIMx_CR1_CMS_POS)

//ARPE: Auto-reload preload enable
//	0: TIMx_ARR register is not buffered
//	1: TIMx_ARR register is buffered
#define	TIMx_CR1_ARPE_POS		(7U)
#define	TIMx_CR1_ARPE_MASK		(1U << TIMx_CR1_ARPE_POS)

//CKD[1:0]: Clock division
//
//This bit-field indicates the division ratio between the timer clock (CK_INT) frequency and the dead-time and sampling clock (tDTS) used by the dead-time generators and the digital filters (ETR, TIx),
//	00: tDTS=tCK_INT
//	01: tDTS=2*tCK_INT
//	10: tDTS=4*tCK_INT
//	11: Reserved, do not program this value
#define	TIMx_CR1_CKDE_POS		(8U)
#define	TIMx_CR1_CKDE_MASK		(3U << TIMx_CR1_CKDE_POS)

/*+++++++++++++++++++++++++++++++++++++++++++++++++++*/

/*-------------------Control Reg 2-------------------*/
//CCPC: Capture/compare preloaded control
//	0: CCxE, CCxNE and OCxM bits are not preloaded
//	1: CCxE, CCxNE and OCxM bits are preloaded, after having been written, they are updated only when a commutation event (COM) occurs (COMG bit set or rising edge detected on TRGI, depending on the CCUS bit).
//Note:
//	This bit acts only on channels that have a complementary output.
#define	TIMx_CR2_CCPC_POS		(0U)
#define	TIMx_CR2_CCPC_MASK		(1U << TIMx_CR2_CCPC_POS)

//CCUS: Capture/compare control update selection
//	0: When capture/compare control bits are preloaded (CCPC=1), they are updated by setting the COMG bit only
//	1: When capture/compare control bits are preloaded (CCPC=1), they are updated by setting the COMG bit or when an rising edge occurs on TRGI
//Note:
//	This bit acts only on channels that have a complementary output.
#define	TIMx_CR2_CCUS_POS		(2U)
#define	TIMx_CR2_CCUS_MASK		(1U << TIMx_CR2_CCUS_POS)

//CCDS: Capture/compare DMA selection
//	0: CCx DMA request sent when CCx event occurs
//	1: CCx DMA requests sent when update event occurs
#define	TIMx_CR2_CCDS_POS		(3U)
#define	TIMx_CR2_CCDS_MASK		(1U << TIMx_CR2_CCDS_POS)

//MMS[2:0]: Master mode selection
//These bits allow to select the information to be sent in master mode to slave timers for synchronization (TRGO). The combination is as follows:
//	000: Reset - the UG bit from the TIMx_EGR register is used as trigger output (TRGO).
//		If the reset is generated by the trigger input (slave mode controller configured in reset mode) then the signal on TRGO is delayed compared to the actual reset.
//
//	001: Enable - the Counter Enable signal CNT_EN is used as trigger output (TRGO).
//		It is useful to start several timers at the same time or to control a window in which a slave timer is enable.
//		The Counter Enable signal is generated by a logic OR between CEN control bit and the trigger input when configured in gated mode.
//		When the Counter Enable signal is controlled by the trigger input, there is a delay on TRGO, except if the master/slave mode is selected (see the MSM bit description in TIMx_SMCR register).
//
//	010: Update - The update event is selected as trigger output (TRGO). For instance a master timer can then be used as a prescaler for a slave timer.
//
//	011: Compare Pulse - The trigger output send a positive pulse when the CC1IF flag is to be set (even if it was already high), as soon as a capture or a compare match occurred. (TRGO).
//
//	100: Compare - OC1REF signal is used as trigger output (TRGO)
//	101: Compare - OC2REF signal is used as trigger output (TRGO)
//	110: Compare - OC3REF signal is used as trigger output (TRGO)
//	111: Compare - OC4REF signal is used as trigger output (TRGO)
//
//Note:
//	The clock of the slave timer and ADC must be enabled prior to receiving events from the master timer, and must not be changed on-the-fly while triggers are received from the master timer.
#define	TIMx_CR2_MMS_POS		(4U)
#define	TIMx_CR2_MMS_MASK		(7U << TIMx_CR2_MMS_POS)

//TI1S: TI1 selection
//	0: The TIMx_CH1 pin is connected to TI1 input
//	1: The TIMx_CH1, CH2 and CH3 pins are connected to the TI1 input (XOR combination)
#define	TIMx_CR2_TI1S_POS		(7U)
#define	TIMx_CR2_TI1S_MASK		(1U << TIMx_CR2_TI1S_POS)

//OIS1: Output Idle state 1 (OC1 output)
//	0: OC1=0 (after a dead-time if OC1N is implemented) when MOE=0
//	1: OC1=1 (after a dead-time if OC1N is implemented) when MOE=0
//
//Note:
//	This bit can not be modified as long as LOCK level 1, 2 or 3 has been programmed (LOCK bits in TIMx_BDTR register).
#define	TIMx_CR2_OIS1_POS		(8U)
#define	TIMx_CR2_OIS1_MASK		(1U << TIMx_CR2_OIS1_POS)

//OIS1N: Output Idle state 1 (OC1N output)
//	0: OC1N=0 after a dead-time when MOE=0
//	1: OC1N=1 after a dead-time when MOE=0
//
//Note:
//	This bit can not be modified as long as LOCK level 1, 2 or 3 has been programmed (LOCK bits in TIMx_BDTR register).
#define	TIMx_CR2_OIS1N_POS		(9U)
#define	TIMx_CR2_OIS1N_MASK		(1U << TIMx_CR2_OIS1N_POS)


//OIS2: Output Idle state 2 (OC2 output) refer to OIS1 bit
#define	TIMx_CR2_OIS2_POS		(10U)
#define	TIMx_CR2_OIS2_MASK		(1U << TIMx_CR2_OIS2_POS)

//OIS2N: Output Idle state 2 (OC2N output) refer to OIS1N bit
#define	TIMx_CR2_OIS2N_POS		(11U)
#define	TIMx_CR2_OIS2N_MASK		(1U << TIMx_CR2_OIS2N_POS)

//OIS2: Output Idle state 3 (OC3 output) refer to OIS1 bit
#define	TIMx_CR2_OIS3_POS		(12U)
#define	TIMx_CR2_OIS3_MASK		(1U << TIMx_CR2_OIS3_POS)

//OIS2N: Output Idle state 3 (OC3N output) refer to OIS1N bit
#define	TIMx_CR2_OIS3N_POS		(13U)
#define	TIMx_CR2_OIS3N_MASK		(1U << TIMx_CR2_OIS3N_POS)

//OIS2: Output Idle state 4 (OC4 output) refer to OIS1 bit
#define	TIMx_CR2_OIS4_POS		(14U)
#define	TIMx_CR2_OIS4_MASK		(1U << TIMx_CR2_OIS4_POS)

/*+++++++++++++++++++++++++++++++++++++++++++++++++++*/

/*-------------------Slave mode control registe Reg-------------------*/
//SMS: Slave mode selection
//	When external signals are selected the active edge of the trigger signal (TRGI) is linked to the polarity selected on the external input (see Input Control register and Control Register description.
//
//	000: Slave mode disabled - if CEN = ‘1’ then the prescaler is clocked directly by the internal clock.
//
//	001: Encoder mode 1 - Counter counts up/down on TI2FP1 edge depending on TI1FP2 level.
//	010: Encoder mode 2 - Counter counts up/down on TI1FP2 edge depending on TI2FP1 level.
//	011: Encoder mode 3 - Counter counts up/down on both TI1FP1 and TI2FP2 edges depending on the level of the other input.
//
//	100: Reset Mode - Rising edge of the selected trigger input (TRGI) reinitializes the counter and generates an update of the registers.
//
//	101: Gated Mode - The counter clock is enabled when the trigger input (TRGI) is high. The counter stops (but is not reset) as soon as the trigger becomes low. Both start and stop of the counter are controlled.
//
//	110: Trigger Mode - The counter starts at a rising edge of the trigger TRGI (but it is not reset). Only the start of the counter is controlled.
//
//	111: External Clock Mode 1 - Rising edges of the selected trigger (TRGI) clock the counter.
//
//Note:
//	The gated mode must not be used if TI1F_ED is selected as the trigger input (TS=’100’). Indeed, TI1F_ED outputs 1 pulse for each transition on TI1F, whereas the gated mode checks the level of the trigger signal.
//
//The clock of the slave timer must be enabled prior to receiving events from the master timer, and must not be changed on-the-fly while triggers are received from the master timer.
#define	TIMx_SMCR_SMS_POS		(0U)
#define	TIMx_SMCR_SMS_MASK		(7U << TIMx_SMCR_SMS_POS)

//TS[2:0]: Trigger selection
//	This bit-field selects the trigger input to be used to synchronize the counter.
//
//	000: Internal Trigger 0 	(ITR0)
//	001: Internal Trigger 1 	(ITR1)
//	010: Internal Trigger 2 	(ITR2)
//	011: Internal Trigger 3 	(ITR3)
//	100: TI1 Edge Detector 		(TI1F_ED)
//	101: Filtered Timer Input 1 	(TI1FP1)
//	110: Filtered Timer Input 2 	(TI2FP2)
//	111: External Trigger input 	(ETRF)
//
//	|Slave TIM|	|ITR0 (TS = 000)|	|ITR1 (TS = 001)|	|ITR2 (TS = 010)|	|ITR3 (TS = 011)|
//	|TIM1	  |	|TIM5_TRGO	|	|TIM2_TRGO	|	|TIM3_TRGO      |       |TIM4_TRGO	|
//Note:
//	These bits must be changed only when they are not used (e.g. when SMS=000) to avoid wrong edge detections at the transition.
#define	TIMx_SMCR_TS_POS		(4U)
#define	TIMx_SMCR_TS_MASK		(7U << TIMx_SMCR_TS_POS)

//MSM: Master/slave mode
//	0: No action
//	1: The effect of an event on the trigger input (TRGI) is delayed to allow a perfect synchronization between the current timer and its slaves (through TRGO).
//
//	It is useful if we want to synchronize several timers on a single external event.
#define	TIMx_SMCR_MSM_POS		(7U)
#define	TIMx_SMCR_MSM_MASK		(1U << TIMx_SMCR_MSM_POS)

//ETF[3:0]: External trigger filter
//	This bit-field then defines the frequency used to sample ETRP signal and the length of the digital filter applied to ETRP.
//	The digital filter is made of an event counter in which N consecutive events are needed to validate a transition on the output:
//
//		0000: No filter, sampling is done at fDTS
//
//		0001: fSAMPLING= fCK_INT,	N=2
//		0010: fSAMPLING= fCK_INT,	N=4
//		0011: fSAMPLING= fCK_INT,	N=8
//
//		0100: fSAMPLING= fDTS/2,	N=6
//		0101: fSAMPLING= fDTS/2,	N=8
//
//		0110: fSAMPLING= fDTS/4,	N=6
//		0111: fSAMPLING= fDTS/4,	N=8
//
//		1000: fSAMPLING= fDTS/8,	N=6
//		1001: fSAMPLING= fDTS/8,	N=8
//
//		1010: fSAMPLING= fDTS/16,	N=5
//		1011: fSAMPLING= fDTS/16,	N=6
//		1100: fSAMPLING= fDTS/16,	N=8
//
//		1101: fSAMPLING= fDTS/32,	N=5
//		1110: fSAMPLING= fDTS/32,	N=6
//		1111: fSAMPLING= fDTS/32,	N=8
#define	TIMx_SMCR_ETF_POS		(8U)
#define	TIMx_SMCR_ETF_MASK		(0xFU << TIMx_SMCR_ETF_POS)

//ETPS[1:0]: External trigger prescaler
//	External trigger signal ETRP frequency must be at most 1/4 of TIMxCLK frequency.
//	A prescaler can be enabled to reduce ETRP frequency. It is useful when inputting fast external clocks.
//
//		00: Prescaler OFF
//		01: ETRP frequency divided by 2
//		10: ETRP frequency divided by 4
//		11: ETRP frequency divided by 8
//
#define	TIMx_SMCR_ETPS_POS		(12U)
#define	TIMx_SMCR_ETPS_MASK		(3U << TIMx_SMCR_ETPS_POS)

//ECE: External clock enable
//	This bit enables External clock mode 2.
//		0: External clock mode 2 disabled
//		1: External clock mode 2 enabled. The counter is clocked by any active edge on the ETRF signal.
//
//Note:
//	1: Setting the ECE bit has the same effect as selecting external clock mode 1 with TRGI connected to ETRF (SMS=111 and TS=111).
//
//	2: It is possible to simultaneously use external clock mode 2 with the following slave modes:
//		reset mode
//		gated mode
//		trigger mode.
//		Nevertheless, TRGI must not be connected to ETRF in this case (TS bits must not be 111).
//	3: If external clock mode 1 and external clock mode 2 are enabled at the same time, the external clock input is ETRF.
#define	TIMx_SMCR_ECE_POS		(14U)
#define	TIMx_SMCR_ECE_MASK		(1U << TIMx_SMCR_ECE_POS)

//ETP: External trigger polarity
//	This bit selects whether ETR or NOR(ETR) is used for trigger operations
//		0: ETR is non-inverted, active at high level or rising edge.
//		1: ETR is inverted, active at low level or falling edge.
#define	TIMx_SMCR_ETP_POS		(15U)
#define	TIMx_SMCR_ETP_MASK		(1U << TIMx_SMCR_ETP_POS)

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/*------------DMA/interrupt enable register------------*/

//UIE: Update interrupt enable
//	0: Update interrupt disabled
//	1: Update interrupt enabled
#define	TIMx_DIER_UIE_POS		(0U)
#define	TIMx_DIER_UIE_MASK		(1U << TIMx_DIER_UIE_POS)

//CCxIE: Capture/Compare x interrupt enable
//	0: CCx interrupt disabled
//	1: CCx interrupt enabled
//Where (x = 1, 2, 3, or 4)
#define	TIMx_DIER_CCxIE_POS		(1U)
#define	TIMx_DIER_CCxIE_MASK		(1U << TIMx_DIER_CCxIE_POS)

//#define	TIMx_DIER_CCxIE_POS(x)		(1U*(x%5))
//#define	TIMx_DIER_CCxIE_MASK(x)		(1U << TIMx_DIER_CCxIE_POS(x))

//COMIE: COM interrupt enable
//	0: COM interrupt disabled
//	1: COM interrupt enabled
#define	TIMx_DIER_COMIE_POS		(5U)
#define	TIMx_DIER_COMIE_MASK		(1U << TIMx_DIER_COMIE_POS)

//TIE: Trigger interrupt enable
//	0: Trigger interrupt disabled
//	1: Trigger interrupt enabled
#define	TIMx_DIER_TIE_POS		(6U)
#define	TIMx_DIER_TIE_MASK		(1U << TIMx_DIER_TIE_POS)

//BIE: Break interrupt enable
//	0: Break interrupt disabled
//	1: Break interrupt enabled
#define	TIMx_DIER_BIE_POS		(7U)
#define	TIMx_DIER_BIE_MASK		(1U << TIMx_DIER_BIE_POS)

//UDE: Update DMA request enable
//	0: Update DMA request disabled
//	1: Update DMA request enabled
#define	TIMx_DIER_UDE_POS		(8U)
#define	TIMx_DIER_UDE_MASK		(1U << TIMx_DIER_UDE_POS)

//CCxDE: Capture/Compare x DMA request enable
//	0: CCx DMA request disabled
//	1: CCx DMA request enabled
#define	TIMx_DIER_CCxDE_POS(x)		(9U + ( (x-1) % 3) )		//TODO: Error Prone
#define	TIMx_DIER_CCxDE_MASK(x)		(1U << TIMx_DIER_CCxDE_POS(x))

//COMDE: COM DMA request enable
//	0: COM DMA request disabled
//	1: COM DMA request enabled
#define	TIMx_DIER_COMDE_POS		(13U)
#define	TIMx_DIER_COMDE_MASK		(1U << TIMx_DIER_COMDE_POS)

//TDE: Trigger DMA request enable
//	0: Trigger DMA request disabled
//	1: Trigger DMA request enabled
#define	TIMx_DIER_TDE_POS		(14U)
#define	TIMx_DIER_TDE_MASK		(1U << TIMx_DIER_TDE_POS)

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/*------------Status register------------*/
//UIF: Update interrupt flag
//	This bit is set by hardware on an update event. It is cleared by software.
//
//	0: No update occurred.
//	1: Update interrupt pending. This bit is set by hardware when the registers are updated:
//
//		– At overflow or underflow regarding the repetition counter value (update if repetition counter = 0) and if the UDIS=0 in the TIMx_CR1 register.
//		– When CNT is reinitialized by software using the UG bit in TIMx_EGR register, if URS=0 and UDIS=0 in the TIMx_CR1 register.
//		– When CNT is reinitialized by a trigger event (refer to TIM1 slave mode control register (TIMx_SMCR)), if URS=0 and UDIS=0 in the TIMx_CR1 register.
#define	TIMx_SR_UIF_POS			(0U)
#define	TIMx_SR_UIF_MASK		(1U << TIMx_SR_UIF_POS)

//CCxIF: Capture/Compare x interrupt flag
//          If channel CCx is configured as output:
//	  	This flag is set by hardware when the counter matches the compare value, with some exception in center-aligned mode (refer to the CMS bits in the TIMx_CRx register description). It is cleared by software.
//
//		0: No match.
//          	1: The content of the counter TIMx_CNT matches the content of the TIMx_CCRx register.
//
//          	When the contents of TIMx_CCRx are greater than the contents of TIMx_ARR, the CCxIF bit goes high on the counter overflow (in upcounting and up/down-counting modes) or underflow (in downcounting mode)
//
//          If channel CCx is configured as input:
//          	This bit is set by hardware on a capture. It is cleared by software or by reading the TIMx_CCRx register.
//
//          	0: No input capture occurred
//          	1: The counter value has been captured in TIMx_CCR1 register (An edge has been detected on IC1 which matches the selected polarity)
#define	TIMx_SR_CCxIF_POS(x)		(1U * (x%5))			//TODO: Error Prone
#define	TIMx_SR_CCxIF_MASK(x)		(1U << TIMx_SR_CCxIF_POS(x))

//COMIF: COM interrupt flag
//	This flag is set by hardware on COM event (when Capture/compare Control bits - CCxE, CCxNE, OCxM - have been updated). It is cleared by software.
//
//		0: No COM event occurred.
//		1: COM interrupt pending.
#define	TIMx_SR_COMIF_POS		(5U)
#define	TIMx_SR_COMIF_MASK		(1U << TIMx_SR_COMIF_POS)

//TIF: Trigger interrupt flag
//	This flag is set by hardware on trigger event (active edge detected on TRGI input when the slave mode controller is enabled in all modes but gated mode.
//	It is set when the counter starts or stops when gated mode is selected.It is cleared by software.
//
//            0: No trigger event occurred.
//            1: Trigger interrupt pending.
#define	TIMx_SR_TIF_POS			(6U)
#define	TIMx_SR_TIF_MASK		(1U << TIMx_SR_TIF_POS)


//BIF: Break interrupt flag
//	This flag is set by hardware as soon as the break input goes active. It can be cleared by software if the break input is not active.
//		0: No break event occurred.
//		1: An active level has been detected on the break input.
#define	TIMx_SR_BIF_POS			(7U)
#define	TIMx_SR_BIF_MASK		(1U << TIMx_SR_BIF_POS)


//CCxOF: Capture/Compare x overcapture flag
//	This flag is set by hardware only when the corresponding channel is configured in input capture mode. It is cleared by software by writing it to ‘0’.
//		0: No overcapture has been detected.
//		1: The counter value has been captured in TIMx_CCRx register while CCxIF flag was already set
#define	TIMx_SR_CCxOF_POS(x)		(9U + (x))			//TODO: Error Prone
#define	TIMx_SR_CCxOF_MASK(x)		(1U << TIMx_SR_CCxOF_POS(x))

/*+++++++++++++++++++++++++++++++++++++++*/

/*------------Event Generation Register------------*/
//UG: Update generation
//	This bit can be set by software, it is automatically cleared by hardware.
//
//		0: No action
//		1: Reinitialize the counter and generates an update of the registers. Note that the prescaler counter is cleared too (anyway the prescaler ratio is not affected).
//		   The counter is cleared if the center-aligned mode is selected or if DIR=0 (upcounting), else it takes the auto-reload value (TIMx_ARR) if DIR=1 (downcounting).
#define	TIMx_EGR_UG_POS			(0U)
#define	TIMx_EGR_UG_MASK		(1U << TIMx_EGR_UG_POS)

//CCxG: Capture/Compare x generation
//	This bit is set by software in order to generate an event, it is automatically cleared by hardware.
//	
//		0: No action
//		1: A capture/compare event is generated on channel x:
//          		If channel CCx is configured as output:
//          			CCxIF flag is set, Corresponding interrupt or DMA request is sent if enabled.
//
//          		If channel CCx is configured as input:
//          			The current value of the counter is captured in TIMx_CCRx register. The CCxIF flag is set, the corresponding interrupt or DMA request is sent if enabled.
//				The CCxOF flag is set if the CCxIF flag was already high.
#define	TIMx_EGR_CCxG_POS(x)		(1U*(x%5))			//TODO:Error Prone
#define	TIMx_EGR_CCxG_MASK(x)		(1U << TIMx_EGR_CCxG_POS(x))

//COMG: Capture/Compare control update generation
//	This bit can be set by software, it is automatically cleared by hardware
//		0: No action
//		1: When CCPC bit is set, it allows to update CCxE, CCxNE and OCxM bits
//Note:
//	This bit acts only on channels having a complementary output.
#define	TIMx_EGR_COMG_POS		(5U)
#define	TIMx_EGR_COMG_MASK		(1U << TIMx_EGR_COMG_POS)

//TG: Trigger generation
//	This bit is set by software in order to generate an event, it is automatically cleared by hardware.
//		0: No action
//		1: The TIF flag is set in TIMx_SR register. Related interrupt or DMA transfer can occur if enabled.
#define	TIMx_EGR_TG_POS			(6U)
#define	TIMx_EGR_TG_MASK		(1U << TIMx_EGR_TG_POS)

//BG: Break generation
//	This bit is set by software in order to generate an event, it is automatically cleared by hardware.
//          	0: No action
//		1: A break event is generated. MOE bit is cleared and BIF flag is set. Related interrupt or DMA transfer can occur if enabled.
#define	TIMx_EGR_BG_POS			(7U)
#define	TIMx_EGR_BG_MASK		(1U << TIMx_EGR_BG_POS)

/*+++++++++++++++++++++++++++++++++++++++++++++++++*/

/*------------Capture/Compare Mode Register 1 & 2------------*/
//The channels can be used in input (capture mode) or in output (compare mode).
//The direction of a channel is defined by configuring the corresponding CCxS bits.
//All the other bits of this register have a different function in input and in output mode.
//For a given bit, OCxx describes its function when the channel is configured in output, ICxx describes its function when the channel is configured in input.

//Output compare mode:

//CC1S: Capture/Compare 1 selection
//	This bit-field defines the direction of the channel (input/output) as well as the used input.
//
//		00: CC1 channel is configured as output
//		01: CC1 channel is configured as input, IC1 is mapped on TI1
//		10: CC1 channel is configured as input, IC1 is mapped on TI2
//		11: CC1 channel is configured as input, IC1 is mapped on TRC. This mode is working only if an internal trigger input is selected through TS bit (TIMx_SMCR register)
//Note:
//	CC1S bits are writable only when the channel is OFF (CC1E = ‘0’ in TIMx_CCER).
#define	TIMx_CCMRx_CC1S_POS		(0U)
#define	TIMx_CCMRx_CC1S_MASK		(3U << TIMx_CCMRx_CC1S_POS)

//CC2S[1:0]: Capture/Compare 2 selection
//	This bit-field defines the direction of the channel (input/output) as well as the used input.
//
//		00: CC2 channel is configured as output
//		01: CC2 channel is configured as input, IC2 is mapped on TI2
//		10: CC2 channel is configured as input, IC2 is mapped on TI1
//		11: CC2 channel is configured as input, IC2 is mapped on TRC.
//			This mode is working only if an internal trigger input is selected through the TS bit (TIMx_SMCR register)
//Note:
//	CC2S bits are writable only when the channel is OFF (CC2E = ‘0’ in TIMx_CCER).
#define	TIMx_CCMRx_CC2S_POS		(8U)
#define	TIMx_CCMRx_CC2S_MASK		(3U << TIMx_CCMRx_CC2S_POS)

//OC1FE: Output Compare 1 fast enable
//	This bit is used to accelerate the effect of an event on the trigger in input on the CC output.
//	
//		0: CC1 behaves normally depending on counter and CCR1 values even when the trigger is ON. The minimum delay to activate CC1 output when an edge occurs on the trigger input is 5 clock cycles.
//          	1: An active edge on the trigger input acts like a compare match on CC1 output.
//		   Then, OC is set to the compare level independently from the result of the comparison. Delay to sample the trigger input and to activate CC1 output is reduced to 3 clock cycles.
//		   OCFE acts only if the channel is configured in PWM1 or PWM2 mode.
#define	TIMx_CCMRx_OC1FE_POS		(2U)
#define	TIMx_CCMRx_OC1FE_MASK		(1U << TIMx_CCMRx_OC1FE_POS)

#define	TIMx_CCMRx_OC2FE_POS		(10U)
#define	TIMx_CCMRx_OC2FE_MASK		(1U << TIMx_CCMRx_OC2FE_POS)

//OC1PE: Output Compare 1 preload enable
//	0: Preload register on TIMx_CCR1 disabled. TIMx_CCR1 can be written at anytime, the new value is taken in account immediately.
//	1: Preload register on TIMx_CCR1 enabled. Read/Write operations access the preload register. TIMx_CCR1 preload value is loaded in the active register at each update event.
//
//Note:
//	1: These bits can not be modified as long as LOCK level 3 has been programmed (LOCK bits in TIMx_BDTR register) and CC1S=’00’ (the channel is configured in output).
//	2: The PWM mode can be used without validating the preload register only in one pulse mode (OPM bit set in TIMx_CR1 register). Else the behavior is not guaranteed.
#define	TIMx_CCMRx_OC1PE_POS		(3U)
#define	TIMx_CCMRx_OC1PE_MASK		(1U << TIMx_CCMRx_OC1PE_POS)

#define	TIMx_CCMRx_OC2PE_POS		(11U)
#define	TIMx_CCMRx_OC2PE_MASK		(1U << TIMx_CCMRx_OC2PE_POS)

//OC1M: Output Compare 1 mode
//	These bits define the behavior of the output reference signal OC1REF from which OC1 and OC1N are derived. OC1REF is active high whereas OC1 and OC1N active level depends on CC1P and CC1NP bits.
//
//		000: Frozen - The comparison between the output compare register TIMx_CCR1 and the counter TIMx_CNT has no effect on the outputs.(this mode is used to generate a timing base).
//
//		001: Set channel 1 to active level on match. OC1REF signal is forced high when the counter TIMx_CNT matches the capture/compare register 1 (TIMx_CCR1).
//
//		010: Set channel 1 to inactive level on match. OC1REF signal is forced low when the counter TIMx_CNT matches the capture/compare register 1 (TIMx_CCR1).
//
//		011: Toggle - OC1REF toggles when TIMx_CNT=TIMx_CCR1.
//
//		100: Force inactive level - OC1REF is forced low.
//
//		101: Force active level - OC1REF is forced high.
//
//		110: PWM mode 1 :
//			In upcounting, channel 1 is active as long as TIMx_CNT<TIMx_CCR1 else inactive.
//			In downcounting, channel 1 is inactive (OC1REF=‘0’) as long as TIMx_CNT>TIMx_CCR1 else active (OC1REF=’1’).
//
//		111: PWM mode 2 :
//			In upcounting, channel 1 is inactive as long as TIMx_CNT<TIMx_CCR1 else active.
//			In downcounting, channel 1 is active as long as TIMx_CNT>TIMx_CCR1 else inactive.
//
//Note:
//	1: These bits can not be modified as long as LOCK level 3 has been programmed (LOCK bits in TIMx_BDTR register) and CC1S=’00’ (the channel is configured in output).
//	2: In PWM mode 1 or 2, the OCREF level changes only when the result of the comparison changes or when the output compare mode switches from “frozen” mode to “PWM” mode.
//	3: On channels having a complementary output, this bit field is preloaded.
//		If the CCPC bit is set in the TIMx_CR2 register then the OC1M active bits take the new value from the preloaded bits only when a COM event is generated.
#define	TIMx_CCMRx_OC1M_POS		(4U)
#define	TIMx_CCMRx_OC1M_MASK		(7U << TIMx_CCMRx_OC1M_POS)

#define	TIMx_CCMRx_OC2M_POS		(12U)
#define	TIMx_CCMRx_OC2M_MASK		(7U << TIMx_CCMRx_OC2M_POS)

//OC1CE: Output Compare 1 clear enable
//	0: OC1Ref is not affected by the ETRF Input
//	1: OC1Ref is cleared as soon as a High level is detected on ETRF input
#define	TIMx_CCMRx_OC1CE_POS		(7U)
#define	TIMx_CCMRx_OC1CE_MASK		(1U << TIMx_CCMRx_OC1CE_POS)

#define	TIMx_CCMRx_OC2CE_POS		(15U)
#define	TIMx_CCMRx_OC2CE_MASK		(1U << TIMx_CCMRx_OC2CE_POS)

//TODO: Input Capture mode:

#if 0

//#define	TIMx_CCMR1__POS		(1U)
//#define	TIMx_CCMR1__MASK	(1U << TIMx_CCMR1__POS)

#endif
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/*------------Capture/Compare Mode Register 2------------*/
//Refer to CCMR1 defined Masks
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/*------------Capture/Compare Enable Register------------*/
//CC1E: Capture/Compare 1 output enable
//	CC1 channel configured as output:
//		0: Off - OC1 is not active. OC1 level is then function of MOE, OSSI, OSSR, OIS1, OIS1N and CC1NE bits.
//          	1: On - OC1 signal is output on the corresponding output pin depending on MOE, OSSI, OSSR, OIS1, OIS1N and CC1NE bits.
//
//	CC1 channel configured as input: This bit determines if a capture of the counter value can actually be done into the input capture/compare register 1 (TIMx_CCR1) or not.
//		0: Capture disabled.
//		1: Capture enabled.
//
//Note:
//	On channels having a complementary output, this bit is preloaded.
//	If the CCPC bit is set in the TIMx_CR2 register then the CC1E active bit takes the new value from the preloaded bit only when a Commutation event is generated.
#define	TIMx_CCER_CC1E_POS		(0U)
#define	TIMx_CCER_CC1E_MASK		(1U << TIMx_CCER_CC1E_POS)

#define	TIMx_CCER_CCxE_POS(x)		((4*(x-1))U)
#define	TIMx_CCER_CCxE_MASK(x)		(1U << TIMx_CCER_CCxE_POS(x))

//CC1P: Capture/Compare 1 output polarity
//
//	CC1 channel configured as output:
//		0: OC1 active high
//		1: OC1 active low
//
//	CC1 channel configured as input: CC1NP/CC1P bits select the active polarity of TI1FP1 and TI2FP1 for trigger or capture operations.
//		00: non-inverted/rising edge
//			The circuit is sensitive to TIxFP1 rising edge (capture or trigger operations in reset, external clock or trigger mode), TIxFP1 is not inverted (trigger operation in gated mode or encoder mode).
//
//		01: inverted/falling edge
//			The circuit is sensitive to TIxFP1 falling edge (capture or trigger operations in reset, external clock or trigger mode), TIxFP1 is inverted (trigger operation in gated mode or encoder mode).
//
//		10: reserved, do not use this configuration.
//
//		11: non-inverted/both edges
//			The circuit is sensitive to both TIxFP1 rising and falling edges (capture or trigger operations in reset, external clock or trigger mode), TIxFP1 is not inverted (trigger operation in gated mode).
//			This configuration must not be used in encoder mode.
//Note:
//	On channels having a complementary output, this bit is preloaded. If the CCPC bit is set in the TIMx_CR2 register then the CC1P active bit takes the new value from the preloaded bit only when a Commutation event is generated.
//Note:
//	This bit is not writable as soon as LOCK level 2 or 3 has been programmed (LOCK bits in TIMx_BDTR register).
#define	TIMx_CCER_CC1P_POS		(1U)
#define	TIMx_CCER_CC1P_MASK		(1U << TIMx_CCER_CC1P_POS)

#define	TIMx_CCER_CCxP_POS(x)		(1+(4*(x-1))U)
#define	TIMx_CCER_CCxP_MASK(x)		(1U << TIMx_CCER_CCxP_POS(x))
//CC1NE: Capture/Compare 1 complementary output enable
//
//	0: Off - OC1N is not active. OC1N level is then function of MOE, OSSI, OSSR, OIS1, OIS1N and CC1E bits.
//	1: On - OC1N signal is output on the corresponding output pin depending on MOE, OSSI, OSSR, OIS1, OIS1N and CC1E bits.
//Note:
//	On channels having a complementary output, this bit is preloaded. If the CCPC bit is set in the TIMx_CR2 register then the CC1NE active bit takes the new value from the bit only when a Commutation event is generated.
#define	TIMx_CCER_CC1NE_POS		(2U)
#define	TIMx_CCER_CC1NE_MASK		(1U << TIMx_CCER_CC1NE_POS)

#define	TIMx_CCER_CCxNE_POS(x)		(2+(4*((x-1)%3))U)
#define	TIMx_CCER_CCxNE_MASK(x)		(1U << TIMx_CCER_CCxNE_POS(x))
//CC1NP: Capture/Compare 1 complementary output polarity
//	CC1 channel configured as output:
//		0: OC1N active high.
//		1: OC1N active low.
//
//	CC1 channel configured as input: This bit is used in conjunction with CC1P to define the polarity of TI1FP1 and TI2FP1. Refer to CC1P description.
//
//Note:
//	On channels having a complementary output, this bit is preloaded. If the CCPC bit is set in the TIMx_CR2 register then the CC1NP active bit takes the new value from the preloaded bit only when a Commutation event is generated.
//Note:
//	This bit is not writable as soon as LOCK level 2 or 3 has been programmed (LOCK bits in TIMx_BDTR register) and CC1S=”00” (the channel is configured in output).
#define	TIMx_CCER_CC1NP_POS		(3U)
#define	TIMx_CCER_CC1NP_MASK		(1U << TIMx_CCER_CC1NP_POS)

#define	TIMx_CCER_CCxNP_POS(x)		(3+(4*((x-1)%3))U)
#define	TIMx_CCER_CCxNP_MASK(x)		(1U << TIMx_CCER_CCxNP_POS(x))

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/*------------Counter Register------------*/

#define	TIMx_CNT_POS		(0U)
#define	TIMx_CNT_MASK		(0xFFFFU << TIMx_CNT_POS)

/*++++++++++++++++++++++++++++++++++++++++*/

/*------------Prescaler Register------------*/

//The counter clock frequency (CK_CNT) is equal to fCK_PSC / (PSC[15:0] + 1).
//PSC contains the value to be loaded in the active prescaler register at each update event
//(including when the counter is cleared through UG bit of TIMx_EGR register or through trigger controller when configured in “reset mode”).
#define	TIMx_PSC_POS		(0U)
#define	TIMx_PSC_MASK		(0xFFFFU << TIMx_PSC_POS)

/*++++++++++++++++++++++++++++++++++++++++++*/


/*------------Auto-Reload Register------------*/

//ARR is the value to be loaded in the actual auto-reload register.
//Refer to Time-base unit for more details about ARR update and behavior.
//The counter is blocked while the auto-reload value is null.
#define	TIMx_ARR_POS		(0U)
#define	TIMx_ARR_MASK		(0xFFFFU << TIMx_ARR_POS)

/*++++++++++++++++++++++++++++++++++++++++++++*/


/*------------Repetition Counter Register------------*/
//Repetition counter value
//	These bits allow the user to set-up the update rate of the compare registers
//		(i.e. periodic transfers from preload to active registers) when preload registers are enable, as well as the update interrupt generation rate, if this interrupt is enable.
//	Each time the REP_CNT related downcounter reaches zero, an update event is generated and it restarts counting from REP value.
//	As REP_CNT is reloaded with REP value only at the repetition update event U_RC, any write to the TIMx_RCR register is not taken in account until the next repetition update event.
//	It means in PWM mode (REP+1) corresponds to:
//		– the number of PWM periods in edge-aligned mode
//		– the number of half PWM period in center-aligned mode.
#define	TIMx_RCR_REP_POS		(0U)
#define	TIMx_RCR_REP_MASK		(0xFFU << TIMx_RCR_REP_POS)

/*+++++++++++++++++++++++++++++++++++++++++++++++++++*/

/*------------Capture/Compare Register------------*/
//If channel CCx[i.e. 1, 2, 3, or 4] is configured as output:
//	CCRx[i.e. 1, 2, 3, or 4] is the value to be loaded in the actual capture/compare x[i.e. 1, 2, 3, or 4] register (preload value).
//	It is loaded permanently if the preload feature is not selected in the TIMx_CCMRx[i.e. 1, 2, 3, or 4] register (bit OCx[i.e. 1, 2, 3, or 4]PE).
//	Else the preload value is copied in the active capture/compare x[i.e. 1, 2, 3, or 4] register when an update event occurs.
//
//The active capture/compare register contains the value to be compared to the counter TIMx_CNT and signaled on OCx[i.e. 1, 2, 3, or 4] output.
//
//If channel CCx[i.e. 1, 2, 3, or 4] is configured as input:
//	CCRx[i.e. 1, 2, 3, or 4] is the counter value transferred by the last input capture x[i.e. 1, 2, 3, or 4] event (ICx[i.e. 1, 2, 3, or 4]). The TIMx_CCRx[i.e. 1, 2, 3, or 4] register is read-only and cannot be programmed.
#define	TIM1_CCRx_POS		(0U)
#define	TIM1_CCRx_MASK		(0xFFFFU << TIM1_CCRx_POS)

/*++++++++++++++++++++++++++++++++++++++++++++++++*/

/*------------Break and dead-time Register------------*/

//DTG[7:0]: Dead-time generator setup
//	This bit-field defines the duration of the dead-time inserted between the complementary outputs. DT correspond to this duration.
//		DTG[7:5]=0xx => DT=DTG[7:0]x tdtg with tdtg=tDTS.
//		DTG[7:5]=10x => DT=(64+DTG[5:0])xtdtg with Tdtg=2xtDTS.
//		DTG[7:5]=110 => DT=(32+DTG[4:0])xtdtg with Tdtg=8xtDTS.
//		DTG[7:5]=111 => DT=(32+DTG[4:0])xtdtg with Tdtg=16xtDTS.
//
//	Example if TDTS=125ns (8MHz), dead-time possible values are:
//		0 to 15875 ns by 125 ns steps,
//		16 us to 31750 ns by 250 ns steps,
//		32 us to 63us by 1 us steps,
//		64 us to 126 us by 2 us steps
//
//Note:
//	This bit-field can not be modified as long as LOCK level 1, 2 or 3 has been programmed (LOCK bits in TIMx_BDTR register).
#define	TIMx_BDTR_DTG_POS			(0U)
#define	TIMx_BDTR_DTG_MASK			(0xFFU << TIMx_BDTR_DTG_POS)

//LOCK[1:0]: Lock configuration
//	These bits offer a write protection against software errors.
//
//		00: LOCK OFF - No bit is write protected.
//		01: LOCK Level 1 = DTG bits in TIMx_BDTR register, OISx and OISxN bits in TIMx_CR2 register and BKE/BKP/AOE bits in TIMx_BDTR register can no longer be written.
//		10: LOCK Level 2 = LOCK Level 1 + CC Polarity bits (CCxP/CCxNP bits in TIMx_CCER register, as long as the related channel is configured in output through the CCxS bits)
//		    as well as OSSR and OSSI bits can no longer be written.
//		11: LOCK Level 3 = LOCK Level 2 + CC Control bits (OCxM and OCxPE bits in TIMx_CCMRx registers, as long as the related channel is configured in output through the CCxS bits) can no longer be written.
//
//Note:
//	The LOCK bits can be written only once after the reset. Once the TIMx_BDTR register has been written, their content is frozen until the next reset.
#define	TIMx_BDTR_LOCK_POS		(8U)
#define	TIMx_BDTR_LOCK_MASK		(3U << TIMx_BDTR_LOCK_POS)

//OSSI: Off-state selection for Idle mode
//	This bit is used when MOE=0 on channels configured as outputs.
//	See OC/OCN enable description for more details (TIM1 capture/compare enable register (TIMx_CCER)).
//
//		0: When inactive, OC/OCN outputs are disabled (OC/OCN enable output signal=0).
//		1: When inactive, OC/OCN outputs are forced first with their idle level as soon as CCxE=1 or CCxNE=1. (OC/OCN enable output signal=1)
//Note:
//	This bit can not be modified as soon as the LOCK level 2 has been programmed (LOCK bits in TIMx_BDTR register).
#define	TIMx_BDTR_OSSI_POS		(10U)
#define	TIMx_BDTR_OSSI_MASK		(1U << TIMx_BDTR_OSSI_POS)

//OSSR: Off-state selection for Run mode
//	This bit is used when MOE=1 on channels having a complementary output which are configured as outputs. OSSR is not implemented if no complementary output is implemented in the timer.
//	See OC/OCN enable description for more details (TIM1 capture/compare enable register (TIMx_CCER)).
//
//		0: When inactive, OC/OCN outputs are disabled (OC/OCN enable output signal=0).
//		1: When inactive, OC/OCN outputs are enabled with their inactive level as soon as CCxE=1 or CCxNE=1. Then, OC/OCN enable output signal=1
//Note:
//	This bit can not be modified as soon as the LOCK level 2 has been programmed (LOCK bits in TIMx_BDTR register).
#define	TIMx_BDTR_OSSR_POS		(11U)
#define	TIMx_BDTR_OSSR_MASK		(1U << TIMx_BDTR_OSSR_POS)

//BKE: Break enable
//	0: Break inputs (BRK and CSS clock failure event) disabled
//	1: Break inputs (BRK and CSS clock failure event) enabled
//Note:
//	This bit cannot be modified when LOCK level 1 has been programmed (LOCK bits in TIMx_BDTR register).
//Note:
//	Any write operation to this bit takes a delay of 1 APB clock cycle to become effective.
#define	TIMx_BDTR_BKE_POS		(12U)
#define	TIMx_BDTR_BKE_MASK		(1U << TIMx_BDTR_BKE_POS)

//BKP: Break polarity
//	0: Break input BRK is active low
//	1: Break input BRK is active high
//Note:
//	This bit can not be modified as long as LOCK level 1 has been programmed (LOCK bits in TIMx_BDTR register).
//Note:
//	Any write operation to this bit takes a delay of 1 APB clock cycle to become effective. Bit 12
#define	TIMx_BDTR_BKP_POS		(13U)
#define	TIMx_BDTR_BKP_MASK		(1U << TIMx_BDTR_BKP_POS)

//AOE: Automatic output enable
//	0: MOE can be set only by software
//	1: MOE can be set by software or automatically at the next update event (if the break input is not be active)
//Note:
//	This bit can not be modified as long as LOCK level 1 has been programmed (LOCK bits in TIMx_BDTR register).
#define	TIMx_BDTR_AOE_POS		(14U)
#define	TIMx_BDTR_AOE_MASK		(1U << TIMx_BDTR_AOE_POS)

//MOE: Main output enable
//	This bit is cleared asynchronously by hardware as soon as the break input is active. It is set by software or automatically depending on the AOE bit.
//	It is acting only on the channels which are configured in output.
//
//		0: OC and OCN outputs are disabled or forced to idle state.
//		1: OC and OCN outputs are enabled if their respective enable bits are set (CCxE, CCxNE in TIMx_CCER register).
//		See OC/OCN enable description for more details (Section 12.4.9: TIM1 capture/compare enable register (TIMx_CCER)).
#define	TIMx_BDTR_MOE_POS		(15U)
#define	TIMx_BDTR_MOE_MASK		(1U << TIMx_BDTR_MOE_POS)

/*++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#if 0
#define	TIMx_DCR__POS		(1U)
#define	TIMx_DCR__MASK		(1U << TIMx_DCR__POS)

#define	TIMx_DMAR__POS		(1U)
#define	TIMx_DMAR__MASK		(1U << TIMx_DMAR__POS)
#endif

#endif //TIMx_HEADER
