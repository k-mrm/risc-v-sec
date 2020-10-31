#include "inst.h"

union inst decode(uint32_t v) {
  union inst i;
  i.v = v;
  return i;
}
