.section .boot
.global reset_interrupt
reset_interrupt:
 LDR sp, =stack_top
 BL kmain
 B .
