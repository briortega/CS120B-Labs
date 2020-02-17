/*
* borte012_lab9_part1.c
* Author : Briana
* Partner 1 Name & E-mail: Vincent Trejo vtrej003@ucr.edu
* Lab Section:021
* Assignment: Lab #9 Exercise #1
* Exercise Description:
*
* I acknowledge all content contained herein, excluding template or example
* code, is my own original work.
*/

#include <avr/io.h>

void set_PWM(double frequency){
	static double current_frequency;
	if(frequency != current_frequency){
		if(!frequency)
		{
			TCCR3B &= 0x08;
		}
		else
		{
			TCCR3B |= 0x03;
		}
		
		if(frequency < 0.954)
		{
			OCR3A = 0xFFFF;
		}
		else if(frequency > 31250)
		{
			OCR3A = 0x0000;
		}
		else
		{
			OCR3A = (short)(8000000 / (128 * frequency)) -1;
		}
		TCNT3 = 0;
		current_frequency = frequency;
	}
}
void PWM_on(){
	TCCR3A	=  (1 << COM3A0);
	TCCR3B = (1 << WGM32) | (1 << CS31) | (1 << CS30);
	set_PWM(0);
}
void PWM_off(){
	TCCR3A = 0x00;
	TCCR3B = 0x00;
}
enum toneSM{start, wait, C, D, E} state; 

unsigned char b0;
unsigned char b1;
unsigned char b2;

void tone_Tick(){
	b0 = (~PINA & 0x02);
	b1 = (~PINA & 0x04);
	b2 = (~PINA & 0x08);
	
	switch(state){
		case start:
			state = wait;
			break;
		case wait:
			if(b0){
				state = C;
			}else if(b1){
				state = D;
			}else if(b2){
				state = E;
			}else{
				state = wait;
			}
			break;
		case C:
			if(b0){
				state = C;
			}else if ((b0 && b1) || (b0 && b2) || (!b0)){
				state = wait;
			}
			break;
		case D:
			if(b1){
				state = D;
			}else if((b1 && b0) || (b1 && b2) || (!b1)){
				state = wait;
			}
			break;
		case E:
			if(b2){
				state = E;
			}else if((b2 && b0) || (b2 && b1) || (!b2)){
				state = wait;
			}
			break;
		default:
			state = start;
			break;
	}
	switch(state){
		case start:
			set_PWM(0);
			break;
		case wait:
			set_PWM(0);
			break;
		case C:
			set_PWM(261.63);
			break;
		case D:
			set_PWM(293.66);
			break;
		case E:
			set_PWM(329.63);
			break;
		default:
			break;
	}
}

int main(void)
{
	//DDRB = x1xx xxxx;
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
    PWM_on();
	state = start;
    while (1) 
    {
		tone_Tick();
    }
}

