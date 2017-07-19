#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <platform/platforms.h>
#include <drivers/uart/uart.h>
#include <kernel/proc.h>
#include <kernel/syscalls/syscalls.h>
#include <kernel/syscalls/user_space.h>

void user_space2(void)
{
    uart_print("user space 2!\n");
    sleep("10ms\n");
}

void user_space1(void)
{
    uart_print("user space 1!\n");
    for (uint8_t i = 0; i < 5; i++) {
        sleep("20ms\n");
    }
}

struct process_data user_space_proc[2];
void kmain()
{
    uint8_t pid = 0;
    process_rc_t prc = TIMER;

    uart_print("Booting system\n");
    init_platform();

    proc_init(&user_space_proc[0], 0, &user_space1);
    proc_init(&user_space_proc[1], 1, &user_space2);
    while (true) {
        for (pid = 0; pid < 2; pid++) {
            if (IDLE != user_space_proc[pid].state) {
                continue;
            }
            enable_timer();
            prc = dispatch_process(&user_space_proc[pid]);
            disable_timer();
            switch (prc) {
            case SYSCALL:
                syscall_run(&user_space_proc[pid]);
                break;
            case TIMER:
                uart_print("timer\n");
                clear_timer();
                break;
            }
        }
    }
}
