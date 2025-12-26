#define F_CPU 16000000UL
#define BAUD_RATE 9600
#define UBRR_VALUE (F_CPU/16/BAUD_RATE - 1)

volatile unsigned char rx_char = 0;
volatile uint8_t rx_flag = 0;

void USART_Init(unsigned int ubrr){
    UBRR0H = (unsigned char)(ubrr >> 8);
    UBRR0L = (unsigned char)(ubrr);
    UCSR0B = (1<<RXEN0) | (1<<TXEN0) | (1<<RXCIE0);
    UCSR0C = (1<<UCSZ01) | (1<<UCSZ00);
}

unsigned char USART_Receive(void){
    while(!(UCSR0A & (1<<RXC0))){}
    return UDR0;
}

void USART_Transmit(unsigned char data){
    while(!(UCSR0A & (1<<UDRE0))){}
    UDR0 = data;
}

void USART_Transmit_String(const char* string){ 
  //transmitere caracter cu caracter 
  for(int i=0; string[i]!='\0'; i++){
    USART_Transmit(string[i]); 
  } 
}

ISR(USART_RX_vect){
    rx_char = UDR0;
    rx_flag = 1;
    PORTD ^= (1 << PD7);
}

int main(void){
    DDRD |= (1 << PD7);
    PORTD &= ~(1 << PD7);

    USART_Init(UBRR_VALUE);
    sei();

    while(1){
        if(rx_flag){
            rx_flag = 0;
            USART_Transmit(rx_char);
        }
    }
}
