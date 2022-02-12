/*
 * Common.h
 *
 * Created: 09.02.2022 12:01:51
 *  Author: Martin
 */ 


#ifndef COMMON_H_
#define COMMON_H_

#include <util/delay.h>
#include <avr/interrupt.h>


unsigned char CountPulse; //Count variable
void DisplayLED(unsigned char);
void EnableInterrupts();
void InitializeCommon();



#endif /* COMMON_H_ */