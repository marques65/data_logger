/*============================================================================*/
#include "display_lcd.h"
#include "../../board/board_definitions/board_definitions.h"
#include "../../pic18f4520/gpio/gpio.h"
#include "../../board/pinout/pinout.h"
#include <stdint.h>

#define STRING_TEST         "DISPLAY TESTE"
/*============================================================================*/
void DisplayLCD_Init( void )
{
    // Wait for more than 15 ms
    __delay_ms(20);
    
    // Configure display PORTx
    PORT_DIGITAL_CONFIGURE(DISPLAY_LCD_D4_PORT, 0x00);
    
    // Send High Byte
    sendNibble(0x20);
    sendNibble(0x20);
    sendNibble(0x30);
    
    // Function set: 4 Bits mode | 2 Lines display | 5x10 dots : COMMAND
    Display_SendByte((DISPLAY_FUNCTION_SET | DISPLAY_4_BITS_MODE | DISPLAY_2_LINE_MODE | DISPLAY_5_10_MATRIX), DISPLAY_COMMAND);
    
    // Entry set Mode: Increment | Disable shift : COMMAND
    Display_SendByte((DISPLAY_ENTRY_SET_MODE | DISPLAY_INCREMENT | DISPLAY_SHIFT_DIS), DISPLAY_COMMAND);
    
    
    // Display ON OFF: Display ON | Cursor ON | Cursor BLINK : COMMAND
    Display_SendByte((DISPLAY_ON_OFF | DISPLAY_ON | DISPLAY_CURSOR_ON | DISPLAY_CURSOR_BLK_EN ), DISPLAY_COMMAND);
    
    // Display Clear: 0b00000001 1.52 ms
    Display_SendByte(DISPLAY_CLEAR, DISPLAY_COMMAND);
   __delay_ms(2); 
   
   //  Set line 2 : 37 us
   // Display_SendByte((DISPLAY_DDRAM_ADD | DISPLAY_DDRAM_ADD_2_1), DISPLAY_COMMAND);
   // __delay_us(50);
    
}
/*============================================================================*/
void sendNibble(uint8_t nibble)
{
    uint8_t auxNibble = 0x00;
    
    PIN_DIGITAL_WRITE(PIN_LOW, DISPLAY_LCD_RS_PORT, DISPLAY_LCD_RS_MASK);
    
    DIGITAL_PORT_WRITE(DISPLAY_LCD_D4_PORT, ((DIGITAL_PORT_READ(DISPLAY_LCD_D4_PORT) & 0x0F) | nibble));
    PIN_DIGITAL_WRITE(PIN_HIGH, DISPLAY_LCD_EN_PORT, DISPLAY_LCD_EN_MASK);
    __delay_us(100);
    PIN_DIGITAL_WRITE(PIN_LOW, DISPLAY_LCD_EN_PORT, DISPLAY_LCD_EN_MASK);
    
    __delay_ms(1);
}
/*============================================================================*/
void Display_SendByte(uint8_t byte, uint8_t comm)
{
    uint8_t auxByte = 0x00;
    
    PIN_DIGITAL_WRITE(comm, DISPLAY_LCD_RS_PORT, DISPLAY_LCD_RS_MASK);
    
    auxByte = (byte & 0xF0);
    
    DIGITAL_PORT_WRITE(DISPLAY_LCD_D4_PORT, ((DIGITAL_PORT_READ(DISPLAY_LCD_D4_PORT) & 0x0F) | auxByte));
    
    PIN_DIGITAL_WRITE(PIN_LOW, DISPLAY_LCD_EN_PORT, DISPLAY_LCD_EN_MASK);
    PIN_DIGITAL_WRITE(PIN_HIGH, DISPLAY_LCD_EN_PORT, DISPLAY_LCD_EN_MASK);
    __delay_us(100);
    PIN_DIGITAL_WRITE(PIN_LOW, DISPLAY_LCD_EN_PORT, DISPLAY_LCD_EN_MASK);
    
    auxByte = (byte << 0x04);
    
    DIGITAL_PORT_WRITE(DISPLAY_LCD_D4_PORT, auxByte);
    
    PIN_DIGITAL_WRITE(PIN_LOW, DISPLAY_LCD_EN_PORT, DISPLAY_LCD_EN_MASK);
    PIN_DIGITAL_WRITE(PIN_HIGH, DISPLAY_LCD_EN_PORT, DISPLAY_LCD_EN_MASK);
    __delay_us(100);
    PIN_DIGITAL_WRITE(PIN_LOW, DISPLAY_LCD_EN_PORT, DISPLAY_LCD_EN_MASK);
    
    __delay_ms(1);
}
/*============================================================================*/
void Display_WriteByte(uint8_t byte)
{
    uint8_t auxByte = 0x00;
    PIN_DIGITAL_WRITE(PIN_HIGH, DISPLAY_LCD_RS_PORT, DISPLAY_LCD_RS_MASK);
    
    auxByte = (byte & 0xF0);
    DIGITAL_PORT_WRITE(DISPLAY_LCD_D4_PORT, ((DIGITAL_PORT_READ(DISPLAY_LCD_D4_PORT) & 0x0F) | auxByte));
    
    PIN_DIGITAL_WRITE(PIN_LOW, DISPLAY_LCD_EN_PORT, DISPLAY_LCD_EN_MASK);
    PIN_DIGITAL_WRITE(PIN_HIGH, DISPLAY_LCD_EN_PORT, DISPLAY_LCD_EN_MASK);
    __delay_us(100);
    PIN_DIGITAL_WRITE(PIN_LOW, DISPLAY_LCD_EN_PORT, DISPLAY_LCD_EN_MASK);
   
    
    auxByte = (byte << 0x04);
    DIGITAL_PORT_WRITE(DISPLAY_LCD_D4_PORT, ((DIGITAL_PORT_READ(DISPLAY_LCD_D4_PORT) & 0x0F) | auxByte));
    
    PIN_DIGITAL_WRITE(PIN_LOW, DISPLAY_LCD_EN_PORT, DISPLAY_LCD_EN_MASK);
    PIN_DIGITAL_WRITE(PIN_HIGH, DISPLAY_LCD_EN_PORT, DISPLAY_LCD_EN_MASK);
    __delay_us(100);
    PIN_DIGITAL_WRITE(PIN_LOW, DISPLAY_LCD_EN_PORT, DISPLAY_LCD_EN_MASK);
    
    __delay_ms(2);
}
/*============================================================================*/
void Display_WriteString(char* string, uint8_t length, uint8_t address)
{
    uint8_t auxLength = 0x00; 
    
    
    for(auxLength = 0; auxLength < length - 1; auxLength++)
    {
        Display_WriteByte((uint8_t)string[auxLength]);
    }
}
/*============================================================================*/