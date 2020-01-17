/*
 * borte012_lab3_part1.c
 * Author : Briana
 * Partner 1 Name & E-mail:
 * Lab Section:021
 * Assignment: Lab #3 Exercise #1
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
	DDRB = 0x00; PORTB = 0xFF;
	DDRC = 0xFF; PORTC = 0x00;
	unsigned char count = 0x00;

	while(1)
	{
		count = 0;
		for(int i = 0; i < 8; i++){
			if (GetBit(PINA,i)){
				count = count + 1;
			}
			if(GetBit(PINB,i)){
				count = count + 1;
			}
		}
		PORTC = count;
	}
}
