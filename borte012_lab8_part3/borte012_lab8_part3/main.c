/*
* borte012_lab8_part3.c
* Author : Briana
* Partner 1 Name & E-mail: Vincent Trejo vtrej003@ucr.edu
* Lab Section:021
* Assignment: Lab #8 Exercise #3
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

	//This worked based on the light provide by a cell phone on the photo resistor
	//Lighting in room was different than the lab room lighting
	//unsigned short x = ADC;
	unsigned short max = 52;
	ADC_init();
	
	while (1)
	{
		//LED turns off when no light hit the photo resistor
		if(ADC <= (max)){
			PORTB = 0x00;
		}
		else if(ADC >= (max)){
			PORTB = 0x01;
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

