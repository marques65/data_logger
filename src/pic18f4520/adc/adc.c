/*============================================================================*/
#include <stdint.h>
/*============================================================================*/
#include "adc.h"
/*============================================================================*/
#include "../../pic18f4520/serial/serial.h"
/*==============================================================================
 * 1. Configure the A/D module:
 *      ? Configure analog pins, voltage reference and digital I/O (ADCON1) 
 *      ? Select A/D input channel (ADCON0)
 *      ? Select A/D acquisition time (ADCON2)
 *      ? Select A/D conversion clock (ADCON2)
 *      ? Turn on A/D module (ADCON0)
 * 2. Configure A/D interrupt (if desired):
 *      ? Clear ADIF bit
 *      ? Set ADIE bit
 *      ? Set GIE bit
 * 3. Wait the required acquisition time (if required).
 * 4. Start conversion:
 *      ? Set GO/DONE bit (ADCON0 register)
 * 
 * 5. Wait for A/D conversion to complete, by either:
 *      ? Polling for the GO/DONE bit to be cleared 
 *                  OR 
 *      ? Waiting for the A/D interrupt
 * 6. Read A/D Result registers (ADRESH:ADRESL); clear bit ADIF, if required.
 * 7. For next conversion, go to step 1 or step 2, as required. 
 *    The A/D conversion time per bit is defined as TAD. A minimum wait of 2 TAD is
 *    required before the next acquisition starts
 * ===========================================================================*/
/*
 * Tosc = 1 / 10 MHz = 0.1e-6 : Tosc
 * TAD > 0.7 us
 * 8 Tosc -> 8 * 0.1e-6 = 0.8e-6 s : Tad
 * TADq > 2.4 us -> 4 TAD = 3.2 us
 * 
 */
void ADC_Configure( adc_config_t* adcConfig)
{
    
    
    TRISAbits.RA0 = 0x01;
    // ? Configure analog pins, voltage reference and digital I/O (ADCON1) 
    
    // Negative voltage reference configure
    if(adcConfig->negative_reference == EXTERNAL_NEGATIVE_REFERENCE)
        ADCON1bits.VCFG1 = 0x01;
    else 
        ADCON1bits.VCFG1 = 0x00;
    
    // Positive voltage reference configure
    if(adcConfig->positive_reference == EXTERNAL_POSITIVE_REFERENCE)
        ADCON1bits.VCFG0 = 0x01;
    else 
        ADCON1bits.VCFG0 = 0x00;
    
    // Configure pins as Analogic input (AN0) @@TODO: Selection by struct field
    ADCON1bits.PCFG = 0x00;
    
    // ? Select A/D input channel (ADCON0)
    ADCON0bits.CHS = adcConfig->adc_channel;
    
    // ? Select A/D acquisition time (ADCON2)
    ADCON2bits.ACQT = adcConfig->acquisition_time;
    
    
    // ? Select A/D conversion clock (ADCON2)
    ADCON2bits.ADCS  = adcConfig->adc_clock;
    
    // ? Turn on A/D module (ADCON0) 
    ADCON0bits.ADON = 0x01;
}
/*============================================================================*/
uint16_t ADC_StartConversion( void )
{
    uint16_t auxADCResult = 0x00;
    
    ADCON0bits.GO_DONE = 0x01;
    while(ADCON0bits.GO_DONE);
    
    
    auxADCResult = (ADRESH << 0x04) | ADRESL;
    
    return auxADCResult;
}