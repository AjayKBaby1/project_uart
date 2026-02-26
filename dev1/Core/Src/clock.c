#include "clock.h"
 
void clock_init(void) {
    // 1. Enable HSE (External High Speed Oscillator)
    RCC->CR |= RCC_CR_HSEON;
    while (!(RCC->CR & RCC_CR_HSERDY)); // Wait until HSE is stable
 
    // 2. Flash Latency: 2 wait states for 72MHz
    FLASH->ACR &= ~FLASH_ACR_LATENCY;
    FLASH->ACR |= FLASH_ACR_LATENCY_2;
 
    // 3. Configure PLL
    // Source: HSE (8MHz). Multiplier: 8MHz * 9 = 72MHz.
    RCC->CFGR &= ~(RCC_CFGR_PLLSRC | RCC_CFGR_PLLXTPRE | RCC_CFGR_PLLMUL);
    // RCC_CFGR_PLLSRC_HSE: Selects HSE as source
    // RCC_CFGR_PLLMUL9: 0x7 value (which is 7 + 2 = 9)
    RCC->CFGR |= (RCC_CFGR_PLLSRC_HSE_PREDIV  | RCC_CFGR_PLLMUL9);
 
    // 4. Set Bus Prescalers
    // APB1 must be <= 36MHz. 72MHz / 2 = 36MHz.
    RCC->CFGR |= RCC_CFGR_PPRE1_DIV2;
 
    // 5. Enable PLL
    RCC->CR |= RCC_CR_PLLON;
    while (!(RCC->CR & RCC_CR_PLLRDY));
 
    // 6. Switch System Clock to PLL
    RCC->CFGR &= ~RCC_CFGR_SW;
    RCC->CFGR |= RCC_CFGR_SW_PLL;
    while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL);
}
