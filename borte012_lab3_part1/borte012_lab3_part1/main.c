/*
 * borte012_lab3_part1.c
 *
 * Created: 1/14/2020 11:25:53 AM
 * Author : Briana
 */ 

#include <avr/io.h>
// Bit-access function
unsigned char SetBit(unsigned char x, unsigned char k, unsigned char b) {
	return (b ? x | (0x01 << k) : x & ~(0x01 << k));
}
unsigned char GetBit(unsigned char x, unsigned char k) {
	return ((x & (0x01 << k)) != 0);
}

int main(void)
{
	DDRA = 0x00; PORTA = 0xFF; // Configure port A's 8 pins as inputs
	DDRB = 0x00; PORTB = 0xFF; // Configure port B's 8 pins as inputs
	DDRC = 0xFF; PORTC = 0x00; // Configure port C's 8 pins as outputs
	// initialize to 0s
	//unsigned char tmpC = 0x00;
	unsigned char count = 0x00;

	//unsigned char tmpB = 0x00; // intermediate variable used for port updates
	unsigned char button = 0x00;
	unsigned char button2 = 0x00;

	while(1)
	{
		// 1) Read Inputs and assign to variables
		button = PINA & 0x01; // Mask PINA to only get the bit you are interested in
		button2 = PINB & 0x01;
		// 2) Perform Computation
		// if PA0 is 1, set PB1PB0=01, else =10
		if (GetBit(button, 0)) { // True if PA0 is 1
			count++;
		}
		if(GetBit(button, 1)){
			count++;
		}
		if(GetBit(button2, 0)){
			count++;
		}
		if(GetBit(button2, 1)){
			count++;
		}		
		// 3) write results to port
		PORTC = count;
	}
}
