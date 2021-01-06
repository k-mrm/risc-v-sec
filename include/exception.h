#ifndef RISC_V_SEC_EXCEPTION_H
#define RISC_V_SEC_EXCEPTION_H

#include "risc-v-sec.h"
#include "cpu.h"

#define MSTATUS_SIE (1 << 1)
#define MSTATUS_MIE (1 << 3)
#define MSTATUS_MIE_SHIFT 3
#define MSTATUS_SPIE (1 << 5)
#define MSTATUS_MPIE (1 << 7)
#define MSTATUS_MPIE_SHIFT 7
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

#define SSTATUS_UIE 1
#define SSTATUS_SIE (1 << 1)
#define SSTATUS_SIE_SHIFT 1
#define SSTATUS_UPIE  (1 << 4)
#define SSTATUS_SPIE  (1 << 5)
#define SSTATUS_SPIE_SHIFT 5
#define SSTATUS_SPP  (1 << 8)
#define SSTATUS_SPP_SHIFT 8
#define SSTATUS_FS  (3 << 13)
#define SSTATUS_XS  (3 << 15)
#define SSTATUS_SUM  (1 << 18)
#define SSTATUS_MXR  (1 << 19)
#define SSTATUS_UXL  (3 << 32)
#define SSTATUS_SD  ((reg_t)1 << (XLEN-1))

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

  /* 16~23: reserved for future standard use */
  RETURN_ADDR_REWRITED  = 24,
};

void raise(struct cpu *cpu, enum exception e, reg_t tval);
void mret(struct cpu *cpu);

#endif
