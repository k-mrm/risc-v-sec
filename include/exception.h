#ifndef RISC_V_SEC_EXCEPTION_H
#define RISC_V_SEC_EXCEPTION_H

#include "risc-v-sec.h"
#include "cpu.h"

#define MSTATUS_SIE (1 << 1)
#define MSTATUS_MIE (1 << 3)
#define MSTATUS_SPIE (1 << 5)
#define MSTATUS_MPIE (1 << 7)
#define MSTATUS_SPP (1 << 8)
#define MSTATUS_MPP (3 << 11)
#define MSTATUS_FS (3 << 13)
#define MSTATUS_XS (3 << 15)
#define MSTATUS_MPRV (1 << 17)
#define MSTATUS_SUM (1 << 18)
#define MSTATUS_MXR (1 << 19)
#define MSTATUS_TVM (1 << 20)
#define MSTATUS_TW (1 << 21)
#define MSTATUS_TSR (1 << 22)
#define MSTATUS_SD ((reg_t)1 << (XLEN-1))

#define MSTATUS_MPP_SHIFT (11)

enum exception {
  INST_ADDR_MISALIGNED  = 0,
  INST_ACCESS_FAULT     = 1,
  ILLEGAL_INSTRUCTION   = 2,
  BREAKPOINT            = 3,
  LOAD_ADDR_MISALIGNED  = 4,
  LOAD_ACCESS_FAULT     = 5,
  STORE_ADDR_MISALIGNED = 6,
  STORE_ACCESS_FAULT    = 7,
  ENV_CALL_FROM_U       = 8,
  ENV_CALL_FROM_S       = 9,
  ENV_CALL_FROM_H       = 10,
  ENV_CALL_FROM_M       = 11,
  INST_PAGEFAULT        = 12,
  LOAD_PAGEFAULT        = 13,
  STORE_PAGEFAULT       = 15,
  /* original */
  RETURN_ADDR_REWRITED  = 16,
};

enum interrupt {
  USER_SOFTWARE_INT     = 0,
  SUPERV_SOFTWARE_INT   = 1,
  MACHINE_SOFTWARE_INT  = 3,
  USER_TIMER_INT        = 4,
  SUPERV_TIMER_INT      = 5,
  MACHINE_TIMER_INT     = 7,
  USER_EXTERNAL_INT     = 8,
  SUPERV_EXTERNAL_INT   = 9,
  MACHINE_EXTERNAL_INT  = 11,
};

void raise(struct cpu *cpu, enum exception e, reg_t mtval);
void mret(struct cpu *cpu);

#endif
