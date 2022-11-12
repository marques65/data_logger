/*=============================================================================
 *      Sensor DHT 11 https://img.filipeflop.com/files/download/Datasheet_DHT11.pdf
 *       _______    _______           _______         _______    
 *      |       |          |         |       |       |       |       
 *      | DHT11 |          |_________|       |_______|       |___ . . . 
 *      |       |          |<-  A  ->|<- B ->|<- C ->|<- D ->|
 *      |_______|           
 *       | | | |      Legend: Initialization
 *    Vcc DT NC GND       A : request data (uc sends)  Duration : 18      ms
 *                        B : delay dht11  (dht sends) Duration:  20 ~ 40 us
 *                        C : dht response signal      Duration:  80      us
 *                        D : dht response signal      Duration:  80      us
 *                                  _______         _________
 *                         |       |       |       |         |
 *                         |_______|       |_______|         |
 *                         |<- E ->|<- D ->|<- F ->|<-  G  ->|
 *                   Legend: Response (byte)
 *                        E: Signal for next bit        Duration: 50      us
 *                        D: Signal of 0                Duration: 26 ~ 28 us
 *                        F: Signal for next bit        Duration: 50      us
 *                        G: Signal of 1                Duration: 70      us
 * 
 * Data presentation: 
 *  TEMP:   XX.X -> temp[2] = {XX, X}
 *  HUM:    YY.Y
 * 1° step: 
 *      vetAux[3] -> strcat(vetAux, temp)
 =============================================================================*/
#include "dht11.h"
#include "../../board/board_definitions/board_definitions.h"
#include "../../pic18f4520/gpio/gpio.h"
#include "../../board/pinout/pinout.h"
#include "../../pic18f4520/timer/timer.h"
#include "../../pic18f4520/serial/serial.h"




#include "../display_lcd/display_lcd.h"
#include "../../pic18f4520/serial/serial.h"
/*============================================================================*/
static uint8_t temperature [2]; // [TEMP HIGH BYTE][TEMP LOW BYTE]
static uint8_t humidity [2]; // [HUM HIGH BYTE][HUM LOW BYTE]



uint8_t Rh_byte1, Rh_byte2, Temp_byte1, Temp_byte2;
uint16_t sum, RH, TEMP;

void DHT11_Start(void) {
    PIN_CONFIGURE_DIGITAL(PIN_OUTPUT, DHT11_DATA_PORT, DHT11_DATA_MASK);
    PIN_DIGITAL_WRITE(PIN_LOW, DHT11_DATA_PORT, DHT11_DATA_MASK);

    __delay_ms(20);
    PIN_CONFIGURE_DIGITAL(PIN_INPUT, DHT11_DATA_PORT, DHT11_DATA_MASK);
}

void DHT11_Check_Response(void) {
    while (DIGITAL_PIN_READ(DHT11_DATA_PORT, DHT11_DATA_BIT)); // wait for pin to go low
    while (!DIGITAL_PIN_READ(DHT11_DATA_PORT, DHT11_DATA_BIT)); // wait for the pin to go HIGH
    while (DIGITAL_PIN_READ(DHT11_DATA_PORT, DHT11_DATA_BIT)); // wait for the pin to go low
}

uint8_t read_data(void) {
    uint8_t i, j;
    for (j = 0; j < 8; j++) {
        while (DIGITAL_PIN_READ(DHT11_DATA_PORT, DHT11_DATA_BIT) == 0); // wait for the pin to go high
        __delay_us(40); // wait for 40 us
        if (DIGITAL_PIN_READ(DHT11_DATA_PORT, DHT11_DATA_BIT) == 0) // if the pin is low 
        {
            i &= ~(1 << (7 - j)); // write 0
        } else i |= (1 << (7 - j)); // if the pin is high, write 1
        while (DIGITAL_PIN_READ(DHT11_DATA_PORT, DHT11_DATA_BIT)); // wait for the pin to go low
    }
    return i;
}

uint8_t DHT11_GetData(uint8_t* Temp_byte1, uint8_t* Temp_byte2, uint8_t* Rh_byte1, uint8_t* Rh_byte2) {
    
    uint8_t check;
    DHT11_Start();
    DHT11_Check_Response();

    // Read 40 bits (5 Bytes) of data
    *Rh_byte1 = read_data();
    *Rh_byte2 = read_data();

    *Temp_byte1 = read_data();
    *Temp_byte2 = read_data();

    check = read_data();

    if (check != (*Rh_byte1 + *Rh_byte2 + *Temp_byte1 + *Temp_byte2)) return DHT11_ERROR_CHECKSUM;
    
    return DHT11_OK;
}