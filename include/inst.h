#ifndef RISC_V_SEC_INST_H
#define RISC_V_SEC_INST_H

#include <stdint.h>

enum optype {
  TYPER,
  TYPEI,
  TYPES,
  TYPEB,
  TYPEU,
  TYPEJ,
};

#define OPCODE(i)   ((uint8_t)((i) & 0x7f))
#define RD(i)       ((uint8_t)(((i) >> 7) & 0x1f))
#define FUNCT3(i)   ((uint8_t)(((i) >> 12) & 0x7))
#define RS1(i)      ((uint8_t)(((i) >> 15) & 0x1f))
#define RS2(i)      ((uint8_t)(((i) >> 20) & 0x1f))
#define SHAMT(i)    ((uint8_t)(((i) >> 20) & 0x3f))
#define FUNCT7(i)   ((uint8_t)(((i) >> 25) & 0x7f))

#endif
