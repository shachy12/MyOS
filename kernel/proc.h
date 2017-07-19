#ifndef PROC_H
#define PROC_H

#include <stdint.h>

typedef enum {
    SYSCALL,
    TIMER
} process_rc_t;

process_rc_t dispatch_process(void *process_stack);

typedef uint32_t process_id_t;

struct context {
    uint32_t next_value;
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
    uint32_t syscall_id;
    uint32_t parameters[];
};

enum process_state {
    IDLE,
    RUNNING,
    WAITING,
    TERMINATE
};

struct process_data {
    void *sp;
    void (*pc)(void);
    enum process_state state;
    uint8_t parameter_index;
    process_id_t pid;
    uint8_t stack[0x10000];
};

void proc_init(struct process_data *proc_data, process_id_t pid, void (*proc_main)(void));

#endif
