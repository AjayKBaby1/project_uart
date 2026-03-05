/*#include "uart.h"
#include "frame.h"

int main(void) {
    UART_Init();
    __enable_irq();

    uint8_t tx_frame[5];
    uint8_t proto = 1; // UART Protocol ID
    uint8_t val = 7;   // The data value

    // Build the frame: [0xAA, 02, 01, 07, 08]
    uint8_t len = Frame_Build(proto, val, tx_frame);

    while(1) {
        UART_Send_IT(tx_frame, len);
        
        // Wait for a response (optional logic)
        for(volatile int d = 0; d < 1000000; d++); 
    }
}*/
#include "uart.h"
#include "frame.h"
#include "comm.h"

#define RETURN_UART  1
#define RESP_SIZE   5


int main(void) {
    Comm_Init(); // Calls UART_Init or SPI_Init
    
    uint8_t tx_buf[RESP_SIZE]; // The frame we want to SEND
    uint8_t rx_buf[RESP_SIZE]; // The frame we expect to RECEIVE back
    uint8_t value = 7;
    uint8_t return_proto = RETURN_UART;
    // 1. Pack the data into the Transmit Buffer
    Frame_Build(return_proto, value, tx_buf);

    while(1) {
        // 2. This one line sends tx_buf AND waits for rx_buf
        Comm_Transfer(tx_buf, RESP_SIZE, rx_buf, RESP_SIZE);

        // 3. Now you can check if the received data is valid
        uint8_t p_proto, p_val;
        if(Frame_Parse(rx_buf, &p_proto, &p_val)) {
        }
    }
}
