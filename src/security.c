#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "security.h"
#include "cpu.h"
#include "exception.h"
#include "log.h"

struct shadowstack *new_shadowstack() {
  struct shadowstack *s = malloc(sizeof(*s));
  s->reserved = 128;
  s->data = malloc(sizeof(reg_t) * s->reserved);
  memset(s->data, 0, sizeof(reg_t) * s->reserved);
  s->depth = 0;
  return s;
}

static void shstk_expand(struct shadowstack *s) {
  s->reserved *= 2;
  s->data = realloc(s->data, sizeof(reg_t) * s->reserved);
}

void shstk_push(struct cpu *cpu, reg_t addr) {
  if(cpu->shstk->depth == cpu->shstk->reserved) {
    shstk_expand(cpu->shstk);
  }
  cpu->shstk->depth++;
  *cpu->shstk->data++ = addr;
}

static reg_t shstk_pop(struct cpu *cpu) {
  if(cpu->shstk->depth-- == 0) {
    panic("shadow stack crushed");
  }
  return *--cpu->shstk->data;
}

void shstk_check(struct cpu *cpu, reg_t addr) {
  reg_t expected = shstk_pop(cpu);

  if(addr != expected) {
    raise(cpu, RETURN_ADDR_REWRITED, 0);
  }
}
