#ifndef RISC_V_SEC_CPU_H
#define RISC_V_SEC_CPU_H

#include <stdint.h>

struct cpu {
  uint32_t x[32];
  uint32_t pc;
};

#endif
