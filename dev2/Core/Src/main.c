#ifdef DEV2
#include "uart.h"
#include "led.h"
 
int main(void)
{
    LED_Init();         // LED on PB3
    UART_Init(115200);  // UART1 to Dev1
 
    while(1)
    {
        // Everything handled by interrupt
        // RX interrupt increments and sends back
    }
}
#endif

