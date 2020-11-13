#include <stdio.h>
#include <stdlib.h>
#include "risc-v-sec.h"
#include "cpu.h"
#include "log.h"

void dump_prg(uint8_t *prg, size_t psize) {
  for(size_t i = 0; i < psize; i++) {
    printf("%02x ", prg[i]);
  }
  puts("");
}

static uint8_t *read_prg(char *prgfname, size_t *prgsize) {
  FILE *prgf = fopen(prgfname, "r");
  if(!prgf) {
    panic("cannot open file: %s", prgfname);
  }

  fseek(prgf, 0, SEEK_END);
  size_t fsize = ftell(prgf);
  fseek(prgf, 0, SEEK_SET);
  uint8_t *prg = malloc(sizeof(char) * (fsize + 1));
  if(fread(prg, 1, fsize, prgf) < fsize) {
    panic("read error");
  }

  *prgsize = fsize;

  dump_prg(prg, fsize);

  return prg;
}

struct emu *emu_open(char *prgfname) {
  struct emu *e = malloc(sizeof(struct emu));
  e->cpu = new_cpu();

  size_t prgsize;
  uint8_t *prg = read_prg(prgfname, &prgsize);
  load_prg(e->cpu->bus->mem, prg, prgsize);
  
  return e;
}

int emu_run(struct emu *e) {
  while(1) {
    cpu_step(e->cpu);
  }
}

void emu_close(struct emu *e) {
  free_cpu(e->cpu);
  free(e);
}
