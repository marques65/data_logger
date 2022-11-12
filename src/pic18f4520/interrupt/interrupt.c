/*============================================================================*/
#include "interrupt.h"
/*============================================================================*/
void Interrupt_GlobalEnable( void ) 
{
    /*
     * IPEN: Interrupt Priority Enable bit
            1 = Enable priority levels on interrupts
            0 = Disable priority levels on interrupts (PIC16CXXX Compatibility mode)
    */
    RCONbits.IPEN = 0x01;
    
    /*
     * Global Interrupt Enable bit
            When IPEN = 0:
                1 = Enables all unmasked interrupts
                0 = Disables all interrupts
            When IPEN = 1:
                1 = Enables all high-priority interrupts
                0 = Disables all interrupts 
     */
    INTCONbits.GIE_GIEH = 0x01;
    
    /*
     * PEIE/GIEL: Peripheral Interrupt Enable bit
            When IPEN = 0:
                1 = Enables all unmasked peripheral interrupts
                0 = Disables all peripheral interrupts
            When IPEN = 1:
                1 = Enables all low-priority peripheral interrupts
                0 = Disables all low-priority peripheral interrupts
     */
    INTCONbits.PEIE_GIEL = 0x01;   
}

/*============================================================================*/