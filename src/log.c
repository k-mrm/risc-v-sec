#include <stdio.h>
#include <stdlib.h>
#include "log.h"

void panic(char *s, ...) {
  va_list args;
  va_start(args, s);
  fprintf(stderr, "[panic] ");
  vfprintf(stderr, s, args);
  fprintf(stderr, "\n");
  va_end(args);

  exit(1);
}

#ifndef NDEBUG
void log_debug(char *s, ...) {
  va_list args;
  va_start(args, s);
  fprintf(stderr, "[debug] ");
  vfprintf(stderr, s, args);
  fprintf(stderr, "\n");
  va_end(args);
}
#endif
