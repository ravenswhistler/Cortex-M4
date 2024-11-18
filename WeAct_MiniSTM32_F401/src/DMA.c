#include "API.h"


uint32_t Get_DMA_Data_Count(DMA_Type *dma, DMA_STREAMx stream)
{
	while(IS_DMAn_Sx_ENABLED(dma, stream));
	return (0xFFFFUL - GET_DMAn_Sx_NDT(dma, stream));
}

void DMA_Transfer(DMA_Type *dma,			\
		  DMA_STREAMx stream, 			\
		  uint32_t src, 			\
		  uint32_t dest, 			\
		  uint32_t count, 			\
		  DMA_STREAM_CHANNEL channel, 		\
		  DMA_STREAM_PRI priority, 		\
		  uint32_t direct_mode, 		\
		  DMA_FIFO_THRSHLD fifo_threshold, 	\
		  DMA_DIRx direction, 			\
		  DMA_FLOW_CONTROLER flow_controller, 	\
		  DMA_DATA_SIZE data_sz, 		\
		  uint32_t pincrement, 			\
		  uint32_t mincrement )
{

//The following sequence should be followed to configure a DMA stream x (where x is the stream number):
//
//	1. If the stream is enabled, disable it by resetting the EN bit in the DMA_SxCR register, then read this bit in order to confirm that there is no ongoing stream operation.
//	   Writing this bit to 0 is not immediately effective since it is actually written to 0 once all the current transfers have finished.
//	   When the EN bit is read as 0, this means that the stream is ready to be configured.
//	   It is therefore necessary to wait for the EN bit to be cleared before starting any stream configuration.
//	   All the stream dedicated bits set in the status register (DMA_LISR and DMA_HISR) from the previous data block DMA transfer should be cleared before the stream can be re-enabled.


		(dma == DMA2) ? ENABLE_DMA2_CLK() : ENABLE_DMA1_CLK();
		DISABLE_DMAn_Sx(dma, stream);
		while(IS_DMAn_Sx_ENABLED(dma, stream));

//	2. Set the peripheral port register address in the DMA_SxPAR register. The data will be moved from/ to this address to/ from the peripheral port after the peripheral event.
//	3. Set the memory address in the DMA_SxMA0R register (and in the DMA_SxMA1R register in the case of a double buffer mode). The data will be written to or read from this memory after the peripheral event.

		SET_DMAn_Sx_PERIPHERAL_ADD(dma, stream, src);
		SET_DMAn_Sx_MMEM0_ADD(dma, stream, dest);

//	4. Configure the total number of data items to be transferred in the DMA_SxNDTR register. After each peripheral event or each beat of the burst, this value is decremented.

		SET_DMAn_Sx_NDT(dma, stream, count);

//	5. Select the DMA channel (request) using CHSEL[2:0] in the DMA_SxCR register.

		SET_DMAn_Sx_CHANNEL(dma, stream, channel);

//	6. If the peripheral is intended to be the flow controller and if it supports this feature, set the PFCTRL bit in the DMA_SxCR register.

		SET_DMAn_Sx_FLOW_CNTRL(dma, stream, flow_controller);

//	7. Configure the stream priority using the PL[1:0] bits in the DMA_SxCR register.

		SET_DMAn_Sx_PRI(dma, stream, priority);

//	8. Configure the FIFO usage (enable or disable, threshold in transmission and reception)

		if(direct_mode > 0)
		{
			ENABLE_DMAn_Sx_DIR_MODE(dma, stream);
		}
		else
		{
			ENABLE_DMAn_Sx_FIFO_MODE(dma, stream);
			SET_DMAn_Sx_FIFO_THRSHLD(dma, stream, fifo_threshold);
		}

//	9. Configure the data transfer direction,

		if(direction == DMA_MEM_TO_MEM)
		{
			DMA_Mem_To_Mem(stream, src, dest, data_sz, channel, priority, fifo_threshold, data_sz);
			return;
		}
		else
		{
			SET_DMAn_Sx_DIR(dma, stream, direction);
		}

//	   peripheral and memory incremented/fixed mode,

		if(pincrement > 0) { ENABLE_DMAn_Sx_P_INCRMNT(dma, stream); }
		if(mincrement > 0) { ENABLE_DMAn_Sx_M_INCRMNT(dma, stream); }
//
//	   single or burst transactions,

		SET_DMAn_Sx_P_BURST(dma, stream, DMA_BURST_SINGLE_TRNSF);
		SET_DMAn_Sx_M_BURST(dma, stream, DMA_BURST_SINGLE_TRNSF);

//	   peripheral and memory data widths,

		SET_DMAn_Sx_PSIZE(dma, stream, data_sz);
		SET_DMAn_Sx_MSIZE(dma, stream, data_sz);

//	   Circular mode,
		
		//DIABLED in MEM To MEM mode
		//The Circular mode is forbidden in peripheral flow controller mode
		//DISABLE_DMAn_Sx_CIRC(dma, stream);

//	   Double buffer mode,

		DISABLE_DMAn_Sx_DBLBUF(dma, stream);

//	   interrupts after half and/or full transfer,

		dma->LIFCR = 0xFFFFFFFF;
		dma->HIFCR = 0xFFFFFFFF;

		ENABLE_DMAn_Sx_TRNSF_HLF_INT(dma, stream);
		ENABLE_DMAn_Sx_TRNSF_CMPLT_INT(dma, stream);

//	   and/or errors in the DMA_SxCR register.
		
		(direct_mode > 0) ? ENABLE_DMAn_Sx_DIR_ERR_INT(dma, stream) : ENABLE_DMAn_Sx_FIFO_ERR_INT(dma, stream);

		ENABLE_DMAn_Sx_TRNSF_ERR_INT(dma, stream);

		

//	10. Activate the stream by setting the EN bit in the DMA_SxCR register.

		ENABLE_DMAn_Sx(dma, stream);


//	As soon as the stream is enabled, it can serve any DMA request from the peripheral connected to the stream.
//
//Once half the data have been transferred on the AHB destination port, the half-transfer flag (HTIF) is set and an interrupt is generated if the half-transfer interrupt enable bit (HTIE) is set.
//At the end of the transfer, the transfer complete flag (TCIF) is set and an interrupt is generated if the transfer complete interrupt enable bit (TCIE) is set.
//
//Warning:
//	To switch off a peripheral connected to a DMA stream request, it is mandatory to, first, switch off the DMA stream to which the peripheral is connected, then to wait for EN bit = 0.
//	Only then can the peripheral be safely disabled.

		return;
}

