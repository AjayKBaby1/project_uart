#include "uart.h"

int main(void) {
    UART_Init();
    __enable_irq();

    uint8_t result[UART_FRAME_SIZE];

    while(1) {
        if(rx_ready) {
            // Increment each received byte
            for(uint8_t i=0; i<UART_FRAME_SIZE; i++) {
                result[i] = rx_buffer[i] + 1;
            }

            // Send back to TX
            UART_Send_IT(result, UART_FRAME_SIZE);

            // Reset for next frame
            rx_ready = 0;
            rx_index = 0;

            __WFI();
        }
    }
}
