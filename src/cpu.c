#include <stdio.h>
#include <stdlib.h>
#include "cpu.h"
#include "inst.h"
#include "rv32i.h"
#include "log.h"

struct cpu *new_cpu() {
  struct cpu *cpu = malloc(sizeof(struct cpu));
  cpu->bus = new_sysbus();
  cpu->pc = 0;
  return cpu;
}

void free_cpu(struct cpu *cpu) {
  free(cpu);
}

static uint32_t cpu_fetch32(struct cpu *cpu) {
  return sysbus_read32(cpu->bus, cpu->pc);
}

reg_t regread(struct cpu *cpu, int i) {
  if(i == 0) return 0;
  return cpu->x[i];
}

void regwrite(struct cpu *cpu, int i, reg_t data) {
  if(i != 0)
    cpu->x[i] = data;
}

static void regdump(struct cpu *cpu) {
  for(int i = 0; i < 32; i++) {
    printf("reg%d: %u\n", i, cpu->x[i]);
  }
  printf("pc: %u\n", cpu->pc);
}

int cpu_step(struct cpu *cpu) {

#define DECODE_R()  \
  do {  \
    rd = RD(inst);  \
    funct3 = FUNCT3(inst);  \
    rs1 = RS1(inst);  \
    rs2 = RS2(inst);  \
    funct7 = FUNCT7(inst);  \
  } while(0)

#define DECODE_I()  \
  do {  \
    funct3 = FUNCT3(inst);  \
    rd = RD(inst);  \
    rs1 = RS1(inst);  \
    imm = (int32_t)inst >> 20; \
    shamt = RS2(inst);  \
    funct7 = FUNCT7(inst);  \
  } while(0)

#define DECODE_S()  \
  do {  \
    funct3 = FUNCT3(inst);  \
    rs1 = RS1(inst);  \
    rs2 = RS2(inst);  \
    int32_t sinst = (int32_t)inst;  \
    imm = (((sinst >> 25) & 0x7f) << 5) | ((sinst >> 7) & 0x1f);  \
  } while(0)

#define DECODE_B()  \
  do {  \
    funct3 = FUNCT3(inst);  \
    rs1 = RS1(inst);  \
    rs2 = RS2(inst);  \
    int32_t sinst = (int32_t)inst;  \
    imm = (((sinst >> 31) & 1)) << 12 |   \
          (((sinst >> 7) & 1) << 11) |    \
          (((sinst >> 25) & 0x3f) << 5) | \
          (((sinst >> 8) & 0xf) << 1);    \
  } while(0)

#define DECODE_U()  \
  do {  \
    rd = RD(inst);  \
    imm = (int32_t)inst & 0xfffff000; \
  } while(0)

#define DECODE_J()  \
  do {  \
    rd = RD(inst);  \
    int32_t sinst = (int32_t)inst;  \
    imm = (((sinst >> 31) & 1) << 20) |     \
          (((sinst >> 12) & 0xff) << 12) |  \
          (((sinst >> 20) & 1) << 11) |     \
          (((sinst >> 21) & 0x3ff) << 1);   \
  } while(0)
  
  uint32_t inst = cpu_fetch32(cpu);
  uint8_t op = OPCODE(inst);
  uint8_t rd;
  uint8_t funct3;
  uint8_t rs1;
  uint8_t rs2;
  uint8_t shamt;
  uint8_t funct7;
  int32_t imm;

  switch(op) {
    case OP_LUI:
      DECODE_U();
      rv32i_lui(cpu, rd, imm);
      break;
    case OP_AUIPC:
      DECODE_U();
      rv32i_auipc(cpu, rd, imm);
      break;
    case OP_JAL:
      DECODE_J();
      rv32i_jal(cpu, rd, imm);
      break;
    case OP_JALR:
      DECODE_I();
      rv32i_jalr(cpu, rd, rs1, imm);
      break;
    case BRANCH:
      DECODE_B();
      switch(funct3) {
        case OP_BEQ:
          rv32i_beq(cpu, rs1, rs2, imm);
          break;
        case OP_BNE:
          rv32i_bne(cpu, rs1, rs2, imm);
          break;
        case OP_BLT:
          rv32i_blt(cpu, rs1, rs2, imm);
          break;
        case OP_BGE:
          rv32i_bge(cpu, rs1, rs2, imm);
          break;
        case OP_BLTU:
          rv32i_bltu(cpu, rs1, rs2, imm);
          break;
        case OP_BGEU:
          rv32i_bgeu(cpu, rs1, rs2, imm);
          break;
        default:
          goto err;
      }
      break;
    case LOAD:
      DECODE_I();
      switch(funct3) {
        case OP_LB:
          rv32i_lb(cpu, rd, rs1, imm);
          break;
        case OP_LH:
          rv32i_lh(cpu, rd, rs1, imm);
          break;
        case OP_LW:
          rv32i_lw(cpu, rd, rs1, imm);
          break;
        case OP_LBU:
          rv32i_lbu(cpu, rd, rs1, imm);
          break;
        case OP_LHU:
          rv32i_lhu(cpu, rd, rs1, imm);
          break;
        default:
          goto err;
      }
      break;
    case STORE:
      DECODE_S();
      switch(funct3) {
        case OP_SB:
          rv32i_sb(cpu, rs1, rs2, imm);
          break;
        case OP_SH:
          rv32i_sh(cpu, rs1, rs2, imm);
          break;
        case OP_SW:
          rv32i_sw(cpu, rs1, rs2, imm);
          break;
        default:
          goto err;
      }
      break;
    case ARITH_IMM:
      DECODE_I();
      switch(funct3) {
        case OP_ADDI:
          rv32i_addi(cpu, rd, rs1, imm);
          break;
        case OP_SLTI:
          rv32i_slti(cpu, rd, rs1, imm);
          break;
        case OP_SLTIU:
          rv32i_sltiu(cpu, rd, rs1, imm);
          break;
        case OP_XORI:
          rv32i_xori(cpu, rd, rs1, imm);
          break;
        case OP_ORI:
          rv32i_ori(cpu, rd, rs1, imm);
          break;
        case OP_ANDI:
          rv32i_andi(cpu, rd, rs1, imm);
          break;
        case OP_SLLI:
          rv32i_slli(cpu, rd, rs1, shamt);
          break;
        case SRXI:
          switch(funct7) {
            case OP_SRLI:
              rv32i_srli(cpu, rd, rs1, shamt);
              break;
            case OP_SRAI:
              rv32i_srai(cpu, rd, rs1, shamt);
              break;
            default:
              goto err;
          }
          break;
      }
      break;
    case ARITH:
      DECODE_R();
      switch(funct3) {
        case ADDSUB:
          switch(funct7) {
            case OP_ADD:
              rv32i_add(cpu, rd, rs1, rs2);
              break;
            case OP_SUB:
              rv32i_sub(cpu, rd, rs1, rs2);
              break;
            default:
              goto err;
          }
          break;
        case OP_SLL:
          rv32i_sll(cpu, rd, rs1, rs2);
          break;
        case OP_SLT:
          rv32i_slt(cpu, rd, rs1, rs2);
          break;
        case OP_SLTU:
          rv32i_sltu(cpu, rd, rs1, rs2);
          break;
        case OP_XOR:
          rv32i_xor(cpu, rd, rs1, rs2);
          break;
        case SRX:
          switch(funct7) {
            case OP_SRL:
              rv32i_srl(cpu, rd, rs1, rs2);
              break;
            case OP_SRA:
              rv32i_sra(cpu, rd, rs1, rs2);
              break;
          }
          break;
        case OP_OR:
          rv32i_or(cpu, rd, rs1, rs2);
          break;
        case OP_AND:
          rv32i_and(cpu, rd, rs1, rs2);
          break;
        default:
          goto err;
      }
      break;
    case MISC_MEM:
      DECODE_I();
      /* TODO */
      switch(funct3) {
        case OP_FENCE: break;
        case OP_FENCEI: break;
      }
      break;
    case SYSTEM:
      DECODE_I();
      switch(funct3) {
        case PRIV:
          switch(imm) {
            case OP_ECALL:
            case OP_EBREAK:
              break;    /* TODO */
          }
          break;
        case OP_CSRRW:
          rv32i_csrrw(cpu, rd, rs1, (uint32_t)imm);
          break;
        case OP_CSRRS:
          rv32i_csrrs(cpu, rd, rs1, (uint32_t)imm);
          break;
        case OP_CSRRC:
          rv32i_csrrc(cpu, rd, rs1, (uint32_t)imm);
          break;
        case OP_CSRRWI:
          rv32i_csrrwi(cpu, rd, rs1, (uint32_t)imm);
          break;
        case OP_CSRRSI:
          rv32i_csrrsi(cpu, rd, rs1, (uint32_t)imm);
          break;
        case OP_CSRRCI:
          rv32i_csrrci(cpu, rd, rs1, (uint32_t)imm);
          break;
      }
      break;
    default:
      goto err;
  }

  cpu->pc += 4;
  return 0;

err:
  /* TODO: raise IllegalInstruction exception */
  regdump(cpu);
  panic("unknown opcode %#x", op);
  return 0;

#undef DECODE_R
#undef DECODE_I
#undef DECODE_S
#undef DECODE_B
#undef DECODE_U
#undef DECODE_J
}

