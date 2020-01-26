/*
* borte012_lab4_part1.c
* Author : Briana
* Partner 1 Name & E-mail:
* Lab Section:021
* Assignment: Lab #4 Exercise #1
* Exercise Description:
*
* I acknowledge all content contained herein, excluding template or example
* code, is my own original work.
*/
#include <avr/io.h>

unsigned char SetBit(unsigned char x, unsigned char k, unsigned char b) {
	return (b ?  (x | (0x01 << k))  :  (x & ~(0x01 << k)) );
}

enum LED_States {LED_SMStart, LED_On_B0, LED_On_B1, wait}LED_States;

unsigned char button;
unsigned char tmpState;
void LED_Tick(){
	button = (PINA & 0x01);
	switch(LED_States){
		case LED_SMStart:
			LED_States = LED_On_B0;
			break;
		case LED_On_B0:
			if (button == 0){
				LED_States = wait;
			}
			else {
				LED_States = LED_On_B1;
			}
			break;
		case LED_On_B1:
			if (button == 1){
				LED_States = LED_On_B1;
			}
			else {
				LED_States = LED_On_B0;
			}
			break;
		case wait:
			if (button == 0){
				LED_States = LED_On_B0;
			}
			else {
				LED_States = LED_On_B1;
			}
			break;
		default:
			LED_States = LED_SMStart;
			break;
	}
	
	switch(LED_States){
		case LED_SMStart:
			//tmpState = SetBit(PINB, 0, 1);
			tmpState = 0;
			break;
		case LED_On_B0:
			//tmpState = SetBit(PINB, 0, 1);
			//tmpState = SetBit(PINB, 1, 0);
			tmpState = 0x01;
			break;
		case LED_On_B1:
			tmpState = 0x02;
			//tmpState = SetBit(PINB, 0, 0);
			//tmpState = SetBit(PINB, 1, 1);
			break;
		case wait:
			tmpState = 0x01;
			break;
		default:
			break;
	}
}

int main(void)
{
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x00;
    LED_States = LED_SMStart;
    while (1)
    {
	    LED_Tick();
		PORTB = tmpState;
    }
}