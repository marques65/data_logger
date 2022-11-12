/*============================================================================*/
#ifndef BLUETOOTH_HC_06_H
#define	BLUETOOTH_HC_06_H
/*============================================================================*/
#include <xc.h>
#include <stdbool.h>
#include <stdint.h>
#include "../../board/board_definitions/board_definitions.h"
/*============================================================================*/
#define BLUETOOTH_DEFAULT_BAUD  9600
#define BLUETOOTH_NAME          BOARD_NAME
#define BLUETOOTH_BAUD          UART_BAUD
#define BLUETOOTH_PIN           BOARD_PIN
/*============================================================================*/
char BLUETOOTH_NAME_COMM[]  =    "AT+NAME";
char BLUETOOTH_PIN_COMM[]   =    "AT+PINXYZW";
char BLUETOOTH_BAUD_COMM[8]  =    "AT+BAUD";
/*============================================================================*/
typedef enum {
    BAUD_1200   = 0x01, 
    BAUD_2400   = 0x02, 
    BAUD_4800   = 0x03, 
    BAUD_9600   = 0x04, 
    BAUD_19200  = 0x05, 
    BAUD_38400  = 0x06, 
    BAUD_57600  = 0x07, 
    BAUD_115200 = 0x08,         
}BLUETOOTH_BAUD_AVALIABLE;
/*============================================================================*/
#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */
/*============================================================================*/
    void Bluetooth_HC_06_Configure(void);
    void Bluetooth_HC_06_WriteString( char* string, uint8_t length );
    void Bluetooth_HC_06_WriteByte(char byte);
    uint8_t Bluetooth_HC_06_Read( void );
    bool User_GetState( void );
    bool User_SetState( bool state );
/*============================================================================*/
#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* BLUETOOTH_HC_06_H */

