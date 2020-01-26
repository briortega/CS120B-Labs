/*
* borte012_lab4_part3.c
* Author : Briana
* Partner 1 Name & E-mail:
* Lab Section:021
* Assignment: Lab #4 Exercise #3
* Exercise Description:
*
* I acknowledge all content contained herein, excluding template or example
* code, is my own original work.
*/
#include <avr/io.h>

enum LockSystem_States {LockSystem_SMStart, X_A0, Y_A1, Hashtag_A2, Hashtag_Wait, Restart, Lock, Unlock}LockSystem_States;

unsigned char button_A0;
unsigned char button_A1;
unsigned char button_A2;
unsigned char button_A7;

void LockSystem_Tick(){
	button_A0 = (PINA & 0x01);
	button_A1 = (PINA & 0x02);
	button_A2 = (PINA & 0x04);
	button_A7 = (PINA & 0x80);
	switch(LockSystem_States){
		case LockSystem_SMStart:
			if ((button_A2) && (!button_A1) && (!button_A0) && (!button_A7)){
				LockSystem_States = Hashtag_A2;
			}
			else if (button_A7){
				LockSystem_States = Lock;
			}
			else{
				LockSystem_States = Restart;
			}
			break;
		case X_A0:
			LockSystem_States = Restart;
			break;
		case Y_A1:
			LockSystem_States = Restart;
			break;
		case Hashtag_A2:
			if ((!button_A1) && (!button_A0) && (button_A2) && (!button_A7)){
				LockSystem_States = Hashtag_Wait;
			}else if (button_A7){
				LockSystem_States = Lock;
			}
			else{
				LockSystem_States = Restart;
			}
			break;
		case Hashtag_Wait:
			if((!button_A1) && (!button_A0) && (button_A2) && (!button_A7)){
				LockSystem_States = Hashtag_Wait;
			}
			else if ((button_A1) && (!button_A0) && (!button_A2) && (!button_A7)){
				LockSystem_States = Unlock;
			}else if (button_A7){
				LockSystem_States = Lock;
			}
			else{
				LockSystem_States = Restart;
			}
			break;
		case Restart:
			if ((button_A2) && (!button_A1) && (!button_A0) && (!button_A7)){
				LockSystem_States = Hashtag_A2;
			}
			else if (button_A7){
				LockSystem_States = Lock;
			}
			else{
				LockSystem_States = Restart;
			}
			break;
		case Lock:
			if (button_A7){
				LockSystem_States = Lock;
			}else{
				LockSystem_States = Restart;
			}
			break;
		case  Unlock:
			if (button_A7){
				LockSystem_States = Lock;
			}else{
				LockSystem_States = Unlock;
			}
			break;
		default:
			LockSystem_States = LockSystem_SMStart;
		break;
	}
	
	switch(LockSystem_States){
		case LockSystem_SMStart:
			PORTC = 0;
			break;
		case X_A0:
			break;
		case Y_A1:
			break;
		case Hashtag_A2:
			break;
		case Hashtag_Wait:
			break;
		case Lock:
			PORTC = 0;
			break;
		case Unlock:
			PORTC = 1;
			break;
		default:
			break;
	}
}

int main(void)
{
	DDRA = 0x00; PORTA = 0xFF;
	DDRC = 0xFF; PORTC = 0x00;
	LockSystem_States = LockSystem_SMStart;
    while (1) 
    {
		LockSystem_Tick();
    }
}

