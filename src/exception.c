#include "cpu.h"
#include "exception.h"
#include "csr.h"
#include "log.h"

void raise(struct cpu *cpu, enum exception e, reg_t tval) {
  reg_t medeleg = csrread(cpu->csrs, MEDELEG);

  if(cpu->priv <= SUPERVISOR && ((medeleg >> e) & 1)) {
    reg_t sstatus = csrread(cpu->csrs, SSTATUS);

    csrwrite(cpu->csrs, SEPC, cpu->pc & ~(reg_t)1);

    cpu->nextpc = csrread(cpu->csrs, STVEC) & ~(reg_t)3;
    
    /* sstatus.spie = sstatus.sie */
    reg_t sie = sstatus & SSTATUS_SIE;
    csrwrite(cpu->csrs, SSTATUS, (sstatus & ~SSTATUS_SPIE) | (sie << SSTATUS_SPIE_SHIFT));

    /* sstatus.sie = 0 */
    sstatus = csrread(cpu->csrs, SSTATUS);
    csrwrite(cpu->csrs, SSTATUS, sstatus & ~SSTATUS_SIE);

    csrwrite(cpu->csrs, SCAUSE, e);

    csrwrite(cpu->csrs, STVAL, tval);

    /* sstatus.spp = cpu->priv */
    sstatus = csrread(cpu->csrs, SSTATUS);
    csrwrite(cpu->csrs, SSTATUS, (sstatus & ~SSTATUS_SPP) | (cpu->priv << SSTATUS_SPP_SHIFT));

    cpu->priv = SUPERVISOR;
  }
  else {
    reg_t mstatus = csrread(cpu->csrs, MSTATUS);

    csrwrite(cpu->csrs, MEPC, cpu->pc & ~(reg_t)1);

    cpu->nextpc = csrread(cpu->csrs, MTVEC) & ~(reg_t)3;

    /* mstatus.mpie = mstatus.mie */
    reg_t mie = mstatus & MSTATUS_MIE;
    csrwrite(cpu->csrs, MSTATUS, (mstatus & ~MSTATUS_MPIE) | (mie << MSTATUS_MPIE_SHIFT));

    /* mstatus.mie = 0 */
    mstatus = csrread(cpu->csrs, MSTATUS);
    csrwrite(cpu->csrs, SSTATUS, mstatus & ~MSTATUS_MIE);

    csrwrite(cpu->csrs, MCAUSE, e);

    csrwrite(cpu->csrs, MTVAL, tval);

    mstatus = csrread(cpu->csrs, MSTATUS);
    csrwrite(cpu->csrs, MSTATUS, (mstatus & ~MSTATUS_MPP) | (cpu->priv << MSTATUS_MPP_SHIFT));

    cpu->priv = MACHINE;
  }
}

void mret(struct cpu *cpu) {
  /* mstatus.mie = mstatus.mpie */
  reg_t mstatus = csrread(cpu->csrs, MSTATUS);
  reg_t mpie = (csrread(cpu->csrs, MSTATUS) & MSTATUS_MPIE) != 0;
  csrwrite(cpu->csrs, MSTATUS, (mstatus & ~MSTATUS_MIE) | (mpie << MSTATUS_MIE_SHIFT));

  /* cpu->priv = mstatus.mpp */
  cpu->priv = (csrread(cpu->csrs, MSTATUS) >> MSTATUS_MPP_SHIFT) & 3;

  /* mstatus.mpie = 0(USER) */
  csrwrite(cpu->csrs, MSTATUS, csrread(cpu->csrs, MSTATUS) | MSTATUS_MPIE);

  /* mstatus.mpp = 0(USER) */
  csrwrite(cpu->csrs, MSTATUS, csrread(cpu->csrs, MSTATUS) & ~MSTATUS_MPP);

  cpu->nextpc = csrread(cpu->csrs, MEPC);
}

void sret(struct cpu *cpu) {
  /* sstatus.sie = sstatus.spie */
  reg_t sstatus = csrread(cpu->csrs, SSTATUS);
  reg_t spie = sstatus & SSTATUS_SPIE;
  csrwrite(cpu->csrs, SSTATUS, (sstatus & ~SSTATUS_SIE) | (spie << SSTATUS_SIE_SHIFT));

  /* cpu->priv = sstatus.spp */
  cpu->priv = (csrread(cpu->csrs, SSTATUS) >> SSTATUS_SPP_SHIFT) & 3;

  /* sstatus.spie = 1 */
  csrwrite(cpu->csrs, SSTATUS, csrread(cpu->csrs, SSTATUS) | SSTATUS_SPIE);

  /* sstatus.spp = 0(USER) */
  csrwrite(cpu->csrs, SSTATUS, csrread(cpu->csrs, SSTATUS) & ~SSTATUS_SPP);

  cpu->nextpc = csrread(cpu->csrs, SEPC);
}
