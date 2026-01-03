#include "functii_i2c.h"
#include "functii_uart.h"
#include "functii_afisare.h"
#include "functii_adc.h"
#include "functii_plus.h"
#include <util/delay.h>


int main() {
    USART_Init(UBRR);
    recover_bus_i2c();
    setup_i2c();
    ADC_Init();

    uint16_t flag = 0;

    while (1) {
        if(bus_stuck_i2c()){
            USART_Transmit_String("BUS RECOVERY\n");
            recover_bus_i2c();
            setup_i2c();
            flag = 0;
        }

        if(flag >= 5 && !bus_stuck_i2c()){
            delay_milisecunde(100);
            setup_7_segm();
            flag = 0;
        }

        uint16_t adc = ADC_Read();
        uint16_t tensiune = (uint32_t)adc * 5000UL / 1023UL;
        
        USART_Transmit_String("Tensiune = ");
        USART_Transmit_Int(tensiune);
        USART_Transmit_String(" mV");

        if(!bus_stuck_i2c()){
            afisare_tensiune(tensiune);
        }
        delay_milisecunde(200);
        flag++;
    }
}
