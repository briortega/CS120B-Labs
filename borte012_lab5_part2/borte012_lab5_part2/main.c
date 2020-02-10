/*
* borte012_lab5_part2.c
* Author : Briana
* Partner 1 Name & E-mail: Vincent Trejo vtrej003@ucr.edu
* Lab Section:021
* Assignment: Lab #5 Exercise #2
* Exercise Description:
*
* I acknowledge all content contained herein, excluding template or example
* code, is my own original work.
*/
#include <avr/io.h>

enum Counter_States {Counter_SMStart, Count_Up, Count_Down, Count_Reset, wait, wait2}Counter_States;

unsigned char button_A0;
unsigned char button_A1;
unsigned char tempValue;

void Counter_Tick(){
	button_A0 = (~PINA & 0x01);
	button_A1 = (~PINA & 0x02);

	switch(Counter_States){
		case Counter_SMStart:
			Counter_States = wait;
			break;
		case wait:
			if ((!button_A0) && (!button_A1)){
				Counter_States = wait;
			}
			else if((button_A0) && (button_A1)){
				Counter_States = wait2;
			}else if((button_A0) && (!button_A1)){
				Counter_States = Count_Up;
			}else if ((!button_A0) && (button_A1)){
				Counter_States = Count_Down;
			}
			break;
		case Count_Up:
			if((button_A0) && (!button_A1)){
				Counter_States = wait2;
			}
			else if ((button_A0) && (button_A1)){
				Counter_States = Count_Reset;
			}
			break;
		case Count_Down:
			if((!button_A0) && (button_A1)){
				Counter_States = wait2;
			}else if ((button_A0) && (button_A1)){
				Counter_States = Count_Reset;
			}
			break;
		case Count_Reset:
				Counter_States =  Counter_SMStart;
			break;
		case wait2:
			if((button_A0) || (button_A1)){
				Counter_States = wait2;
			}else if ((!button_A0) && (!button_A1)){
				Counter_States = wait;
			}else if ((button_A0) && (button_A1)){
				Counter_States = Count_Reset;
			}
			break;
		default:
			Counter_States = Counter_SMStart;
			break;
	}
	
	switch(Counter_States){
		case Counter_SMStart:
			tempValue = tempValue;
			break;
		case Count_Up:
			if(tempValue < 9){
				tempValue = tempValue + 1;
			}
			break;
		case Count_Down:
			if (tempValue > 0 ){
				tempValue = tempValue - 1;
			}
			break;
		case Count_Reset:
			tempValue = 0x00;
			break;
		case wait:
			break;
		case wait2:
			break;
		default:
			break;
	}
}

int main(void)
{
	DDRA = 0x00; PORTA = 0xFF;
	DDRC = 0xFF; PORTC = 0x00;
	
	tempValue = 0;
	Counter_States = Counter_SMStart;
	
	while (1)
	{
		Counter_Tick();
		PORTC = tempValue;
	}
}

