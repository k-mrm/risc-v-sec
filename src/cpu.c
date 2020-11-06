#include "cpu.h"
#include "inst.h"
#include "opcode.h"

uint32_t cpu_fetch32(struct cpu *cpu) {
  uint32_t d = (uint32_t)sysbus_read(cpu->bus, cpu->pc) << 3 |
               (uint32_t)sysbus_read(cpu->bus, cpu->pc+1) << 2 |
               (uint32_t)sysbus_read(cpu->bus, cpu->pc+2) << 1 |
               (uint32_t)sysbus_read(cpu->bus, cpu->pc+3);
  cpu->pc += 4;
  return d;
}

int cpu_step(struct cpu *cpu) {
  uint32_t inst = cpu_fetch32(cpu);
  uint8_t op = OPCODE(inst);
  uint8_t rd;

  switch(op) {
    case OP_LUI:
    case OP_AUIPC:
    case OP_JAL:
    case OP_JALR:
    default: break;
  }
}
