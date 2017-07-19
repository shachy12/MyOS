#include <string.h>
#include <stdlib.h>
#include <kernel/proc.h>
void terminate(void);

void proc_init(struct process_data *proc_data, process_id_t pid, void (*proc_main)(void))
{
    struct context *ctx = NULL;

    memset(proc_data, 0, sizeof(*proc_data));
    proc_data->sp = proc_data->stack + sizeof(proc_data->stack) - sizeof(struct context);
    proc_data->pc = proc_main;
    proc_data->pid = pid;
    ctx = proc_data->sp;
    ctx->lr = &terminate;
}

