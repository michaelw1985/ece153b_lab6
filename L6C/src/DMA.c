/*
 * ECE 153B
 *
 * Name(s):
 * Section:
 * Lab: 6C
 */
 
#include "DMA.h"
#include "CRC.h"
#include "SysTimer.h"

void DMA_Init(void) {
	RCC->AHB1ENR |= RCC_AHB1ENR_DMA1EN;
	delay(20); //swapped from while loop

	// 3. Disable the channel
	DMA1_Channel6->CCR &= ~DMA_CCR_EN;

	// 4. Set Memory-to-memory mode
	DMA1_Channel6->CCR |= DMA_CCR_MEM2MEM;

	// 5. Set channel priority to high (10)
	DMA1_Channel6->CCR &= ~DMA_CCR_PL_0;
	DMA1_Channel6->CCR |= DMA_CCR_PL_1;
	
	// 6. Set peripheral size to 32-bit (10)
	DMA1_Channel6->CCR &= ~DMA_CCR_PSIZE_0;
	DMA1_Channel6->CCR |= DMA_CCR_PSIZE_1;

	// 7. Set memory size to 32-bit (10)
	DMA1_Channel6->CCR &= ~DMA_CCR_MSIZE_0;
	DMA1_Channel6->CCR |= DMA_CCR_MSIZE_1;

	// 8. Disable peripheral increment mode
	DMA1_Channel6->CCR &= ~DMA_CCR_PINC;

	// 9. Enable memory increment mode
	DMA1_Channel6->CCR |= DMA_CCR_MINC;

	// 10. Disable circular mode
	DMA1_Channel6->CCR &= ~DMA_CCR_CIRC;

	// 11. Set data transfer direction to Memory-to-Peripheral
	DMA1_Channel6->CCR |= DMA_CCR_DIR;

	// 12. Set the data source to data buffer provided in CRC.h
	DMA1_Channel6->CMAR =(uint32_t)DataBuffer;

	// 13. Set the data destination to the data register of the CRC block
	DMA1_Channel6->CPAR =(uint32_t) &CRC->DR;

	// Then we need to setup the DMA interrupts:
	// 14. Disable half transfer interrupt
	DMA1_Channel6->CCR &= ~DMA_CCR_HTIE;

	// 15. Disable transfer error interrupt
	DMA1_Channel6->CCR &= ~DMA_CCR_TEIE;

	// 16. Enable transfer complete interrupt
	DMA1_Channel6->CCR |= DMA_CCR_TCIE;

	// 17. Set interrupt priority to 0 in NVIC
	NVIC_SetPriority(DMA1_Channel6_IRQn, 0);

	// 18. Enable interrupt in NVIC
	NVIC_EnableIRQ(DMA1_Channel6_IRQn);
}

void DMA1_Channel6_IRQHandler(void){ 
	// 	1. Clear NVIC interrupt flag
	NVIC_ClearPendingIRQ(DMA1_Channel6_IRQn);

	// 2. Check Transfer Complete interrupt flag. If it occurs, clear the flag and mark computation
	// as completed by calling computationComplete.
	if (DMA1_Channel6->CCR & DMA_CCR_TCIE) {
		DMA1->IFCR |= DMA_IFCR_CTCIF6;
		completeCRC(CRC->DR);
	}

	// 3. Clear global DMA interrupt flag.
	DMA1->IFCR |= DMA_IFCR_CGIF6;
}

