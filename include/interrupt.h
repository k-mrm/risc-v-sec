#ifndef RISC_V_SEC_INTERRUPT_H
#define RISC_V_SEC_INTERRUPT_H

#include "risc-v-sec.h"
#include "cpu.h"

enum interrupt {
  USER_SOFTWARE_INT     = 0,
  SUPERV_SOFTWARE_INT   = 1,
  MACHINE_SOFTWARE_INT  = 3,
  USER_TIMER_INT        = 4,
  SUPERV_TIMER_INT      = 5,
  MACHINE_TIMER_INT     = 7,
  USER_EXTERNAL_INT     = 8,
  SUPERV_EXTERNAL_INT   = 9,
  MACHINE_EXTERNAL_INT  = 11,
};

void interrupt(struct cpu *cpu, enum interrupt cause, reg_t val);

#endif
