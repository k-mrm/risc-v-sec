#include "rv32i.h"

void rv32i_lui(struct cpu *cpu) {
  ;
}

void rv32i_auipc(struct cpu *cpu) {
  ;
}

void rv32i_add(struct cpu *cpu, uint8_t rd, uint8_t rs1, uint8_t rs2) {
  reg_t a = regread(cpu, rs1) + regread(cpu, rs2);
  regwrite(cpu, rd, a);
}

void rv32i_addi(struct cpu *cpu, uint8_t rd, uint8_t rs1, int32_t imm) {
  reg_t a = regread(cpu, rs1) + imm;
  regwrite(cpu, rd, a);
}
