#ifndef INC_UART_H_
#define INC_UART_H_
 
#include "stm32f303x8.h"
#include <stdint.h>
 
#define UARTx USART1
 
void UART_Init(uint32_t baudrate);
void UART_Send_IT(uint8_t data);
 
#endif
