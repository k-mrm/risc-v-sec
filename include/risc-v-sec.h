#ifndef RISC_V_SEC_H
#define RISC_V_SEC_H

#include <stdint.h>

#define XLEN 32

#if XLEN == 32
  typedef reg_t uint32_t;
#elif XLEN == 64
  typedef reg_t uint64_t;
#endif

#endif /* RISC_V_SEC_H */
