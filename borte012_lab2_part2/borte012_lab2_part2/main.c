/*
* borte012_lab2_part2.c
*
* Author : Briana
* Partner 1 Name & E-mail:
* Lab Section:021
* Assignment: Lab #2 Exercise #2
* Exercise Description: Available spaces
*
* I acknowledge all content contained herein, excluding template or example
* code, is my own original work.
*/

#include <avr/io.h>

int main(void)
{
	DDRA = 0x00; PORTA = 0xFF; // Configure port A's 8 pins as inputs
	DDRB = 0xFF; PORTB = 0x00; // Configure port B's 8 pins as outputs, initialize to 0s
	DDRC = 0xFF; PORTC = 0x00; // Configure port C's 8 pins as outputs, initialize to 0s

	unsigned char space0 = 0x00;
	unsigned char space1 = 0x00;
	unsigned char space2 = 0x00;
	unsigned char space3 = 0x00;
	unsigned char cntavai = 0x00;
	unsigned char taken = 0x00;
	
    while (1) 
    {
		space0 = PINA & 0x01;
		space1 = PINA & 0x02;
		space2 = PINA & 0x04;
		space3 = PINA & 0x08;
		cntavai = 4;
		taken = 0;
		
		if (space0 == 0x01){
			taken = taken + 1;
		}
		if(space1 == 0x02){
			taken = taken + 1;
		}
		if(space2 == 0x04){
			taken = taken + 1;
		}
		if(space3 == 0x08){
			taken = taken + 1;
		}
		cntavai = cntavai - taken;
		PORTC = cntavai;
    }
	return 0;
}

