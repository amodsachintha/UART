#ifndef UART_H_INCLUDED
#define UART_H_INCLUDED

void init_uart(void);
void uart_putchar(char c);
char uart_getchar();
void transmit();
void txString(char *str);

#endif // UART_H_INCLUDED
