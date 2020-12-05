#include <stdio.h>
#include "uart.h"

void uartread(reg_t addr) {
}

void uartwrite(reg_t addr, uint8_t data) {
  if(addr == UART0 + THR) {
    putchar(data);
    fflush(stdout);
  }
}
