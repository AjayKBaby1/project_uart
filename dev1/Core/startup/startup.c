#include<stdint.h>

extern uint32_t _sdata;
extern uint32_t _edata;
extern uint32_t _sidata;
extern uint32_t _sbss;
extern uint32_t _ebss;
extern uint32_t _estack;

void Reset_Handler(void);
extern int main(void);

void Default_Handler(void)
{
	while(1);
}

void NMI_Handler(void)       __attribute__((weak,alias("Default_Handler")));
void HardFault_Handler(void) __attribute__((weak,alias("Default_Handler")));
void USART1_IRQHandler(void)  __attribute__((weak, alias("Default_Handler")));
void USART2_IRQHandler(void)  __attribute__((weak, alias("Default_Handler")));
void SPI1_IRQHandler(void)    __attribute__((weak, alias("Default_Handler")));
void I2C1_EV_IRQHandler(void) __attribute__((weak,alias("Default_Handler")));
void I2C1_ER_IRQHandler(void) __attribute__((weak,alias("Default_Handler")));

//vector table
__attribute__((section(".isr_vector")))
const uint32_t vectors[] =
	{
	(uint32_t)&_estack,
	(uint32_t)Reset_Handler,
	(uint32_t)NMI_Handler,
	(uint32_t)HardFault_Handler,
	0,0,0,0,0,0,0,
	(uint32_t)0,
	0,0,
	(uint32_t)0,
	(uint32_t)0,
	[47] = (uint32_t)I2C1_EV_IRQHandler,
    	[48] = (uint32_t)I2C1_ER_IRQHandler,
    	[51] = (uint32_t)SPI1_IRQHandler,
	[53] = (uint32_t)USART1_IRQHandler,
   	[54] = (uint32_t)USART2_IRQHandler,
	};

//Reset_Hadler Function
void Reset_Handler(void)
{	
	//copy .data section from flash to SRAM
	uint32_t size = ((uint32_t)&_edata - (uint32_t)&_sdata)/4;
	uint32_t *pDst = (uint32_t*)&_sdata;
	uint32_t *pSrc = (uint32_t*)&_sidata;

	for(uint32_t i=0;i<size;i++)
	{
		*pDst++ = *pSrc++;
	}
	//init .bss section to zero
	size = ((uint32_t)&_ebss - (uint32_t)&_sbss)/4;
   	pDst = (uint32_t*)&_sbss;
        for(uint32_t i = 0; i < size; i++)
       	{
        	*pDst++ = 0;
   	}
	
	//Call main function
	main();

	while(1);
}









































