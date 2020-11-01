#ifndef RISC_V_SEC_CPU_H
#define RISC_V_SEC_CPU_H

#include <stdint.h>
#include <risc-v-sec.h>

struct cpu {
  reg_t x[32];
  reg_t pc;
};

#endif
