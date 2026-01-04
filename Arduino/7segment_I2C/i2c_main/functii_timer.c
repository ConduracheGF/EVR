#include "functii_timer.h"
#include <avr/io.h>
#include <avr/interrupt.h>

volatile uint32_t timer = 0;

void init_timer1(){
  //CTC
  TCCR1B = (1<<WGM12);

  //prescalar 64
  TCCR1B |= (1<<CS11) | (1<<CS10);

  //16mhz/64/1000-1
  OCR1A = 249;

  TCNT1 = 0;

  //intrerupere compare match
  TIMSK1 = (1<<OCIE1A);

  //activeaza intrerupere globala
  sei();
}

ISR(TIMER1_COMPA_vect){
  timer++;
  if(timer >= 200){
    timer = 0;
    main_timer1();
  }
}