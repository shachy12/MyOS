.global vector_table_start
vector_table_start:
    ldr pc, reset_interrupt_address
    ldr pc, reserved_interrupt_address
    ldr pc, svcall_interrupt_address
    ldr pc, reserved_interrupt_address
    ldr pc, reserved_interrupt_address
    ldr pc, reserved_interrupt_address
    ldr pc, timer_interrupt_address
    ldr pc, reserved_interrupt_address
    ldr pc, reserved_interrupt_address
    ldr pc, reserved_interrupt_address
    ldr pc, reserved_interrupt_address
    ldr pc, reserved_interrupt_address
    ldr pc, reserved_interrupt_address
reset_interrupt_address: .word reset_interrupt
reserved_interrupt_address: .word reserved_interrupt
svcall_interrupt_address: .word svcall_interrupt
timer_interrupt_address: .word timer_interrupt

.global vector_table_end
vector_table_end:
