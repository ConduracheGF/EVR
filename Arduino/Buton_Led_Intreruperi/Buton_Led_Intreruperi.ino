void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  DDRD |= (1<<PD6);
  DDRB |= (1<<PB4); //| (1<<PB3);
  PORTD &= ~(1<<PD6); 
  PCICR |= (1<<PCIE0);
  PCMSK0 |= (1<<PCINT4);
  sei();
}
ISR(PCINT0_vect){
  if(PINB & (1<<PB4) ){
    PORTD |= (1<<PD6);
  } 
  else {
    PORTD=0;
  }
}
//volatile uint32_t i;
//uint8_t flag = 0;
// the loop function runs over and over again forever
void loop() {
  
 /* for(i = 0; i<=400000; i++){}  
    PORTB |= (1<<PB4);
  for(i = 0; i<=500000; i++){}
    PORTB |= (1<<PB3);
  if(PB5 && PB4 && PB3) flag = 1;

  if(flag==1){
    for(i = 0; i<=200000; i++){} 
    PORTB &= ~(1<<PB5);   // turn the LED off by making the voltage LOW
    for(i = 0; i<=400000; i++){}  
    PORTB &= ~(1<<PB4);
    for(i = 0; i<=500000; i++){}
    PORTB &= ~(1<<PB3);
  }
  */
}
