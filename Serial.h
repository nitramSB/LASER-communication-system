/*
 * USART.h
 *
 * Created: 09.02.2022 12:22:31
 *  Author: Martin
 
 
 Credits: This code is taken from ERTP sample code made/provided by Richard Anthony.


 */ 


#ifndef USART_H_
#define USART_H_


#include <avr/io.h>
#include <avr/interrupt.h>

#define F_CPU 1000000UL
#include <util/delay.h>
#include <string.h>

#define CR 0x0D
#define LF 0x0A
#define SPACE 0x20
#define UC unsigned char

void InitializeSerial();
void USART0_SETUP_9600_BAUD_ASSUME_1MHz_CLOCK();
void USART0_TX_SingleByte(unsigned char cByte);
void USART0_TX_String(char* sData);
void USART0_DisplayBanner();
void USART0_DisplayPrompt();




#endif /* USART_H_ */