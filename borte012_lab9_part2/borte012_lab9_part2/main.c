/*
* borte012_lab9_part2.c
* Author : Briana
* Partner 1 Name & E-mail: Vincent Trejo vtrej003@ucr.edu
* Lab Section:021
* Assignment: Lab #9 Exercise #2
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
enum toneSM{start, wait, toneUp , toneDown, hold, release, off, on} state; 

unsigned char b0; // on/off
unsigned char b1; //up
unsigned char b2; //down
unsigned char tone;

void tone_Tick(){
	b0 = (~PINA & 0x02);
	b1 = (~PINA & 0x04);
	b2 = (~PINA & 0x08);
	
	switch(state){
		case start:
			state = off;
			break;
		case off:
			if (b0){
				state = on;
			}else{
				state = off;
			}
			break;
		case on:
			if (b0){
				state = off;
			}else{
				state = wait;
			}
			break;
		case wait:
			if(b0){
				state = off;
			}else if(b1){
				state = toneUp;
			}else if(b2){
				state = toneDown;
			}else{
				state = wait;
			}
			break;
		case toneUp:
			if(b1){
				state = hold;
			}else if (b0){
				state = off;
			}else{
				state = wait;
			}
			break;
		case toneDown:
			if(b2){
				state = hold;
			}else if(b0){
				state = off;
			}
			else{
				state = wait;
			}
			break;
		case hold:
			if(b1 || b2){
				state = hold;
			}else{
				state = release;
			}
			break;
		case release:
			state = wait;
			break;
		default:
			state = start;
			break;
	}
	switch(state){
		case start:
			set_PWM(0);
			tone = 0;
			break;
		case off:
			set_PWM(0);
			break;
		case on:
			set_PWM(0);
			break;
		case wait:
			if (tone == 1){
				set_PWM(261.63);
			}
			else if (tone == 2){
				set_PWM(293.66);
			}
			else if (tone == 3){
				set_PWM(329.63);
			}
			else if (tone == 4){
				set_PWM(349.23);
			}
			else if (tone == 5){
				set_PWM(392.00);
			}
			else if (tone == 6){
				set_PWM(440.00);
			}
			else if (tone == 7){
				set_PWM(493.88);
			}
			else if (tone == 8){
				set_PWM(523.25);
			}else{
				set_PWM(0);
			}
			break;
		case toneUp:
			//set_PWM(tone);
			if (tone < 8){
				tone++;
			}
			break;
		case toneDown:
			//set_PWM(tone);
			if (tone > 0){
				tone--;
			}
			break;
		case hold:
			set_PWM(tone);
			break;
		case release:
			break;
		default:
			break;
	}
}

int main(void)
{
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
 
    PWM_on();
    state = start;
 
    while (1) 
    {
		tone_Tick();
    }
}