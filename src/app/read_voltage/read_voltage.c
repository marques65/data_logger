/*============================================================================*/
#include "read_voltage.h"
#include "../../pic18f4520/gpio/gpio.h"
#include "../../board/pinout/pinout.h"
/*============================================================================*/
uint8_t Voltage_Read( void )
{
    return DIGITAL_PIN_READ(VOLTAGE_INPUT_PORT, VOLTAGE_INPUT_BIT);
}



/*============================================================================*/