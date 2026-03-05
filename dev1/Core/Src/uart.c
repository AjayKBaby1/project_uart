#include "uart.h"

volatile uint8_t rx_buffer[UART_FRAME_SIZE];
volatile uint8_t rx_index = 0;
volatile uint8_t rx_ready = 0;
volatile uint8_t tx_busy = 0;

// Initialize USART1 on PA9(TX), PA10(RX), 9600 baud
void UART_Init(void) {
    RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
    RCC->APB2ENR |= RCC_APB2ENR_USART1EN;

    // PA9(TX), PA10(RX) AF7
    GPIOA->MODER &= ~(GPIO_MODER_MODER9_Msk | GPIO_MODER_MODER10_Msk);
    GPIOA->MODER |=  (2U << GPIO_MODER_MODER9_Pos) | (2U << GPIO_MODER_MODER10_Pos);
    GPIOA->AFR[1] &= ~(GPIO_AFRH_AFRH1_Msk | GPIO_AFRH_AFRH2_Msk);
    GPIOA->AFR[1] |= (7U << GPIO_AFRH_AFRH1_Pos) | (7U << GPIO_AFRH_AFRH2_Pos);
    GPIOA->PUPDR &= ~GPIO_PUPDR_PUPDR10_Msk;
    GPIOA->PUPDR |= (1U << GPIO_PUPDR_PUPDR10_Pos);

    USART1->BRR = 8000000 / 9600;  // Assuming 8 MHz

    USART1->CR1 = USART_CR1_TE | USART_CR1_RE | USART_CR1_RXNEIE;
    USART1->CR1 |= USART_CR1_UE;
    USART1->ICR = 0xFFFFFFFF;

    NVIC_EnableIRQ(USART1_IRQn);
}

// Send multiple bytes using TXE interrupt (blocking simple version)
void UART_Send_IT(uint8_t *data, uint8_t length) {
    for(uint8_t i=0; i<length; i++) {
        while(tx_busy);  // wait for previous byte to finish
        tx_busy = 1;
        USART1->TDR = data[i];
        USART1->CR1 |= USART_CR1_TXEIE;
    }
}

void USART1_IRQHandler(void) {
    uint32_t isr = USART1->ISR;

    if(isr & USART_ISR_RXNE) {
        uint8_t data = (uint8_t)USART1->RDR;

        // NEW: Sync logic - only start filling if we see the START_BYTE
        // or if we are already in the middle of a frame.
        if (rx_index == 0 && data != 0xAA) {
            // Ignore noise until we see 0xAA
        } else {
            if(rx_index < UART_FRAME_SIZE) {
                rx_buffer[rx_index++] = data;
            }
            if(rx_index == UART_FRAME_SIZE) {
                rx_ready = 1; 
            }
        }
    }

    if((isr & USART_ISR_TXE) && (USART1->CR1 & USART_CR1_TXEIE)) {
        USART1->CR1 &= ~USART_CR1_TXEIE;
        tx_busy = 0;
    }

    if(isr & (USART_ISR_ORE | USART_ISR_NE | USART_ISR_FE)) {
        USART1->ICR = USART_ICR_ORECF | USART_ICR_NCF | USART_ICR_FECF;
        (void)USART1->RDR;
        // Optional: Reset rx_index on error to restart sync
        rx_index = 0;
    }
}
