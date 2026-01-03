#include "functii_uart.h"
#include "functii_afisare.h"
#include "functii_i2c.h"
#include <util/delay.h>


void setup_7_segm(){
  send_i2c(0x00, 0x09, 0xFF);
  //USART_Transmit_String("1. BCD Decode!\n");

  send_i2c(0x00, 0x0A, 0x0F);
  //USART_Transmit_String("2. Intensity!\n");

  send_i2c(0x00, 0x0B, 0x03);
  //USART_Transmit_String("3. Initializarea unui digit!\n");

  send_i2c(0x00, 0x0C, 0x01);
  ///USART_Transmit_String("4. Normal Operation for Shutdown register!\n");

  //reset_7_segm();
}

void reset_7_segm(){
  //shutdown
  send_i2c(0x00, 0x0C, 0x00);
  //normal operation
  send_i2c(0x00, 0x0C, 0x01);

  //digit0->digit3
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

void afisare_tensiune(uint16_t mV) {
  int cifra[4] = {0};

  if (mV > 5000) mV = 5000;

  uint16_t val = (uint32_t)mV * 1000 / 1000;

  cifra[0] = (val/1000)%10;
  cifra[1] = (val/100)%10;
  cifra[2] = (val/10)%10;
  cifra[3] = val%10;

  cifra[0] |= 0x80;  

  afisare(cifra);
}