#ifndef RISC_V_SEC_RV32A_H
#define RISC_V_SEC_RV32A_H

#include "cpu.h"

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
