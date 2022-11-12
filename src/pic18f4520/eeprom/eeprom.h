/*============================================================================*/
#ifndef EEPROM_H
#define	EEPROM_H
/*============================================================================*/
#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h>
#include <stdbool.h>
/*============================================================================*/
#define ADDR_BASE           0x00        // first memory address
#define ADDR_END_MEMORY     0xFF

#define DEFAULT_MEMORY_DATA 0xFF

uint8_t address    =     ADDR_BASE;
/*============================================================================*/
#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */
/*============================================================================*/
    uint8_t EEPROM_DataWrite(unsigned char data, unsigned char addr);
    unsigned char EEPROM_DataRead( unsigned char addr );
    void EEPROM_ReadBlock(uint8_t* dataRead, uint8_t start, uint8_t length);
    bool EEPROM_BlanckCheck( void );
    void EEPROM_Erase( void );
    void EEPROM_WriteBuffer(unsigned char* buffer, uint8_t length);
/*============================================================================*/
#ifdef	__cplusplus
}
#endif /* __cplusplus */
#endif	/* EEPROM_H */
/*============================================================================*/
