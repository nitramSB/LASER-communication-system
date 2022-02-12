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


#include "Common.h"
#include "Input.h"
#include "Transmit.h"
#include "Receive.h"
#include "SevenSegment.h"
#include "Serial.h"




int main(void)
{

	EnableInterrupts(); // Enable Interrupts globally
	InitializeCommon(); // Initialize Common functionality
	InitializeInput(); // Initialize LED Port and Input Port
	InitializeTransmit(); // Initialize Transmit (LASER)
	InitializeReceive(); // Initialize Receive (Solar Panel)
	InitializeSevenSegment(); // Initialize SevenSegment
	InitializeSerial(); // Initialize Serial communication to PC
	
		

    while (1)
    {
		
		KeyValue = ScanKeypad();
		
		if(NoKey != KeyValue)
		{
			
			// Calculate the individual DECIMAL digit value for display - leftmost digit
			uDisplayDigitValue = KeyValue;
			// Look up how to display the required character
			uDisplayPattern = g_CharacterArray[uDisplayDigitValue];
			PORTH = 0b10111111;	// Select Leftmost (MSD) digit
			PORTA = uDisplayPattern;
			//g_eSegment = Rightmost_LSD;
			DebounceDelay();
			
			//TransmitLaserUSART(uDisplayPattern); //Send uDisplayPattern to the LASER
			TransmitLaserUSART(0b0000001);
			
			//InitializeTimer0(); //Initializes and starts the timer that pulses the LASER. 
		
		}
}
}



