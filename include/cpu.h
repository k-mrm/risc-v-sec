#ifndef RISC_V_SEC_CPU_H
#define RISC_V_SEC_CPU_H

#include <stdint.h>
#include "risc-v-sec.h"
#include "security.h"
#include "system-bus.h"
#include "csr.h"

enum priv {
  USER = 0,
  SUPERVISOR = 1,
  HYPERVISOR = 2, /* reserved */
  MACHINE = 3,
};

struct reservation_set {
  reg_t *addrs;
  int size;
  int capa;
};

struct cpu {
  reg_t x[32];
  reg_t pc;
  reg_t nextpc;
  reg_t csrs[4096];
  struct sysbus *bus;
  enum priv priv;
  struct shadowstack *shstk; /* shadow stack */
  reg_t reservation; /* for lr/sc */
};

struct cpu *new_cpu(void);
void free_cpu(struct cpu *cpu);
int cpu_step(struct cpu *cpu);
reg_t regread(struct cpu *cpu, int i);
void regwrite(struct cpu *cpu, int i, reg_t data);

uint8_t cpuread8(struct cpu *cpu, reg_t addr);
uint16_t cpuread16(struct cpu *cpu, reg_t addr);
uint32_t cpuread32(struct cpu *cpu, reg_t addr);
uint64_t cpuread64(struct cpu *cpu, reg_t addr);

void cpuwrite8(struct cpu *cpu, reg_t addr, uint8_t src);
void cpuwrite16(struct cpu *cpu, reg_t addr, uint16_t src);
void cpuwrite32(struct cpu *cpu, reg_t addr, uint32_t src);
void cpuwrite64(struct cpu *cpu, reg_t addr, uint64_t src);

#endif
