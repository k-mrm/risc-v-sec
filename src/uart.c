#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "uart.h"

struct uart *new_uart() {
  struct uart *u = malloc(sizeof(struct uart));
  memset(u->reg, 0, sizeof(u->reg));
  return u;
}

uint8_t uartread(struct uart *uart, reg_t addr) {
  return uart->reg[addr - UART0];
}

void uartwrite(struct uart *uart, reg_t addr, uint8_t data) {
  if(addr == UART0 + THR) {
    putchar(data);
    fflush(stdout);
  }
  else {
    uart->reg[addr - UART0] = data;
  }
}
