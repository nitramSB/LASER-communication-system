/*
 * LaserCom.c
 *
 * Created: 09.02.2022 00:24:14
 * Author : Martin
 
 */ 

#include "Input.h"


void InitializeInput()
{
	//DDRC = 0xFF;			// Configure PortC direction for Output
	//PORTC = 0x00;			// Set all LEDs initially off (inverted on the board, so '1' = off)
	
	// Port L is used to scan/read the keypad matrix (output on Row bits, read Column bits)
	//	Bit 7 = column 4 input
	//	Bit 6 = column 3 input
	//	Bit 5 = column 2 input
	//	Bit 4 = column 1 input
	//	Bit 3 = row 4 output
	//	Bit 2 = row 3 output
	//	Bit 1 = row 2 output
	//	Bit 0 = row 1 output
	
	
	DDRL = 0b00001111;	// Port L data direction register (row pins output, column pins input)
	PORTL= 0b11110000;	// Set pullup resistors on column pins (so they read '1' when no key is pressed)
	
}


unsigned char ScanKeypad()
{
	unsigned char RowWeight;
	unsigned char KeyValue;

	// ScanRow0					// Row 0 is connected to port bit 0
	RowWeight = 0;			// Remember which row is being scanned
	PORTL = ScanKeypadRow0;	// Set bit 0 low (Row 0), bits 6,5,4 high (rows 1,2,3)
	//PORTC = ScanKeypadRow0;
	KeyValue = ScanColumns(RowWeight);
	if(NoKey != KeyValue)
	{
		return KeyValue;	// A key was detected in row 0
	}
	
	// ScanRow1					// Row 1 is connected to port bit 6
	RowWeight = 1;			// Remember which row is being scanned
	PORTL = ScanKeypadRow1;	// Set bit 6 low (Row 1), bits 7,5,4 high (rows 0,2,3)
	KeyValue = ScanColumns(RowWeight);
	if(NoKey != KeyValue)
	{
		return KeyValue;	// A key was detected in row 1
	}

	// ScanRow2					// Row 2 is connected to port bit 5
	RowWeight = 2;			// Remember which row is being scanned
	PORTL = ScanKeypadRow2;	// Set bit 5 low (Row 2), bits 7,6,4 high (rows 0,1,3)
	KeyValue = ScanColumns(RowWeight);
	if(NoKey != KeyValue)
	{
		return KeyValue;	// A key was detected in row 2
	}

	// ScanRow3					// Row 3 is connected to port bit 4
	RowWeight = 3;			// Remember which row is being scanned
	PORTL = ScanKeypadRow3;	// Set bit 4 low (Row 3), bits 7,6,5 high (rows 0,1,2)
	KeyValue = ScanColumns(RowWeight);
	return KeyValue;		// EITHER   A key was detected in row 3   OR   KeyValue will have the value 'NoKey'
}

unsigned char ScanColumns(unsigned char RowWeight)
{	// For each row, we come here and examine all the columns
	
	unsigned char ColumnPinsValue;
	
	// Mask bits 7,6,5,4 as high, as only interested in any low values in bits 3,2,1,0 (i.e. the column bits)
	//PORTC = PINL | KeypadMaskColumns;
	ColumnPinsValue = PINL | KeypadMaskColumns; // '0' in any column position means key pressed
	ColumnPinsValue = ~ColumnPinsValue;			// '1' in any column position means key pressed  (~ performs 1's complement)
	//PORTC = ColumnPinsValue;
	

	if(KeypadMaskColumn0 == (ColumnPinsValue & KeypadMaskColumn0))
	{
		return (RowWeight * 4) + 0 + 1;	// Indicates current row + column 0
		
	}
	
	if(KeypadMaskColumn1 == (ColumnPinsValue & KeypadMaskColumn1))
	{
		return (RowWeight * 4) + 1 + 1;	// Indicates current row + column 1
		

	}

	if(KeypadMaskColumn2 == (ColumnPinsValue & KeypadMaskColumn2))
	{
		return (RowWeight * 4) + 2 + 1;	// Indicates current row + column 2
	}

	if(KeypadMaskColumn3 == (ColumnPinsValue & KeypadMaskColumn3))
	{
		return (RowWeight * 4) + 3 + 1;	// Indicates current row + column 3
	}
	
	// If we get to here then no column value has been detected, so no key was pressed in any column
	return NoKey;	// Indicate no key was pressed
}

void DisplayKeyValue(unsigned char KeyValue)
{
	PORTA = KeyValue;		// Regular numeric key was pressed
	
}

void DebounceDelay()	// This delay is needed because after pressing a key, the mechanical switch mechanism tends
// to bounce, possibly leading to many key presses being falsely detected. The debounce delay
// makes the program wait long enough for the bouncing to stop before reading the keypad again.
{
	for(int i = 0; i < 50; i++)
	{
		for(int j = 0; j < 255; j++);
	}
}



