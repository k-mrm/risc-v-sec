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
  uint32_t d = (uint32_t)sysbus_read(cpu->bus, cpu->pc) << 24 |
               (uint32_t)sysbus_read(cpu->bus, cpu->pc+1) << 16 |
               (uint32_t)sysbus_read(cpu->bus, cpu->pc+2) << 8 |
               (uint32_t)sysbus_read(cpu->bus, cpu->pc+3);
  return d;
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
  printf("pc: %u", cpu->pc);
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
  uint8_t funct7;
  int32_t imm;

  switch(op) {
    case OP_LUI:
      DECODE_U();
      rv32i_lui(cpu, rd, imm);
      break;
    case ARITH_IMM:
      DECODE_I();
      switch(funct3) {
        case OP_ADDI:
          rv32i_addi(cpu, rd, rs1, imm);
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
          }
      }
      break;
    default:
      goto err;
  }

  cpu->pc += 4;

err:
  /* TODO: raise IllegalInstruction exception */
  panic("?");
  return 0;

#undef DECODE_R
#undef DECODE_I
#undef DECODE_S
#undef DECODE_B
#undef DECODE_U
#undef DECODE_J
}

