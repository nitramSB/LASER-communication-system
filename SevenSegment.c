/*
 * SevenSegment.c
 *
 * Created: 09.02.2022 10:00:36
 *  Author: Martin
 
 Credits: This code is an modified version of the code made/provided by Richard Anthony in ERTP.

 */ 

#include "SevenSegment.h"


void InitializeSevenSegment()
{
	DDRA = 0xFF;			// Set port B direction OUTPUT (Seven Segment display - segment select)
	PORTA = 0x00;			// Active HIGH,		Set all LED segments initially off

	
	DDRH = 0b01111000;			// Set port H direction OUTPUT (Seven Segment display - digit select)
	PORTH = 0b01111000;		// Active LOW bits {3,4,5,6},		Set all LED digits initially off
	
	//g_eSegment = Rightmost_LSD;
	//g_iCount = 0;
	KeyValue = 0;
	SetSevenSegmentCharacterPatternsInArray();
}

/*

void InitialiseTimer0_InterlaceInterval_1ms()   // Generate an interrupt after a 1 millisecond interval
{
	TCCR0A = 0b00000010;	// Normal port operation (OC0A, OC0B), CTC waveform generation
	TCCR0B = 0b00000101;	// CTC waveform generation, Use 1024 prescaler
	
	// For 1 MHz clock (with 1024 prescaler) Compare Match Interrupt needs to occur after counting to 1
	// (because already divided by 1024)
	// So interrupt occurs after 1024 * 1 / 1000000 = 0.001 seconds
	OCR0A = 1;	// 1000Hz interlace
	//OCR0A = 250;	// 4Hz slow interlace for visual confirmation / testing
	TCNT0 = 0;		// Timer/Counter count initialised to zero

	TIMSK0 = 0b00000010;		// Use Compare Match 'A' Interrupt
}



ISR(TIMER0_COMPA_vect) // TIMER0 Compare Match Handler (Interrupt Handler for Timer 0)
{	// Provides the 4-digit interlace control (display sequence is right LSD  to  left MSD)
	// Displays value with fixed precision in format DD.DD
	unsigned char uDisplayDigitValue;
	unsigned char uDisplayPattern;
	// Display the four segments, in sequence - the interleaving must be fast enough to trick the eye
	switch(g_eSegment) {
		case Rightmost_LSD:
		// Calculate the individual DECIMAL digit value for display - LSD
		uDisplayDigitValue = g_iCount % 10;
		// Look up how to display the required character
		uDisplayPattern = g_CharacterArray[uDisplayDigitValue];
		PORTH = 0b11110111;	// Select Rightmost (LSD) digit
		PORTC = uDisplayPattern;
		g_eSegment = Center_Right;
		break;
		case Center_Right:
		// Calculate the individual DECIMAL digit value for display - 2nd digit from right
		uDisplayDigitValue = (g_iCount % 100) / 10;
		// Look up how to display the required character
		uDisplayPattern = g_CharacterArray[uDisplayDigitValue];
		PORTH = 0b11101111;	// Select Center Right digit
		PORTC = uDisplayPattern;
		g_eSegment = Center_Left;
		break;
		case Center_Left:
		// Calculate the individual DECIMAL digit value for display - 3rd digit from right
		uDisplayDigitValue = (g_iCount % 1000) / 100;
		// Look up how to display the required character
		uDisplayPattern = g_CharacterArray[uDisplayDigitValue] + DecimalPoint;  // Turn on decimal point
		PORTH = 0b11011111;	// Select Center Left digit
		PORTC = uDisplayPattern;
		g_eSegment = Leftmost_MSD;
		break;
		case Leftmost_MSD:
		// Calculate the individual DECIMAL digit value for display - leftmost digit
		uDisplayDigitValue = (g_iCount % 10000) / 1000;
		// Look up how to display the required character
		uDisplayPattern = g_CharacterArray[uDisplayDigitValue];
		PORTH = 0b10111111;	// Select Leftmost (MSD) digit
		PORTC = uDisplayPattern;
		g_eSegment = Rightmost_LSD;
		break;
	}
}

void InitialiseTimer1_CountIncrement_200ms()   // Generate an interrupt after a 200ms interval
{
	TCCR1A = 0b00000000;	// Normal port operation (OC1A, OC1B, OC1C), Clear Timer on 'Compare Match' (CTC) waveform mode)
	TCCR1B = 0b00001101;	// CTC waveform mode, use prescaler 1024
	TCCR1C = 0b00000000;
	
	// For 1 MHz clock (with 1024 prescaler) to achieve a 200ms interval:
	// Need to count 0.2 million clock cycles (but already divided by 1024)
	// So actually need to count to (200000 / 1024 =) 195 decimal
	OCR1A = 195; // Comprises Output Compare Registers (16 bit) OCR1AH and OCR1AL

	TCNT1 = 0;	// Comprises Timer/Counter count/value registers (16 bit) TCNT1H and TCNT1L
	TIMSK1 = 0b00000010;	// bit 1 OCIE1A		Use 'Output Compare A Match' Interrupt, i.e. generate an interrupt
	// when the timer reaches the set value (in the OCR1A registers)
}

ISR(TIMER1_COMPA_vect) // TIMER1_CompareA_Handler (Interrupt Handler for Timer 1)
{	// Increment the demonstration-display count
	g_iCount++;
	if(9999 < g_iCount)
	{
		g_iCount = 0;
	}
}

*/



