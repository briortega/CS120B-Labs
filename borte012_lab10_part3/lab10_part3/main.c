/*
  borte012_lab10_part3.c
  Author : Briana
  Partner 1 Name & E-mail: Vincent Trejo vtrej003@ucr.edu
  Lab Section: 021
  Assignment: Lab #10 Exercise #3
  Exercise Description:

  I acknowledge all content contained herein, excluding template or example
  code, is my own original work.
*/
#include <avr/io.h>
#include "io.h"
#include <avr/interrupt.h>

unsigned char threeLEDs = 0x00;
unsigned char blinkingLED = 0x00;
unsigned char sound = 0x00;

enum threeLEDsSm { threeLED_SMStart, light1, light2, light3} threeLEDs_States;
enum blinkingLEDSM{ blinkingLED_SMStart, blinking_off, blinking_on} blinkingLED_States;
enum soundSM{ soundOn, soundOff} sound_States;
enum Combine_StateSM{Combine_start} combine_State;

void TickFct_threeLEDsSM() {
	switch(threeLEDs_States){
		case threeLED_SMStart:
			threeLEDs_States = light1;
			break;
		case light1:
			threeLEDs_States = light2;
			break;
		case light2:
			threeLEDs_States = light3;
			break;
		case light3:
			threeLEDs_States = light1;
			break;
		default:
			threeLEDs_States = threeLED_SMStart;
			break;
	}
	switch(threeLEDs_States){
		case threeLED_SMStart:
			break;
		case light1:
			threeLEDs = 0x01;
			break;
		case light2:
			threeLEDs = 0x02;
			break;
		case light3:
			threeLEDs = 0x04;
			break;
		default:
			break;
	}
}

void TickFct_blinkingLEDSM(){
	switch (blinkingLED_States)
	{
		case blinkingLED_SMStart:
			blinkingLED_States = blinking_off;
			break;
		case blinking_off:
			blinkingLED_States = blinking_on;
			break;
		case blinking_on:
			blinkingLED_States = blinking_off;
			break;
		default:
			break;
	}
	switch (blinkingLED_States)
	{
		case blinkingLED_SMStart:
			break;
		case blinking_off:
			blinkingLED = 0x00;
			break;
		case blinking_on:
			blinkingLED = 0x08;
			break;
		default:
			break;
	}
}

void TickFct_soundSM(){
	unsigned char button = (~PINA & 0x04);
	switch(sound_States){
		case soundOn:
			if (button){
				sound_States = soundOff;
			}else{
				sound_States = soundOn;
			}
			break;
		case soundOff:
			if (button){
				sound_States = soundOn;
			}else{
				sound_States = soundOff;
			}
			break;
		default:
			break;
	}
	switch(sound_States){
		case soundOn:
			sound = 0x10;
			break;
		case soundOff:
			sound = 0x00;
			break;
		default:
			break;
	}
}

void TickFct_Combine_StateSM(){
	switch(combine_State){
		case Combine_start:
			break;
	}
	switch(combine_State){
		case Combine_start:
			PORTB = threeLEDs | blinkingLED | sound;
			break;
		default:
			break;
	}
}

volatile unsigned char TimerFlag = 0;
unsigned long _avr_timer_M = 1;
unsigned long _avr_timer_cntcurr = 0;

void TimerOn(){
	TCCR1B = 0x0B;
	OCR1A = 125;
	TIMSK1 = 0x02;
	TCNT1 = 0;
	_avr_timer_cntcurr = _avr_timer_M;
	SREG |= 0x80;
}
void TimerOff(){
	TCCR1B = 0x00;
}
void TimerISR(){
	TimerFlag = 1;
}
ISR(TIMER1_COMPA_vect){
	_avr_timer_cntcurr--;
	if(_avr_timer_cntcurr == 0){
		TimerISR();
		_avr_timer_cntcurr = _avr_timer_M;
	}
}
void TimerSet(unsigned long M){
	_avr_timer_M = M;
	_avr_timer_cntcurr = _avr_timer_M;
}

int main(void)
{
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	
	unsigned long threeLED_elapsedTime = 0;
	unsigned long blinkingLED_elapsedTime = 0;
	const unsigned long timerPeriod = 2;
	
	TimerSet(timerPeriod);
	TimerOn();
	
	threeLEDs_States = threeLED_SMStart;
	blinkingLED_States = blinkingLED_SMStart;
	sound_States = soundOff;
	combine_State = Combine_start;
	
	while (1)
	{
		if (threeLED_elapsedTime >= 300) {
			TickFct_threeLEDsSM();
			threeLED_elapsedTime = 0;
		}
		if (blinkingLED_elapsedTime >= 1000) {
			TickFct_blinkingLEDSM();
			blinkingLED_elapsedTime = 0;
		}
		TickFct_soundSM();
		TickFct_Combine_StateSM();
		
		while (!TimerFlag) {}
		TimerFlag = 0;
		
		threeLED_elapsedTime += timerPeriod;
		blinkingLED_elapsedTime += timerPeriod;
	}
}