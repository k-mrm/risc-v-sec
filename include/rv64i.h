#ifndef RISC_V_SEC_RV64I_H
#define RISC_V_SEC_RV64I_H

#include "risc-v-sec.h"
#include "cpu.h"

#define OP_LWU  0b110
#define OP_LD 0b011

#define OP_SD 0b011

#define OP_IMM_32 0b0011011
# define OP_ADDIW 0b000
# define OP_SLLIW 0b001
# define SRXIW 0b101
#   define OP_SRLIW 0b0000000
#   define OP_SRAIW 0b0100000

#define OP_32 0b0111011
# define ADDSUBW  0b000
#   define OP_ADDW  0b0000000
#   define OP_SUBW  0b0100000
# define OP_SLLW  0b001
# define SRXW 0b101
#   define OP_SRLW  0b0000000
#   define OP_SRAW  0b0100000

void rv64i_lwu(struct cpu *cpu, uint8_t rd, uint8_t rs1, int32_t off);
void rv64i_ld(struct cpu *cpu, uint8_t rd, uint8_t rs1, int32_t off);
void rv64i_sd(struct cpu *cpu, uint8_t rs1, uint8_t rs2, int32_t off);
void rv64i_addiw(struct cpu *cpu, uint8_t rd, uint8_t rs1, int32_t imm);
void rv64i_slliw(struct cpu *cpu, uint8_t rd, uint8_t rs1, uint8_t shamt);
void rv64i_srliw(struct cpu *cpu, uint8_t rd, uint8_t rs1, uint8_t shamt);
void rv64i_sraiw(struct cpu *cpu, uint8_t rd, uint8_t rs1, uint8_t shamt);
void rv64i_addw(struct cpu *cpu, uint8_t rd, uint8_t rs1, uint8_t rs2);
void rv64i_subw(struct cpu *cpu, uint8_t rd, uint8_t rs1, uint8_t rs2);
void rv64i_sllw(struct cpu *cpu, uint8_t rd, uint8_t rs1, uint8_t rs2);
void rv64i_srlw(struct cpu *cpu, uint8_t rd, uint8_t rs1, uint8_t rs2);
void rv64i_sraw(struct cpu *cpu, uint8_t rd, uint8_t rs1, uint8_t rs2);

#endif
