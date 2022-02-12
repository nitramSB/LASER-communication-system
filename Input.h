/*
 * Input.h
 *
 * Created: 09.02.2022 09:27:31
 *  Author: Martin
 */ 


#ifndef INPUT_H_
#define INPUT_H_



#include <avr/io.h>
#include <avr/interrupt.h>


#define ScanKeypadRow0 0b11111110	// Bits 4-7 individually pulled low depending on which row is being scanned
#define ScanKeypadRow1 0b11111101
#define ScanKeypadRow2 0b11111011
#define ScanKeypadRow3 0b11110111

#define KeypadMaskColumns 0b00001111
#define KeypadMaskColumn0 0b00010000
#define KeypadMaskColumn1 0b00100000
#define KeypadMaskColumn2 0b01000000
#define KeypadMaskColumn3 0b10000000

#define DecimalPoint	0b10000000	// Bit 7 of the segment-select data port


#define NoKey	0xFF	// This is equivalent to all '1' bits on the port, it is the state when no key has been pressed: 11111111

void InitializeInput(void);
unsigned char ScanKeypad(void);
unsigned char ScanColumns(unsigned char);
void DisplayKeyValue(unsigned char);
void DebounceDelay(void);

unsigned char KeyValue;


#endif /* INPUT_H_ */