#ifndef UART_H_
#define UART_H_

#include "stm32f303x8.h"
#include <stdint.h>

#define UART_FRAME_SIZE 5

// Shared variables
extern volatile uint8_t rx_buffer[UART_FRAME_SIZE];
extern volatile uint8_t rx_index;
extern volatile uint8_t rx_ready;
extern volatile uint8_t tx_busy;

// Function prototypes
void UART_Init(void);
void UART_Send_IT(uint8_t *data, uint8_t length);

#endif /* UART_H_ */
