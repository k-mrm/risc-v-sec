#include <stdlib.h>
#include "system-bus.h"
#include "memmap.h"
#include "uart.h"

struct sysbus *new_sysbus() {
  struct sysbus *s = malloc(sizeof(struct sysbus));
  s->mem = new_mem(128 * 1024 * 1024);
  return s;
}

uint8_t sysbus_read8(struct sysbus *bus, reg_t addr) {
  return memread(bus->mem, addr);
}

void sysbus_write8(struct sysbus *bus, reg_t addr, uint8_t src) {
  if(UART0 <= addr && addr < UARTEND) {
    uartwrite(addr, src);
  }
  else {
    memwrite(bus->mem, addr, src);
  }
}

uint16_t sysbus_read16(struct sysbus *bus, reg_t addr) {
  return (uint16_t)sysbus_read8(bus, addr) |
         (uint16_t)sysbus_read8(bus, addr+1) << 8;
}

void sysbus_write16(struct sysbus *bus, reg_t addr, uint16_t src) {
  uint8_t h = (src >> 8) & 0xff;
  uint8_t l = src & 0xff;
  sysbus_write8(bus, addr, l);
  sysbus_write8(bus, addr+1, h);
}

uint32_t sysbus_read32(struct sysbus *bus, reg_t addr) {
  return (uint32_t)sysbus_read8(bus, addr) |
         (uint32_t)sysbus_read8(bus, addr+1) << 8 |
         (uint32_t)sysbus_read8(bus, addr+2) << 16 |
         (uint32_t)sysbus_read8(bus, addr+3) << 24;
}

void sysbus_write32(struct sysbus *bus, reg_t addr, uint32_t src) {
  uint8_t b3 = (src >> 24) & 0xff;
  uint8_t b2 = (src >> 16) & 0xff;
  uint8_t b1 = (src >> 8) & 0xff;
  uint8_t b0 = src & 0xff;
  sysbus_write8(bus, addr, b0);
  sysbus_write8(bus, addr + 1, b1);
  sysbus_write8(bus, addr + 2, b2);
  sysbus_write8(bus, addr + 3, b3);
}

uint64_t sysbus_read64(struct sysbus *bus, reg_t addr) {
  return (uint64_t)sysbus_read8(bus, addr) |
         (uint64_t)sysbus_read8(bus, addr+1) << 8 |
         (uint64_t)sysbus_read8(bus, addr+2) << 16 |
         (uint64_t)sysbus_read8(bus, addr+3) << 24 |
         (uint64_t)sysbus_read8(bus, addr+4) << 32 |
         (uint64_t)sysbus_read8(bus, addr+5) << 40 |
         (uint64_t)sysbus_read8(bus, addr+6) << 48 |
         (uint64_t)sysbus_read8(bus, addr+7) << 56; 
}

void sysbus_write64(struct sysbus *bus, reg_t addr, uint64_t src) {
  uint8_t b7 = (src >> 56) & 0xff;
  uint8_t b6 = (src >> 48) & 0xff;
  uint8_t b5 = (src >> 40) & 0xff;
  uint8_t b4 = (src >> 32) & 0xff;
  uint8_t b3 = (src >> 24) & 0xff;
  uint8_t b2 = (src >> 16) & 0xff;
  uint8_t b1 = (src >> 8) & 0xff;
  uint8_t b0 = src & 0xff;
  sysbus_write8(bus, addr, b0);
  sysbus_write8(bus, addr + 1, b1);
  sysbus_write8(bus, addr + 2, b2);
  sysbus_write8(bus, addr + 3, b3);
  sysbus_write8(bus, addr + 4, b4);
  sysbus_write8(bus, addr + 5, b5);
  sysbus_write8(bus, addr + 6, b6);
  sysbus_write8(bus, addr + 7, b7);
}
