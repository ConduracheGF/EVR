#define F_OSC 16000000
#define bottom 0
#define max 0xFF

ISR(TIMER1_COMPA_vect){
  PORTD ^= (1<<PD7);
}

int main(void){
  DDRD |= (1<<PD7); //setare iesire
  PORTD &= ~(1<<PD7); //led stins

  TCCR1A |= (1<<COM1A1);
  TCCR1B |= (1<<CS12) | (1<<CS10) | (1<<WGM12);//prescalar 256 cu mod CTC
  OCR1A = 1952; //prag focn=fosc/2/scalar/(1+ocn1a)

  TIMSK1 |= (1<<TOIE1) | (1<<OCIE1A); //setare intrerupere output compare match a
  PCICR = (1<<PCIE1);
  PCMSK1 = (1<<PCINT4);
  sei();
  while(1){}
}