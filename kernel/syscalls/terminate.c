#include <kernel/syscalls/syscalls_def.h>
#include <drivers/uart/uart.h>

SYSCALL_HANDLER(terminate)
{
    /* The scheduler will remove this process */
    self->state = TERMINATE;
}
