#ifndef RISC_V_SEC_MMU_H
#define RISC_V_SEC_MMU_H

#include "cpu.h"
#include "csr.h"


#if XLEN == 64
/* Sv39 */

#define SATP_PPN(satp)  ((satp) & 0xfffffffffff)
#define SATP_ASID(satp) (((satp) >> 44) & 0xffff)
#define SATP_MODE(satp) (((satp) >> 60) & 0xf)

#define PAGE_OFFSET(va) ((va) & 0xfff)
#define VPN0(va)  (((va) >> 12) & 0x1ff)
#define VPN1(va)  (((va) >> 21) & 0x1ff)
#define VPN2(va)  (((va) >> 30) & 0x1ff)

#define PAGESIZE  4096

#define LEVELS  3
#define PTESIZE 8

#elif XLEN == 32
/* Sv32 */

#define SATP_PPN(satp)  ((satp) & 0x3fffff)
#define SATP_ASID(satp)  (((satp) >> 22) & 0x1ff)
#define SATP_MODE(satp)  (((satp) >> 31) & 0x1)

#define PAGE_OFFSET(va) ((va) & 0xfff)
#define VPN0(va)  (((va) >> 12) & 0x3ff)
#define VPN1(va)  (((va) >> 22) & 0x3ff)

#define PAGESIZE 4096
#define LEVELS 2
#define PTESIZE 4

#define PTE_RSW(p)  (((p) >> 8) & 0x3)
#define PTE_PPN(p)  (((p) >> 10) & 0x3fffff)
#define PTE_PPN0(p)  (((p) >> 10) & 0x3ff)
#define PTE_PPN1(p)  (((p) >> 20) & 0xfff)

#endif

#define PTE_V(p)  ((p) & 0x1)
#define PTE_R(p)  (((p) >> 1) & 0x1)
#define PTE_W(p)  (((p) >> 2) & 0x1)
#define PTE_X(p)  (((p) >> 3) & 0x1)
#define PTE_U(p)  (((p) >> 4) & 0x1)
#define PTE_G(p)  (((p) >> 5) & 0x1)
#define PTE_A(p)  (((p) >> 6) & 0x1)
#define PTE_D(p)  (((p) >> 7) & 0x1)

#endif
