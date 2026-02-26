#ifndef INC_LED_H_
#define INC_LED_H_
 
#include "stm32f303x8.h"
#include <stdint.h>
 
#define LED_PORT GPIOB
#define LED_PIN  3
 
void LED_Init(void);
void LED_On(void);
void LED_Off(void);
void LED_Toggle(void);
void LED_Blink(uint8_t times);
 
#endif
