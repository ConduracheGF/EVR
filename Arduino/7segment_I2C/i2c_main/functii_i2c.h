#ifndef FUNCTII_I2C_H_
#define FUNCTII_I2C_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define START 0x08
#define MT_SLA_ACK 0x18
#define MT_DATA_ACK 0x28
#define TIMEOUT 50000

void setup_i2c();
void send_i2c(unsigned int address, unsigned int reg, unsigned int data);
uint8_t wait_twint_i2c();
uint8_t bus_stuck_i2c();
void recover_bus_i2c();

#ifdef __cplusplus
}
#endif

#endif