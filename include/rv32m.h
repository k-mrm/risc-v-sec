#ifndef RISC_V_SEC_RV32M_H
#define RISC_V_SEC_RV32M_H

#include "risc-v-sec.h"
#include "cpu.h"

#define OP_MUL      0b000
#define OP_MULH     0b001
#define OP_MULHSU   0b010
#define OP_MULHU    0b011
#define OP_DIV      0b100
#define OP_DIVU     0b101
#define OP_REM      0b110
#define OP_REMU     0b111

void rv32m_mul(struct cpu *cpu, uint8_t rd, uint8_t rs1, uint8_t rs2);
void rv32m_mulh(struct cpu *cpu, uint8_t rd, uint8_t rs1, uint8_t rs2);
void rv32m_mulhsu(struct cpu *cpu, uint8_t rd, uint8_t rs1, uint8_t rs2);
void rv32m_mulhu(struct cpu *cpu, uint8_t rd, uint8_t rs1, uint8_t rs2);
void rv32m_div(struct cpu *cpu, uint8_t rd, uint8_t rs1, uint8_t rs2);
void rv32m_divu(struct cpu *cpu, uint8_t rd, uint8_t rs1, uint8_t rs2);
void rv32m_rem(struct cpu *cpu, uint8_t rd, uint8_t rs1, uint8_t rs2);
void rv32m_remu(struct cpu *cpu, uint8_t rd, uint8_t rs1, uint8_t rs2);

#endif
