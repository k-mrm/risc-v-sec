#include <stdlib.h>
#include "system-bus.h"

struct sysbus *new_sysbus() {
  struct sysbus *s = malloc(sizeof(struct sysbus));
  s->mem = new_mem(1024 * 1024);
  return s;
}

uint8_t sysbus_read8(struct sysbus *bus, reg_t addr) {
  return memread(bus->mem, addr);
}

void sysbus_write8(struct sysbus *bus, reg_t addr, uint8_t src) {
  memwrite(bus->mem, addr, src);
}

uint16_t sysbus_read16(struct sysbus *bus, reg_t addr) {
  return (uint16_t)memread(bus->mem, addr) << 8 | memread(bus->mem, addr + 1);
}

void sysbus_write16(struct sysbus *bus, reg_t addr, uint16_t src) {
  uint8_t h = (src >> 8) & 0xff;
  uint8_t l = src & 0xff;
  memwrite(bus->mem, addr, h);
  memwrite(bus->mem, addr + 1, l);
}
