/*============================================================================*/
#ifndef XC_HEADER_TEMPLATE_H
#define	XC_HEADER_TEMPLATE_H
/*============================================================================*/
// Oscillator Freq
#define _XTAL_FREQ          12000000UL

// Peripheral Definitions
#define SERIAL_INTERFACE    UART
#define UART_BAUD           9600


// Board Definitions
#define BOARD_NAME          "DATA LOGGER v0.01"
#define BOARD_PIN           "1234"

// Bluetooth 
#define START_BLUETOOTH     "START_BLUETOOTH"

// String To Send User 
#define STRING_TEMP "TEMP: "
#define STRING_HUM  "HUM: "

#define DEFAULT_DATA_VALUE  "XX.X"


char string_temp[11] = STRING_TEMP;
char string_hum[sizeof(STRING_TEMP) + sizeof(DEFAULT_DATA_VALUE)] = STRING_HUM;

// DHT11 STRINGS
#define DHT11_WORKING       "DHT11 OK"
#define DHT11_TIMEOUT       "DHT11 TIMEOUT"


// Data logger Commands
#define DATA_LOGGER_SEND_BACKUP     "<SBK>"
#define DATA_LOGGER_DELETE_BACKUP   "<DBK>"

// Time to send data, in ms
#define TIME_TO_SEND_SEG    5
/*============================================================================*/
#endif	/* BOARD_DEFINITIONS_H */
/*============================================================================*/
