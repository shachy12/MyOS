#include <stdint.h>
#include <string.h>
#include <platform/platforms.h>
#include <kernel/interrupts/vector_table.h>

#define INTERRUPTS_VECTOR_ADDRESS ((void *)(0))
#define TIMER0 ((volatile uint32_t *)0x101E2000)
#define TIMER_CONTROL_OFFSET (2)
#define TIMER_CLOCK_SPEED (1000000) /*  1 MHz */
#define TIMER_ENABLE (1 << 7)
#define TIMER_PERIODIC (1 << 6)
#define TIMER_INT_ENABLE (1 << 5)
#define TIMER_32_BIT_SIZE (1 << 1)
#define INTERRUPT_CONTROLLER ((volatile uint32_t *)(0x10140000))
#define TIMER_INTERRUPT_ENABLE (1 << 4)
#define VIC_INTENABLE (0x4)
#define TIMER_INTCLR (0x3) /* 0x0C bytes */

void init_platform()
{
    memcpy(INTERRUPTS_VECTOR_ADDRESS,
           &vector_table_start,
           (uint32_t)(&vector_table_end) - (uint32_t)(&vector_table_start));
    set_timer(10); /*  Context switch every 10ms */
}

void set_timer(uint32_t millis)
{
    *(INTERRUPT_CONTROLLER + VIC_INTENABLE) = TIMER_INTERRUPT_ENABLE;
    *(TIMER0) = TIMER_CLOCK_SPEED / 1000 * millis;
    *(TIMER0 + TIMER_CONTROL_OFFSET) = TIMER_ENABLE | TIMER_PERIODIC | TIMER_INT_ENABLE | TIMER_32_BIT_SIZE;
}

void clear_timer()
{
    *(TIMER0 + TIMER_INTCLR) = 1; /* Clear interrupt */
}

void enable_timer()
{
    *(INTERRUPT_CONTROLLER + VIC_INTENABLE) = TIMER_INTERRUPT_ENABLE;
}

void disable_timer()
{
    *(INTERRUPT_CONTROLLER + VIC_INTENABLE) &= ~TIMER_INTERRUPT_ENABLE;
}
