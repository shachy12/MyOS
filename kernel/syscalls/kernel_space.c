#include <kernel/proc.h>
#include <kernel/syscalls/syscalls_def.h>
#include <kernel/drivers/uart/uart.h>

#define SYSCALL(__name) SYSCALL_HANDLER(__name);
#include <kernel/syscalls/syscalls_handlers.hx>
#undef SYSCALL

/* syscall_t syscalls_table[] = { */
/*     &syscall_sleep */
/* /1* #define SYSCALL(__name) syscall_##__name, *1/ */
/* /1* #include <kernel/syscalls/syscalls_handlers.hx> *1/ */
/* /1* #undef SYSCALL *1/ */
/* }; */

void call_syscall(struct process_data_t *self)
{
    struct context_s *ctx = (struct context_s *)(self->sp);
    /* syscalls_table(ctx->syscall_id); */
    if (ctx->syscall_id == 0) {
        uart_print("sleep syscall\n");
    }
    else {

        uart_print("wtf\n");
    }
    self->parameter_index = 0;
    /* syscall_sleep(self); */
}
