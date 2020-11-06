#ifndef RISC_V_SEC_SYSTEM_BUS_H
#define RISC_V_SEC_SYSTEM_BUS_H

#include "mem.h"

struct sysbus {
  mem_t mem;
};

uint8_t sysbus_read(struct sysbus *, reg_t);
void sysbus_write(struct sysbus *, reg_t, uint8_t);

#endif
