/*============================================================================*/
#ifndef GPIO_H
#define	GPIO_H
/*============================================================================*/
#include <xc.h> // include processor files - each processor file is guarded.  
/*============================================================================*/
#define PIN_OUTPUT          0x00
#define PIN_INPUT           0x01

#define PIN_DIGITAL         0x00
#define PIN_ANALOGIC        0x01

#define PIN_HIGH            0x01
#define PIN_LOW             0x00
/*============================================================================*/
#define PASTE2B(a , b)      a##b
#define PASTE2(a , b)       PASTE2B(a, b)

#define PASTE3B(a, b, c)    a##b##c
#define PASTE3(a, b, c)     PASTE3B(a, b, c)
/*============================================================================*/
#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */
/*============================================================================*/
#define PIN_CONFIGURE_DIGITAL(type, port, mask)                                \
            if(type == PIN_OUTPUT)                                             \
                PASTE2(TRIS, port) = (PASTE2(TRIS, port) & (~mask));           \
            else                                                               \
                PASTE2(TRIS, port) = (PASTE2(TRIS, port) | mask);
/*============================================================================*/
#define PIN_DIGITAL_WRITE(value, port, mask)                                   \
            if(value == PIN_HIGH)                                              \
                PASTE2(LAT, port) = (PASTE2(PORT, port) | mask);               \
            else                                                               \
                PASTE2(LAT, port) =  (PASTE2(PORT, port) & ~(mask));
/*============================================================================*/
#define DIGITAL_PIN_READ(port, bit)                                            \
                ((PASTE2(PORT, port) >> bit)& 0b00000001)    
/*============================================================================*/
#define DIGITAL_PIN_TOGGLE(port, mask)                                         \
                   PASTE2(LAT, port) = (PASTE2(PORT, port) ^ mask);
/*============================================================================*/
#define DIGITAL_PORT_WRITE(port, value)                                        \
                PASTE2(LAT, port) = value;
/*============================================================================*/
#define DIGITAL_PORT_READ(port)                                                \
                PASTE2(PORT, port)
/*============================================================================*/
#define PORT_DIGITAL_CONFIGURE(port, value)                                    \
                PASTE2(TRIS, port) = value;
#ifdef	__cplusplus
}
#endif /* __cplusplus */
#endif	/* GPIO_H */
/*============================================================================*/