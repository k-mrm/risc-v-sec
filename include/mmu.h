#ifndef RISC_V_SEC_MMU_H
#define RISC_V_SEC_MMU_H

#include "cpu.h"
#include "csr.h"


#if XLEN == 64
/* Sv39 */

#define SATP_PPN(satp)  ((satp) & 0xfffffffffff)
#define SATP_ASID(satp) (((satp) >> 43) & 0xffff)
#define SATP_MODE(satp) (((satp) >> 59) & 0xf)

#define PAGE_OFFSET(va) ((va) & 0xfff)
#define VPN0(va)  (((va) >> 12) & 0x1ff)
#define VPN1(va)  (((va) >> 21) & 0x1ff)
#define VPN2(va)  (((va) >> 30) & 0x1ff)

#define PAGESIZE  4096

#define LEVELS  3
#define PTESIZE 8

#elif XLEN == 32
/* Sv32 */

#endif

#endif
