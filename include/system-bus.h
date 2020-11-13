#ifndef RISC_V_SEC_SYSTEM_BUS_H
#define RISC_V_SEC_SYSTEM_BUS_H

#include "risc-v-sec.h"
#include "mem.h"

struct sysbus {
  uint8_t *mem;
};

struct sysbus *new_sysbus(void);
uint8_t sysbus_read(struct sysbus *, reg_t);
void sysbus_write(struct sysbus *, reg_t, uint8_t);

#endif
