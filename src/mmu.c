#include "mmu.h"

reg_t sv32_translate(struct cpu *cpu, reg_t vaddr) {
  reg_t offset = PAGE_OFFSET(vaddr);
  reg_t vpn[2] = { VPN0(vaddr), VPN1(vaddr) };
  reg_t satp = csrread(cpu->csrs, SATP);

  reg_t a = SATP_PPN(satp) * PAGESIZE;
  reg_t i = LEVELS - 1;

  while(1) {
    reg_t pte = sysbus_read32(cpu->bus, a + vpn[i] * PTESIZE);

    if(PTE_R(pte) == 1 && PTE_X(pte) == 1) {
      break;
    }
    i--;
    a = PTE_PPN(pte) * PAGESIZE;
  }

  reg_t pa_pgoff = PAGE_OFFSET(vaddr);
  reg_t pte_ppn[2] = { PTE_PPN0(pte), PTE_PPN1(pte) };
  reg_t ppn[2];
  if(i > 0) {
    for(int j = 0; j <= i - 1; j++) {
      ppn[j] = vpn[j];
    }
  }
  for(int j = i; j <= LEVELS - 1; j++) {
    ppn[j] = pte_ppn[j];
  }

  return (ppn[1] << 22) | (ppn[0] << 12) | offset;
}

reg_t sv39_translate(struct cpu *cpu, reg_t vaddr) {
  reg_t offset = PAGE_OFFSET(vaddr);
  reg_t vpn[3] = { VPN0(vaddr), VPN1(vaddr), VPN2(vaddr) };
  reg_t satp = csrread(cpu->csrs, SATP);

  reg_t a = SATP_PPN(satp) * PAGESIZE;
  reg_t i = LEVELS - 1;

  reg_t pte = sysbus_read64(cpu->bus, a + vpn[i] * PTESIZE);
}
