#ifndef DRIVERS_UART_H
#define DRIVERS_UART_H

void uart_putc(const char c);
void uart_print(const char *s);
uint8_t uart_getc();

#endif
