/*
 * Receive.c
 *
 * Created: 10.02.2022 20:19:21
 *  Author: Martin
 
 
  Credits: This code is an modified version of the code made/provided by Richard Anthony in ERTP.


 */ 


#include "Receive.h"
#include "Serial.h"
#include "Input.h"


void InitializeReceive(){
	Initialize_HW_Interrupts(); // Initialize
	InitializeTimer1(); //Initialize
		
	startbit = 0x00;
	bit = 0x00;
	toggle = 0x00;
	ReceiveByte = 0x00;
	
	
	DDRC = 0xFF; // 8 LEDS connected to this port. Shows received byte. 
	PORTC = 0x00; 
	
	DDRB = 0xFF; // Used to analyze Timer1 period to check that it samples the input signal correctly. 
	PORTB = 0x00;
	
	DDRG = 0xFF;
	PORTG = 0x00;
	
}

void Initialize_HW_Interrupts() // Set up INT0
{
	EICRA = 0b00000011;		// External Interrupt Control Register A: INT 3,2 not used, Interrupt Sense INT0 rising-edge triggered
	EICRB = 0b00000000;		// INT7 ... 4 not used
	
	EIMSK = 0b00000001;		// External Interrupt Mask Register: Enable INT0
	EIFR = 0b00000001;		// External Interrupt Flag Register: Clear INT0 interrupt flag (in case a spurious interrupt has occurred during chip startup)
}


ISR(INT0_vect) // Hardware_INT0_Handler (Interrupt Handler for INT0)
{
	
	// According to the data sheet the pulse duration needs to be greater than 50ns for it to be sensed.
	// Should not be a problem at 2400 baud rate.
	
	if (startbit == 0){ //Initial value
		TIMSK1 = 0b00000010;	// Enable bit 1 OCIE1A to Use 'Output Compare A Match' Interrupt, i.e. generate an interrupt					
		startbit = 1; // Change global variable
		

		/*
		// Empirical results shows that the timer needs to be delayed with x micro seconds.
		// Software delay can be used for tuning the system.
		for(int i = 0; i < 10; i++)
		{
			for(int j = 0; j < 10; j++);
		}
		*/
		
		//TCNT1 = 0b00000000; // Initially tried to reset the counter while running, but like the datasheet stated, this is not recommended.
							  // The timer used to much time to stabilize. 
	}

}


void InitializeTimer1()		// Configure to generate an interrupt after a 420 microsecond interval
{
	TCCR1A = 0b00000000;	// Normal port operation (OC1A, OC1B, OC1C), Clear Timer on 'Compare Match' (CTC) waveform mode)
	TCCR1B = 0b00001011;	// CTC waveform mode, use prescaler 64
	TCCR1C = 0b00000000;

	// For 1 MHz clock (with 64 prescaler) to achieve a 640 microsecond interval:
	// Need to count 640 clock cycles
	// So actually need to count to (640 / 64 =) 10 decimal, = 0A Hex
	// After empirical testing with oscilloscope the value 9 decimal is closer to 640 microsecond interval. 
	// This is probably because I am measuring at slightly different times than it is being executed.
	// The Timer1 ISR has quite many instructions that take up clock cycles that causes a delay. 
	
	OCR1AH = 0x00; // Output Compare Registers (16 bit) OCR1BH and OCR1BL
	OCR1AL = 0x09;

	// Timer/Counter count/value registers (16 bit) TCNT1H and TCNT1L. Initialized to zero.
	TCNT1H = 0b00000000;
	TCNT1L = 0b00000000; 
	
}

ISR(TIMER1_COMPA_vect) // TIMER1_CompareA_Handler (Interrupt Handler for Timer 1)
{
	
	if (startbit == 1){ // Checks if INT0 has received the start bit
		
		 unsigned char Sample = 0x00; // Creates a temporarely sampling variable
			Sample = PING; // Read the digital value
			if (Sample & 0b00100000){ // Check if incoming bit is 1
				
				switch(bit){
					case 0:
					ReceiveByte |= 0b00000001; // Force bit 0=1. Leave other bits unchanged.
					break;
					case 1:
					ReceiveByte |= 0b00000010; // Force bit 1=1. Leave other bits unchanged.
					break;
					case 2:
					ReceiveByte |= 0b00000100; // Force bit 2=1. Leave other bits unchanged.
					break;
					case 3:
					ReceiveByte |= 0b00001000; // Force bit 3=1. Leave other bits unchanged.
					break;
					case 4:
					ReceiveByte |= 0b00010000; // Force bit 4=1. Leave other bits unchanged.
					break;
					case 5:
					ReceiveByte |= 0b00100000; // Force bit 5=1. Leave other bits unchanged.
					break;
					case 6:
					ReceiveByte |= 0b01000000; // Force bit 6=1. Leave other bits unchanged.
					break;
					case 7:
					ReceiveByte |= 0b10000000; // Force bit 7=1. Leave other bits unchanged.
					break;
					case 8: // Stop bit
					startbit = 0;
					bit = 0;
					PORTC = ~ReceiveByte; // Write the received byte to the 8 LEDs. 
										// First compliment because the original byte transmitted by USART1 TX was inverted		 
					break;
				}
				bit++;
			}
		}
	

	// Code used to test if the timer period is correct. This allows for seeing when this ISR is executed on an oscilloscope
	// and comparing the incoming bit stream with the sampling signal. However, this takes place after the code above
	// is executed, and will therefore be delayed by some factor. Moving this code to the top of the ISR and comparing can
	//give an indication of the delay time.
	
	if (toggle == 0){
		PORTB = 0b00000100;
		toggle = 1;
	}
	else if (toggle == 1)
	{
		PORTB = 0b00000000;
		toggle = 0;
	}
	
	
	}
