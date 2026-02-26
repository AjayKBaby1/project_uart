#include "stm32f303x8.h"
#include "led.h"
volatile uint8_t rx_data;
volatile uint8_t tx_data;
volatile uint8_t tx_busy = 0;
 
void UART_Init(uint32_t baudrate)
{
    /* GPIO Setup PA9=TX, PA10=RX */
    RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
    RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
 
    GPIOA->MODER &= ~((3 << (9 * 2)) | (3 << (10 * 2)));
    GPIOA->MODER |=  ((2 << (9 * 2)) | (2 << (10 * 2)));
 
    GPIOA->AFR[1] &= ~((0xF << ((9 - 8) * 4)) | (0xF << ((10 - 8) * 4)));
    GPIOA->AFR[1] |=  ((7 << ((9 - 8) * 4)) | (7 << ((10 - 8) * 4)));
 
    /* UART Config */
    USART1->CR1 &= ~USART_CR1_UE;
    USART1->CR1 = USART_CR1_TE | USART_CR1_RE | USART_CR1_RXNEIE;
    USART1->BRR = 8000000 / baudrate;
    NVIC_EnableIRQ(USART1_IRQn);
    USART1->CR1 |= USART_CR1_UE;
}
 
void UART_Send_IT(uint8_t data)
{
    tx_data = data;
    tx_busy = 1;
    USART1->CR1 |= USART_CR1_TXEIE;
}
