#include "rv32a.h"
#include "security.h"

void rv32a_amoadd_w(struct cpu *cpu, uint8_t rd, uint8_t rs1, uint8_t rs2) {
  int32_t t = (int32_t)sysbus_read32(cpu->bus, regread(cpu, rs1));
  t += (int32_t)regread(cpu, rs2);
  regwrite(cpu, rd, (sreg_t)t);
}

void rv32a_amoand_w(struct cpu *cpu, uint8_t rd, uint8_t rs1, uint8_t rs2) {
  int32_t t = (int32_t)sysbus_read32(cpu->bus, regread(cpu, rs1));
  t &= (int32_t)regread(cpu, rs2);
  regwrite(cpu, rd, (sreg_t)t);
}

void rv32a_amomax_w(struct cpu *cpu, uint8_t rd, uint8_t rs1, uint8_t rs2) {
  int32_t t = (int32_t)sysbus_read32(cpu->bus, regread(cpu, rs1));
  int32_t u = (int32_t)regread(cpu, rs2);
  t = t > u? t : u;
  regwrite(cpu, rd, (sreg_t)t);
}

void rv32a_amomaxu_w(struct cpu *cpu, uint8_t rd, uint8_t rs1, uint8_t rs2) {
  uint32_t t = sysbus_read32(cpu->bus, regread(cpu, rs1));
  uint32_t u = regread(cpu, rs2);
  t = t > u? t : u;
  regwrite(cpu, rd, (sreg_t)t);
}

void rv32a_amomin_w(struct cpu *cpu, uint8_t rd, uint8_t rs1, uint8_t rs2) {
  int32_t t = (int32_t)sysbus_read32(cpu->bus, regread(cpu, rs1));
  int32_t u = (int32_t)regread(cpu, rs2);
  t = t > u? u : t;
  regwrite(cpu, rd, (sreg_t)t);
}

void rv32a_amominu_w(struct cpu *cpu, uint8_t rd, uint8_t rs1, uint8_t rs2) {
  uint32_t t = sysbus_read32(cpu->bus, regread(cpu, rs1));
  uint32_t u = regread(cpu, rs2);
  t = t > u? u : t;
  regwrite(cpu, rd, (sreg_t)t);
}

void rv32a_amoor_w(struct cpu *cpu, uint8_t rd, uint8_t rs1, uint8_t rs2) {
  uint32_t t = sysbus_read32(cpu->bus, regread(cpu, rs1));
  uint32_t u = regread(cpu, rs2);
  t |= u;
  regwrite(cpu, rd, (sreg_t)t);
}

void rv32a_amoswap_w(struct cpu *cpu, uint8_t rd, uint8_t rs1, uint8_t rs2) {
  uint32_t t = sysbus_read32(cpu->bus, regread(cpu, rs1));
  uint32_t u = regread(cpu, rs2);
  regwrite(cpu, rs2, (sreg_t)t);
  regwrite(cpu, rd, (sreg_t)u);
}

void rv32a_amoxor_w(struct cpu *cpu, uint8_t rd, uint8_t rs1, uint8_t rs2) {
  uint32_t t = sysbus_read32(cpu->bus, regread(cpu, rs1));
  uint32_t u = regread(cpu, rs2);
  t ^= u;
  regwrite(cpu, rd, (sreg_t)t);
}

