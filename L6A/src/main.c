/*
 * ECE 153B
 *
 * Name(s):
 * Section:
 * Lab: 6A
 */

#include "stm32l476xx.h"
#include "SysClock.h"
#include "SysTimer.h"
#include "LED.h"
#include "CRC.h"
#include "UART.h"
#include <stdio.h>

/* Expected CRC Value */
#define uwExpectedCRCValue 0x5A60861E

static volatile uint32_t Software_ComputedCRC;

int main(void) {
	
	// Switch System Clock = 80 MHz
	System_Clock_Init(); 
	// TODO initialize modules
	SysTick_Init();
	LED_Init();
	UART2_GPIO_Init();
	UART2_Init();
	USART_Init(USART2);
	printf("connected");
	
	while(1) {
		LED_Toggle();
		startTimer();
		Software_ComputedCRC = INITIAL_CRC_VALUE;
		// compute CRC
		for (int i=0; i < 512; i++) {
			Software_ComputedCRC = CrcSoftwareFunc(Software_ComputedCRC, DataBuffer[i], POLYNOME);			
		}
		uint32_t time = endTimer();
		if (Software_ComputedCRC != uwExpectedCRCValue) {
			LED_Off();
			break;
		}
		printf("%d \n", time);
		delay(1000);
	}
}