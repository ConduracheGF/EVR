#ifdef __cplusplus
extern "C" {
#endif


/*==================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/

#include "AS1115.h"
#include "CDD_I2c.h"

/*==================================================================================================
*                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/


/*==================================================================================================
*                                       LOCAL MACROS
==================================================================================================*/
#define DRIVER_SLAVE_ADDRESS 0x00

/*==================================================================================================
*                                      LOCAL CONSTANTS
==================================================================================================*/


/*==================================================================================================
*                                      LOCAL VARIABLES
==================================================================================================*/


/*==================================================================================================
*                                      GLOBAL CONSTANTS
==================================================================================================*/


/*==================================================================================================
*                                      GLOBAL VARIABLES
==================================================================================================*/


/*==================================================================================================
*                                   LOCAL FUNCTION PROTOTYPES
==================================================================================================*/


/*==================================================================================================
*                                       LOCAL FUNCTIONS
==================================================================================================*/


/*==================================================================================================
*                                       GLOBAL FUNCTIONS
==================================================================================================*/

void AS1115_Write(AS1115Registers_t SelectedRegister, uint8_t Value){
    //structura bufferului
	uint8_t buffer[2] = {
    		(uint8_t)SelectedRegister,
			Value
    };

    //pregatire cerere
    I2c_RequestType request = {0};
    request.SlaveAddress = DRIVER_SLAVE_ADDRESS;
    request.DataDirection = I2C_SEND_DATA;
    request.DataBuffer = buffer;
    request.BufferSize = 2;

    I2c_SyncTransmit(0, &request); //cerere pe canalul 0
}

uint8_t AS1115_Read(AS1115Registers_t SelectedRegister){
    uint8_t value = 0;
    uint8_t registru = (uint8_t)SelectedRegister;

    //scriem registrul dorit
    I2c_RequestType writeRequest = {0};
    writeRequest.SlaveAddress = DRIVER_SLAVE_ADDRESS;
    writeRequest.DataDirection = I2C_SEND_DATA;
    writeRequest.DataBuffer = &registru;
    writeRequest.BufferSize = 1;
    I2c_SyncTransmit(0, &writeRequest);

    //citim valoarea
    I2c_RequestType readRequest = {0};
    readRequest.SlaveAddress = DRIVER_SLAVE_ADDRESS;
    readRequest.DataDirection = I2C_RECEIVE_DATA;
    readRequest.DataBuffer = &value;
    readRequest.BufferSize = 1;
    I2c_SyncTransmit(0, &readRequest);

    return value;
}

#ifdef __cplusplus
}
#endif
