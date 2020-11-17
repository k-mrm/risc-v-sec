#include "csr.h"
#include "cpu.h"

reg_t csrread(reg_t *csrs, enum csr c) {
  return csrs[c];
}

void csrwrite(reg_t *csrs, enum csr c, reg_t val) {
  csrs[c] = val;
}
