#include <kernel/proc.h>
#include <kernel/utils.h>
#include <kernel/syscalls/syscalls_def.h>
#include <drivers/uart/uart.h>

#define SYSCALL(__name) SYSCALL_HANDLER(__name);
#include <kernel/syscalls/syscalls_handlers.hx>
#undef SYSCALL

syscall_t syscalls_table[] = {
#define SYSCALL(__name) syscall_##__name,
#include <kernel/syscalls/syscalls_handlers.hx>
#undef SYSCALL
};

void call_syscall(struct process_data_t *self)
{
    struct context_s *ctx = (struct context_s *)(self->sp);
    if (ARRAY_SIZE(syscalls_table) > ctx->syscall_id) {
        syscalls_table[ctx->syscall_id](self);
    }
    self->parameter_index = 0;
}
