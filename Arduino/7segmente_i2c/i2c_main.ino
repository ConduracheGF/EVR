#include "functii_i2c.h"
#include "functii_uart.h"
#include "functii_afisare.h"

int main(){
  //initializari pt usart, i2c si cele 7segmente
  USART_Init(UBRR);
  setup_i2c();
  setup_7_segm();

  while(1){
    unsigned char in = USART_Receive();
    if(in >= '0' && in <= '9'){
        afisare(in - '0');
    }
  }
}