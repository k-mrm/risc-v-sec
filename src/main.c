#include <stdio.h>
#include "risc-v-sec.h"
#include "log.h"

int main(int argc, char **argv) {
  if(argc != 2) {
    panic("required binary file");
  }
  struct emu *e = emu_open(argv[1]);
  emu_run(e);
  emu_close(e);
}
