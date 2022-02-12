/*
 * Receive.c
 *
 * Created: 10.02.2022 20:19:21
 *  Author: Martin
 */ 


#include "Receive.h"
#include "Common.h"
#include "Serial.h"

unsigned char startbit = 0;

void InitializeReceive(){
	Initialize_HW_Interrupts();

}

void Initialize_HW_Interrupts()
{
	EICRA = 0b00000011;		// External Interrupt Control Register A: INT 3,2 not used, Interrupt Sense INT0 rising-edge triggered
	EICRB = 0b00000000;		// INT7 ... 4 not used
	
	EIMSK = 0b00000001;		// External Interrupt Mask Register: Enable INT0
	EIFR = 0b00000001;		// External Interrupt Flag Register: Clear INT0 interrupt flag (in case a spurious interrupt has occurred during chip startup)
}

/*
ISR(INT0_vect) // Hardware_INT0_Handler (Interrupt Handler for INT0)
{
	
	// The pulse duration needs to be greater than 50ns for it to be sensed.
	if (startbit == 0){
		
		
		
		
		startbit = 1;
		
	}
	DisplayLED();				// Display count value
	//TCCR1B = 0b00001101;		// Start the timer (CTC and Prescaler 1024)
}
*/
ISR(USART1_RX_vect) // (USART_RX_Complete_Handler) USART Receive-Complete Interrupt Handler
{
	char cData = UDR1;
	switch(cData)
	{
		case '1':
		//USART0_TX_String("Command '1' received");
		DisplayLED(cData);
		break;
		case '2':
		USART0_TX_String("Command '2' received");
		break;
		case '3':
		USART0_TX_String("Command '3' received");
		break;
		case '4':
		USART0_TX_String("Command '4' received");
		break;
	}
	USART0_DisplayPrompt();
}
