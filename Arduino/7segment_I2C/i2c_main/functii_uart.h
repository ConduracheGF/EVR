#ifndef FUNCTII_UART_H_
#define FUNCTII_UART_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define FOSC 16000000
#define FSCL 100000
#define BAUD_RATE 9600
#define UBRR FOSC/16/BAUD_RATE-1

void USART_Init(unsigned int ubrr);

void USART_Transmit(unsigned char data);

void USART_Transmit_String(const char* string);

void USART_Transmit_Int(uint16_t string);

#ifdef __cplusplus
}
#endif

#endif