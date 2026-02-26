#ifdef DEV1
#include "uart.h"
#include <stdint.h>
 
#define UART2_TX_PIN 2  // Optional terminal TX
#define UART2_RX_PIN 3  // Optional terminal RX
 
void Dev1_UART2_Init(void)
{
    RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
    RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
 
    GPIOA->MODER &= ~((3 << (UART2_TX_PIN *2)) | (3 << (UART2_RX_PIN*2)));
    GPIOA->MODER |=  ((2 << (UART2_TX_PIN*2)) | (2 << (UART2_RX_PIN*2)));
 
    GPIOA->AFR[0] &= ~((0xF << (UART2_TX_PIN*4)) | (0xF << (UART2_RX_PIN*4)));
    GPIOA->AFR[0] |=  ((7 << (UART2_TX_PIN*4)) | (7 << (UART2_RX_PIN*4)));
 
    USART2->CR1 &= ~USART_CR1_UE;
    USART2->CR1 = USART_CR1_TE | USART_CR1_RE;
    USART2->BRR = 8000000 / 115200;
    USART2->CR1 |= USART_CR1_UE;
}
 
void UART2_Send(uint8_t data)
{
    while(!(USART2->ISR & USART_ISR_TXE));
    USART2->TDR = data;
}
 
uint8_t UART2_Receive(void)
{
    while(!(USART2->ISR & USART_ISR_RXNE));
    return USART2->RDR;
}
 
int main(void)
{
    UART_Init(115200);    // UART1 to Dev2
    Dev1_UART2_Init();    // UART2 to terminal
 
   /*
    while(1)
    {
        // Example: Get input from terminal and send to Dev2
        uint8_t ch = UART2_Receive();
        UART_Send_IT(ch);        // Send via UART1 to Dev2
 
        // Wait until TX done
        while(tx_busy);
 
        // Dev1 receives response from Dev2
        while(!(USART1->ISR & USART_ISR_RXNE));
        uint8_t resp = USART1->RDR;
 
        UART2_Send(resp);        // Print back to terminal
    }
    */
 while(1)
{
    uint8_t frame[3] = {'1', 'B', '7'};   // ✅ Hardcoded 3-part frame

    for(int i = 0; i < 3; i++)
    {
        UART_Send_IT(frame[i]);   // Send byte to Dev2

        while(tx_busy);           // Wait for TX complete

        while(!(USART1->ISR & USART_ISR_RXNE));
        uint8_t resp = USART1->RDR;

        UART2_Send(resp);         // Print response to terminal
    }

    for(volatile int d=0; d<500000; d++);  // Small delay
}
}
#endif
