#include "mmu.h"

reg_t sv39_translate(struct cpu *cpu, reg_t vaddr) {
  reg_t offset = PAGE_OFFSET(vaddr);
  reg_t vpn[3] = { VPN0(vaddr), VPN1(vaddr), VPN2(vaddr) };
  reg_t satp = csrread(cpu->csrs, SATP);

  reg_t a = SATP_PPN(satp) * PAGESIZE;
  reg_t i = LEVELS - 1;

  reg_t pte = sysbus_read64(cpu->bus, a + vpn[i] * PTESIZE);
}
