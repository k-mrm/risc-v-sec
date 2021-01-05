#include "cpu.h"
#include "exception.h"
#include "csr.h"
#include "log.h"

void raise(struct cpu *cpu, enum exception e, reg_t mtval) {
  reg_t mstatus = csrread(cpu->csrs, MSTATUS);
  reg_t mie = (mstatus & MSTATUS_MIE) != 0;
  csrwrite(cpu->csrs, MEPC, cpu->pc);
  cpu->nextpc = csrread(cpu->csrs, MTVEC) & ~(reg_t)3;
  log_dbg("raise: pc %#x", cpu->nextpc);
  csrwrite(cpu->csrs, MCAUSE, e);
  csrwrite(cpu->csrs, MTVAL, mtval);
  if(mie)
    csrwrite(cpu->csrs, MSTATUS, (mstatus & ~MSTATUS_MIE) | MSTATUS_MPIE);
  else
    csrwrite(cpu->csrs, MSTATUS, (mstatus & ~MSTATUS_MIE) & ~MSTATUS_MPIE);

  mstatus = csrread(cpu->csrs, MSTATUS);
  csrwrite(cpu->csrs, MSTATUS, mstatus | (cpu->priv << MSTATUS_MPP_SHIFT));

  cpu->priv = MACHINE;
}

void mret(struct cpu *cpu) {
  cpu->nextpc = csrread(cpu->csrs, MEPC);
  cpu->priv = (csrread(cpu->csrs, MSTATUS) >> MSTATUS_MPP_SHIFT) & 3;
  reg_t mpie = (csrread(cpu->csrs, MSTATUS) & MSTATUS_MPIE) != 0;
  if(mpie)
    csrwrite(cpu->csrs, MSTATUS, csrread(cpu->csrs, MSTATUS) | MSTATUS_MIE);
  else
    csrwrite(cpu->csrs, MSTATUS, csrread(cpu->csrs, MSTATUS) & ~MSTATUS_MIE);
  csrwrite(cpu->csrs, MSTATUS, csrread(cpu->csrs, MSTATUS) | MSTATUS_MPIE);
}
