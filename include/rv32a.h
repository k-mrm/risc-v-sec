#ifndef RISC_V_SEC_RV32A_H
#define RISC_V_SEC_RV32A_H

#include "cpu.h"

#define RL(op)  (((op) >> 25) & 1)
#define AQ(op)  (((op) >> 26) & 1)
#define FUNCT5(op)  (((op) >> 27) & 0x1f)

#define AMO   0b0101111
#define OP_AMOSWAP  0b00001
#define OP_AMOADD 0b00000
#define OP_AMOXOR 0b00100
#define OP_AMOAND 0b01100
#define OP_AMOOR  0b01000
#define OP_AMOMIN 0b10000
#define OP_AMOMAX 0b10100
#define OP_AMOMINU  0b11000
#define OP_AMOMAXU  0b11100

void rv32a_lr_w(struct cpu *cpu, uint8_t rd, uint8_t rs1);
void rv32a_sc_w(struct cpu *cpu, uint8_t rd, uint8_t rs1, uint8_t rs2);
void rv32a_amoadd_w(struct cpu *cpu, uint8_t rd, uint8_t rs1, uint8_t rs2);
void rv32a_amoand_w(struct cpu *cpu, uint8_t rd, uint8_t rs1, uint8_t rs2);
void rv32a_amomax_w(struct cpu *cpu, uint8_t rd, uint8_t rs1, uint8_t rs2);
void rv32a_amomaxu_w(struct cpu *cpu, uint8_t rd, uint8_t rs1, uint8_t rs2);
void rv32a_amomin_w(struct cpu *cpu, uint8_t rd, uint8_t rs1, uint8_t rs2);
void rv32a_amominu_w(struct cpu *cpu, uint8_t rd, uint8_t rs1, uint8_t rs2);
void rv32a_amoor_w(struct cpu *cpu, uint8_t rd, uint8_t rs1, uint8_t rs2);
void rv32a_amoswap_w(struct cpu *cpu, uint8_t rd, uint8_t rs1, uint8_t rs2);
void rv32a_amoxor_w(struct cpu *cpu, uint8_t rd, uint8_t rs1, uint8_t rs2);

#endif
