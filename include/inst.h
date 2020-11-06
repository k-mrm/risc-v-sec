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

#define OPCODE(i) ((uint8_t)((i) & 0x3f))

#endif
