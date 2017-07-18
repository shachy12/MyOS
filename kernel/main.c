#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <platform/platforms.h>
#include <kernel/drivers/uart/uart.h>

void print_svc(void)
{
    uart_print("SVC!\n");
}


void user_space(void)
{
    while (true) {
        uart_print("user space!\n");
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
    proc_data->sp = proc_data->stack + sizeof(proc_data->stack) - 0x200;
    proc_data->pc = proc_main;
}

void kmain()
{
    struct process_data_t user_space_proc;

    init_process(&user_space_proc, &user_space);

    uart_getc();
    uart_print("Booting system\n");
    init_platform();
    /* syscall(); */
    /* uart_print("After SVC!\n"); */
    dispatch_process(&user_space_proc);
    while (true) {
        uart_print("timer!\n");
        clear_timer();
        dispatch_process(&user_space_proc);
    }
}
