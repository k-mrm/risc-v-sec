#include "exception.h"
#include "csr.h"

void raise(struct cpu *cpu, enum exception e, reg_t mtval) {
  reg_t mstatus = csrread(cpu->csrs, MSTATUS);
  reg_t mie = (mstatus & MSTATUS_MIE) != 0;
  csrwrite(cpu->csrs, MEPC, cpu->pc);
  cpu->pc = csrread(cpu->csrs, MTVEC);
  csrwrite(cpu->csrs, MCAUSE, e);
  csrwrite(cpu->csrs, MTVAL, mtval);
  if(mie)
    csrwrite(cpu->csrs, MSTATUS, (mstatus & ~MSTATUS_MIE) | MSTATUS_MPIE);
  else
    csrwrite(cpu->csrs, MSTATUS, (mstatus & ~MSTATUS_MIE) & ~MSTATUS_MPIE);
}
