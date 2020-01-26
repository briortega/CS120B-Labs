/*
 * borte012_lab5_part1.c
 * Author : Briana
 * Partner 1 Name & E-mail: Vince
 * Lab Section:021
 * Assignment: Lab #5 Exercise #1
 * Exercise Description:
 *
 * I acknowledge all content contained herein, excluding template or example
 * code, is my own original work.
 */
#include <avr/io.h>

unsigned char GetBit(unsigned char x, unsigned char k) {
	return ((x & (0x01 << k)) != 0);
}

int main(void)
{
	DDRA = 0x00; PORTA = 0xFF;
	DDRC = 0xFF; PORTC = 0x00;
	
	unsigned char tempValue = 0x00;
	unsigned char tempC = 0x00;
	
    while (1) 
    {
		tempValue = ~PINA & 0x0F;
		
		if((tempValue == 1) || (tempValue == 2)){
			PORTC = 0x20;
		}
		if((tempValue == 3) || (tempValue == 4)){
			PORTC = 0x30;
		}
		if((tempValue == 5) || (tempValue == 6)){
			PORTC = 0x38;
		}
		if((tempValue == 7) || (tempValue == 8) || (tempValue == 9)){
			PORTC = 0x3C;
		}
		if( (tempValue == 10) || (tempValue == 11) || (tempValue == 12)){
			PORTC = 0x3E;
		}
		if((tempValue == 13) || (tempValue == 14) || (tempValue == 15)){
			PORTC = 0x3F;
		}
		
		tempC = PORTC;
		
		if (tempValue <= 4){
			PORTC = (tempC | 0x40);
		}
		
		tempC = PORTC;
	}
}

