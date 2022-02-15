/*
 * Transmit.h
 *
 * Created: 09.02.2022 10:03:36
 *  Author: Martin
 
  Credits: This code is an modified version of the code made/provided by Richard Anthony in ERTP.


 */ 


#ifndef TRANSMIT_H_
#define TRANSMIT_H_


#include <avr/io.h>
#include <avr/interrupt.h>


#define CR 0x0D
#define LF 0x0A
#define SPACE 0x20

void InitializeTransmit();
void Initialize_HW_Interrupts();
void TransmitLaserUSART(unsigned char);
void InitializeTimer0();
void USART1_SETUP_9600_BAUD_ASSUME_1MHz_CLOCK();









#endif /* TRANSMIT_H_ */