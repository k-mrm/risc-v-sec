#ifndef RISC_V_SEC_SECURITY_H
#define RISC_V_SEC_SECURITY_H

#include "risc-v-sec.h"

struct shadowstack {
  reg_t *data;
  int depth;
  int reserved; 
};

struct cpu;

struct shadowstack *new_shadowstack(void);

void shstk_push(struct cpu *cpu, reg_t addr);
void shstk_check(struct cpu *cpu, reg_t addr);

#endif
