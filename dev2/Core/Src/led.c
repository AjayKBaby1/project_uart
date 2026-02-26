#include "led.h"
 
void LED_Init(void)
{
    RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
 
    LED_PORT->MODER &= ~(3 << (LED_PIN * 2));
    LED_PORT->MODER |=  (1 << (LED_PIN * 2));
}
 
void LED_On(void)
{
    LED_PORT->BSRR = (1 << LED_PIN);
}
 
void LED_Off(void)
{
    LED_PORT->BSRR = (1 << (LED_PIN + 16));
}
 
void LED_Toggle(void)
{
    LED_PORT->ODR ^= (1 << LED_PIN);
}
 
void LED_Blink(uint8_t times)
{
    for(uint8_t i = 0; i < times; i++)
    {
        LED_On();
        for(volatile int d=0; d<100000; d++);
        LED_Off();
        for(volatile int d=0; d<100000; d++);
    }
}
