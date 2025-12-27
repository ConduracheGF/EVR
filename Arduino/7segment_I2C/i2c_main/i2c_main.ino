#include "functii_i2c.h"
#include "functii_uart.h"
#include "functii_afisare.h"
#include "functii_adc.h"
#include <util/delay.h>


int main() {
    USART_Init(UBRR);
    setup_i2c();
    setup_7_segm();
    ADC_Init();

    while (1) {
        uint16_t adc = ADC_Read();
        uint16_t tensiune = (uint32_t)adc * 5000UL / 1023UL;
        USART_Transmit_String("Tensiune = ");
        USART_Transmit_Int(tensiune);
        USART_Transmit_String(" mV");

        afisare_tensiune(tensiune);
        _delay_ms(2000);
    }
}
