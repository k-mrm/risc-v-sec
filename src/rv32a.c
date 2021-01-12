#include "rv32a.h"
#include "security.h"
#include "log.h"

void rv32a_lr_w(struct cpu *cpu, uint8_t rd, uint8_t rs1) {
  reg_t addr = regread(cpu, rs1);
  uint32_t v = cpuread32(cpu, addr);
  regwrite(cpu, rd, (sreg_t)(int32_t)v);
  cpu->reservation = addr;
}

void rv32a_sc_w(struct cpu *cpu, uint8_t rd, uint8_t rs1, uint8_t rs2) {
  uint32_t v = regread(cpu, rs2);
  reg_t addr = regread(cpu, rs1);
  if(cpu->reservation == addr) {
    cpuwrite32(cpu, regread(cpu, rs1), v);
    regwrite(cpu, rd, 0);
  }
  else {
    regwrite(cpu, rd, 1);
  }
  cpu->reservation = 0;
}

void rv32a_amoadd_w(struct cpu *cpu, uint8_t rd, uint8_t rs1, uint8_t rs2) {
  reg_t addr = regread(cpu, rs1);
  int32_t t = (int32_t)cpuread32(cpu, addr);
  cpuwrite32(cpu, addr, (reg_t)(sreg_t)(t + (int32_t)regread(cpu, rs2)));
  regwrite(cpu, rd, (reg_t)(sreg_t)t);
}

void rv32a_amoand_w(struct cpu *cpu, uint8_t rd, uint8_t rs1, uint8_t rs2) {
  reg_t addr = regread(cpu, rs1);
  int32_t t = (int32_t)cpuread32(cpu, addr);
  cpuwrite32(cpu, addr, (reg_t)(sreg_t)(t & (int32_t)regread(cpu, rs2)));
  regwrite(cpu, rd, (reg_t)(sreg_t)t);
}

void rv32a_amoxor_w(struct cpu *cpu, uint8_t rd, uint8_t rs1, uint8_t rs2) {
  reg_t addr = regread(cpu, rs1);
  int32_t t = (int32_t)cpuread32(cpu, addr);
  cpuwrite32(cpu, addr, (reg_t)(sreg_t)(t ^ (int32_t)regread(cpu, rs2)));
  regwrite(cpu, rd, (reg_t)(sreg_t)t);
}

void rv32a_amoor_w(struct cpu *cpu, uint8_t rd, uint8_t rs1, uint8_t rs2) {
  reg_t addr = regread(cpu, rs1);
  int32_t t = (int32_t)cpuread32(cpu, addr);
  cpuwrite32(cpu, addr, (reg_t)(sreg_t)(t | (int32_t)regread(cpu, rs2)));
  regwrite(cpu, rd, (reg_t)(sreg_t)t);
}

void rv32a_amomax_w(struct cpu *cpu, uint8_t rd, uint8_t rs1, uint8_t rs2) {
  reg_t addr = regread(cpu, rs1);
  int32_t t = (int32_t)cpuread32(cpu, addr);
  int32_t u = (int32_t)regread(cpu, rs2);
  cpuwrite32(cpu, addr, (reg_t)(sreg_t)(t > u? t : u));
  regwrite(cpu, rd, (reg_t)(sreg_t)t);
}

void rv32a_amomaxu_w(struct cpu *cpu, uint8_t rd, uint8_t rs1, uint8_t rs2) {
  reg_t addr = regread(cpu, rs1);
  uint32_t t = cpuread32(cpu, addr);
  uint32_t u = (uint32_t)regread(cpu, rs2);
  cpuwrite32(cpu, addr, (reg_t)(t > u? t : u));
  regwrite(cpu, rd, (reg_t)(sreg_t)t);
}

void rv32a_amomin_w(struct cpu *cpu, uint8_t rd, uint8_t rs1, uint8_t rs2) {
  reg_t addr = regread(cpu, rs1);
  int32_t t = (int32_t)cpuread32(cpu, addr);
  int32_t u = (int32_t)regread(cpu, rs2);
  cpuwrite32(cpu, addr, (reg_t)(sreg_t)(t > u? u : t));
  regwrite(cpu, rd, (reg_t)(sreg_t)t);
}

void rv32a_amominu_w(struct cpu *cpu, uint8_t rd, uint8_t rs1, uint8_t rs2) {
  reg_t addr = regread(cpu, rs1);
  uint32_t t = cpuread32(cpu, addr);
  uint32_t u = (uint32_t)regread(cpu, rs2);
  cpuwrite32(cpu, addr, (reg_t)(t > u? u : t));
  regwrite(cpu, rd, (reg_t)(sreg_t)t);
}

void rv32a_amoswap_w(struct cpu *cpu, uint8_t rd, uint8_t rs1, uint8_t rs2) {
  reg_t addr = regread(cpu, rs1);
  uint32_t t = cpuread32(cpu, addr);
  uint32_t u = (uint32_t)regread(cpu, rs2);
  cpuwrite32(cpu, addr, (reg_t)u);
  regwrite(cpu, rd, (reg_t)(sreg_t)t);
}

