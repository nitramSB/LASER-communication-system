/*
 * Common.c
 *
 * Created: 09.02.2022 12:01:05
 *  Author: Martin
 */ 

#include "Common.h"

void InitializeCommon(){
	
	CountPulse = 0;
	DDRC = 0xFF;			// Configure PortC direction for output (LEDs)
	PORTC = 0x00;		// Initial pull-down configuration to avoid floating value/voltage.
	
}
void DisplayLED(unsigned char Byte)
{
	
	PORTC = Byte;
	/*
	if (CountPulse == 255){
		// Do nothing
	}
	else{
		CountPulse++;
	}
	*/
	
}

void EnableInterrupts()
{
	sei();		// Enable interrupts at global level set Global Interrupt Enable (I) bit
}

