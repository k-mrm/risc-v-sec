#ifndef RISC_V_SEC_CPU_H
#define RISC_V_SEC_CPU_H

#include <stdint.h>
#include "risc-v-sec.h"
#include "system-bus.h"
#include "csr.h"

enum mode {
  USER,
  SUPERVISOR,
  HYPERVISOR,
  MACHINE,
};

struct cpu {
  reg_t x[32];
  reg_t pc;
  reg_t csrs[4096];
  struct sysbus *bus;
};

struct cpu *new_cpu(void);
void free_cpu(struct cpu *cpu);
int cpu_step(struct cpu *cpu);
reg_t regread(struct cpu *cpu, int i);
void regwrite(struct cpu *cpu, int i, reg_t data);

#endif
