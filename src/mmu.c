#include "mmu.h"

#if XLEN == 32
/* Sv32 */
reg_t translate(struct cpu *cpu, reg_t vaddr, enum accesstype acc) {
  if(paging_mode(cpu) == BARE || cpu->priv == MACHINE) {
    return vaddr;
  }

  reg_t offset = PAGE_OFFSET(vaddr);
  reg_t vpn[2] = { VPN0(vaddr), VPN1(vaddr) };
  reg_t satp = csrread(cpu->csrs, SATP);

  reg_t a = SATP_PPN(satp) * PAGESIZE;
  reg_t i = LEVELS - 1;
  reg_t pte;

  while(1) {
    pte = sysbus_read32(cpu->bus, a + vpn[i] * PTESIZE);

    if(PTE_R(pte) == 1 && PTE_X(pte) == 1) {
      break;
    }
    i--;
    a = PTE_PPN(pte) * PAGESIZE;
  }

  if(PTE_A(pte) == 0 || (acc == ACCSTORE && PTE_D(pte) == 0)) {
    pte = pte | (1 << 6) | (acc == ACCSTORE? 1 << 7 : 0);
  }

  reg_t pa_pgoff = PAGE_OFFSET(vaddr);
  reg_t pte_ppn[2] = { PTE_PPN0(pte), PTE_PPN1(pte) };
  reg_t ppn[2];
  for(int j = 0; j <= i - 1; j++) {
    ppn[j] = vpn[j];
  }
  for(int j = i; j <= LEVELS - 1; j++) {
    ppn[j] = pte_ppn[j];
  }

  return (ppn[1] << 22) | (ppn[0] << 12) | offset;
}

#elif XLEN == 64
/* Sv39 */
reg_t translate(struct cpu *cpu, reg_t vaddr, enum accesstype acc) {
  reg_t offset = PAGE_OFFSET(vaddr);
  reg_t vpn[3] = { VPN0(vaddr), VPN1(vaddr), VPN2(vaddr) };
  reg_t satp = csrread(cpu->csrs, SATP);

  reg_t a = SATP_PPN(satp) * PAGESIZE;
  reg_t i = LEVELS - 1;

  reg_t pte = sysbus_read64(cpu->bus, a + vpn[i] * PTESIZE);
}
#endif

enum pagingmode paging_mode(struct cpu *cpu) {
  reg_t satp = csrread(cpu->csrs, SATP);
  return SATP_MODE(satp);
}
