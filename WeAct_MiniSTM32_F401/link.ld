/*RM0368 Rev 5 - 42/847 Memory Mappings*/
/*We are always booting from Flash*/

MEMORY
{
	FLASH 	(rx) 	: ORIGIN = 0x08000000, LENGTH = 256K
	RAM	(rwx) 	: ORIGIN = 0x20000000, LENGTH = 64K
}


ENTRY(RESET)

SECTIONS {

	.isr_vector : {
		KEEP(*(.isr_vector))	/*This section contains an array of pointers interrupts routines with the first entry being the stack pointer*/
	} > FLASH

	.text : {
					/*text section starts here*/
	    *(.text)
	    *(.text*)
	    *(.rodata)
	    *(.rodata*)
		. = ALIGN;		/*align the location counter or the MCU will start complaining*/
		__etext__ = .;		/*text section ends here*/
	} > FLASH
	
	.data : {
		__sdtata__ = .;		/*__sdata__ designate the start of data section and actually equals to __etext__ but i am aliasing it just out of convienice(mispelled)*/
	    *(.data)
	    *(.data*)
		. = ALIGN;
		__edata__ = .;		/*data section ends here*/
	} > RAM AT> FLASH		/*data section is flashed immediately after __etext__ but will be loaded at RAM's Origin*/

		__data_size__ = __edata__ - __sdata__;		/*i'll need this to determining the stack size*/

	.bss :
	{
	    __sbss__ = .;		/*You gussed right!*/
	    *(.bss)
	    *(.bss.*)
		. = ALIGN;
	    __ebss__ = .;
	} > RAM

		__bss_size__ = __ebss__ - __sbss__;		/*i'll need this to determining the stack size*/

	/*NOTE: bss section is a niche idea; this section is a simple place holder for symbols with undetermined values until runtime, or not at all(that's why we init them). \
	 	Therefore, we explicilty reserve space for these values in case we needed their respective symbols in our calculation during runtime.

		The data section is the rule and this is the exception; we store initalizd data (predetermined values) at flash,	\
		only to load these values in the order of definition of their respective symbols into RAM after reset/boot.		

		Both sections will contain variables that will hold addresses in RAM from main() because the symbols loaded there are mutable, or inherently non-constant.

		The data section holds values that will be copied in word-size chunks to RAM in the RESET() entry (aka. the reset handler).

		Restrictely speaking starutp code isn't necessarily the reset handler, but can hold boot sequence that calls reset handler eventually, and then the handler utlimately calls main().
	 */
	    

	
/* Stack starts at the top of the RAM, and moves down! */
__stack_top__	= ORIGIN(RAM) + LENGTH(RAM);
__stack_end__	= ORIGIN(RAM) + (__data_size__ + __bss_size__);
__stack_size__	= __stack_top__ - __stack_end__;

}
