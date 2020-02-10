/*
* borte012_lab7_part1.c
* Author : Briana
* Partner 1 Name & E-mail: Vincent Trejo vtrej003@ucr.edu
* Lab Section:021
* Assignment: Lab #7 Exercise #1
* Exercise Description:
*
* I acknowledge all content contained herein, excluding template or example
* code, is my own original work.
*/

#include <avr/io.h>
#include "io.h"
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

enum Counter_States {Counter_SMStart, Count_Up, Count_Down, Count_Reset, wait,hold}Counter_States;

unsigned char button_A0;
unsigned char button_A1;
unsigned char tempValue;
unsigned char count;

void Counter_Tick(){
	button_A0 = (~PINA & 0x02);
	button_A1 = (~PINA & 0x04);

	switch(Counter_States){
		case Counter_SMStart:
			Counter_States = wait;
			break;
		case wait:
			if(button_A0 && button_A1){
				Counter_States = Count_Reset;
			}else if(button_A0 && !button_A1){
				Counter_States = Count_Up;
			}else if (!button_A0 && button_A1){
				Counter_States = Count_Down;
			}else{
				Counter_States = wait;
			}
			break;
		case Count_Up:
			if(button_A0 && !button_A1){
				Counter_States = hold;
			}else if (button_A0 && button_A1){
				Counter_States = Count_Reset;
			}else{
				Counter_States = wait;
			}
			break;
		case Count_Down:
			if(!button_A0 && button_A1){
				Counter_States = hold;
			}else if (button_A0 && button_A1){
				Counter_States = Count_Reset;
			}else{
				Counter_States = wait;
			}
			break;
		case hold:
			if(button_A0 && button_A1){
				Counter_States = Count_Reset;
			}else if (button_A0 && !button_A1){
				if((count % 9) == 0){
					Counter_States = Count_Up;
				}else{
					Counter_States = hold;
				}
			}else if(!button_A0 && button_A1)
			{
				if((count % 9) == 0){
					Counter_States = Count_Down;
				}else{
					Counter_States = hold;
				}
			}
			else{
				Counter_States = wait;
			}
			break;
		case Count_Reset:
			Counter_States = wait;
			break;
		default:
			Counter_States = Counter_SMStart;
			break;
	}
	
	switch(Counter_States){
		case Counter_SMStart:
			tempValue = 0;
			break;
		case Count_Up:
		    count = 0;
			if(tempValue < 9)
			{
				tempValue = tempValue + 1;
			}
			break;
		case Count_Down:
			count = 0;
			if(tempValue > 0)
			{
				tempValue = tempValue - 1;
			}
			break;
		case Count_Reset:
			tempValue = 0x00;
			break;
		case wait:
			break;
		case hold:
			count++;
			break;
		default:
			break;
	}
	
}

int main(void)
{
    DDRA = 0x00; PORTA = 0xFF;
	DDRC = 0xFF; PORTC = 0x00;
	DDRD = 0xFF; PORTD = 0x00;
	
	TimerSet(100);
	TimerOn();

	LCD_init();
	LCD_ClearScreen();

	tempValue = 0;
	count = 0;
	Counter_States = Counter_SMStart;
	
	while (1)
	{
		Counter_Tick();
		LCD_Cursor(1);
		LCD_WriteData(tempValue + '0');
		while(!TimerFlag);
		TimerFlag = 0;
	}
}