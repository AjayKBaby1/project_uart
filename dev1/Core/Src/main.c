#include "uart.h"

int main(void) {
    UART_Init();
    __enable_irq();

    uint8_t data[UART_FRAME_SIZE] = {'1','2','3'};

    while(1) {
        // Send frame
        rx_ready = 0;
        UART_Send_IT(data, UART_FRAME_SIZE);

        // Wait until echo received
        while(!rx_ready);

        // At this point, rx_buffer contains {'2','3','4'}
        // You can inspect rx_buffer here, or use in logic

        // Reset ready for next frame
        rx_ready = 0;
        rx_index = 0;

        // Delay before sending again
        for(volatile int i=0; i<1000000; i++);
    }
}
