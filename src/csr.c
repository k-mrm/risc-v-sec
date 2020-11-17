#include "csr.h"
#include "cpu.h"

reg_t csr_read(reg_t *csrs, enum csr c) {
  return csrs[c];
}

void csr_write(reg_t *csrs, enum csr c, reg_t val) {
  csrs[c] = val;
}
