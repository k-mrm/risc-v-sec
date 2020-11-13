#include <stdlib.h>
#include "system-bus.h"

struct sysbus *new_sysbus() {
  struct sysbus *s = malloc(sizeof(struct sysbus));
  s->mem = new_mem(1024 * 1024);
  return s;
}

uint8_t sysbus_read(struct sysbus *bus, reg_t addr) {
  return memread(bus->mem, addr);
}

void sysbus_write(struct sysbus *bus, reg_t addr, uint8_t src) {
  return memwrite(bus->mem, addr, src);
}
