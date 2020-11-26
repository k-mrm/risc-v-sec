#ifndef RISC_V_SEC_LOG_H
#define RISC_V_SEC_LOG_H

#include <stdarg.h>

void panic(char *s, ...);

#ifndef NDEBUG
#define log_dbg(...)  log_debug(__VA_ARGS__)
void log_debug(char *s, ...);
#else
#define log_dbg(...)  ((void)0)
#endif

#endif
