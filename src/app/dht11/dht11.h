/*============================================================================*/
#ifndef DHT11_H
#define	DHT11_H
/*============================================================================*/
#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h>
/*============================================================================*/
#define DHT11_OK                 0
#define DHT11_ERROR_TIMEOUT      1
#define DHT11_ERROR_CHECKSUM     2
/*============================================================================*/
#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */
/*============================================================================*/
    
    void DHT11_Start( void );
    void DHT11_Check_Response(void);
    uint8_t read_data (void);
    uint8_t DHT11_GetData(uint8_t* Temp_byte1, uint8_t* Temp_byte2, uint8_t* Rh_byte1, uint8_t* Rh_byte2);
    
    
/*============================================================================*/
#ifdef	__cplusplus
}
#endif /* __cplusplus */
#endif	/* DHT11_H */
/*============================================================================*/
