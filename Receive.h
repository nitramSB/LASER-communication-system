/*
 * Receive.h
 *
 * Created: 10.02.2022 20:19:54
 *  Author: Martin
 
 
 */ 


#ifndef RECEIVE_H_
#define RECEIVE_H_


unsigned char startbit; // Flag variable
unsigned char bit; // To correctly synthesize the incoming bit stream one must know which bit goes where.
unsigned char toggle; // Toggle variable
volatile unsigned char ReceiveByte; // The variable that holds the incoming byte.


void InitializeReceive(); 
void Initialize_HW_Interrupts();
void InitializeTimer1();


#endif /* RECEIVE_H_ */