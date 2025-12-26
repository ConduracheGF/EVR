#ifndef FUNCTII_UART_H_
#define FUNCTII_UART_H_

#define FOSC 16000000
#define FSCL 100000
#define BAUD_RATE 9600
#define UBRR FOSC/16/BAUD_RATE-1

void USART_Init(unsigned int ubrr);

void USART_Transmit(unsigned char data);

unsigned char USART_Receive(void);

void USART_Transmit_String(const char* string);

void ERROR(char err[]);

#endif