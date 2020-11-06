#include "mem.h"

uint8_t memread(mem_t mem, reg_t addr) {
  return mem[addr];
}

void memwrite(mem_t mem, reg_t addr, uint8_t src) {
  mem[addr] = src;
}