void DMA_Mem_To_Mem(DMA_STREAMx stream, 		\
		    uint32_t src, 			\
		    uint32_t dest, 			\
		    uint32_t count, 			\
		    DMA_STREAM_CHANNEL channel, 	\
		    DMA_STREAM_PRI priority, 		\
		    DMA_FIFO_THRSHLD fifo_threshold, 	\
		    DMA_DATA_SIZE data_sz )
{

//The following sequence should be followed to configure a DMA stream x (where x is the stream number):
//
//	1. If the stream is enabled, disable it by resetting the EN bit in the DMA_SxCR register, then read this bit in order to confirm that there is no ongoing stream operation.
//	   Writing this bit to 0 is not immediately effective since it is actually written to 0 once all the current transfers have finished.
//	   When the EN bit is read as 0, this means that the stream is ready to be configured.
//	   It is therefore necessary to wait for the EN bit to be cleared before starting any stream configuration.
//	   All the stream dedicated bits set in the status register (DMA_LISR and DMA_HISR) from the previous data block DMA transfer should be cleared before the stream can be re-enabled.


		ENABLE_DMA2_CLK();
		DISABLE_DMAn_Sx(DMA2, stream);
		while(IS_DMAn_Sx_ENABLED(DMA2, stream));

//	2. Set the peripheral port register address in the DMA_SxPAR register. The data will be moved from/ to this address to/ from the peripheral port after the peripheral event.
//	3. Set the memory address in the DMA_SxMA0R register (and in the DMA_SxMA1R register in the case of a double buffer mode). The data will be written to or read from this memory after the peripheral event.

		SET_DMAn_Sx_PERIPHERAL_ADD(DMA2, stream, src);
		SET_DMAn_Sx_MMEM0_ADD(DMA2, stream, dest);

//	4. Configure the total number of data items to be transferred in the DMA_SxNDTR register. After each peripheral event or each beat of the burst, this value is decremented.

		SET_DMAn_Sx_NDT(DMA2, stream, count);

//	5. Select the DMA channel (request) using CHSEL[2:0] in the DMA_SxCR register.

		SET_DMAn_Sx_CHANNEL(DMA2, stream, channel);

//	6. If the peripheral is intended to be the flow controller and if it supports this feature, set the PFCTRL bit in the DMA_SxCR register.
//	7. Configure the stream priority using the PL[1:0] bits in the DMA_SxCR register.

		SET_DMAn_Sx_PRI(DMA2, stream, priority);

//	8. Configure the FIFO usage (enable or disable, threshold in transmission and reception)
		ENABLE_DMAn_Sx_FIFO_MODE(DMA2, stream);
		SET_DMAn_Sx_FIFO_THRSHLD(DMA2, stream, fifo_threshold);

//	9. Configure the data transfer direction,

		SET_DMAn_Sx_DIR(DMA2, stream, DMA_MEM_TO_MEM);

//	   peripheral and memory incremented/fixed mode,

		ENABLE_DMAn_Sx_P_INCRMNT(DMA2, stream);
		ENABLE_DMAn_Sx_M_INCRMNT(DMA2, stream);
//
//	   single or burst transactions,

		SET_DMAn_Sx_P_BURST(DMA2, stream, DMA_BURST_SINGLE_TRNSF);
		SET_DMAn_Sx_M_BURST(DMA2, stream, DMA_BURST_SINGLE_TRNSF);

//	   peripheral and memory data widths,

		SET_DMAn_Sx_PSIZE(DMA2, stream, data_sz);
		SET_DMAn_Sx_MSIZE(DMA2, stream, data_sz);

//	   Circular mode,
		
		//DIABLED in MEM To MEM mode
		//DISABLE_DMAn_Sx_CIRC(DMA2, stream);

//	   Double buffer mode,

		DISABLE_DMAn_Sx_DBLBUF(DMA2, stream);

//	   interrupts after half and/or full transfer,
		DMA2->LIFCR = 0xFFFFFFFF;
		DMA2->HIFCR = 0xFFFFFFFF;

		ENABLE_DMAn_Sx_TRNSF_HLF_INT(DMA2, stream);
		ENABLE_DMAn_Sx_TRNSF_CMPLT_INT(DMA2, stream);

//	   and/or errors in the DMA_SxCR register.
		
		ENABLE_DMAn_Sx_TRNSF_ERR_INT(DMA2, stream);
		ENABLE_DMAn_Sx_FIFO_ERR_INT(DMA2, stream);


//	10. Activate the stream by setting the EN bit in the DMA_SxCR register.

		ENABLE_DMAn_Sx(DMA2, stream);


//	As soon as the stream is enabled, it can serve any DMA request from the peripheral connected to the stream.
//
//Once half the data have been transferred on the AHB destination port, the half-transfer flag (HTIF) is set and an interrupt is generated if the half-transfer interrupt enable bit (HTIE) is set.
//At the end of the transfer, the transfer complete flag (TCIF) is set and an interrupt is generated if the transfer complete interrupt enable bit (TCIE) is set.
//
//Warning:
//	To switch off a peripheral connected to a DMA stream request, it is mandatory to, first, switch off the DMA stream to which the peripheral is connected, then to wait for EN bit = 0.
//	Only then can the peripheral be safely disabled.

	return;
}
