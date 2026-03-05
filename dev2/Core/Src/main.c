/*#include "uart.h"

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
}*/
/*
#include "uart.h"
#include "led.h"

int main(void) {
    LED_Init();
    UART_Init();
    __enable_irq();

    uint8_t result[UART_FRAME_SIZE];

    while(1) {
        if(rx_ready) {
            LED_On();

            for(uint8_t i=0; i<UART_FRAME_SIZE; i++) {
                result[i] = rx_buffer[i] + 1;
            }

            UART_Send_IT(result, UART_FRAME_SIZE);

            rx_ready = 0;
            rx_index = 0;

            __WFI();
        }
    }
}
#include "uart.h"
#include "frame.h"
#include "led.h"

int main(void) {
    LED_Init();
    UART_Init();
    __enable_irq();

    uint8_t p_proto, p_val;
    uint8_t response_frame[5];

    while(1) {
        if(rx_ready) {
            // Check if the received 5 bytes follow the protocol
            if(Frame_Parse((uint8_t *)rx_buffer, &p_proto, &p_val)) {
                
                LED_On();
                //p_val++;
                Frame_Build(p_proto, p_val, response_frame);
                UART_Send_IT(response_frame, 5);
            }

            // Reset buffers
            rx_ready = 0;
            rx_index = 0;
            __WFI();
        }
    }
}*/
#include "uart.h"
#include "frame.h"
#include "comm.h"
#include "led.h"
#define RESP_SIZE   5

int main(void)
{
    LED_Init();
    Comm_Init();      // Calls UART_Init
    __enable_irq();

    uint8_t p_proto, p_val;
    uint8_t tx_buf[RESP_SIZE]; // Buffer to hold the response frame

    while(1)
    {
        // Wait for the UART Interrupt to set rx_ready
        if(rx_ready) 
        {
            // 1. Parse what the TX board sent us
            if(Frame_Parse((uint8_t *)rx_buffer, &p_proto, &p_val)) 
            {
                LED_On();
                p_val++;

                // 2. Prepare the SAME data to send back (as requested: 7 stays 7)
                Frame_Build(p_proto, p_val, tx_buf);

                // 3. Send the response back to the TX board
                UART_Send_IT(tx_buf, RESP_SIZE);
            }

            // 4. Reset for the next incoming message
            rx_ready = 0;
            rx_index = 0;
            
            // Go to sleep until next interrupt to save power
            __WFI(); 
        }
    }
}
