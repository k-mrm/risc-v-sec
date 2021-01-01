#ifndef RISC_V_SEC_MMU_H
#define RISC_V_SEC_MMU_H

#include "csr.h"

#define SATP_PPN(satp)  ((satp) & 0xfffffffffff)
#define SATP_ASID(satp) (((satp) >> 43) & 0xffff)
#define SATP_MODE(satp) (((satp) >> 59) & 0xf)

#endif
