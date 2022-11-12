/*============================================================================*/
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
/*============================================================================*/
#include "../../pic18f4520/timer/timer.h"
#include "../../pic18f4520/gpio/gpio.h"
#include "../../board/pinout/pinout.h"
/*============================================================================*/
#include "../../board/board_definitions/board_definitions.h"
/*============================================================================*/
#include "main-app.h"
#include "../../app/dht11/dht11.h"
#include "../../app/display_lcd/display_lcd.h"
#include "../../app/read_voltage/read_voltage.h"
#include "../../app/bluetooth-hc-06/bluetooth_hc_06.h"
#include "../../board/peripheral-controller/peripheral_controller.h"
#include "../../pic18f4520/eeprom/eeprom.h"
/*============================================================================*/
static bool log = false;
#define PRIMEIRO_LOG    "prim. log"
#define SEGUNDO_LOG     "seg. log"
#define TEM_ENERGIA     "TEM ENERGIA"
char segundo[sizeof (SEGUNDO_LOG)];
static uint8_t count = 0x00;
char vetorTempLocal[4] = {35, 0, 0xf8, 0x43};
char vetorHumLocal[3] = {90, 5, 0x25};
bool TimeIsElapsed = false;

uint8_t i = 0x00;


char vetorTemp [6] = "TEMP: ";
char vetorHum [7] = "HUM : ";

extern uint8_t Rh_byte1;
extern uint8_t Rh_byte2;
extern uint8_t Temp_byte1;
extern uint8_t Temp_byte2;
extern uint16_t sum;

