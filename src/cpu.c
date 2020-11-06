#include <stdio.h>
#include "cpu.h"
#include "inst.h"

static uint32_t cpu_fetch32(struct cpu *cpu) {
  uint32_t d = (uint32_t)sysbus_read(cpu->bus, cpu->pc) << 3 |
               (uint32_t)sysbus_read(cpu->bus, cpu->pc+1) << 2 |
               (uint32_t)sysbus_read(cpu->bus, cpu->pc+2) << 1 |
               (uint32_t)sysbus_read(cpu->bus, cpu->pc+3);
  cpu->pc += 4;
  return d;
}

reg_t regread(struct cpu *cpu, int i) {
  if(i == 0) return 0;
  return cpu->x[i];
}

void regwrite(struct cpu *cpu, int i, reg_t data) {
  if(i != 0) {
    cpu->x[i] = data;
  }
}

static void cpu_dump(struct cpu *cpu) {
  puts("cpu state:");
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
    imm = inst >> 20; \
  } while(0)

#define DECODE_S()  \
  do {  \
    funct3 = FUNCT3(inst);  \
    rs1 = RS1(inst);  \
    rs2 = RS2(inst);  \
  } while(0)

#define DECODE_B()  \
  do {  \
    funct3 = FUNCT3(inst);  \
    rs1 = RS1(inst);  \
    rs2 = RS2(inst);  \
  } while(0)

#define DECODE_U()  \
  do {  \
    rd = RD(inst);  \
    imm = inst & 0xfffff000; \
  } while(0)

#define DECODE_J()  \
  do {  \
    rd = RD(inst);  \
    imm = (inst >> 8) << 10 | (inst >> 9) << 1 | 0; /* TODO */ \
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
      break;
    case ARITH_IMM:
      DECODE_I();
      switch(funct3) {
        case OP_ADDI:
          rv32i_addi(cpu, rd, rs1, imm);
          break;
      }
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
    default:
      goto err;
  }

err:
  /* TODO: raise IllegalInstruction exception */

#undef DECODE_R
#undef DECODE_I
#undef DECODE_S
#undef DECODE_B
#undef DECODE_U
#undef DECODE_J
}

