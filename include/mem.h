#ifndef RISC_V_SEC_MEM_H
#define RISC_V_SEC_MEM_H

#include <stdio.h>
#include <stdint.h>
#include "risc-v-sec.h"
#include "cpu.h"

typedef uint8_t mem_t;

uint8_t *new_mem(size_t size);
void load_prg(uint8_t *mem, uint8_t *prg, size_t size);
uint8_t memread(uint8_t *mem, reg_t addr);
void memwrite(uint8_t *mem, reg_t addr, uint8_t src);

#endif
