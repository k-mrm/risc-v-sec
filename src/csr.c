#include "risc-v-sec.h"
#include "csr.h"
#include "cpu.h"

#if XLEN == 64
# define MXL  2
#elif XLEN == 32
# define MXL  1
#endif

void reset_csr(reg_t *csrs) {
  memset(csrs, 0, sizeof(reg_t) * 4096);

  /* SMIA */
  reg_t misa = (MXL << (XLEN-2)) | (1 << 18) | (1 << 12) | (1 << 8) | (1 << 0);

  csrwrite(csrs, MISA);
}

reg_t csrread(reg_t *csrs, enum csr c) {
  return csrs[c];
}

void csrwrite(reg_t *csrs, enum csr c, reg_t val) {
  csrs[c] = val;
}
