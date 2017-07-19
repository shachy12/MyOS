#include <kernel/syscalls/syscalls_def.h>
#include <drivers/uart/uart.h>

SYSCALL_HANDLER(sleep)
{
    char *seconds = SYSCALL_PARAMETER_VALUE(char *);
    uart_print(seconds);
}
