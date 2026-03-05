#include "comm.h"
#include "uart.h"

void Comm_Init(void)
{
    // Initialize UART1 at 9600 baud as defined in your uart.c
    UART_Init();
}

void Comm_Transfer(uint8_t *tx, 
                   uint8_t tx_len, 
                   uint8_t *rx, 
                   uint8_t rx_len)
{
    // 1. Send the frame out via Interrupts
    UART_Send_IT(tx, tx_len);

    // 2. Wait for the RX board to send a response back.
    // The UART_IRQHandler will set rx_ready to 1 when a full frame arrives.
    while(!rx_ready); 

    // 3. Copy the received data from the global rx_buffer to the local rx pointer
    for(uint8_t i = 0; i < rx_len; i++)
    {
        rx[i] = rx_buffer[i];
    }

    // 4. Reset UART flags so we are ready for the next transfer
    rx_ready = 0;
    rx_index = 0;
}
