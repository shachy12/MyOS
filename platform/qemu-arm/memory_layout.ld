ENTRY(reset_interrupt)
SECTIONS
{
	. = 0x10000;
	.text : {
        *(.boot)
        *(.text)
    }
	.data : { *(.data) }
	.bss : { *(.bss COMMON) }
	. = ALIGN(8);
	. = . + 0xf00000; /* 4kB of stack memory */
	stack_top = .;
}
