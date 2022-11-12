/*============================================================================*/
#include "timer.h"
#include <stdint.h>
/*============================================================================*/
static void (*tickHook_func_prt)(global_timer_t*);
/*============================================================================*/
    void Timer0_Config( timer_config_t* timerConfig )
{
    /*
     * TMR0ON: Timer0 On/Off Control bit
     *   1 = Enables Timer0
     *   0 = Stops Timer0 
    */
    T0CONbits.TMR0ON = 0x00;
    
    
    /*T08BIT: Timer0 8-Bit/16-Bit Control bit
     *       1 = Timer0 is configured as an 8-bit timer/counter
     *      0 = Timer0 is configured as a 16-bit timer/counter  
    */
    
    T0CONbits.T08BIT = timerConfig->timer_length;
    
    /*
     * T0CS: Timer0 Clock Source Select bit
     *       1 = Transition on T0CKI pin
     *       0 = Internal instruction cycle clock (CLKO)
    */
    T0CONbits.T0CS = timerConfig->timer_clk_src; 
    
    
    /*
         * PSA: Timer0 Prescaler Assignment bit
         *      1 = TImer0 prescaler is not assigned. Timer0 clock input bypasses prescaler.
         *      0 = Timer0 prescaler is assigned. Timer0 clock input comes from prescaler output.
         */
    if(!(T0CONbits.PSA =  timerConfig->timer_prescaler_assign))
    {
        
        
        /*
         * T0PS<2:0>: Timer0 Prescaler Select bits
         *  111 = 1:256 Prescale value      011 = 1:16 Prescale value
         *  110 = 1:128 Prescale value      010 = 1:8  Prescale value
         *  101 = 1:64  Prescale value      001 = 1:4  Prescale value
         *  100 = 1:32  Prescale value      000 = 1:2  Prescale value
         */
        T0CONbits.T0PS = timerConfig->timer_prescaler_value;
    }
    
    /*
     * ========================================================================*
     *                              INTERRUPT ENABLE
     * ========================================================================*
    */
    
    /*
     * 
     * TMR0IE: TMR0 Overflow Interrupt Enable bit
     *      1 = Enables the TMR0 overflow interrupt
            0 = Disables the TMR0 overflow interrupt 
    */
    INTCONbits.TMR0IE = 0x01;
    /*
     * TMR0IP: TMR0 Overflow Interrupt Priority bit
     *      1 = High priority
            0 = Low priority
     */
    INTCON2bits.TMR0IP = 0x01;
    
    
    // TMR0 = 0xD9D9;
    TMR0 = 0xD238;
    // TMR0 = 0xE17B;
    
    T0CONbits.TMR0ON = 0x01;
}
/*============================================================================*/
uint32_t Timer0_GetGlobalTime( void )
{
    return global_timer_value;
}
/*============================================================================*/
void Timer0_SetTickHook(void (*tickFunc)(global_timer_t*))
{
    tickHook_func_prt = tickFunc;
}
/*============================================================================*/
void tickHook_Execute(global_timer_t* global_timer_value)
{
    if(tickHook_func_prt != NULL)
    {
        tickHook_func_prt(global_timer_value);
    }
}
/*============================================================================*/
void Timer0_WaitMS(uint16_t timerWait)
{
    static uint32_t timeStart; 
    timeStart = global_timer_value; 
    
    while((global_timer_value - timeStart) <= timerWait){
        
    }
}
/*============================================================================*/