/*
* borte012_lab6_part1.c
* Author : Briana
* Partner 1 Name & E-mail: Vincent Trejo vtrej003@ucr.edu
* Lab Section:021
* Assignment: Lab #6 Exercise #1
* Exercise Description:
*
* I acknowledge all content contained herein, excluding template or example
* code, is my own original work.
*/

#include <avr/io.h>
#include <avr/interrupt.h>

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

enum syncSM { start, led1, led2, led3} state;
void syncSM_tick();

int main(void)
{
    DDRB = 0xFF;
    PORTB = 0x00;
    TimerSet(1000);
    TimerOn();
	state = start;

    while (1)
    {
		syncSM_tick();
	    while(!TimerFlag);
	    TimerFlag = 0;
    }
}

void syncSM_tick()
{
    switch(state)//transition
	{
		case start :
			state = led1;
			break;
		case led1 :
			state = led2;
			break;
		case led2 :
			state = led3;
			break;
		case led3 :
			state = led1;
			break;
		default : 
			break;	
	}
	
	 switch(state)//actions
	 {
		 case start:
		    break;
		 case led1:
			PORTB = 0x01;
			break;
		 case led2:
			PORTB = 0x02;
			break;
		 case led3:
			PORTB = 0x04;
			break;
		 default :
			break;
	 }
}