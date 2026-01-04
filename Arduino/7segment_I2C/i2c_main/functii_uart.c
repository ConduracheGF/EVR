#include "functii_uart.h"
#include <avr/io.h>

void USART_Init(unsigned int ubrr){
  //setare high
  UBRR0H = (unsigned char)(ubrr>>8);
  //setare low
  UBRR0L = (unsigned char)(ubrr);
  //activare transmit si receive
  UCSR0B = (1<<RXEN0) | (1<<TXEN0);
  //format 8biti, fara par, 2 biti stop, mod asincron
  UCSR0C = (1<<USBS0) | (3<<UCSZ00) | (0<<UMSEL00) | (0<<UPM00);
}

void USART_Transmit(unsigned char data){
  //buffer gol
  while(!(UCSR0A & (1<<UDRE0))){}
  //incarci caracter
  UDR0 = data;
}

void USART_Transmit_String(const char* string){
  //transmitere caracter cu caracter
  for(int i=0; string[i]!='\0'; i++){
    USART_Transmit(string[i]);
  }
  USART_Transmit('\r');
  USART_Transmit('\n');
}

void USART_Transmit_Int(uint16_t string){
  char buff[32];
  int i = 0;
  
  if (string==0){
    USART_Transmit('0');
    return;
  }
  while(string){
    buff[i++] = ((string % 10) + '0');
    string/=10;
  }
  while(i--){
    USART_Transmit(buff[i]);
  }
}

