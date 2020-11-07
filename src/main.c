#include <stdio.h>
#include "risc-v-sec.h"

int main(int argc, char **argv) {
  struct emu *e = emu_open(argv[1]);
  emu_run(e);
  emu_close(e);
}
