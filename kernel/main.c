#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <platform/platforms.h>
#include <kernel/drivers/uart/uart.h>
#include <kernel/proc.h>

void print_svc(void)
{
    uart_print("SVC!\n");
}


void sleep(char *millis);

void user_space2(void)
{
    while (true) {
        sleep("10ms\n");
        uart_print("After SVC!\n");
    }
}

void user_space1(void)
{
    while (true) {
        uart_print("user space 1!\n");
    }
}



void init_process(struct process_data_t *proc_data, process_id_t pid, void (*proc_main)(void))
{
    memset(proc_data, 0, sizeof(*proc_data));
    proc_data->sp = proc_data->stack + sizeof(proc_data->stack) - sizeof(struct context_s);
    proc_data->pc = proc_main;
    proc_data->pid = pid;
}

void call_syscall(struct process_data_t *self);
struct process_data_t user_space_proc[2];
void kmain()
{
    uint8_t pid = 0;
    process_rc_t prc = TIMER;

    uart_print("Booting system\n");
    init_platform();

    init_process(&user_space_proc[0], 0, &user_space1);
    init_process(&user_space_proc[1], 1, &user_space2);
    while (true) {
        for (pid = 0; pid < 2; pid++) {
            enable_timer();
            prc = dispatch_process(&user_space_proc[pid]);
            disable_timer();
            switch (prc) {
            case SYSCALL:
                call_syscall(&user_space_proc[pid]);
                break;
            case TIMER:
                uart_print("timer\n");
                clear_timer();
                break;
            }
        }
    }
}
