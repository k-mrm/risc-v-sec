#ifndef RISC_V_SEC_CPU_H
#define RISC_V_SEC_CPU_H

#include <stdint.h>
#include "risc-v-sec.h"
#include "system-bus.h"

struct cpu {
  reg_t x[32];
  reg_t pc;
  struct sysbus *bus;
};

int cpu_step(struct cpu *);

#endif
