#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "security.h"
#include "cpu.h"
#include "log.h"

reg_t *new_shadowstack() {
  reg_t *s = malloc(sizeof(reg_t) * 128);
  memset(s, 0, sizeof(reg_t) * 128);
  return s;
}

void shstk_push(struct cpu *cpu, reg_t addr) {
  *cpu->shstk++ = addr;
}

static reg_t shstk_pop(struct cpu *cpu) {
  return *--cpu->shstk;
}

void shstk_check(struct cpu *cpu, reg_t addr) {
  reg_t expected = shstk_pop(cpu);

  if(addr != expected) {
    panic("return address rewriting detected!");
  }
}
