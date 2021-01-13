#include <stdlib.h>
#include <string.h>
#include "mem.h"
#include "memmap.h"

uint8_t *new_mem(size_t size) {
  return malloc(sizeof(uint8_t) * size);
}

void load_prg(uint8_t *mem, uint8_t *prg, size_t size) {
  memcpy(mem, prg, size);
}

uint8_t memread(uint8_t *mem, reg_t addr) {
  return mem[addr - DRAMBASE];
}

void memwrite(uint8_t *mem, reg_t addr, uint8_t src) {
  mem[addr - DRAMBASE] = src;
}
