#include "stm32f303x8.h"   // CMSIS device header (REQUIRED)
#include "uart.h"

#ifdef DEV2
#include "led.h"
#endif



void USART1_IRQHandler(void)
{
    /* RX Interrupt */
    if (USART1->ISR & USART_ISR_RXNE)
    {
        rx_data = USART1->RDR;  // Clear RXNE

        /* Dev2 behavior: Increment and LED blink */
#ifdef DEV2
        uint8_t incremented = rx_data + 1;
        LED_Blink(1);            // Blink once
        UART_Send_IT(incremented);
#endif
    }

    /* TX Interrupt */
    if (USART1->ISR & USART_ISR_TXE)
    {
        if (tx_busy)
        {
            USART1->TDR = tx_data;
            tx_busy = 0;
        }
        USART1->CR1 &= ~USART_CR1_TXEIE;
    }
}

