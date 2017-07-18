.global syscall
syscall:
    push {lr}
    svc 0
    pop {lr}
    bx lr
