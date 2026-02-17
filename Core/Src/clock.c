#include "clock.h"

void clock_init(void) {
    // 1. Start HSI (Internal High Speed oscillator)
    RCC->CR |= RCC_CR_HSION;
    while (!(RCC->CR & RCC_CR_HSIRDY));

    // 2. Flash Latency: Essential when running > 24MHz
    // 72MHz requires 2 wait states
    FLASH->ACR &= ~FLASH_ACR_LATENCY;
    FLASH->ACR |= FLASH_ACR_LATENCY_1;

    // 3. Configure PLL
    // Source: HSI / 2 = 4MHz. Multiplier: 4MHz * 18 = 72MHz.
    RCC->CFGR &= ~(RCC_CFGR_PLLSRC | RCC_CFGR_PLLMUL); 
    RCC->CFGR |= (RCC_CFGR_PLLSRC_HSI_DIV2 | RCC_CFGR_PLLMUL18);

    // 4. Set Bus Prescalers
    // APB1 must not exceed 36MHz -> Set Divider to /2
    RCC->CFGR |= RCC_CFGR_PPRE1_DIV2;

    // 5. Enable PLL
    RCC->CR |= RCC_CR_PLLON;
    while (!(RCC->CR & RCC_CR_PLLRDY));

    // 6. Switch System Clock to PLL
    RCC->CFGR &= ~RCC_CFGR_SW;
    RCC->CFGR |= RCC_CFGR_SW_PLL;
    while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL);
}

