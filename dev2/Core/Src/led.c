#include "stm32f303x8.h"
#include "led.h"

#define LED_PORT GPIOB
#define LED_PIN  3

void LED_Init(void)
{
    RCC->AHBENR |= RCC_AHBENR_GPIOBEN;

    LED_PORT->MODER &= ~(3 << (LED_PIN * 2));
    LED_PORT->MODER |=  (1 << (LED_PIN * 2));
}

void LED_On(void)
{
    LED_PORT->ODR |= (1 << LED_PIN);
}

void LED_Off(void)
{
    LED_PORT->ODR &= ~(1 << LED_PIN);
}
