#include "functii_uart.h"
#include "functii_afisare.h"
#include "functii_i2c.h"

void setup_7_segm(){
  send_i2c(0x00, 0x09, 0xFF);
  USART_Transmit_String("1. BCD Decode!\n");

  send_i2c(0x00, 0x0A, 0x0F);
  USART_Transmit_String("2. Intensity!\n");

  send_i2c(0x00, 0x0B, 0x00);
  USART_Transmit_String("3. Initializarea unui digit!\n");

  send_i2c(0x00, 0x0C, 0x01);
  USART_Transmit_String("4. Normal Operation for Shutdown register!\n");

  reset_7_segm();
}

void reset_7_segm(){
  send_i2c(0x00,0x01,0);
}

void afisare(int cifra){
  reset_7_segm();
  send_i2c(0x00, 0x01, cifra);
}