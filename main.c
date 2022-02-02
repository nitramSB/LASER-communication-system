/*
 * LaserCom.c
 *
 * Created: 02.02.2022 08:00:14
 * Author : Martin
 */ 

#include <avr/io.h>
#define F_CPU 1000000UL // Assumes 1MHz clock speed // Set to 8000000UL or 16000000UL if your uC has a 8MHz or 16MHz clock speed.
#include <util/delay.h>



void InitializeGeneral();

int main(void)
{
	
	InitializeGeneral();
    /* Replace with your application code */
    while (1) 
    {
		
		PORTC = 0b00000001;
		_delay_ms(1000);
		PORTC = 0b00000000;
		_delay_ms(1000);


		
    }
}

void InitializeGeneral()
{
	DDRC= 0b11111111;			// Configure PortC direction for Output
	PORTC = 0b00000000;		// Pull output low
	
	
	//sei(); // Set timer enable bit
}




