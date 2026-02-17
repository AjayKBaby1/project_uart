#include "timer.h"

void timer_init(void) {
    // Enable TIM2 clock
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;

    // Prescaler: 72MHz / 72,000 = 1,000 ticks/second
    TIM2->PSC = 71999;
    
    // Auto-reload to max value
    TIM2->ARR = 0xFFFFFFFF;
    
    // Force an update to load the prescaler value
    TIM2->EGR |= TIM_EGR_UG;
    
    // Start the timer
    TIM2->CR1 |= TIM_CR1_CEN;
}

void delay_ms(uint32_t ms) {
    // Reset counter to 0
    TIM2->CNT = 0;
    
    // Wait until counter reaches the desired milliseconds
    while (TIM2->CNT < ms);
}
