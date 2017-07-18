#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <platform/platforms.h>
#include <kernel/drivers/uart/uart.h>

void print_svc(void)
{
    uart_print("SVC!\n");
}



void user_space2(void)
{
    while (true) {
        uart_print("user space 2!\n");
    }
}

void user_space1(void)
{
    while (true) {
        uart_print("user space 1!\n");
    }
}

void dispatch_process(void *process_stack);
void syscall(void);

struct process_data_t {
    void *sp;
    void (*pc)(void);
    uint8_t stack[0x10000];
};

struct context_s {
    uint32_t r0;
    uint32_t r1;
    uint32_t r2;
    uint32_t r3;
    uint32_t r4;
    uint32_t r5;
    uint32_t r6;
    uint32_t r7;
    uint32_t r8;
    uint32_t r9;
    uint32_t r10;
    uint32_t r11;
    void (*lr)(void);
};

void init_process(struct process_data_t *proc_data, void (*proc_main)(void))
{
    proc_data->sp = proc_data->stack + sizeof(proc_data->stack) - sizeof(struct context_s) - 4;
    proc_data->pc = proc_main;
}

void kmain()
{
    uint8_t pid = 0;
    struct process_data_t user_space_proc[2];

    uart_print("Booting system\n");
    init_platform();

    init_process(&user_space_proc[0], &user_space1);
    init_process(&user_space_proc[1], &user_space2);
    /* syscall(); */
    /* uart_print("After SVC!\n"); */
    while (true) {
        for (pid = 0; pid < 2; pid++) {
            clear_timer();
            dispatch_process(&user_space_proc[pid]);
        }
    }
}
