#include <stdint.h>
#include <stdbool.h>

volatile unsigned int * const UART0DR = (unsigned int *)0x101f1000;
volatile unsigned int * const UART0TFR = (unsigned int *)0x101f1018;

void uart_putc(const char c)
{
    /* Wait until fifo not full */
    while (*UART0TFR & 0x40);
    *UART0DR = (unsigned int)(c); /* Transmit char */
}

void uart_print(const char *s)
{
	while(*s != '\0') { /* Loop until end of string */
        uart_putc(*s);
        s++; /* Next char */
	}
}

uint8_t uart_getc()
{
    /* Wait for new character */
    while (*UART0TFR & 0x10);
    /* Received new character */
    return *UART0DR;
}