/*============================================================================*/
void main_application(void* args) {

    static bool localUserState = false;

    static uint8_t localVoltageStatus = 0x00;

    uint8_t aux = 0x00;
    uint8_t aux1 = 0x00;
    uint8_t aux2 = 0x00;
    uint8_t aux3 = 0x00;
    
    uint8_t auxAddress = 0x00;
    
    uint8_t Temp_aux1;
    uint8_t Temp_aux2;
    uint8_t Rhum_aux1;
    uint8_t Rhum_aux2;

    while (1) {

        // Funcionando 
        if (TimeIsElapsed) {
            
            DHT11_Start();
            DHT11_Check_Response();

            // Read 40 bits (5 Bytes) of data
            Rh_byte1 = read_data();
            Rh_byte2 = read_data();

            Temp_byte1 = read_data();
            Temp_byte2 = read_data();

            sum = read_data();
            
            // Verifica que a leitura foi bem suces
            if(sum == (Temp_byte1 + Temp_byte2 + Rh_byte1 + Rh_byte2))
            {
                Temp_aux1 = (Temp_byte1 / 10) + 48;
                Temp_aux2 = (Temp_byte1 % 10) + 48;
                
                Rhum_aux1 = (Rhum_aux1 / 10) + 48;
                Rhum_aux2 = (Rhum_aux2 % 10) + 48;
                
                /* Get User Status */
                localUserState = User_GetState();

                Display_SendByte(DISPLAY_CLEAR, DISPLAY_COMMAND);
                __delay_ms(3);
                Display_WriteString("HUMD: ", 7, 0);
                Display_WriteByte((Rh_byte1 / 10) + 48); 
                Display_WriteByte(((Rh_byte1 % 10)) + 48);
                
                Display_WriteByte(0x2e);                // . simbol
                
                Display_WriteByte((Rh_byte2 / 10) + 48);  
                Display_WriteByte(((Rh_byte2 % 10)) + 48);
                Display_WriteByte(0x25);                // % simbol

                Display_SendByte((DISPLAY_DDRAM_ADD | DISPLAY_DDRAM_ADD_2_1), DISPLAY_COMMAND);
                Display_WriteString("TEMP: ", 7, 0);
                Display_WriteByte((Temp_byte1 / 10) + 48);
                Display_WriteByte(((Temp_byte1 % 10)) + 48);
                
                Display_WriteByte(0x2e);                // . simbol
                
                Display_WriteByte((Temp_byte2 / 10) + 48);
                Display_WriteByte(((Temp_byte2 % 10)) + 48);
                
                Display_WriteByte(0xDF);                // °
                Display_WriteByte(0x43);
                
                Display_WriteByte(0x20);
                
                Display_WriteByte(0xF1);
                Display_WriteByte(0x32);
               
                
                
                
                if (localUserState) {
                    // Existe um Log para enviar para o usuário
                    if (log) {
                        Bluetooth_HC_06_WriteString("\n***ULTIMO LOG***\n", 18);
                        for (aux2 = 0x00; aux2 <= 0x08; aux2 += 2) {
                            
                            aux = EEPROM_DataRead(aux2);
                            
                            if (aux != 0xFF)
                            {
                                aux1 = aux2;
                                aux1++;
                                Bluetooth_HC_06_WriteString("\nTemperatura:   ", 17);
                                Bluetooth_HC_06_WriteByte((aux / 10) + 48);    
                                Bluetooth_HC_06_WriteByte((aux % 10) + 48);
                                
                                aux3 = EEPROM_DataRead(aux1);
                                
                                Bluetooth_HC_06_WriteString("   Umidade:  ", 14);
                                Bluetooth_HC_06_WriteByte((aux3 / 10) + 48);    
                                Bluetooth_HC_06_WriteByte((aux3 % 10) + 48);
                            }
                        }

                        log = false;
                        address = ADDR_BASE;
                        
                        return;
                    } else // Não existe log antigo -> Enviar dados atuais
                    {
                        /*
                        Display_SendByte(DISPLAY_CLEAR, DISPLAY_COMMAND);
                        __delay_ms(3);
                        Display_WriteString("Nao tem Log", 12, 0);
                        __delay_ms(1000);
                        */
                        Bluetooth_HC_06_WriteString("\n***ENVIA LOG ATUAL: ***\n", 25);
                        Bluetooth_HC_06_WriteString("\nTemperatura:   ", 17);
                        Bluetooth_HC_06_WriteByte((Temp_byte1 / 10) + 48);
                        Bluetooth_HC_06_WriteByte((Temp_byte1 % 10) + 48);
                                
                        Bluetooth_HC_06_WriteString("   Umidade:  ", 14);
                        Bluetooth_HC_06_WriteByte((Rh_byte1 / 10 ) + 48);
                        Bluetooth_HC_06_WriteByte((Rh_byte1 % 10 ) + 48);
                    }

                } else // Usuário não conectado, devemos ver a condição da energia
                {
                    
                    // Verifica o estado do pino de energia
                    localVoltageStatus = Voltage_Read();

                    if (localVoltageStatus) {
                        Display_SendByte(DISPLAY_CLEAR, DISPLAY_COMMAND);
                        __delay_ms(5);
                        Display_WriteString("Tem energia", 12, 0);
                        __delay_ms(500);
                    }
                    else
                    {
                        /*
                        Display_SendByte(DISPLAY_CLEAR, DISPLAY_COMMAND);
                        __delay_ms(5);
                        Display_WriteString("Nao tem energia", 16, 0);
                        __delay_ms(500);
                        */
                        if (address <= 0x08) {
                            // Escreve a temperatura registrada
                            
                            // EEPROM_DataWrite((0x41 + i), address);
                            EEPROM_DataWrite(Temp_byte1, address);
                            
                            auxAddress = address;
                            auxAddress++;
                            
                            EEPROM_DataWrite(Rh_byte1, auxAddress);
                            __delay_ms(1000);
                            /**/
                            /*
                            Display_SendByte(DISPLAY_CLEAR, DISPLAY_COMMAND);
                            __delay_ms(5);
                            Display_WriteString("EEPROM:", 8, 0);
                            */
                            /*
                            Display_WriteByte(0x20);
                            Display_WriteByte(Temp_aux1);
                            Display_WriteByte(Temp_aux2);
                            
                            Display_WriteByte(0x20);
                            Display_WriteByte(Rhum_aux1);
                            Display_WriteByte(Rhum_aux2);
                            

                            Display_WriteByte(0x20);
                            Display_WriteByte(address + 48);
                            Display_WriteByte(auxAddress + 48);
                            __delay_ms(1000);
                            */
                            address += 2;
                            
                        } else {
                            Display_SendByte(DISPLAY_CLEAR, DISPLAY_COMMAND);
                            __delay_ms(5);
                            Display_WriteString("FULL MEM.", 10, 0);
                            __delay_ms(350);
                        }

                        log = true;
                    }
                }
            } else // erro no sensor
            {
                Display_SendByte(DISPLAY_CLEAR, DISPLAY_COMMAND);
                __delay_ms(3);
                Display_WriteString("Erro Sensor", 12, 0);
                __delay_ms(2000);
            }

            TimeIsElapsed = false;
        }
    }
}

/*============================================================================*/
void Display_Update(char* temp, char* hum) {
    Display_SendByte(DISPLAY_CLEAR, DISPLAY_COMMAND);
    __delay_ms(5);

    Display_WriteString(vetorTemp, sizeof (vetorTemp), 0); // Temp: 

    Display_WriteByte((temp[0] / 10) + 0x30);
    Display_WriteByte((temp[0] % 10) + 0x30); // TEMP: XX

    Display_WriteByte(0xDF); //  TEMP: XX.X°
    Display_WriteByte(0x43); //  TEMP: XX.X°C

    // Escreve segunda linha 1° coluna
    Display_SendByte((DISPLAY_DDRAM_ADD | DISPLAY_DDRAM_ADD_2_1), DISPLAY_COMMAND);
    __delay_us(500);


    Display_WriteString(vetorHum, sizeof (vetorHum), 0); // HUM: 

    Display_WriteByte((hum[0] / 10) + 0x30);
    Display_WriteByte((hum[0] % 10) + 0x30); // HUM: XX

    Display_WriteByte(0x25); // HUM: XX.X%

}
/*============================================================================*/