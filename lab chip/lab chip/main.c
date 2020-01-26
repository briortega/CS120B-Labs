/*
 * lab chip.c
 *
 * Created: 1/23/2020 11:50:10 AM
 * Author : Briana
 */ 

#include <avr/io.h>



int main(void)
{
	DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x00;
	unsigned char led = 0x00;
	unsigned char button = 0x00;
    while (1) 
    {
		button = ~PINA & 0x01;
		if(button){
			led = (led & 0xFC) | 0x01;
		}else{
			led = (led & 0xFC) | 0x02;
		}
		PORTB = led;
    }
	
}

