/*
* borte012_lab2_part1.c
* Author : Briana
* Partner 1 Name & E-mail:
* Lab Section:021
* Assignment: Lab #2 Exercise #1
* Exercise Description: Garage sensor
*
* I acknowledge all content contained herein, excluding template or example
* code, is my own original work.
*/

#include <avr/io.h>

int main(void)
{
	DDRA = 0x00; PORTA = 0xFF; // Configure port A's 8 pins as inputs
	DDRB = 0xFF; PORTB = 0x00; // Configure port B's 8 pins as outputs, initialize to 0s

	unsigned char tmpA0 = 0x00;
	unsigned char tmpA1 = 0x00;

    while (1) 
    {
		tmpA0 = PINA & 0x01;
		tmpA1 = PINA & 0x02;
		if ((tmpA1 == 0x01) && (tmpA0 == 0x02)){
			PORTB = 0x01;
		}
		else{
			PORTB = 0x00;
		}
    }
	return 0;
}