#ifndef RISC_V_SEC_UART_H
#define RISC_V_SEC_UART_H

#include <stdint.h>
#include "risc-v-sec.h"
#include "memmap.h"
/* uart 16550 */

#define UART0 0x10000000
#define RBR   0
#define THR   0
#define DLL   0
#define IER   1
#define DLM   1
#define IIR   2
#define FCR   2
#define LCR   3
#define MCR   4
#define LSR   5
#define MSR   6
#define SCR   7

struct uart {
  reg_t reg[UARTSIZE];
};

struct uart *new_uart(void);
void uartread(struct uart *uart, reg_t addr);
void uartwrite(struct uart *uart, reg_t addr, uint8_t data);

#endif
