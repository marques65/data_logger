#include <xc.h>
#include <stdio.h>
#include <stdbool.h>
/*============================================================================*/
#include "pic18f4520/fuse/fuse.h"
/*============================================================================*/
#include "pic18f4520/gpio/gpio.h"
#include "board/pinout/pinout.h"
/*============================================================================*/
#include "pic18f4520/timer/timer.h"
#include "pic18f4520/interrupt/interrupt.h"
#include "pic18f4520/serial/serial.h"
/*============================================================================*/
#include "board/board_definitions/board_definitions.h"
/*============================================================================*/
#include "app/main-app/main-app.h"
#include "app/bluetooth-hc-06/bluetooth_hc_06.h"
#include "app/display_lcd/display_lcd.h"
#include "app/dht11/dht11.h"
/*============================================================================*/
#include "pic18f4520/adc/adc.h"
#include "pic18f4520/eeprom/eeprom.h"
/*============================================================================*/
timer_config_t timerConfig = {
    .timer_length = TIMER_LENGTH_16,
    .timer_clk_src = TIMER_CLKO_SRC,
    .timer_transition = TIMER_TRANSITION_LOW_HIGH,
    .timer_prescaler_assign = TIMER_PRESCALER_IS_ASSIGNED,
    .timer_prescaler_value = TIMER_PRESCALER_256
};
/*============================================================================*/
serial_config_t serialConfig = {
    .serial_sync_com = SERIAL_ASSYNC_MODE,
    .serial_data_length = SERIAL_DATA_LENGTH_8,
    .serial_op_mode = SERIAL_MASTER_MODE,
    .serial_desired_baud = SPEED_SERIAL
};
/*============================================================================*/
extern global_timer_t global_timer_value;
/*============================================================================*/
uint8_t count = 0x00;
volatile char vector[3] = {0, 0, 0};
static uint8_t i = 0x00;
char byteReceived;
uint8_t firstReceive;
/*============================================================================*/
static global_timer_t t = 0;
extern bool TimeIsElapsed;

/*============================================================================*/
void tickHook_func(global_timer_t *timer_value) {
    (*timer_value)++;
    if ((*timer_value - t) >= TIME_TO_SEND_SEG) {
        t = (*timer_value);
        TimeIsElapsed = true;
    }
}

/*============================================================================*/
void __interrupt() TC0INT(void) {


    // Interrupção Timer 0
    if (INTCONbits.TMR0IF == 0x01) {

        tickHook_Execute(&global_timer_value);

        TMR0 = 0xD238; // TMR0 = 0x9E58; 
        INTCONbits.T0IF = 0x00; // Clean Timer Flag 
    }

    // Interrupção recepção serial
    if (PIR1bits.RCIF) {
        byteReceived = RCREG;
        Serial_Transmit(byteReceived);
        
        if(byteReceived == 0x43)
        {
            DIGITAL_PIN_TOGGLE(LED_HEARTBEAT1_PORT, LED_HEARTBEAT1_MASK);
            User_SetState(true);
        }else if(byteReceived == 0x44)
        {
            DIGITAL_PIN_TOGGLE(LED_HEARTBEAT2_PORT, LED_HEARTBEAT2_MASK);
            User_SetState(false);
        }
        
        byteReceived = 0x00;
        PIR1bits.RCIF = 0x00;
    }
}

/*============================================================================*/
void main(void) {
    
    uint8_t a;
    uint8_t b = 0x00;
    /**/
    Interrupt_GlobalEnable();
    Timer0_Config(&timerConfig);
    Timer0_SetTickHook(tickHook_func);
     
    Serial_1_Config(&serialConfig);

    PIN_CONFIGURE_DIGITAL(PIN_OUTPUT, LED_HEARTBEAT1_PORT, LED_HEARTBEAT1_MASK);
    PIN_CONFIGURE_DIGITAL(PIN_OUTPUT, LED_HEARTBEAT2_PORT, LED_HEARTBEAT2_MASK);
    PIN_CONFIGURE_DIGITAL(PIN_INPUT, VOLTAGE_INPUT_PORT, VOLTAGE_INPUT_MASK);
    
    // StartSystem(NULL);
    __delay_ms(300);
    DisplayLCD_Init();
    
    
    EEPROM_Erase();
    
    uint8_t Rh_byte1, Rh_byte2, Temp_byte1, Temp_byte2;
    uint16_t sum, RH, TEMP;
    uint8_t check = 0;
    
   __delay_ms(2000);
    
    while (1) { 
        main_application(NULL);
    }
    return;
}
/*============================================================================*/
/*============================================================================*/