void SetSevenSegmentCharacterPatternsInArray()
{	// The pin-to-segment, and pin-to-digit mapping below relates to a quite common configuration of 4-digit common cathode
	// seven-segment display. However, there are a great many actual devices available and therefore you need to check the
	// specific datasheet for the device you are using, prior to connecting.
	
	// Seven Segment LED map (segments numbered A-G + Decimal point) mapped as follows
	// Segment name		Atmel Port A position	Physical appearance position	Connection pin on module
	// A				port bit 0				Top Center						11
	// B				port bit 1				Top Right						7
	// C				port bit 2				Bottom Right					4
	// D				port bit 3				Bottom Center					2
	// E				port bit 4				Bottom Left						1
	// F				port bit 5				Top Left						10
	// G				port bit 6				Middle Center					5
	// DP				port bit 7				Decimal point					3

	// Seven Segment LED    Digit selector indexing mapped as follows
	// Digit name		Atmel Port H position	Physical appearance position	Connection pin on module
	// 0				port bit 3				Rightmost_LSD					6
	// 1				port bit 4				Center_Right					8
	// 2				port bit 5				Center_Left						9
	// 3				port bit 6				Leftmost_MSD					12

	g_CharacterArray[0] = 0b00111111;		// character code for '0'
	g_CharacterArray[1] = 0b00000110;		// character code for '1'
	g_CharacterArray[2] = 0b01011011;		// character code for '2'
	g_CharacterArray[3] = 0b01001111;		// character code for '3'
	g_CharacterArray[4] = 0b01100110;		// character code for '4'
	g_CharacterArray[5] = 0b01101101;		// character code for '5'
	g_CharacterArray[6] = 0b01111101;		// character code for '6'
	g_CharacterArray[7] = 0b00000111;		// character code for '7'
	g_CharacterArray[8] = 0b01111111;		// character code for '8'
	g_CharacterArray[9] = 0b01101111;		// character code for '9'
	g_CharacterArray[10] = 0b01110111;	// character code for 'A'
	g_CharacterArray[11] = 0b01111100;	// character code for 'B'
	g_CharacterArray[12] = 0b00111001;	// character code for 'C'
	g_CharacterArray[13] = 0b01011110;	// character code for 'D'
	g_CharacterArray[14] = 0b01111001;	// character code for 'E'
	g_CharacterArray[15] = 0b01110001;	// character code for 'F'
	g_CharacterArray[16] = 0b10000000;	// character code for '.'
	g_CharacterArray[17] = 0b00000000;	// character code for  blank
}
