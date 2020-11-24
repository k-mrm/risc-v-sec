#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cpu.h"
#include "inst.h"
#include "rv32i.h"
#include "log.h"
#include "exception.h"

struct cpu *new_cpu() {
  struct cpu *cpu = malloc(sizeof(struct cpu));
  cpu->bus = new_sysbus();
  cpu->pc = 0;
  memset(cpu->csrs, 0, sizeof(cpu->csrs));
  return cpu;
}

void free_cpu(struct cpu *cpu) {
  free(cpu);
}

static uint32_t cpu_fetch32(struct cpu *cpu) {
  cpu->nextpc = cpu->pc + 4;
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

static char *regname[32] = {
  "zero", "ra", "sp", "gp", "tp", "t0", "t1", "t2",
  "fp", "s1", "a0", "a1", "a2", "a3", "a4", "a5",
  "a6", "a7", "s2", "s3", "s4", "s5", "s6", "s7",
  "s8", "s9", "s10", "s11", "t3", "t4", "t5", "t6",
};

static void regdump(struct cpu *cpu) {
  for(int i = 0; i < 32; i++) {
    printf("reg%d(%s): %u\n", i, regname[i], cpu->x[i]);
  }
  printf("pc: %#x\n", cpu->pc);
}

int cpu_step(struct cpu *cpu) {
  uint32_t inst = cpu_fetch32(cpu);
  log_dbg("inst %#x, pc: %#x", inst, cpu->pc);
  uint8_t op = OPCODE(inst);
  uint8_t rd = RD(inst);
  uint8_t funct3 = FUNCT3(inst);
  uint8_t rs1 = RS1(inst);
  uint8_t rs2 = RS2(inst);
  uint8_t shamt = RS2(inst);
  uint8_t funct7 = FUNCT7(inst);
  int32_t imm, sinst;

  switch(op) {
    case OP_LUI:
      imm = (int32_t)inst & 0xfffff000;
      log_dbg("U: rd %d imm %d", rd, imm);
      rv32i_lui(cpu, rd, imm);
      break;
    case OP_AUIPC:
      imm = (int32_t)inst & 0xfffff000;
      log_dbg("U: rd %d imm %d", rd, imm);
      rv32i_auipc(cpu, rd, imm);
      break;
    case OP_JAL:
      sinst = (int32_t)inst;
      imm = ((sinst >> 31) << 20) |
            (((sinst >> 12) & 0xff) << 12) |
            (((sinst >> 20) & 1) << 11) |
            (((sinst >> 21) & 0x3ff) << 1);
      log_dbg("J: rd %d imm %d", rd, imm);
      rv32i_jal(cpu, rd, imm);
      break;
    case OP_JALR:
      imm = (int32_t)inst >> 20;
      log_dbg("I: rd %d f3 %d rs1 %d imm %d f7 %d", rd, funct3, rs1, imm, funct7);  \
      rv32i_jalr(cpu, rd, rs1, imm);
      break;
    case BRANCH:
      imm = (((int32_t)inst >> 31) << 12) |
            ((((int32_t)inst >> 7) & 1) << 11) |
            ((((int32_t)inst >> 25) & 0x3f) << 5) |
            ((((int32_t)inst >> 8) & 0xf) << 1);
      log_dbg("B: f3 %d rs1 %d rs2 %d imm %d", funct3, rs1, rs2, imm);
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
      imm = (int32_t)inst >> 20;
      log_dbg("I: rd %d f3 %d rs1 %d imm %d f7 %d", rd, funct3, rs1, imm, funct7);  \
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
      sinst = (int32_t)inst;
      imm = ((sinst >> 25) << 5) | ((sinst >> 7) & 0x1f);
      log_dbg("S: f3 %d rs1 %d rs2 %d imm %d", funct3, rs1, rs2, imm);
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
      imm = (int32_t)inst >> 20;
      log_dbg("I: rd %d f3 %d rs1 %d imm %d f7 %d", rd, funct3, rs1, imm, funct7);
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
            default:
              goto err;
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
      imm = inst >> 20;
      log_dbg("I: rd %d f3 %d rs1 %d imm %d f7 %d", rd, funct3, rs1, imm, funct7);  \
      /* TODO */
      switch(funct3) {
        case OP_FENCE: break;
        case OP_FENCEI: break;
      }
      break;
    case SYSTEM:
      imm = inst >> 20;
      log_dbg("I: rd %d f3 %d rs1 %d imm %d f7 %d", rd, funct3, rs1, imm, funct7);  \
      log_dbg("imm:%x", imm);
      switch(funct3) {
        case PRIV:
          switch(imm) {
            case OP_ECALL:
              if(regread(cpu, 3) & 1) {
                goto err;
              }
              raise(cpu, ENV_CALL_FROM_M, 0);
              break;
            case OP_EBREAK:
              raise(cpu, BREAKPOINT, 0);
              break;
            case OP_SRET:
              break;
            case OP_MRET:
              break;
            default:
              goto err;
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
        default:
          goto err;
      }
      break;
    default:
      goto err;
  }

  cpu->pc = cpu->nextpc;
  return 0;

err:
  /* TODO: raise IllegalInstruction exception */
  regdump(cpu);
  if(regread(cpu, 3) == 1) {
    puts("maybe passed");
    exit(0);
  }
  panic("unknown opcode %#x", op);
  return 1;
}

