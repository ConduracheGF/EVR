#define F_CPU 16000000UL
#define BAUD 9600
#define UBRR_VALUE ((F_CPU / (16UL * BAUD)) - 1)

void USART_Init(unsigned int ubrr){
  UBRR0H = (unsigned char)(ubrr >> 8);
  UBRR0L = (unsigned char)ubrr;
  UCSR0B = (1 << TXEN0);
  UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

void USART_Transmit(unsigned char data){
  while(!(UCSR0A &(1<<UDRE0)));
  UDR0 = data;
}

void USART_Transmit_String(const char* string){
  //transmitere caracter cu caracter
  for(int i=0; string[i]!='\0'; i++){
    USART_Transmit(string[i]);
  }
}

void USART_Transmit_Int(uint16_t string){
  char buff[32];
  int i = 0;
  while(string){
    buff[i++] = ((string % 10) + '0');
    string/=10;
  }
  while(i--){
    USART_Transmit(buff[i]);
  }
}

void USART_Transmit_Voltaj(uint16_t volt){
    uint16_t volt_frac = 0;

    if(volt)
      USART_Transmit_Int(volt);
    else
      USART_Transmit_Int(0);
    USART_Transmit('.');
    
    if(volt_frac < 100) USART_Transmit('0');
    USART_Transmit_Int(volt_frac);
}

void ADC_Init(){
  ADMUX = (1 << REFS0); /*| (1 << MUX0);  //avcc 5v, adc1*/
  ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1<<ADPS0); //prescalar 128
}

uint16_t ADC_Read(){
  ADCSRA |= (1 << ADSC); //start conversie
  while(ADCSRA & (1 << ADSC)); //asteapta finalizarea si dupa incepe
  uint16_t val = ADCL;
  val |= (ADCH << 8);
  return val;
}

char buffer[32];

int main(void){
    USART_Init(UBRR_VALUE);
    ADC_Init();
    while(1){
        uint16_t val = ADC_Read();
        uint16_t tensiune = (uint32_t)val * (uint32_t)5000 / (uint32_t)1023;
        USART_Transmit_String("Tensiunea = ");
        USART_Transmit_Voltaj(tensiune);
        USART_Transmit_String(" mV");
        USART_Transmit('\n');
        USART_Transmit('\r');
        _delay_ms(200);
    }
}