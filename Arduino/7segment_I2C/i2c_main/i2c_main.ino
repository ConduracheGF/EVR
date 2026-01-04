#include "functii_i2c.h"
#include "functii_uart.h"
#include "functii_adc.h"
#include "functii_plus.h"
#include "state_machine.h"
#include "driver_task.h"
#include "functii_timer.h"

void main_timer1(){
    uint16_t adc = ADC_Read();
    uint16_t tensiune = (uint32_t)adc * 5000UL / 1023UL;
        
    driver_task(tensiune);

    USART_Transmit_String("Tensiune = ");
    USART_Transmit_Int(tensiune);
    USART_Transmit_String(" mV");
}

int main() {
    USART_Init(UBRR);
    setup_i2c();
    ADC_Init();

    driver_state = DRIVER_NEEDS_INIT;

    init_timer1();

    while (1){}
}
