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

uint32_t sysbus_read32(struct sysbus *bus, reg_t addr) {
  return (uint32_t)memread(bus->mem, addr) << 24 |
         (uint32_t)memread(bus->mem, addr+1) << 16 |
         (uint32_t)memread(bus->mem, addr+2) << 8 |
         (uint32_t)memread(bus->mem, addr+3);
}

void sysbus_write32(struct sysbus *bus, reg_t addr, uint32_t src) {
  uint8_t b0 = (src >> 24) & 0xff;
  uint8_t b1 = (src >> 16) & 0xff;
  uint8_t b2 = (src >> 8) & 0xff;
  uint8_t b3 = src & 0xff;
  memwrite(bus->mem, addr, b0);
  memwrite(bus->mem, addr + 1, b1);
  memwrite(bus->mem, addr + 2, b2);
  memwrite(bus->mem, addr + 3, b3);
}
