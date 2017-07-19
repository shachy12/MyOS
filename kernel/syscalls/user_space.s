.macro create_syscall id
    push {r0, r1, r2, r3}
    mov r0, \id
    push {r0}
    svc 0
    pop {r0}
    pop {r0, r1, r2, r3}
    bx lr
.endm

.global terminate
terminate:
    create_syscall #0

.global sleep
sleep:
    create_syscall #1
