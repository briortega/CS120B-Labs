/*
* borte012_lab8_part4.c
* Author : Briana
* Partner 1 Name & E-mail: Vincent Trejo vtrej003@ucr.edu
* Lab Section:021
* Assignment: Lab #8 Exercise #4
* Exercise Description:
*
* I acknowledge all content contained herein, excluding template or example
* code, is my own original work.
*/
#include <avr/io.h>

void ADC_init(){
	ADCSRA |= (1 << ADEN) | (1 << ADSC) | (1 << ADATE);
}

int main(void)
{
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	DDRD = 0xFF; PORTD = 0x00;

	//unsigned short x = ADC;
	unsigned short max = 52;
	ADC_init();
	
	while (1)
	{
		// 6.5
		if(ADC <= 0){
			PORTB = 0x00;
		}
		else if(ADC <= (6.5 * 2)){
			PORTB = 0x01;
		}
		else if(ADC <= (6.5 * 3)){
			PORTB = 0x02;
		}
		else if(ADC <= (6.5 * 4)){
			PORTB = 0x04;
		}
		else if(ADC <= (6.5 * 5)){
			PORTB = 0x08;
		}
		else if(ADC <= (6.5 * 6)){
			PORTB = 0x10;
		}
		else if(ADC <= (6.5 * 7)){
			PORTB = 0x20;
		}
		else if(ADC <= (6.5 * 8)){
			PORTB = 0x40;
		}
		else if(ADC <= (6.5 * 9)){
			PORTB = 0x80;
		}
		//LED turns on when light hits the photo resistor
		//if(ADC >= (max)){
		//PORTB = 0x00;
		//}
		//else if(ADC <= (max)){
		//PORTB = 0x01;
		//}
	}
}

