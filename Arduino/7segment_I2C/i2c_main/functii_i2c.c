#include "functii_i2c.h"
#include "functii_uart.h"
#include <avr/io.h>

void setup_i2c(){
    TWSR |= 0x00;
    TWBR = 72;
    TWCR |= (1<<TWEN);
}

void send_i2c(unsigned int address, unsigned int reg, unsigned int data){
    if (bus_stuck_i2c()){
        ERROR("I2C BUS STUCK\n");
        recover_bus_i2c();
    }

    //USART_Transmit_String("Start condition\n");
    //send start condition
    TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);

    //wait for TWINT Flag set. This indicates that the start condition has been transmitted
    if (!wait_twint_i2c()){
        ERROR("START TIMEOUT\n");
        recover_bus_i2c();
        return;
    }

    //check value of TWI Status Register. Clear TWINT to start transmission of address
    if ((TWSR & 0xf8) != START){
        ERROR("START ERR\n");
        recover_bus_i2c();
        return;
    }
    
    //USART_Transmit_String("Load address\n");
    //load address into twdr register. clear twint bit in twcr to start transmission of address
    TWDR = address << 1;
    TWCR = (1<<TWINT) | (1<<TWEN);
    if(!wait_twint_i2c()){
        ERROR("ADDR TIMEOUT\n");
        recover_bus_i2c();
        return;
    }

    //check value of TWI STATUS Register. Mask prescaler bits. If status different from MT_SLA_ACK from ERROR
    if ((TWSR & 0xF8) != MT_SLA_ACK){
        ERROR("ADDRESS ERR\n");
        recover_bus_i2c();
        return;
    }

    TWDR = reg;
    TWCR = (1 << TWINT) | (1 << TWEN);
    if (!wait_twint_i2c()){
        ERROR("REG TIMEOUT\n");
        recover_bus_i2c();
        return;
    }

    
    if ((TWSR & 0xF8) != MT_DATA_ACK){
        ERROR("REG ERR");
        recover_bus_i2c();
        return;
    }

    //USART_Transmit_String("Load data\n");
    //Load data into twdr register. clear twint bit in twcr to start transmission of data
    TWDR = data;
    TWCR = (1<<TWINT) | (1<<TWEN);
    if (!wait_twint_i2c()){
        ERROR("DATA TIMEOUT\n");
        recover_bus_i2c();
        return;
    }

    //check value of twi status register. mask prescaler bits. If status different from MT_DATA_ACK go to ERROR
    if ((TWSR & 0xF8) != MT_DATA_ACK){
        ERROR("DATA ERR\n");
        recover_bus_i2c();
        return;
    }
    
    //transmit stop condition
    TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO);
    //USART_Transmit_String("Stop condition\n");
}

uint8_t wait_twint_i2c(void) {
    //functie care pune o pauza dupa realizarea unei etape complete de transmitere a datelor
    uint32_t timeout = TIMEOUT;
    while (!(TWCR & (1 << TWINT))) {
        if(--timeout == 0) return 0;
    }
    return 1;
}

uint8_t bus_stuck_i2c(){
    //verificare daca sda se duce pe low de la slave
    if(!(PIND & (1 << PD1)))
        return 1; //sda low duce in blocaj
    return 0;
}

void recover_bus_i2c(){
    ///dezactiveaza twi
    TWCR &= ~(1 << TWEN);

    //scl out si sda in
    DDRD |= (1 << PD0);
    DDRD &= ~(1 << PD1);
    //pull up sda
    PORTD |= (1 << PD1);
    
    for (uint8_t i=0; i<10; i++){
        PORTD &= ~(1 << PD0);
        //delay_microsecunde(5);
        PORTD |= (1 << PD0);
        //delay_microsecunde(5);
    }

    PORTD |= (1 << PD0);
    //delay_microsecunde(5);
    //lipsa delayurilor s-a testat prin rularea codului si nu altereaza progresul executiei sale

    setup_i2c();
}