#include "driver_task.h"
#include "state_machine.h"
#include "functii_afisare.h"
#include "functii_uart.h"
#include "functii_plus.h"

void driver_task(uint16_t tensiune){
  switch(driver_state){
    case DRIVER_NEEDS_INIT:
      USART_Transmit_String("State: NEEDS_INIT");
      if(setup_7_segm() == SEND_SUCCESSFUL){
        driver_state = DRIVER_OK;
        USART_Transmit_String("INIT SUCCESS");
      }
      else
        USART_Transmit_String("INIT FAILED, retrying");
      break;
    case DRIVER_OK:
      USART_Transmit_String("State: OK");
      if(afisare_tensiune(tensiune) != SEND_SUCCESSFUL){
        USART_Transmit_String("AFISARE FAILED");
      }
      break;
    case DRIVER_NOT_RESPONDING:
      USART_Transmit_String("State: NOT_RESPONDING");
      driver_state = DRIVER_NEEDS_INIT;
      break;
  }
}