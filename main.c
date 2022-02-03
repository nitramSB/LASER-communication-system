/*
 * LaserCom.c
 *
 * Created: 02.02.2022 08:00:14
 * Author : Martin
 
 First part of the Laser communication link project. This program modulates a LASER connected to PortK bit 0 and receives the modulated
 signal on a solar panel connected to External Interrupt 0 (INT0). The ISR then increments a counter and displays the binary value
 on an 8 bit LED array connected to PortC. 
 
 */ 

#include <avr/io.h>
#define F_CPU 1000000UL // Assumes 1MHz clock speed // Set to 8000000UL or 16000000UL if your uC has a 8MHz or 16MHz clock speed.
#include <util/delay.h>
#include <avr/interrupt.h>


 unsigned char CountPulse; //Count variable


void InitializeGeneral();
void Initialize_HW_Interrupts();
void DisplayLED();
void ToggleLASER();
void InitializeTimer0();



int main(void)
{
	
	CountPulse = 0x00;
	InitializeGeneral();
	InitializeTimer0();

	Initialize_HW_Interrupts();
	
    while (1)
    {
		
		
	}
	
	
}

void InitializeGeneral()
{
	DDRC = 0xFF;			// Configure PortC direction for output (LEDs)
	PORTC = 0x00;		// Initial pull-down configuration to avoid floating value/voltage.
	
	DDRK = 0b00000001; // Configure PortK bit 0 for LASER modulation
	PORTK = 0b00000000; // LASER initially turned off
	
	sei(); // Set Status Register (SREG) enable bit
}

void InitializeTimer0()		// Configure Timer0 (8 bit) to generate an interrupt that toggles the LASER at ~30Hz.
{
	TCCR0A = 0b00000000;	// Timer/Counter Control Register A: Initializing register with default values (0s). 
	TCCR0B = 0b00000011;	// Timer/Counter Control Register B: Initializing the register with prescaler 64 (xxxxx011). This results in (64/1000000)*256 = 16.3ms delay between interrupts.
							// This results in a frequency ~30 Hz which still makes it possible to see the laser flicker. Nice to be able to see the difference between solid ON and high frequency. 
	
		// WGM = Waveform Generation Mode
		// The Output Compare Unit can be used to generate interrupts at some given time. Using the Output Compare to
		//generate waveforms in Normal mode is not recommended, since this will occupy too much of the CPU time.

	
	TIMSK0 = 0b00000001;		// Timer/Counter Interrupt Mask Register:  Overflow Interrupt Enabled. 
	
}

ISR(TIMER0_OVF_vect) // TIMER0_Overflow_Handler (Interrupt Handler for Timer 0)
{	// Shift LED BAR left
	
	ToggleLASER();
}



void Initialize_HW_Interrupts()
{
	EICRA = 0b00000011;		// External Interrupt Control Register A: INT 3,2 not used, Interrupt Sense INT0 rising-edge triggered
	EICRB = 0b00000000;		// INT7 ... 4 not used
	
	EIMSK = 0b00000001;		// External Interrupt Mask Register: Enable INT0
	EIFR = 0b00000001;		// External Interrupt Flag Register: Clear INT0 interrupt flag (in case a spurious interrupt has occurred during chip startup)
}

ISR(INT0_vect) // Hardware_INT0_Handler (Interrupt Handler for INT0)
{
	
	// The pulse duration needs to be greater than 50ns for it to be sensed.
	
	DisplayLED();				// Clear the display
	//TCCR1B = 0b00001101;		// Start the timer (CTC and Prescaler 1024)
}





void ToggleLASER(){
	
	unsigned char temp;
	temp = PINK;			// (Can actually read the port value even when its set as output)
	if(temp & 0b00000001)	// Bitwise version of AND - Check if bit 0 is currently set '1'
	{
		temp &= 0b11111110;	// Currently set, so force it to '0' without changing other bits
	}
	else
	{
		temp |= 0b00000001;	// Currently cleared, so force it to '1' without changing other bits
	}
	PORTK = temp;
	
}


void DisplayLED()
{
	
	PORTC = CountPulse;
	
	if (CountPulse == 255){
		//
	}
	else{
		
			CountPulse++;


	}
	
}




