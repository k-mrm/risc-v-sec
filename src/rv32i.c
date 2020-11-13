#include "rv32i.h"

void rv32i_lui(struct cpu *cpu, uint8_t rd, int32_t imm) {
  regwrite(cpu, rd, imm);
}

void rv32i_auipc(struct cpu *cpu, uint8_t rd, int32_t imm) {
  regwrite(cpu, rd, cpu->pc + imm);
}

void rv32i_jal(struct cpu *cpu, uint8_t rd, int32_t off) {
  regwrite(cpu, rd, cpu->pc + 4);
  cpu->pc += off;
}

void rv32i_jalr(struct cpu *cpu, uint8_t rd, uint8_t rs1, int32_t off) {
  reg_t t = cpu->pc + 4;
  cpu->pc = (regread(cpu, rs1) + off) & ~1;
  regwrite(cpu, rd, t);
}

void rv32i_beq(struct cpu *cpu, uint8_t rs1, uint8_t rs2, int32_t off) {
  if(regread(cpu, rs1) == regread(cpu, rs2)) {
    cpu->pc += off;
  }
}

void rv32i_bne(struct cpu *cpu, uint8_t rs1, uint8_t rs2, int32_t off) {
  if(regread(cpu, rs1) != regread(cpu, rs2)) {
    cpu->pc += off;
  }
}

void rv32i_blt(struct cpu *cpu, uint8_t rs1, uint8_t rs2, int32_t off) {
  if((sreg_t)regread(cpu, rs1) < (sreg_t)regread(cpu, rs2)) {
    cpu->pc += off;
  }
}

void rv32i_bge(struct cpu *cpu, uint8_t rs1, uint8_t rs2, int32_t off) {
  if((sreg_t)regread(cpu, rs1) >= (sreg_t)regread(cpu, rs2)) {
    cpu->pc += off;
  }
}

void rv32i_bltu(struct cpu *cpu, uint8_t rs1, uint8_t rs2, int32_t off) {
  if(regread(cpu, rs1) < regread(cpu, rs2)) {
    cpu->pc += off;
  }
}

void rv32i_bgeu(struct cpu *cpu, uint8_t rs1, uint8_t rs2, int32_t off) {
  if(regread(cpu, rs1) >= regread(cpu, rs2)) {
    cpu->pc += off;
  }
}

void rv32i_lb(struct cpu *cpu, uint8_t rd, uint8_t rs1, int32_t off) {
  reg_t addr = regread(cpu, rs1) + off;
  uint8_t m = sysbus_read8(cpu->bus, addr);
  regwrite(cpu, rd, (sreg_t)(int8_t)m);
}

void rv32i_lh(struct cpu *cpu, uint8_t rd, uint8_t rs1, int32_t off) {
  reg_t addr = regread(cpu, rs1) + off;
  uint16_t m = sysbus_read16(cpu->bus, addr);
  regwrite(cpu, rd, (sreg_t)(int16_t)m);
}

void rv32i_lw(struct cpu *cpu, uint8_t rd, uint8_t rs1, int32_t off) {
  reg_t addr = regread(cpu, rs1) + off;
  uint32_t m = sysbus_read32(cpu->bus, addr);
  regwrite(cpu, rd, (sreg_t)(int32_t)m);
}

void rv32i_lbu(struct cpu *cpu, uint8_t rd, uint8_t rs1, int32_t off) {
  reg_t addr = regread(cpu, rs1) + off;
  uint8_t m = sysbus_read8(cpu->bus, addr);
  regwrite(cpu, rd, (reg_t)m);
}

void rv32i_lhu(struct cpu *cpu, uint8_t rd, uint8_t rs1, int32_t off) {
  reg_t addr = regread(cpu, rs1) + off;
  uint16_t m = sysbus_read16(cpu->bus, addr);
  regwrite(cpu, rd, (reg_t)m);
}

void rv32i_addi(struct cpu *cpu, uint8_t rd, uint8_t rs1, int32_t imm) {
  reg_t a = regread(cpu, rs1) + imm;
  regwrite(cpu, rd, a);
}

void rv32i_add(struct cpu *cpu, uint8_t rd, uint8_t rs1, uint8_t rs2) {
  reg_t a = regread(cpu, rs1) + regread(cpu, rs2);
  regwrite(cpu, rd, a);
}

void rv32i_xor(struct cpu *cpu, uint8_t rd, uint8_t rs1, uint8_t rs2) {
  reg_t a = regread(cpu, rs1) ^ regread(cpu, rs2);
  regwrite(cpu, rd, a);
}

void rv32i_or(struct cpu *cpu, uint8_t rd, uint8_t rs1, uint8_t rs2) {
  reg_t a = regread(cpu, rs1) | regread(cpu, rs2);
  regwrite(cpu, rd, a);
}

void rv32i_and(struct cpu *cpu, uint8_t rd, uint8_t rs1, uint8_t rs2) {
  reg_t a = regread(cpu, rs1) & regread(cpu, rs2);
  regwrite(cpu, rd, a);
}

