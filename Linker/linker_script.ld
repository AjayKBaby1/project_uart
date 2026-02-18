ENTRY(Reset_Handler)

MEMORY
{
    FLASH (rx)  : ORIGIN = 0x08000000, LENGTH = 64K
    SRAM  (rwx) : ORIGIN = 0x20000000, LENGTH = 12K
}

SECTIONS
{
    
	.isr_vector :
	{
        	 . = ALIGN(4);
        	KEEP(*(.isr_vector)) 
        	. = ALIGN(4);
        } > FLASH
    
	.text :
        {
        	. = ALIGN(4);
        	*(.text)
        	*(.text*)
        	*(.rodata)
        	*(.rodata*)
        	. = ALIGN(4);
    	} > FLASH
   
	.data :
    	{
        	. = ALIGN(4);
        	_sdata = .;              /* Start of .data in SRAM */
        	*(.data)
        	*(.data*)
        	. = ALIGN(4);
        	_edata = .;              /* End of .data in SRAM */
    	} > SRAM AT > FLASH

    	_sidata = LOADADDR(.data);   /* Start of .data in FLASH */
 
	.bss :
    	{
        	. = ALIGN(4);
        	_sbss = .;               /* Start of .bss */
        	*(.bss)
        	*(.bss*)
        	*(COMMON)
        	. = ALIGN(4);
        	_ebss = .;               /* End of .bss */
    	} > SRAM
 
	. = ALIGN(8);
    	_estack = ORIGIN(SRAM) + LENGTH(SRAM);   /* Top of stack (8-byte aligned) */

}
