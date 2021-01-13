#ifndef RISC_V_SEC_H
#define RISC_V_SEC_H

#include <stdint.h>

#define XLEN 32

#if XLEN == 32
  typedef uint32_t reg_t;
  typedef int32_t sreg_t;
  typedef uint64_t dreg_t;
  typedef int64_t dsreg_t;
#elif XLEN == 64
  typedef uint64_t reg_t;
  typedef int64_t sreg_t;
  typedef unsigned __int128 dreg_t;
  typedef __int128 dsreg_t;
#else
# error illegal xlen
#endif

struct cpu;
struct emu {
  struct cpu *cpu;
};

struct emu *emu_open(char *prgfname);
int emu_run(struct emu *e);
void emu_close(struct emu *e);

#endif /* RISC_V_SEC_H */
