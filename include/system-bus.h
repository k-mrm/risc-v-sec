#ifndef RISC_V_SEC_SYSTEM_BUS_H
#define RISC_V_SEC_SYSTEM_BUS_H

#include "risc-v-sec.h"
#include "mem.h"

struct sysbus {
  uint8_t *mem;
};

struct sysbus *new_sysbus(void);
uint8_t sysbus_read8(struct sysbus *bus, reg_t addr);
void sysbus_write8(struct sysbus *bus, reg_t addr, uint8_t src);

uint16_t sysbus_read16(struct sysbus *bus, reg_t addr);
void sysbus_write16(struct sysbus *bus, reg_t addr, uint16_t src);

uint32_t sysbus_read32(struct sysbus *bus, reg_t addr);
void sysbus_write32(struct sysbus *bus, reg_t addr, uint32_t src);

uint64_t sysbus_read64(struct sysbus *bus, reg_t addr);
void sysbus_write64(struct sysbus *bus, reg_t addr, uint64_t src);

#endif
