/*
* borte012_lab6_part2.c
* Author : Briana
* Partner 1 Name & E-mail: Vincent Trejo vtrej003@ucr.edu
* Lab Section:021
* Assignment: Lab #6 Exercise #2>>
* Exercise Description:
*
* I acknowledge all content contained herein, excluding template or example
* code, is my own original work.
*/
#include <avr/io.h>
#include <avr/interrupt.h>

volatile unsigned char TimerFlag = 0;
unsigned long _avr_timer_M = 1;
unsigned long _avr_timer_cntcurr = 0;

void TimerOn() {
  TCCR1B = 0x0B;
  OCR1A = 125;
  TIMSK1 = 0x02;
  TCNT1 = 0;
  _avr_timer_cntcurr = _avr_timer_M;
  SREG |= 0x80;
}
void TimerOff() {
  TCCR1B = 0x00;
}
void TimerISR() {
  TimerFlag = 1;
}
ISR(TIMER1_COMPA_vect) {
  _avr_timer_cntcurr--;
  if (_avr_timer_cntcurr == 0) {
    TimerISR();
    _avr_timer_cntcurr = _avr_timer_M;
  }
}
void TimerSet(unsigned long M) {
  _avr_timer_M = M;
  _avr_timer_cntcurr = _avr_timer_M;
}

enum syncSM { start, initS, led, pause, resume} state;
void syncSM_tick();

unsigned char button;
unsigned char ledIndex;

int main(void)
{
  DDRA = 0x00; PORTA = 0xFF;
  DDRB = 0xFF; PORTB = 0x00;
 
  TimerSet(100); //100 works better
  TimerOn();
  state = start;
  while (1)
  {
    syncSM_tick();
    while (!TimerFlag);
    TimerFlag = 0;
  }
}

void syncSM_tick()
{
  
  button = (~PINA & 0x01);
  switch (state) //transition
  {
    case start:
        state = initS;
        break;

    case initS:
		state = led;
        break;

    case led:
      if (button == 0x00)
      {
        state = led;
        break;
      }
      else if ( button == 0x01)
      {
        state = pause;
        break;
      }
      else
      {
        state = state;
        break;
      }

    case pause:
      if (button == 0x00)
      {
        state = resume;
        break;
      }
      else if (button == 0x01)
      {
          state = pause;
          break;
      }
      else
      {
          state = state;
          break;
      }
    case resume:
      if (button == 0x01)
      {
        state = led;
        break;
      }
      else
      {
        state = resume;
        break;
      }

    default :
      break;
      }

  switch (state) //actions
  {
    case start:
      
      break;

    case initS:
      PORTA = 0x00;
      PORTB = 0x00;
 
      button = 0x00;
      ledIndex = 0x01;
      break;

    case led:
      if (ledIndex > 0x03)
      {
        ledIndex = 0x01;
        break;
      }
      else
      {
        ledIndex = (ledIndex << 1);
        break;
      }

    case pause: // set time flag to 0 until button pressed
        PORTA = 0x01;
        TimerISR();
        break;
    case resume:
        button = 0x00;
        TimerSet(100);
      break;

    default :
      break;
  }
  PORTB = ledIndex;
}
