#include "functii_i2c.h"
#include "functii_uart.h"
#include <avr/io.h>

void setup_i2c(){
    TWSR |= 0x00;
    TWBR = 72;
    TWCR |= (1<<TWEN);
}

void send_i2c(unsigned int address, unsigned int reg, unsigned int data){
    //USART_Transmit_String("Start condition\n");
    //send start condition
    TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);

    //wait for TWINT Flag set. This indicates that the start condition has been transmitted
    while(!(TWCR & (1<<TWINT)));

    //check value of TWI Status Register. Clear TWINT to start transmission of address
    if ((TWSR & 0xf8) != START)
        ERROR("START ERR\n");
    
    //USART_Transmit_String("Load address\n");
    //load address into twdr register. clear twint bit in twcr to start transmission of address
    TWDR = address << 1;
    TWCR = (1<<TWINT) | (1<<TWEN);

    //wait for twint flag set. This indicates that the SLA+W has been transmitted, and ACK/NACK has been received.
    while(!(TWCR & (1<<TWINT)));

    //check value of TWI STATUS Register. Mask prescaler bits. If status different from MT_SLA_ACK from ERROR
    if ((TWSR & 0xF8) != MT_SLA_ACK)
        ERROR("ADDRESS ERR\n");

    TWDR = reg;
    TWCR = (1<<TWINT)|(1<<TWEN);
    while (!(TWCR & (1<<TWINT)));
    if ((TWSR & 0xF8) != MT_DATA_ACK)
        ERROR("REG ERR");

    //USART_Transmit_String("Load data\n");
    //Load data into twdr register. clear twint bit in twcr to start transmission of data
    TWDR = data;
    TWCR = (1<<TWINT) | (1<<TWEN);

    //wait for twint flag set. this indicates that the data has been transmitted and ack/nack has been received
    while (!(TWCR & (1<<TWINT)));

    //check value of twi status register. mask prescaler bits. If status different from MT_DATA_ACK go to ERROR
    if ((TWSR & 0xF8) != MT_DATA_ACK)
        ERROR("DATA ERR\n");
    
    //transmit stop condition
    TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO);
    //USART_Transmit_String("Stop condition\n");
}