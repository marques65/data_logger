/*============================================================================*/ 
#ifndef ADC_H
#define	ADC_H
/*============================================================================*/ 
#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h>
/*============================================================================*/
typedef enum {
    CHANNEL_AN0 = 0b0000,
    CHANNEL_AN1 = 0b0001,
    CHANNEL_AN2 = 0b0010,
    CHANNEL_AN3 = 0b0011,
    CHANNEL_AN4 = 0b0100,
    CHANNEL_AN5 = 0b0101,
    CHANNEL_AN6 = 0b0110,
    CHANNEL_AN7 = 0b0111,
    CHANNEL_AN8 = 0b1000,
    CHANNEL_AN9 = 0b1001,
    CHANNEL_AN10 = 0b1010,
    CHANNEL_AN11 = 0b1011,
    CHANNEL_AN12 = 0b1100
}ADC_CHANNEL;
/*============================================================================*/ 
typedef enum 
{
    INTERNAL_NEGATIVE_REFERENCE = 0b00, 
    EXTERNAL_NEGATIVE_REFERENCE =  0b01
}NEGATIVE_VOLTAGE_REFERENCE;
/*============================================================================*/ 
typedef enum 
{
    INTERNAL_POSITIVE_REFERENCE = 0b00, 
    EXTERNAL_POSITIVE_REFERENCE =  0b01
}POSITIVE_VOLTAGE_REFERENCE;
/*============================================================================*/ 
typedef enum 
{
    LEFT_JUSTIFIED = 0b00,
    RIGHT_JUSTIFIED = 0b01
}RESULT_FORMAT;
/*============================================================================*/ 
typedef enum 
{
    TAD_20 = 0b111,
    TAD_16 = 0b110,
    TAD_12 = 0b101,
    TAD_8 = 0b100,
    TAD_6 = 0b011,
    TAD_4 = 0b010,
    TAD_2 = 0b001,
    TAD_0 = 0b000
}ACQUISITION_TIME;
/*============================================================================*/ 

typedef enum {
    FRC     = 0b111,
    FOSC_64 = 0b110,
    FOSC_16 = 0b101,
    FOSC_4  = 0b100,
    FRC_1   = 0b011,
    FOSC_32 = 0b010,
    FOSC_8  = 0b001,
    FOSC_2  = 0b000
}ADC_CLOCK;
/*============================================================================*/ 
typedef struct
{
    uint8_t adc_channel;
    uint8_t negative_reference;
    uint8_t positive_reference;
    uint8_t result_format;
    uint8_t acquisition_time;
    uint8_t adc_clock;
    
}adc_config_t;

/*============================================================================*/ 
#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */
/*============================================================================*/ 
    void ADC_Configure( adc_config_t* adcConfig );
    uint16_t ADC_StartConversion( void );
/*============================================================================*/ 
#ifdef	__cplusplus
}
#endif /* __cplusplus */
#endif	/* ADC_H */
/*============================================================================*/ 
