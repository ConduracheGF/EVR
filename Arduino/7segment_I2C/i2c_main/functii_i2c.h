#ifndef FUNCTII_I2C_H_
#define FUNCTII_I2C_H_

#ifdef __cplusplus
extern "C" {
#endif

#define START 0x08
#define MT_SLA_ACK 0x18
#define MT_DATA_ACK 0x28

void setup_i2c();
void send_i2c(unsigned int address, unsigned int reg, unsigned int data);

#ifdef __cplusplus
}
#endif

#endif