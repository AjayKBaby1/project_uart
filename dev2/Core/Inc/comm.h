#ifndef COMM_H
#define COMM_H

#include <stdint.h>

/* Initializes the underlying hardware (UART) */
void Comm_Init(void);

/* * Sends a frame and waits for a response.
 * tx: pointer to data to send
 * tx_len: number of bytes to send (usually 5)
 * rx: pointer to buffer where response will be stored
 * rx_len: number of bytes to receive (usually 5)
 */
void Comm_Transfer(uint8_t *tx, 
                   uint8_t tx_len, 
                   uint8_t *rx, 
                   uint8_t rx_len);

#endif
