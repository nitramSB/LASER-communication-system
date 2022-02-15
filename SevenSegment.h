/*
 * SevenSegment.h
 *
 * Created: 09.02.2022 10:00:50
 *  Author: Martin
 
  Credits: This code is an modified version of the code made/provided by Richard Anthony in ERTP.


 */ 


#ifndef SEVENSEGMENT_H_
#define SEVENSEGMENT_H_

#include <avr/io.h>
#include <avr/interrupt.h>

#define NumCharPatterns 18

volatile enum Segment {	Rightmost_LSD, Center_Right, Center_Left, Leftmost_MSD } g_eSegment;

void InitialiseTimer0_InterlaceInterval_1ms();
void InitialiseTimer1_CountIncrement_200ms();
void InitializeSevenSegment();
void SetSevenSegmentCharacterPatternsInArray();



unsigned char g_CharacterArray[NumCharPatterns]; // To hold display patterns for characters '0' - '9' and 'A' - 'F' and decimal point
volatile unsigned int g_iCount; // The number to display (required TEST range is 4 DECIMAL digits 0000 - 9999)

unsigned char KeyValue;
unsigned char uDisplayDigitValue;
unsigned char uDisplayPattern;
	

#endif /* SEVENSEGMENT_H_ */