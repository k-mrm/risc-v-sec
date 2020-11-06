#ifndef RISC_V_SEC_H
#define RISC_V_SEC_H

#include <stdint.h>

#define XLEN 32

#if XLEN == 32
  typedef uint32_t reg_t;
#elif XLEN == 64
  typedef uint64_t reg_t;
#else
# error illegal xlen
#endif

#endif /* RISC_V_SEC_H */
