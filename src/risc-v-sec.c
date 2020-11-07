#include <stdio.h>
#include <stdlib.h>
#include "risc-v-sec.h"
#include "log.h"

static uint8_t *read_prg(char *prgfname) {
  FILE *prgf = fopen(prgfname, "r");
  if(!prgf) {
    panic("cannot open file: %s", prgfname);
  }

  fseek(prgf, 0, SEEK_END);
  size_t fsize = ftell(prgf);
  fseek(prgf, 0, SEEK_SET);
  unsigned char *prg = malloc(sizeof(char) * (fsize + 1));
  if(fread(prg, 1, fsize, prgf) < fsize) {
    panic("read error");
  }

  return prg;
}

struct emu *emu_open(char *prgfname) {
  struct emu *e = malloc(sizeof(struct emu));
  uint8_t *prg = read_prg(prgfname);
  return e;
}

int emu_run(struct emu *e) {
  ;
}

void emu_close(struct emu *e) {
  free(e);
}
