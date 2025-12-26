volatile int brightness = 0;
volatile int pas = 1;

ISR(TIMER1_OVF_vect) {
    brightness += pas; 
    if (brightness >= 1000) pas = -1;
    if (brightness <= 0)    pas = 1;
    OCR1A = brightness;
}

int main(void)
{
    DDRB |= (1 << PB1); // pin PWM
    TCCR1A |= (1<<COM1A1) | (1<<WGM11);
    TCCR1B |= (1<<WGM12) | (1<<WGM13) | (1<<CS11); // fast PWM, scalar 8
    ICR1 = 1999; //fPWM = Fclk / scalar*(1+ICR1)
    OCR1A = 0;
    TIMSK1 |= (1<<TOIE1);//intrerupere doar de Ov
    sei();

    while(1){}
}