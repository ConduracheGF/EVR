#include "state_machine.h"
#include "functii_afisare.h"

i2c_bus_state_t i2c_bus_state = I2C_OK;
driver_state_t driver_state = DRIVER_NEEDS_INIT;

void driver_task(uint16_t tensiune){
  switch(driver_state){
    case DRIVER_NEEDS_INIT:
      if(setup_7_segm() == SEND_SUCCESSFUL){
        driver_state = DRIVER_OK;
      }
      break;
    case DRIVER_OK:
      if(afisare_tensiune(tensiune) != SEND_SUCCESSFUL){
        driver_state = DRIVER_NEEDS_INIT;
      }
      break;
  }
}