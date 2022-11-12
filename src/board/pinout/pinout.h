/*============================================================================*/
#ifndef PINOUT_H
#define PINOUT_H
/*==============================================================================
 *                                  LED 
 ===============================================================================
 */
#define LED_HEARTBEAT1_PORT             B
#define LED_HEARTBEAT1_BIT              0
#define LED_HEARTBEAT1_MASK             (1 << LED_HEARTBEAT1_BIT)

#define LED_HEARTBEAT2_PORT             B
#define LED_HEARTBEAT2_BIT              1
#define LED_HEARTBEAT2_MASK             (1 << LED_HEARTBEAT2_BIT)

#define LED_HEARTBEAT3_PORT             A 
#define LED_HEARTBEAT3_BIT              4
#define LED_HEARTBEAT3_MASK             (1 << LED_HEARTBEAT3_BIT)
/*==============================================================================
 *                              SENSOR DHT11
 ===============================================================================
 */
#define DHT11_DATA_PORT                 D
#define DHT11_DATA_BIT                  1
#define DHT11_DATA_MASK                 (1 << DHT11_DATA_BIT)

/*==============================================================================
 *                              DISPLAY LCD
 ===============================================================================
 */
#define DISPLAY_LCD_D4_PORT             B
#define DISPLAY_LCD_D4_BIT              4
#define DISPLAY_LCD_D4_MASK             (1 << DISPLAY_LCD_D4_BIT)

#define DISPLAY_LCD_D5_PORT             B
#define DISPLAY_LCD_D5_BIT              5
#define DISPLAY_LCD_D5_MASK             (1 << DISPLAY_LCD_D5_BIT)

#define DISPLAY_LCD_D6_PORT             B
#define DISPLAY_LCD_D6_BIT              6
#define DISPLAY_LCD_D6_MASK             (1 << DISPLAY_LCD_D6_BIT)

#define DISPLAY_LCD_D7_PORT             B
#define DISPLAY_LCD_D7_BIT              7
#define DISPLAY_LCD_D7_MASK             (1 << DISPLAY_LCD_D7_BIT)

#define DISPLAY_LCD_RS_PORT             B
#define DISPLAY_LCD_RS_BIT              3
#define DISPLAY_LCD_RS_MASK             (1 << DISPLAY_LCD_RS_BIT)

#define DISPLAY_LCD_EN_PORT             B
#define DISPLAY_LCD_EN_BIT              2
#define DISPLAY_LCD_EN_MASK             (1 << DISPLAY_LCD_EN_BIT)
/*==============================================================================
 *                          MODULE BLUETOOTH
 ===============================================================================
 */
#define BLUETOOTH_TX_PORT               C
#define BLUETOOTH_TX_BIT                6
#define BLUETOOTH_TX_MASK               ( 1 << BLUETOOTH_TX_BIT)

#define BLUETOOTH_RX_PORT               C
#define BLUETOOTH_RX_BIT                7
#define BLUETOOTH_RX_MASK               ( 1 << BLUETOOTH_RX_BIT ) 

/*==============================================================================
 *                              VOLTAGE INPUT
 ===============================================================================
 */
#define VOLTAGE_INPUT_PORT              D
#define VOLTAGE_INPUT_BIT               0
#define VOLTAGE_INPUT_MASK              (1 << VOLTAGE_INPUT_BIT)

/*============================================================================*/
#endif /* PINOUT_H */
/*============================================================================*/