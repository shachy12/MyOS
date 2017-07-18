.global svcall_interrupt
svcall_interrupt:
    msr CPSR_c, #0xDF /* System mode */
    push {r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, ip, lr}
    mov ip, sp

    msr CPSR_c, #0xD3 /* Supervisor mode */
    pop {r0}
    add r0, r0, #0x8
    stmfd r0!, {ip, lr}
    pop {r4, r5, r6, r7, r8, r9, r10, r11, ip, lr}
    msr SPSR, #0x13
    mov r0, #0 /* Indicate syscall */
    bx lr

.global timer_interrupt
timer_interrupt:
    msr CPSR_c, #0xDF /* System mode */
    push {r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, ip, lr}
    mov ip, sp

	msr CPSR_c, #0xD2 /* IRQ mode */
	sub r1, lr, #0x4 /* lr is address of next instruction */

    msr CPSR_c, #0xD3 /* Supervisor mode */
    pop {r0}
    mov lr, r1
    add r0, r0, #0x8
    stmfd r0!, {ip, lr}
    pop {r4, r5, r6, r7, r8, r9, r10, r11, ip, lr}
    mov r0, #1 /* Indicate timer */
    msr SPSR, #0x13
    bx lr


.global reserved_interrupt
reserved_interrupt:
    bx lr

.global dispatch_process
dispatch_process:
    push {r4, r5, r6, r7, r8, r9, r10, r11, ip, lr}
    push {r0}
    ldmfd r0!, {ip, lr}
/* when executing the movs instruction we will be in user mode */
    msr SPSR, #0x10
    msr CPSR_c, #0xDF /* System mode */
    mov sp, ip
    pop {r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, ip, lr}

    msr CPSR_c, #0xD3 /* Supervisor mode */
    movs pc, lr
