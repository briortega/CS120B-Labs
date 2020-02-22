/*
  borte012_lab11_part2.c
  Author : Briana
  Partner 1 Name & E-mail: Vincent Trejo vtrej003@ucr.edu
  Lab Section: 021
  Assignment: Lab #11 Exercise #2
  Exercise Description:

  I acknowledge all content contained herein, excluding template or example
  code, is my own original work.
*/
#include <avr/interrupt.h>
#include <avr/io.h>
#include "keypad.h"
#include "scheduler.h"
#include "timer.h"
#include "bit.h"

unsigned char tmpB = 0x00;
const unsigned char message[38] = {'C','S','1','2','0','B',' ','i','s',' ','L','e','g','e','n','d','.','.','.',' ',
	'w','a','i','t',' ','f','o','r',' ','i','t',' ','D','A','R','Y','!'};
unsigned char cursorCounter = 1;
enum SM_Task {SM_output};

int SM_TaskTick(int state){
	switch(state){
		case SM_output:
			for (int i = 0; i <= 16; i++){
				LCD_Cursor(i);
				LCD_WriteData(message[cursorCounter + i - 2]);
				if (cursorCounter + i + 1 == 40){
					cursorCounter = 1;
				}
			}
			cursorCounter++;
			break;
	}
	return state;
}

int main(void)
{
	DDRC = 0xFF; PORTC = 0x00;
	DDRD = 0xFF; PORTD = 0x00;
	
	unsigned long int SM_TaskTick_time = 1000;
	unsigned long int tmpGCD = 10;
	unsigned long int GCD = tmpGCD;
	unsigned long int SM_Task_period = SM_TaskTick_time/GCD;
	
	static task task1;
	task *tasks[] = {&task1};
	const unsigned short numTasks = sizeof(tasks)/sizeof(task*);

	task1.state = 0;
	task1.period = SM_Task_period;
	task1.elapsedTime = SM_Task_period;
	task1.TickFct = &SM_TaskTick;
	
	TimerSet(GCD);
	TimerOn();
	LCD_init();
	LCD_ClearScreen();
	
	unsigned short i;
    while (1) {
		for (i = 0; i < numTasks; i++){
			if (tasks[i] ->elapsedTime == tasks[i] ->period ){
				tasks[i] ->state = tasks[i] ->TickFct(tasks[i] ->state);
				tasks[i] ->elapsedTime = 0;
			}
			tasks[i] ->elapsedTime += 1;
		}
		
		while(!TimerFlag);
		TimerFlag = 0;
  }
	return 0;
}