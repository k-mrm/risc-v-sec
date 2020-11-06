#ifndef RISC_V_SEC_OPCODE_H
#define RISC_V_SEC_OPCODE_H

#define OP_LUI        0b0110111
#define OP_AUIPC      0b0010111
#define OP_JAL        0b1101111
#define OP_JALR       0b1100111
#define BRANCH        0b1100011
# define OP_BEQ       0b000
# define OP_BNE       0b001
# define OP_BLT       0b100
# define OP_BGE       0b101
# define OP_BLTU      0b110
# define OP_BGEU      0b111
#define LOAD          0b0000011
# define OP_LB        0b000
# define OP_LH        0b001
# define OP_LW        0b010
# define OP_LBU       0b100
# define OP_LHU       0b101
#define STORE         0b0100011
# define OP_SB        0b000
# define OP_SH        0b001
# define OP_SW        0b010
#define ARITH_IMM     0b0010011
# define OP_ADDI      0b000
# define OP_SLTI      0b010
# define OP_SLTIU     0b011
# define OP_XORI      0b100
# define OP_ORI       0b110
# define OP_ANDI      0b111
# define OP_SLLI      0b001
# define OP_SRXI      0b101
#   define OP_SRLI    0b0000000
#   define OP_SRAI    0b0100000
#define ARITH         0b0110011
# define ADDSUB       0b000
#   define OP_ADD     0b0000000
#   define OP_SUB     0b0100000
# define OP_SLL       0b001
# define OP_SLT       0b010
# define OP_SLTU      0b011
# define OP_XOR       0b100
# define SRX          0b101
#   define OP_SRL     0b0000000
#   define OP_SRA     0b0100000
# define OP_OR        0b110
# define OP_AND       0b111

#endif
