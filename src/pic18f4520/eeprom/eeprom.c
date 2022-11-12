/*============================================================================*/
#include <stdbool.h>
/*============================================================================*/
#include "eeprom.h"
#include "../../board/board_definitions/board_definitions.h"
/*============================================================================*/
uint8_t EEPROM_DataWrite(unsigned char data, unsigned char addr)
{
    
    uint8_t STATUS_INTCON = INTCONbits.GIE_GIEH;
    while( EECON1bits.WR);
    
    EEADR  = addr;
    EEDATA = data;
    
    EECON1bits.EEPGD = 0x00;
    EECON1bits.CFGS  = 0x00;
    EECON1bits.WREN  = 1;
    
    INTCONbits.GIE   = 0;
    
    EECON2 = 0x55;
    EECON2 = 0xAA;
    EECON1bits.WR    = 1;
    
    INTCONbits.GIE_GIEH = 1;
    
    
    return address;
}
/*============================================================================*/
unsigned char EEPROM_DataRead( unsigned char addr )
{
    while(EECON1bits.WR);
    
    EEADR = addr;
    EECON1bits.EEPGD = 0x00;
    EECON1bits.CFGS = 0x00;
    
    EECON1bits.RD = 0x01;
    
    return (EEDATA);
}
/*============================================================================*/
void EEPROM_ReadBlock(uint8_t* dataRead, uint8_t posStart, uint8_t length)
{
    uint8_t dataAddr = 0x00;
    
    for(dataAddr = 0; dataAddr < length; dataAddr++)
    {
        *(dataRead + (dataAddr + posStart)) = (uint8_t) EEPROM_DataRead(dataAddr + posStart);
    }   
}
/*============================================================================*/
bool EEPROM_BlanckCheck( void )
{
    uint8_t aux;
    uint8_t i;
    
    for(i = 0; i <= ADDR_END_MEMORY; i++)
    {
        aux = EEPROM_DataRead(i);
        if(aux != DEFAULT_MEMORY_DATA) return false;
    }
    
    return true;
    
}
/*============================================================================*/
void EEPROM_Erase( void )
{
    uint8_t addr;
    // EEPROM_DataWrite(unsigned char data, unsigned char addr)
    for(addr = 0; addr < ADDR_END_MEMORY; addr++)
    {
         EEPROM_DataWrite(0xFF,  addr);
    }
    
    address = ADDR_BASE;
}
/*============================================================================*/
void EEPROM_WriteBuffer(unsigned char* buffer, uint8_t length)
{
    uint8_t i;
    for(i = 0; i <= length; i++)
    {
        EEPROM_DataWrite(*(buffer + i), i);
    }
}
/*============================================================================*/