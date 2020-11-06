#include "system-bus.h"

uint8_t sysbus_read(struct sysbus *bus, reg_t addr) {
  return memread(bus->mem, addr);
}

void sysbus_write(struct sysbus *bus, reg_t addr, uint8_t src) {
  return memwrite(bus->mem, addr, src);
}
