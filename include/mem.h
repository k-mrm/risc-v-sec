#ifndef RISC_V_SEC_MEM_H
#define RISC_V_SEC_MEM_H

#include <stdint.h>
#include "risc-v-sec.h"

typedef uint8_t mem_t[1024*1024];

uint8_t memread(mem_t, reg_t);
void memwrite(mem_t, reg_t, uint8_t);

#endif
