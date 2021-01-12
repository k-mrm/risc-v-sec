#include "rv64i.h"

void rv64i_lwu(struct cpu *cpu, uint8_t rd, uint8_t rs1, int32_t off) {
  reg_t addr = regread(cpu, rs1) + off;
  uint32_t m = sysbus_read32(cpu->bus, addr);
  regwrite(cpu, rd, (reg_t)m);
}

void rv64i_ld(struct cpu *cpu, uint8_t rd, uint8_t rs1, int32_t off) {
  reg_t addr = regread(cpu, rs1) + off;
  uint64_t m = sysbus_read64(cpu->bus, addr);
  regwrite(cpu, rd, m);
}

void rv64i_sd(struct cpu *cpu, uint8_t rs1, uint8_t rs2, int32_t off) {
  reg_t addr = regread(cpu, rs1) + off;
  sysbus_write64(cpu->bus, addr, regread(cpu, rs2));
}

void rv64i_addiw(struct cpu *cpu, uint8_t rd, uint8_t rs1, int32_t imm) {
  sreg_t v = (sreg_t)(int32_t)((regread(cpu, rs1) + imm) & 0xffffffff);
  regwrite(cpu, rd, v);
}

void rv64i_slliw(struct cpu *cpu, uint8_t rd, uint8_t rs1, uint8_t shamt) {
  sreg_t v = (sreg_t)(int32_t)((regread(cpu, rs1) << shamt) & 0xffffffff);
  regwrite(cpu, rd, v);
}

void rv64i_srliw(struct cpu *cpu, uint8_t rd, uint8_t rs1, uint8_t shamt) {
  sreg_t v = (sreg_t)(int32_t)((regread(cpu, rs1) & 0xffffffff) >> shamt);
  regwrite(cpu, rd, v);
}

void rv64i_sraiw(struct cpu *cpu, uint8_t rd, uint8_t rs1, uint8_t shamt) {
  sreg_t v = (sreg_t)(int32_t)((sreg_t)(int32_t)(regread(cpu, rs1) & 0xffffffff) >> shamt);
  regwrite(cpu, rd, v);
}

void rv64i_addw(struct cpu *cpu, uint8_t rd, uint8_t rs1, uint8_t rs2) {
  sreg_t v = (sreg_t)(int32_t)(((sreg_t)regread(cpu, rs1) + (sreg_t)regread(cpu, rs2)) & 0xffffffff);
  regwrite(cpu, rd, v);
}

void rv64i_subw(struct cpu *cpu, uint8_t rd, uint8_t rs1, uint8_t rs2) {
  sreg_t v = (sreg_t)(int32_t)(((sreg_t)regread(cpu, rs1) - (sreg_t)regread(cpu, rs2)) & 0xffffffff);
  regwrite(cpu, rd, v);
}

void rv64i_sllw(struct cpu *cpu, uint8_t rd, uint8_t rs1, uint8_t rs2) {
  uint8_t shift = regread(cpu, rs2) & 0x1f;
  sreg_t v = (sreg_t)(int32_t)((regread(cpu, rs1) << shift) & 0xffffffff);
  regwrite(cpu, rd, v);
}

void rv64i_srlw(struct cpu *cpu, uint8_t rd, uint8_t rs1, uint8_t rs2) {
  sreg_t v = (sreg_t)(int32_t)((regread(cpu, rs1) & 0xffffffff) >> (regread(cpu, rs2) & 0x1f));
  regwrite(cpu, rd, v);
}

void rv64i_sraw(struct cpu *cpu, uint8_t rd, uint8_t rs1, uint8_t rs2) {
  sreg_t v = (sreg_t)(int32_t)((sreg_t)(int32_t)(regread(cpu, rs1) & 0xffffffff) >> (regread(cpu, rs2) & 0x1f));
  regwrite(cpu, rd, v);
}
