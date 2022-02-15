/*
 * LaserCom.c
 *
 * Created: 02.02.2022 08:00:14
 * Author : Martin
 
 
 This program is made to demonstrate the use of LASER light for transmitting 1 byte of data through a loop-back interface
 using an Atmel 2560 micro controller.  
 
 - USART TX1 is connected to a logic NOT gate used to enable/disable a MOSFET acting as a switch.
 - PORTC is connected to 8 LEDs as an output device
 - PORTL is connected to a 4x4 keypad as an input device
 - PORTA and PORTH[3,6] is connected to an Seven Segment display as an output device
 - INT0 is connected to the output from the solar panel's filtering circuitry
 - PORTH[0] is connected to INT0 as an input pin
 - USART0 is interfaced by default internally to the USB port.
 
 
 Program operation:
 - User presses a key on the keypad
 - Key pressed is displayed on the Seven Segment Display
 - USART TX1 transmits a byte corresponding to the key pressed to the LASER
 - The startbit from the USART byte will trigger INT0
 - INT0 ISR initializes Timer1
 - Timer1 samples the incoming bit stream
 - The incoming byte is displayed on the 8 LEDs
 - The incoming byte is sent to the PC using USART0
 
 
 */ 

#include <avr/io.h>
#define F_CPU 1000000UL // Assumes 1MHz clock speed // Set to 8000000UL or 16000000UL if your uC has a 8MHz or 16MHz clock speed.
#include <util/delay.h>
#include <avr/interrupt.h>


#include "Input.h"
#include "Transmit.h"
#include "Receive.h"
#include "SevenSegment.h"
#include "Serial.h"



int main(void)
{

	sei();		// Enable interrupts at global level set Global Interrupt Enable (I) bit
	InitializeInput(); // Initialize LED Port and Input Port
	InitializeTransmit(); // Initialize Transmit (LASER)
	InitializeReceive(); // Initialize Receive (Solar Panel)
	InitializeSevenSegment(); // Initialize SevenSegment
	InitializeSerial(); // Initialize Serial communication to PC
	

    while (1)
    {
		
		KeyValue = ScanKeypad(); //Check if any key has been pressed
		if(NoKey != KeyValue) //If key has been pressed
		{
			
			uDisplayDigitValue = KeyValue;
			// Look up how to display the required character
			uDisplayPattern = g_CharacterArray[uDisplayDigitValue];
			PORTH = 0b10111111;	// Select Leftmost (MSD) digit. Only really relevant if multiple Seven Segments are multiplexed
			// -------------------Now as I am going through the code
			// before I submit I noticed a mistake. Here I am writing a logical 1 to bit 0 which is the same bit that 
			// I am sampling in the Timer1 ISR...This could explain some problems.

			PORTA = uDisplayPattern; //Write the character to the seven segment
			DebounceDelay(); // Delay to avoid false key presses because of voltage fluctuations.
			
			TransmitLaserUSART(uDisplayPattern); //Send uDisplayPattern to the LASER
			//TransmitLaserUSART(0b00001111); //Used for debugging and verification on the oscilloscope
			//USART0_TX_SingleByte(ReceiveByte); // Transmit the byte to the monitor. This is not complete
												// This will transmit the SevenSegment combination for the key pressed
												// not the number itself. I am aware of this. I did not have time to finish it
												// But I had time I would convert it to a number and then to ANSI character. 
			
		}
}
}



