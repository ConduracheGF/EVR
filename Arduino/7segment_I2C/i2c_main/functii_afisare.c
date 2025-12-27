#include "functii_uart.h"
#include "functii_afisare.h"
#include "functii_i2c.h"

void setup_7_segm(){
  send_i2c(0x00, 0x09, 0xFF);
  USART_Transmit_String("1. BCD Decode!\n");

  send_i2c(0x00, 0x0A, 0x0F);
  USART_Transmit_String("2. Intensity!\n");

  send_i2c(0x00, 0x0B, 0x03);
  USART_Transmit_String("3. Initializarea unui digit!\n");

  send_i2c(0x00, 0x0C, 0x01);
  USART_Transmit_String("4. Normal Operation for Shutdown register!\n");

  reset_7_segm();
}

void reset_7_segm(){
  send_i2c(0x00,0x01,0);
  send_i2c(0x00,0x02,0);
  send_i2c(0x00,0x03,0);
  send_i2c(0x00,0x04,0);
}

void afisare(int cifra[]) {
    // trimite cifrele catre AS1115
    for (int i = 0; i < 4; i++) {
        send_i2c(0x00, i + 1, cifra[3-i]);
    }
}