#ifndef SYSCALLS_DEF_H
#define SYSCALLS_DEF_H

#include <kernel/proc.h>

#define SYSCALL_HANDLER(__name) void syscall_##__name(struct process_data *self)

#define SYSCALL_PARAMETER_VALUE(__type) (__type)(((struct context *)(self->sp))->parameters[self->parameter_index++])

#define SYSCALL_SET_RETURN_VALUE(__value) ((struct context *)(self->sp))->parameters[0] = (uint32_t)(__value)

typedef void (*syscall_t)(struct process_data *);
#endif
