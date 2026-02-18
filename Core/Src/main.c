#include "stm32f303x8.h"

int main(void)
{
    
    RCC->AHBENR |= RCC_AHBENR_GPIOBEN;

    GPIOB->MODER &= ~(3 << (3 * 2));

    GPIOB->MODER |=  (1 << (3 * 2));

    GPIOB->OTYPER &= ~(1 << 3);

    GPIOB->OSPEEDR |= (3 << (3 * 2));

    while(1)
    {
        GPIOB->ODR ^= (1 << 3);
    }
}

