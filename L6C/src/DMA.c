/*
 * ECE 153B
 *
 * Name(s):
 * Section:
 * Lab: 6C
 */
 
#include "DMA.h"
#include "CRC.h"

void DMA_Init(void) {
	RCC->AHB1ENR |= RCC_AHB1ENR_DMA1EN;
	delay(20);

	// 3. Disable the channel
	DMA->CCR6 &= ~DMA_CCR_EN;

	// 4. Set Memory-to-memory mode
	DMA->CCR6 |= DMA_CCR_MEM2MEM;

	// 5. Set channel priority to high (10)
	DMA->CCR6 &= ~DMA_CCR_PL_0;
	DMA->CCR6 |= DMA_CCR_PL_1;
	
	// 6. Set peripheral size to 32-bit (10)
	DMA->CCR6 &= ~DMA_CCR_PSIZE_0;
	DMA->CCR6 |= DMA_CCR_PSIZE_1;

	// 7. Set memory size to 32-bit (10)
	DMA->CCR6 &= ~DMA_CCR_MSIZE_0;
	DMA->CCR6 |= DMA_CCR_MSIZE_1;

	// 8. Disable peripheral increment mode
	DMA->CCR6 &= ~DMA_CCR_PINC;

	// 9. Enable memory increment mode
	DMA->CCR6 |= DMA_CCR_MINC;

	// 10. Disable circular mode
	DMA->CCR6 &= ~DMA_CCR_CIRC;

	// 11. Set data transfer direction to Memory-to-Peripheral
	DMA->CCR6 &= ~DMA_CCR_DIR;

	// 12. Set the data source to data buffer provided in CRC.h
	DMA->CPAR6 = &DataBuffer; //TODO: DC

	// 13. Set the data destination to the data register of the CRC block
	DMA->CMAR6 = CRC_DR_DR; //TODO: DC

	// Then we need to setup the DMA interrupts:
	// 14. Disable half transfer interrupt
	DMA->ISR &= ~DMA_ISR_HTIF6;

	// 15. Disable transfer error interrupt
	DMA->ISR &= ~DMA_ISR_TEIF6;

	// 16. Enable transfer complete interrupt
	DMA->ISR |= DMA_ISR_TCIF6;

	// 17. Set interrupt priority to 0 in NVIC
	NVIC_SetPriority(DMA1_Stream1_IRQn);

	// 18. Enable interrupt in NVIC
	NVIC_EnableIRT(DMA1_Stream1_IRQn):
}

void DMA1_Channel6_IRQHandler(void){ 
	
	
}

