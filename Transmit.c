/*
 * Transmit.c
 *
 * Created: 09.02.2022 10:03:23
 *  Author: Martin
 */ 


#include "Transmit.h"
#include "Common.h"
#include <string.h>
// Code here

void InitializeTransmit()
{
	
	
	//DDRK = 0b00000001; // Configure PortK bit 0 for LASER modulation
	//PORTK = 0b00000000; // LASER initially turned off
	DDRD = 0b00001000;
	PORTD = 0b00000000;
	
	USART1_SETUP_9600_BAUD_ASSUME_1MHz_CLOCK();
	
	//InitializeTimer0();
}

/*
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
*/

ISR(TIMER0_OVF_vect) // TIMER0_Overflow_Handler (Interrupt Handler for Timer 0)
{	// Shift LED BAR left
	
	//unsigned char test = 0b00000001;
	//ToggleLASER(test);
	
}

void USART1_SETUP_9600_BAUD_ASSUME_1MHz_CLOCK()
{
	//UCSR0A – USART Control and Status Register A
	// bit 7 RXC Receive Complete (flag)
	// bit 6 TXC Transmit Complete (flag)
	// bit 5 UDRE Data Register Empty (flag)
	// bit 4 FE Frame Error (flag) - programmatically clear this when writing to UCSRA
	// bit 3 DOR Data OverRun (flag)
	// bit 2 PE Parity Error
	// bit 1 UX2 Double the USART TX speed (but also depends on value loaded into the Baud Rate Registers)
	// bit 0 MPCM Multi-Processor Communication Mode
	UCSR1A = 0b00000010; // Set U2X (Double the USART Tx speed, to reduce clocking error) // Data sheet states that bit 0-2 is read-only 110?

	// UCSR0B - USART Control and Status Register B
	// bit 7 RXCIE Receive Complete Interrupt Enable
	// bit 6 TXCIE Transmit Complete Interrupt Enable
	// bit 5 UDRIE Data Register Empty Interrupt Enable
	// bit 4 RXEN Receiver Enable
	// bit 3 TXEN Transmitter Enable
	// bit 2 UCSZ2 Character Size (see also UCSZ1:0 in UCSRC)
	// 0 = 5,6,7 or 8-bit data
	// 1 = 9-bit data
	// bit 1 RXB8 RX Data bit 8 (only for 9-bit data)
	// bit 0 TXB8 TX Data bit 8 (only for 9-bit data)
	UCSR1B = 0b10001000;  // RX Complete Int Enable, RX Disabled (Becuase we do not receive here), TX Enable, 8-bit data

	// UCSR0C - USART Control and Status Register C
	// *** This register shares the same I/O location as UBRRH ***
	// Bits 7:6 – UMSELn1:0 USART Mode Select (00 = Asynchronous)
	// bit 5:4 UPM1:0 Parity Mode
	// 00 Disabled
	// 10 Even parity
	// 11 Odd parity
	// bit 3 USBS Stop Bit Select
	// 0 = 1 stop bit
	// 1 = 2 stop bits
	// bit 2:1 UCSZ1:0 Character Size (see also UCSZ2 in UCSRB)
	// 00 = 5-bit data (UCSZ2 = 0)
	// 01 = 6-bit data (UCSZ2 = 0)
	// 10 = 7-bit data (UCSZ2 = 0)
	// 11 = 8-bit data (UCSZ2 = 0)
	// 11 = 9-bit data (UCSZ2 = 1)
	// bit 0 UCPOL Clock POLarity
	// 0 Rising XCK edge
	// 1 Falling XCK edge
	UCSR1C = 0b00000111;		// Asynchronous, No Parity, 1 stop, 8-bit data, Falling XCK edge

	// UBRR0 - USART Baud Rate Register (16-bit register, comprising UBRR0H and UBRR0L)
	UBRR1H = 0; // 2400 baud, UBRR = 51, and  U2X must be set to '1' in UCSRA
	UBRR1L = 51;
}



void TransmitLaserUSART(unsigned char cByte){
	
	while(!(UCSR1A & (1 << UDRE1)));	// Wait for Tx Buffer to become empty (check UDRE flag)
	UDR1 = cByte;	// Writing to the UDR transmit buffer causes the byte to be transmitted
	
}


