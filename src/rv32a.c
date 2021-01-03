#include "rv32a.h"
#include "security.h"
#include "log.h"

void rv32a_lr_w(struct cpu *cpu, uint8_t rd, uint8_t rs1) {
  ;
}

void rv32a_sc_w(struct cpu *cpu, uint8_t rd, uint8_t rs1, uint8_t rs2) {
  ;
}

void rv32a_amoadd_w(struct cpu *cpu, uint8_t rd, uint8_t rs1, uint8_t rs2) {
  reg_t addr = regread(cpu, rs1);
  int32_t t = (int32_t)sysbus_read32(cpu->bus, addr);
  sysbus_write32(cpu->bus, addr, (reg_t)(sreg_t)(t + (int32_t)regread(cpu, rs2)));
  regwrite(cpu, rd, (reg_t)(sreg_t)t);
}

void rv32a_amoand_w(struct cpu *cpu, uint8_t rd, uint8_t rs1, uint8_t rs2) {
  reg_t addr = regread(cpu, rs1);
  int32_t t = (int32_t)sysbus_read32(cpu->bus, addr);
  sysbus_write32(cpu->bus, addr, (reg_t)(sreg_t)(t & (int32_t)regread(cpu, rs2)));
  regwrite(cpu, rd, (reg_t)(sreg_t)t);
}

void rv32a_amoxor_w(struct cpu *cpu, uint8_t rd, uint8_t rs1, uint8_t rs2) {
  reg_t addr = regread(cpu, rs1);
  int32_t t = (int32_t)sysbus_read32(cpu->bus, addr);
  sysbus_write32(cpu->bus, addr, (reg_t)(sreg_t)(t ^ (int32_t)regread(cpu, rs2)));
  regwrite(cpu, rd, (reg_t)(sreg_t)t);
}

void rv32a_amoor_w(struct cpu *cpu, uint8_t rd, uint8_t rs1, uint8_t rs2) {
  reg_t addr = regread(cpu, rs1);
  int32_t t = (int32_t)sysbus_read32(cpu->bus, addr);
  sysbus_write32(cpu->bus, addr, (reg_t)(sreg_t)(t | (int32_t)regread(cpu, rs2)));
  regwrite(cpu, rd, (reg_t)(sreg_t)t);
}

void rv32a_amomax_w(struct cpu *cpu, uint8_t rd, uint8_t rs1, uint8_t rs2) {
  reg_t addr = regread(cpu, rs1);
  int32_t t = (int32_t)sysbus_read32(cpu->bus, addr);
  int32_t u = (int32_t)regread(cpu, rs2);
  sysbus_write32(cpu->bus, addr, (reg_t)(sreg_t)(t > u? t : u));
  regwrite(cpu, rd, (reg_t)(sreg_t)t);
}

void rv32a_amomaxu_w(struct cpu *cpu, uint8_t rd, uint8_t rs1, uint8_t rs2) {
  reg_t addr = regread(cpu, rs1);
  uint32_t t = sysbus_read32(cpu->bus, addr);
  uint32_t u = (uint32_t)regread(cpu, rs2);
  sysbus_write32(cpu->bus, addr, (reg_t)(t > u? t : u));
  regwrite(cpu, rd, (reg_t)(sreg_t)t);
}

void rv32a_amomin_w(struct cpu *cpu, uint8_t rd, uint8_t rs1, uint8_t rs2) {
  reg_t addr = regread(cpu, rs1);
  int32_t t = (int32_t)sysbus_read32(cpu->bus, addr);
  int32_t u = (int32_t)regread(cpu, rs2);
  sysbus_write32(cpu->bus, addr, (reg_t)(sreg_t)(t > u? u : t));
  regwrite(cpu, rd, (reg_t)(sreg_t)t);
}

void rv32a_amominu_w(struct cpu *cpu, uint8_t rd, uint8_t rs1, uint8_t rs2) {
  reg_t addr = regread(cpu, rs1);
  uint32_t t = sysbus_read32(cpu->bus, addr);
  uint32_t u = (uint32_t)regread(cpu, rs2);
  sysbus_write32(cpu->bus, addr, (reg_t)(t > u? u : t));
  regwrite(cpu, rd, (reg_t)(sreg_t)t);
}

void rv32a_amoswap_w(struct cpu *cpu, uint8_t rd, uint8_t rs1, uint8_t rs2) {
  reg_t addr = regread(cpu, rs1);
  uint32_t t = sysbus_read32(cpu->bus, addr);
  uint32_t u = (uint32_t)regread(cpu, rs2);
  sysbus_write32(cpu->bus, addr, (reg_t)u);
  regwrite(cpu, rd, (reg_t)(sreg_t)t);
}

