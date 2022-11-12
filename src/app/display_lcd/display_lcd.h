/*============================================================================*/
#ifndef DISPLAY_LCD_H
#define	DISPLAY_LCD_H
/*============================================================================*/
#include <xc.h> 
#include <stdint.h>
/*============================================================================*/
#define DISPLAY_COMMAND             0
#define DISPLAY_WRITE               1   
/*============================================================================*/
#define DISPLAY_FUNCTION_SET        0b00100000

#define DISPLAY_4_BITS_MODE         0b00000000
#define DISPLAY_8_BITS_MODE         0b00010000

#define DISPLAY_2_LINE_MODE         0b00001000
#define DISPLAY_1_LINE_MODE         0b00000000

#define DISPLAY_7_8_MATRIX          0b00000000
#define DISPLAY_5_10_MATRIX         0b00000100
/*============================================================================*/
#define DISPLAY_ENTRY_SET_MODE      0b00000100
                
#define DISPLAY_INCREMENT           0b00000010
#define DISPLAY_DECREMENT           0b00000000

#define DISPLAY_SHIFT_EN            0b00000001
#define DISPLAY_SHIFT_DIS           0b00000000
/*============================================================================*/
#define DISPLAY_ON_OFF              0b00001000

#define DISPLAY_ON                  0b00000100
#define DISPLAY_OFF                 0b00000000

#define DISPLAY_CURSOR_ON           0b00000010
#define DISPLAY_CURSOR_OFF          0b00000000

#define DISPLAY_CURSOR_BLK_EN       0b00000001
#define DISPLAY_CURSOR_BLK_DIS      0b00000000
/*============================================================================*/
#define DISPLAY_DDRAM_ADD           0b10000000
#define DISPLAY_DDRAM_ADD_2_1       0b01000000
#define DISPLAY_DDRAM_ADD_1_1       0b00000000
/*============================================================================*/
#define DISPLAY_CLEAR               0b00000001
/*============================================================================*/
#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */
/*============================================================================*/
    void DisplayLCD_Init( void );
    void Display_SendByte(uint8_t byte, uint8_t comm);
    void Display_WriteByte(uint8_t byte);
    void Display_WriteString(char* string, uint8_t length, uint8_t address);
    void sendNibble(uint8_t nibble);
/*============================================================================*/
#ifdef	__cplusplus
}
#endif /* __cplusplus */
#endif	/* DISPLAY_LCD_H */
/*============================================================================*/
