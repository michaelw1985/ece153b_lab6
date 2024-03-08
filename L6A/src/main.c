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
	UART2_Init();
	
	while(1) {
		LED_Toggle();
		startTimer();
		uint32_t CRCinitial = 0xFFFFFFFF;
		// compute CRC
		for (x in DataBuffer) {
			CrcSoftwareFunc(CRCinitial, x, 0x04C11DB7);
			//these lines below were og outside the for loop
			uint32_t time = endTimer();
			if (value == uwExpectedCRCValue) {
				LED_Toggle();
				exit;
			}
			printf("%u", time);
			delay(1000);
		}
		
	}
}
