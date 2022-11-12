/*============================================================================*/ 
#ifndef TIMER_H
#define	TIMER_H
/*============================================================================*/
#include <xc.h> // include processor files - each processor file is guarded.
#include <stdint.h>
/*============================================================================*/
#define global_timer_t uint32_t 
/*============================================================================*/
global_timer_t global_timer_value = 0x01;
/*============================================================================*/
typedef enum {
    TIMER_LENGTH_16 = 0x00,
    TIMER_LENGTH_8  = 0x01
}TIMER_LENGTH;
/*============================================================================*/
typedef enum {
    TIMER_CLKO_SRC  = 0x00, 
    TIMER_T0CLK_SCR = 0x01
}TIMER_CLK_SRC;
/*============================================================================*/
typedef enum {
    TIMER_TRANSITION_LOW_HIGH = 0x00, 
    TIMER_TRANSITION_HIGH_LOW = 0x01
}TIMER_TRANSITION;
/*============================================================================*/
typedef enum {
    TIMER_PRESCALER_IS_ASSIGNED  = 0x00, 
    TIMER_PRESCALER_NOT_ASSIGNED = 0x01
}TIMER_PRESCALER_ASSIGN;
/*============================================================================*/
typedef enum {
    TIMER_PRESCALER_2 = 0b000,
    TIMER_PRESCALER_4 = 0b001,
    TIMER_PRESCALER_8 = 0b010,
    TIMER_PRESCALER_16 = 0b011,
    TIMER_PRESCALER_32 = 0b100,
    TIMER_PRESCALER_64 = 0b101,
    TIMER_PRESCALER_128 = 0b110,
    TIMER_PRESCALER_256 = 0b111
}TIMER_PRESCALER_VALUE;
/*============================================================================*/
typedef struct {
    TIMER_LENGTH           timer_length; 
    TIMER_CLK_SRC          timer_clk_src; 
    TIMER_TRANSITION  timer_transition;
    TIMER_PRESCALER_ASSIGN timer_prescaler_assign; 
    TIMER_PRESCALER_VALUE  timer_prescaler_value;
}timer_config_t;
/*============================================================================*/
#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */
/*============================================================================*/
    void Timer0_Config( timer_config_t* timerConfig );
/*============================================================================*/
    void Timer0_SetTickHook(void (*tickFunc)(global_timer_t*));
/*============================================================================*/
    void tickHook_Execute(global_timer_t* global_timer_value);
/*============================================================================*/
    uint32_t Timer0_GetGlobalTime( void );
/*============================================================================*/
    void Timer0_WaitMS( uint16_t timeWait );
/*============================================================================*/
#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* TIMER_H */

