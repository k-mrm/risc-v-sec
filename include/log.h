#ifndef RISC_V_SEC_LOG_H
#define RISC_V_SEC_LOG_H

#include <stdarg.h>

void panic(char *s, ...);
void log_dbg(char *s, ...);

#endif
