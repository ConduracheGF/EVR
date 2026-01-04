#ifndef STATE_MACHINE_H_
#define STATE_MACHINE_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
  I2C_OK,
  I2C_STUCK
} i2c_bus_state_t;

typedef enum {
  DRIVER_OK,
  DRIVER_NEEDS_INIT
} driver_state_t;

typedef enum {
  SEND_SUCCESSFUL,
  SEND_NOT_SUCCESSFUL
} send_status_t;

extern i2c_bus_state_t i2c_bus_state;
extern driver_state_t driver_state;

void driver_task(uint16_t tensiune);

#ifdef __cplusplus
}
#endif

#endif

